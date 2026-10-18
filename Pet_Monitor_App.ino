#include <lvgl.h>
#include "Arduino_GFX_Library.h"
#include "Arduino_DriveBus_Library.h"
#include "lv_conf.h"
#include "pin_config.h"
#include ".\src\ui\ui.h"
#include ".\src\ui\vars.h"
#include ".\src\ui\actions.h"

#include ".\src\cloud\thingProperty.h"
#include ".\src\date_heure\date_heure.h"

#define EXAMPLE_LVGL_TICK_PERIOD_MS 2

static const uint16_t screenWidth = 240;
static const uint16_t screenHeight = 280;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 10];

/* LCD - Display Hardware Interface Definitions */
Arduino_DataBus *bus = new Arduino_ESP32SPI(LCD_DC, LCD_CS, LCD_SCK, LCD_MOSI);

Arduino_GFX *gfx = new Arduino_ST7789(bus, LCD_RST /* RST */,
                                      0 /* rotation */, true /* IPS */, LCD_WIDTH, LCD_HEIGHT, 0, 20, 0, 20);

/* Touch - Touchscreen Hardware Interface Definitions */
std::shared_ptr<Arduino_IIC_DriveBus> IIC_Bus =
  std::make_shared<Arduino_HWIIC>(IIC_SDA, IIC_SCL, &Wire);

void Arduino_IIC_Touch_Interrupt(void);  // Function forward declaration

std::unique_ptr<Arduino_IIC> CST816T(new Arduino_CST816x(IIC_Bus, CST816T_DEVICE_ADDRESS,
                                                         TP_RST, TP_INT, Arduino_IIC_Touch_Interrupt));
// Touch Interrupt Service Function
void Arduino_IIC_Touch_Interrupt(void) {
  CST816T->IIC_Interrupt_Flag = true;
}

/* LVGL Display Refresh Callback */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);

  lv_disp_flush_ready(disp);
}

/* LVGL Touch Read Callback */
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  // Read coordinates from the touch chip
  int32_t touchX = CST816T->IIC_Read_Device_Value(CST816T->Arduino_IIC_Touch::Value_Information::TOUCH_COORDINATE_X);
  int32_t touchY = CST816T->IIC_Read_Device_Value(CST816T->Arduino_IIC_Touch::Value_Information::TOUCH_COORDINATE_Y);

  // Check the interrupt flag to determine if a new touch event has occurred
  if (CST816T->IIC_Interrupt_Flag == true) {
    CST816T->IIC_Interrupt_Flag = false;  // Clear the flag
    data->state = LV_INDEV_STATE_PR;      // State: Pressed

    /* Set coordinates after checking their validity */
    if (touchX >= 0 && touchY >= 0) {
      data->point.x = touchX;
      data->point.y = touchY;
    }
  } else {
    data->state = LV_INDEV_STATE_REL;  // State: Released
  }
}

/* LVGL Tick Increment Callback */
void example_increase_lvgl_tick(void *arg) {
  /* Inform LVGL of the elapsed milliseconds */
  lv_tick_inc(EXAMPLE_LVGL_TICK_PERIOD_MS);
}


/* --- UI Interface Code --- */


void refresh_date() {
  // Update the date and time variable for the UI
    // Exemple de lecture et affichage.
    static uint32_t dernier_affichage = 0;
    char affichage[24];
    if ((uint32_t)(millis() - dernier_affichage) >= 1000U) {
        dernier_affichage = millis();

        if (date_heure_format_sec(affichage, sizeof(affichage)) >= 0) {
            Serial.println(affichage);
            // set the Date without sec for the GUI
            date_heure_format_min(affichage, sizeof(affichage));
            set_var_date_full(affichage);
            // Set the hours for the historic popup in GUI 
            date_heure_format_hours(affichage, sizeof(affichage));
            set_var_date_hours(affichage);
        }
    }

  
}

//--------------SETUP section--------------------------------------
void setup() {
  // @YMA debug
  Serial.begin(115200);
  delay(1000);
  // 1. Hardware Initialization
  // First, complete all initialization for direct communication with physical hardware (screen, touch, backlight, etc.).
  
  // Initialize screen display
  gfx->begin();
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH);  // Turn on backlight

  // Initialize touch controller
  // @YMA debug
  // while (CST816T->begin() == false) {
  //  delay(2000);  // If it fails, wait for a period and then retry
  //}
  //CST816T->IIC_Write_Device_State(CST816T->Arduino_IIC_Touch::Device::TOUCH_DEVICE_INTERRUPT_MODE,
  //                               CST816T->Arduino_IIC_Touch::Device_Mode::TOUCH_DEVICE_INTERRUPT_PERIODIC);
  Serial.println("Initializing CST816T...");

  bool touch_ok = CST816T->begin();

  if (touch_ok) {
    Serial.println("CST816T initialized OK");

    CST816T->IIC_Write_Device_State(
    CST816T->Arduino_IIC_Touch::Device::
      TOUCH_DEVICE_INTERRUPT_MODE,
    CST816T->Arduino_IIC_Touch::Device_Mode::
      TOUCH_DEVICE_INTERRUPT_PERIODIC
  );
  } else {
    Serial.println("CST816T initialization FAILED");
    Serial.println("Continuing without touch...");
  }
  //---end @YMA DEBuG
  // 2. LVGL Core and Tick Initialization
  lv_init();

  const esp_timer_create_args_t lvgl_tick_timer_args = {
    .callback = &example_increase_lvgl_tick,
    .name = "lvgl_tick"
  };
  esp_timer_handle_t lvgl_tick_timer = NULL;
  esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer);
  esp_timer_start_periodic(lvgl_tick_timer, EXAMPLE_LVGL_TICK_PERIOD_MS * 1000);

  // 3. LVGL Driver Registration
  // Connect LVGL's logical operations with hardware callback functions

  // --- Initialize display driver ---
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * screenHeight / 10);
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  // --- Initialize input device (touch) driver ---
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;  // Type: pointer/touch
  indev_drv.read_cb = my_touchpad_read;    // Register read callback
  lv_indev_drv_register(&indev_drv);

  // 4. UI Creation & Application Initialization
  // After all underlying layers are ready, begin creating the graphical interface.

  // Set screen background color
  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0xFFFFFF), LV_PART_MAIN);

  // HMI init
  ui_init();
  
  //--@debug -Arduino Cloud section-----------
  // Defined in thingProperties.h
  //initProperties();
  //---Connect to Arduino IoT Cloud
  // ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  // setDebugMessageLevel(4);
  // ArduinoCloud.printDebugInfo();

  // Initialisation avec la date de référence.
  bool result;
  result = date_heure_init("18-oct-26 11h15", millis());
  if (result) {
      Serial.println("Horloge initialisee.");
  } else {
       Serial.println("Erreur de date/heure ! Code: ");
       Serial.println(result);
    }
}

//-----------MAIN SECTION-----------------------------------------------
void loop() {
  lv_timer_handler(); /* Let the LVGL GUI handle its tasks (such as animations, events, etc.) */
  delay(5);
  ui_tick();
  // Mise à jour non bloquante.
  date_heure_update(millis());
  refresh_date();
  // @debug ArduinoCloud.update();
}


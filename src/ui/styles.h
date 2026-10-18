#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: Event_Button_Style
lv_style_t *get_style_event_button_style_MAIN_DISABLED();
lv_style_t *get_style_event_button_style_MAIN_DEFAULT();
void add_style_event_button_style(lv_obj_t *obj);
void remove_style_event_button_style(lv_obj_t *obj);

// Style: Arc_Event_Style
lv_style_t *get_style_arc_event_style_INDICATOR_HOVERED();
lv_style_t *get_style_arc_event_style_INDICATOR_DEFAULT();
lv_style_t *get_style_arc_event_style_KNOB_DEFAULT();
lv_style_t *get_style_arc_event_style_MAIN_DEFAULT();
void add_style_arc_event_style(lv_obj_t *obj);
void remove_style_arc_event_style(lv_obj_t *obj);

// Style: Screen_Style
lv_style_t *get_style_screen_style_MAIN_DEFAULT();
void add_style_screen_style(lv_obj_t *obj);
void remove_style_screen_style(lv_obj_t *obj);

// Style: Panel_Style
lv_style_t *get_style_panel_style_MAIN_DEFAULT();
void add_style_panel_style(lv_obj_t *obj);
void remove_style_panel_style(lv_obj_t *obj);

// Style: Label_Pet_Name
lv_style_t *get_style_label_pet_name_MAIN_DEFAULT();
void add_style_label_pet_name(lv_obj_t *obj);
void remove_style_label_pet_name(lv_obj_t *obj);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/
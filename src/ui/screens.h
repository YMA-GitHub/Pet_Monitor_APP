#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_SCREEN_MEDIC_11 = 1,
    SCREEN_ID_SCREEN_SORTIE_12 = 2,
    SCREEN_ID_SCREEN_REPAS_13 = 3,
    SCREEN_ID_SCREEN_SORTIE_22 = 4,
    SCREEN_ID_SCREEN_REPAS_23 = 5,
    _SCREEN_ID_LAST = 5
};

typedef struct _objects_t {
    lv_obj_t *screen_medic_11;
    lv_obj_t *screen_sortie_12;
    lv_obj_t *screen_repas_13;
    lv_obj_t *screen_sortie_22;
    lv_obj_t *screen_repas_23;
    lv_obj_t *date_label_11;
    lv_obj_t *no_wifi_icon_11;
    lv_obj_t *obj0;
    lv_obj_t *pet_name_11;
    lv_obj_t *btn_medic_11;
    lv_obj_t *weel_medic_11;
    lv_obj_t *btn_screen_right_11;
    lv_obj_t *obj1;
    lv_obj_t *btn_screen_bottom_11;
    lv_obj_t *obj2;
    lv_obj_t *wheel_medic_label_11;
    lv_obj_t *obj3;
    lv_obj_t *wifi_icon_11;
    lv_obj_t *info_icon_11;
    lv_obj_t *histo_icon_14;
    lv_obj_t *information_text;
    lv_obj_t *historic_text_11;
    lv_obj_t *date_label_12;
    lv_obj_t *wifi_icon_12;
    lv_obj_t *obj4;
    lv_obj_t *pet_name_12;
    lv_obj_t *bnt_sortie_12;
    lv_obj_t *obj5;
    lv_obj_t *wheel_sortie_label_12;
    lv_obj_t *weel_sortie_12;
    lv_obj_t *btn_screen_right_12;
    lv_obj_t *obj6;
    lv_obj_t *btn_screen_bottom_12;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *btn_screen_top_12;
    lv_obj_t *obj9;
    lv_obj_t *info_icon_12;
    lv_obj_t *histo_icon_12;
    lv_obj_t *information_text_2;
    lv_obj_t *historic_text_12;
    lv_obj_t *wifi_icon_13;
    lv_obj_t *obj10;
    lv_obj_t *pet_name_13;
    lv_obj_t *bnt_repas_13;
    lv_obj_t *obj11;
    lv_obj_t *wheel_sortie_label_13;
    lv_obj_t *weel_repas_13;
    lv_obj_t *btn_screen_right_13;
    lv_obj_t *obj12;
    lv_obj_t *obj13;
    lv_obj_t *btn_screen_top_13;
    lv_obj_t *obj14;
    lv_obj_t *date_label_13;
    lv_obj_t *info_icon_13;
    lv_obj_t *histo_icon_13;
    lv_obj_t *information_text_1;
    lv_obj_t *historic_text_13;
    lv_obj_t *obj15;
    lv_obj_t *pet_name_21;
    lv_obj_t *bnt_sortie_22;
    lv_obj_t *obj16;
    lv_obj_t *wheel_sortie_label_22;
    lv_obj_t *weel_sortie_22;
    lv_obj_t *btn_screen_bottom_22;
    lv_obj_t *date_14;
    lv_obj_t *obj17;
    lv_obj_t *btn_screen_left_21;
    lv_obj_t *obj18;
    lv_obj_t *pet_name_22;
    lv_obj_t *bnt_repas_23;
    lv_obj_t *obj19;
    lv_obj_t *wheel_repas_label_23;
    lv_obj_t *weel_repas_23;
    lv_obj_t *btn_screen_bottom_23;
    lv_obj_t *date_15;
    lv_obj_t *obj20;
    lv_obj_t *btn_screen_left_23;
} objects_t;

extern objects_t objects;

void create_screen_screen_medic_11();
void tick_screen_screen_medic_11();

void create_screen_screen_sortie_12();
void tick_screen_screen_sortie_12();

void create_screen_screen_repas_13();
void tick_screen_screen_repas_13();

void create_screen_screen_sortie_22();
void tick_screen_screen_sortie_22();

void create_screen_screen_repas_23();
void tick_screen_screen_repas_23();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/
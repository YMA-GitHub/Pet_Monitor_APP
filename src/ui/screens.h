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
    SCREEN_ID_SCREEN_MEDIC_21 = 3,
    _SCREEN_ID_LAST = 3
};

typedef struct _objects_t {
    lv_obj_t *screen_medic_11;
    lv_obj_t *screen_sortie_12;
    lv_obj_t *screen_medic_21;
    lv_obj_t *obj0;
    lv_obj_t *pet_name_11;
    lv_obj_t *btn_medic_10;
    lv_obj_t *weel_medic_01;
    lv_obj_t *btn_screen_right_11;
    lv_obj_t *btn_screen_bottom_11;
    lv_obj_t *wheel_medic_label_01;
    lv_obj_t *date_01;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *pet_name_12;
    lv_obj_t *bnt_sortie_12;
    lv_obj_t *obj3;
    lv_obj_t *wheel_sortie_label_12;
    lv_obj_t *weel_sortie_12;
    lv_obj_t *btn_screen_right_12;
    lv_obj_t *btn_screen_bottom_12;
    lv_obj_t *date_12;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *pet__name_21;
    lv_obj_t *btn_medic_21;
    lv_obj_t *medic_weel_21;
    lv_obj_t *btn_screen_left_21;
    lv_obj_t *btn_screen_bottom_21;
    lv_obj_t *wheel_medic_label_21;
    lv_obj_t *date_21;
    lv_obj_t *obj6;
} objects_t;

extern objects_t objects;

void create_screen_screen_medic_11();
void tick_screen_screen_medic_11();

void create_screen_screen_sortie_12();
void tick_screen_screen_sortie_12();

void create_screen_screen_medic_21();
void tick_screen_screen_medic_21();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/
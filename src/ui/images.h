#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_battery_green;
extern const lv_img_dsc_t img_info_icon;
extern const lv_img_dsc_t img_histo_icon;
extern const lv_img_dsc_t img_wifi_icon;
extern const lv_img_dsc_t img_menu_bone;
extern const lv_img_dsc_t img_medic_icon;
extern const lv_img_dsc_t img_walk_icon;
extern const lv_img_dsc_t img_moly_med;
extern const lv_img_dsc_t img_wifi_no_icon;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[9];

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/
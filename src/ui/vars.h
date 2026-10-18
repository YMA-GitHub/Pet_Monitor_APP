#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_MEDIC_NB_11 = 0,
    FLOW_GLOBAL_VARIABLE_SORTIE_NB_12 = 1,
    FLOW_GLOBAL_VARIABLE_MEDIC_LABEL_11 = 2,
    FLOW_GLOBAL_VARIABLE_SORTIE_LABEL_12 = 3,
    FLOW_GLOBAL_VARIABLE_REPAS_NB_13 = 4,
    FLOW_GLOBAL_VARIABLE_REPAS_LABEL_13 = 5,
    FLOW_GLOBAL_VARIABLE_INFO_TEXT_FLAG_11 = 6,
    FLOW_GLOBAL_VARIABLE_INFO_TEXT_FLAG_13 = 7,
    FLOW_GLOBAL_VARIABLE_INFO_TEXT_FLAG_12 = 8,
    FLOW_GLOBAL_VARIABLE_HISTO_TEXT_FLAG_12 = 9,
    FLOW_GLOBAL_VARIABLE_HISTO_TEXT_FLAG_13 = 10,
    FLOW_GLOBAL_VARIABLE_HISTO_TEXT_FLAG_11 = 11,
    FLOW_GLOBAL_VARIABLE_HISTO_TEXT_11 = 12,
    FLOW_GLOBAL_VARIABLE_HISTO_TEXT_12 = 13,
    FLOW_GLOBAL_VARIABLE_HISTO_TEXT_13 = 14
};

// Native global variables

extern const char *get_var_date_full();
extern void set_var_date_full(const char *value);
extern bool get_var_wifi_flag();
extern void set_var_wifi_flag(bool value);
extern const char *get_var_date_hours();
extern void set_var_date_hours(const char *value);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/
#include <string.h>
#include "vars.h"

// Global variables

// WiFi icon flag variable
bool g_var_wifi_flag = false;

bool get_var_wifi_flag() {
    return g_var_wifi_flag;
}

void set_var_wifi_flag(bool value) {
    g_var_wifi_flag = value;
}

// Date and time variable
char date_heure_full[50] = { 0 };
char date_hours[20] = { 0 };

const char *get_var_date_full() {
    return date_heure_full;
}

void set_var_date_full(const char *value) {
    strncpy(date_heure_full, value, sizeof(date_heure_full) / sizeof(char));
    date_heure_full[sizeof(date_heure_full) / sizeof(char) - 1] = 0;
}
const char *get_var_date_hours(){
    return date_hours;
}
void set_var_date_hours(const char *value){
    strncpy(date_hours, value, sizeof(date_hours) / sizeof(char));
    date_hours[sizeof(date_hours) / sizeof(char) - 1] = 0;
}
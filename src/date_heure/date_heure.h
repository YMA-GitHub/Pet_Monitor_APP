
#ifndef DATE_HEURE_H
#define DATE_HEURE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint16_t annee;   // Année complète : 2026
    uint8_t mois;     // 1 à 12
    uint8_t jour;     // 1 à 31
    uint8_t heure;    // 0 à 23
    uint8_t minute;   // 0 à 59
    uint8_t seconde;  // 0 à 59
} DateHeure;

/*
 * Initialise la date et l'heure à partir d'une chaîne :
 * "17-oct-26 16h10" ou "17-oct-26 16:10"
 *
 * Retourne true si la chaîne est valide.
 */
bool date_heure_init(const char *reference, uint32_t maintenant_ms);

/* Met à jour l'heure sans bloquer.
 * Appeler régulièrement avec millis().
 */
void date_heure_update(uint32_t maintenant_ms);

/* Copie la date et l'heure courantes. */
DateHeure date_heure_get(void);

/* Formate la date avec les secondes :
 * Exemple : "17-oct-26 16h10:05"
 * Retourne le nombre de caractères écrits, hors '\0',
 * ou -1 si le tampon est trop petit ou invalide.
 */
int date_heure_format_sec(char *buffer, size_t taille);
int date_heure_format_min(char *buffer, size_t taille);
int date_heure_format_hours(char *buffer, size_t taille);
#ifdef __cplusplus
}
#endif

#endif


#include "date_heure.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

static DateHeure date_courante;
static uint32_t dernier_ms = 0;
static uint32_t reste_ms = 0;
static bool initialise = false;

static const char *const mois_noms[12] = {
    "jan", "fev", "mar", "avr", "mai", "jun",
    "jul", "aou", "sep", "oct", "nov", "dec"
};

static bool annee_bissextile(uint16_t annee)
{
    return ((annee % 4 == 0) &&
            ((annee % 100 != 0) || (annee % 400 == 0)));
}

static uint8_t jours_dans_mois(uint16_t annee, uint8_t mois)
{
    static const uint8_t jours[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (mois < 1 || mois > 12)
        return 0;

    if (mois == 2 && annee_bissextile(annee))
        return 29;

    return jours[mois - 1];
}

static int mois_depuis_chaine(const char *texte)
{
    char m[4];

    for (int i = 0; i < 3; i++) {
        if (texte[i] == '\0')
            return -1;

        m[i] = (char)tolower((unsigned char)texte[i]);
    }
    m[3] = '\0';

    // Abréviations françaises et anglaises usuelles.
    static const char *const noms[] = {
        "jan", "fev", "feb", "mar", "avr", "apr",
        "mai", "may", "jun", "jul", "aou", "aug",
        "sep", "oct", "nov", "dec"
    };

    static const uint8_t numeros[] = {
        1, 2, 2, 3, 4, 4,
        5, 5, 6, 7, 8, 8,
        9, 10, 11, 12
    };

    for (size_t i = 0; i < sizeof(numeros) / sizeof(numeros[0]); i++) {
        if (strcmp(m, noms[i]) == 0)
            return numeros[i];
    }

    return -1;
}

static void incrementer_seconde(void)
{
    date_courante.seconde++;

    if (date_courante.seconde < 60)
        return;

    date_courante.seconde = 0;
    date_courante.minute++;

    if (date_courante.minute < 60)
        return;

    date_courante.minute = 0;
    date_courante.heure++;

    if (date_courante.heure < 24)
        return;

    date_courante.heure = 0;
    date_courante.jour++;

    if (date_courante.jour <=
        jours_dans_mois(date_courante.annee, date_courante.mois))
        return;

    date_courante.jour = 1;
    date_courante.mois++;

    if (date_courante.mois <= 12)
        return;

    date_courante.mois = 1;
    date_courante.annee++;
}

bool date_heure_init(const char *reference, uint32_t maintenant_ms)
{
    if (reference == NULL)
        return false;

    int jour, annee, heure, minute;
    char mois_txt[4];
    char separateur;
    int consommes = 0;

    /*
     * Accepte par exemple :
     * 17-oct-26 16h10
     * 17-oct-26 16:10
     *
     * Le format exact doit contenir 3 lettres pour le mois.
     */
    // int nb = sscanf(reference,
    //                 "%2d-%3[a-zA-Z]-%2d %2d%1[hH:]%2d%n",
    //                 &jour, mois_txt, &annee,
    //                 &heure, &separateur, &minute, &consommes);
    int nb = sscanf(reference,
                "%2d-%3[a-zA-Z]-%2d %2d%c%2d%n",
                &jour, mois_txt, &annee,
                &heure, &separateur, &minute, &consommes);

    if (nb != 6 || consommes == 0)
        return false;

    // Refuser les caractères supplémentaires.
    if (reference[consommes] != '\0')
        return false;

    int mois = mois_depuis_chaine(mois_txt);

    if (mois < 1 || mois > 12)
        return false;

    // Convention : 00 à 99 correspondent à 2000 à 2099.
    annee += 2000;

    if (jour < 1 ||
        jour > jours_dans_mois((uint16_t)annee, (uint8_t)mois) ||
        heure < 0 || heure > 23 ||
        minute < 0 || minute > 59 ||
        (separateur != 'h' && separateur != 'H' &&
         separateur != ':')) {
        return false;
    }

    date_courante.annee = (uint16_t)annee;
    date_courante.mois = (uint8_t)mois;
    date_courante.jour = (uint8_t)jour;
    date_courante.heure = (uint8_t)heure;
    date_courante.minute = (uint8_t)minute;
    date_courante.seconde = 0;

    dernier_ms = maintenant_ms;
    reste_ms = 0;
    initialise = true;

    return true;
}

void date_heure_update(uint32_t maintenant_ms)
{
    if (!initialise)
        return;

    // La soustraction non signée gère le débordement de millis().
    uint32_t ecoule = maintenant_ms - dernier_ms;
    dernier_ms = maintenant_ms;

    // Conserver les fractions de seconde entre les appels.
    uint32_t total_ms = reste_ms + ecoule;
    uint32_t secondes = total_ms / 1000U;

    reste_ms = total_ms % 1000U;

    // Rattraper les secondes si loop() a été occupée.
    while (secondes > 0) {
        incrementer_seconde();
        secondes--;
    }
}

DateHeure date_heure_get(void)
{
    return date_courante;
}

int date_heure_format_sec(char *buffer, size_t taille)
{
    if (buffer == NULL || taille == 0 || !initialise)
        return -1;

    int n = snprintf(buffer, taille,
                     "%02u-%s-%02u %02uh%02u:%02u",
                     (unsigned)date_courante.jour,
                     mois_noms[date_courante.mois - 1],
                     (unsigned)(date_courante.annee % 100),
                     (unsigned)date_courante.heure,
                     (unsigned)date_courante.minute,
                     (unsigned)date_courante.seconde);

    if (n < 0 || (size_t)n >= taille)
        return -1;

    return n;
}
int date_heure_format_min(char *buffer, size_t taille)
{
    if (buffer == NULL || taille == 0 || !initialise)
        return -1;

    int n = snprintf(buffer, taille,
                     "%02u-%s-%02u %02uh%02u",
                     (unsigned)date_courante.jour,
                     mois_noms[date_courante.mois - 1],
                     (unsigned)(date_courante.annee % 100),
                     (unsigned)date_courante.heure,
                     (unsigned)date_courante.minute);

    if (n < 0 || (size_t)n >= taille)
        return -1;

    return n;
}
int date_heure_format_hours(char *buffer, size_t taille)
{
    if (buffer == NULL || taille == 0 || !initialise)
        return -1;

    int n = snprintf(buffer, taille,
                     "%02uh%02u",
                     (unsigned)date_courante.heure,
                     (unsigned)date_courante.minute);

    if (n < 0 || (size_t)n >= taille)
        return -1;

    return n;
}
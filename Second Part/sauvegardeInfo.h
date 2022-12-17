#ifndef SAUVEGARDE_INFO_H
#define SAUVEGARDE_INFO_H

// Structure de sauvegarde des états
typedef struct chemin {
    int x;
    int y;
    struct chemin * suiv;
} Chemin_t;

// Structure de sauvegarde des états
typedef struct action {
    int indice;
    struct action * suiv;
} Action_t;

// Structure de sauvegarde des récompenses
typedef struct recompense {
    int indice;
    struct recompense * suiv;
} Recompense_t;

void insertionTete(Chemin_t ** chemin, int x, int y);

#endif 
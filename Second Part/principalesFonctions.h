#ifndef PRINCIPALES_FONCTIONS_H
#define PRINCIPALES_FONCTIONS_H

#define LIGNE 7
#define COLONNE 7

typedef struct etat {
    int x;
    int y;
} Etat_t;

// 0: Up, 1: Down, 2: Left, 3: Right
typedef struct action {
    float direction[4];
} Action_t;

int len(float * tab);
float * enumAction(Etat_t * etat, Action_t * Q[LIGNE][COLONNE]);
int ActionAvecMeilleureQualite(Action_t * Q[LIGNE][COLONNE], int i, int j);
int choixActionParEpsGreedy(Etat_t * etat, Action_t * Q[LIGNE][COLONNE], float epsilon);
int choixActionPLB(Etat_t * etat, Action_t * Q[LIGNE][COLONNE], float T, float alpha);

void etatSuivant(int * x, int * y, int indiceAction);
void deplacerVoiture (Etat_t * etat, int choice);

int estTerminal(Etat_t * etat);

#endif

#ifndef Q_TABLE_H
#define Q_TABLE_H 

#include "grille.h"
#include "principalesFonctions.h"

void allouerQ(Action_t  * Q[LIGNE][COLONNE]);
void initQ(Action_t * Q[LIGNE][COLONNE]);
void afficherQ(Action_t * Q[LIGNE][COLONNE]);

#endif 
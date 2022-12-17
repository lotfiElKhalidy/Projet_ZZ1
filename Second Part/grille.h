#ifndef GRILLE_H
#define GRILLE_H

#define LIGNE 7
#define COLONNE 7


#define NOMBRE_OBSTACLE 20

void initialiser(int grille[LIGNE][COLONNE]);
void afficherGrille(int grille[LIGNE][COLONNE]);
void genererGrille(int grille[LIGNE][COLONNE]);
void sauvegarderGrille(int grille[LIGNE][COLONNE], int grille1[LIGNE][COLONNE]);
void copieGrille(int source[LIGNE][COLONNE], int destination[LIGNE][COLONNE]);
void updateGrille(int grille[LIGNE][COLONNE], int action, int ** recompense, int * recompenseCumulee);
void drawWorldFromGrid(int grille[LIGNE][COLONNE], SDL_Texture * cash, SDL_Texture * bomb, SDL_Texture * flag,
                        SDL_Texture * carUp,SDL_Texture * carLeft,SDL_Texture * carDown,SDL_Texture * carRight, SDL_Window * window, 
                        SDL_Renderer * renderer,int action);


void defineRewardFromGrid (int grille[LIGNE][COLONNE], int *** recompense);

void afficherRecompense (int ** recompense);
void libererRecompense(int ** recompense);

#endif 
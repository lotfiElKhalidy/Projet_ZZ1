#ifndef JEU_H
#define JEU_H 

#include "grille.h"
#include "affichage.h"
#include "principalesFonctions.h"
#include "SDL.h"
#include "Qtable.h"

#define NB_MAX_ETAT_PAR_EPOQUE 1000

void jeu(SDL_Window  ** window, SDL_Renderer ** renderer, SDL_Texture ** carUp, SDL_Texture ** carDown,
                                SDL_Texture ** carLeft, SDL_Texture ** carRight, SDL_Texture ** cash, 
                                SDL_Texture ** bomb, SDL_Texture ** flag, SDL_Texture ** background, TTF_Font *font);

#endif 
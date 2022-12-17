#ifndef AFFICHAGE_H
#define AFFICHAGE_H

void afficherVoitureUpDown(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer, int abscisse, int ordonnee);
void afficherVoitureRightLeft(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer, int abscisse, int ordonnee);
void afficherCash(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer, int abscisse, int ordonnee);
void afficherBomb(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer, int abscisse, int ordonnee);
void afficherFlag(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer, int abscisse, int ordonnee);
void afficherBackground(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer);
void affficherTexteBienvenue(SDL_Window** window,SDL_Renderer** renderer,TTF_Font *font);

#endif


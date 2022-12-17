#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "SDL.h"
#include "jeu.h"


int main(int argc, char ** argv) {

    SDL_Window   * window   = NULL;
    SDL_Renderer * renderer = NULL;
     
    // Voiture
    SDL_Texture  * carUp    = NULL;
    SDL_Texture  * carDown  = NULL;
    SDL_Texture  * carLeft  = NULL;
    SDL_Texture  * carRight = NULL;

    // Obstacles
    SDL_Texture  * cash = NULL;
    SDL_Texture  * bomb = NULL;

    // Flag
    SDL_Texture  * flag = NULL;

    // Background
    SDL_Texture  * background = NULL;

    //text
    if (TTF_Init() < 0) end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);  
    TTF_Font* font_head = NULL; 
    font_head = TTF_OpenFont("./fonts/Pacifico.ttf", 45);
    if (font_head == NULL) end_sdl(0, "Can't load font", window, renderer);
    TTF_Font* font_form = NULL; 
    font_form = TTF_OpenFont("./fonts/Pacifico.ttf", 30);
    if (font_form == NULL) end_sdl(0, "Can't load font", window, renderer);
    
    srand(time(NULL));

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        end_sdl(0, "Echec de l'initialisation de la SDL", window, renderer);
    }

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Jeu :  2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 600, SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
        end_sdl(0, "Echec de la création de la fenetre", window, renderer);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        end_sdl(0, "Echec du la création du rendu  dans la fenetre", window, renderer);
    }
    
    /* Chargement des images dans la texture */
    carUp      = load_texture_from_image("img/carUp.png", &window, &renderer);
    carDown    = load_texture_from_image("img/carDown.png", &window, &renderer);
    carLeft    = load_texture_from_image("img/carLeft.png", &window, &renderer);
    carRight   = load_texture_from_image("img/carRight.png", &window, &renderer);

    cash       = load_texture_from_image("img/cash.png", &window, &renderer);
    bomb       = load_texture_from_image("img/bomb.png", &window, &renderer);

    flag       = load_texture_from_image("img/flag.png", &window, &renderer);

    background = load_texture_from_image("img/sky.png", &window, &renderer);

    // Lancement du jeu
    jeu(&window, &renderer, &carUp, &carDown, &carLeft, &carRight, &cash, &bomb, &flag, &background, font_head);
     
    if (background != NULL)
        SDL_DestroyTexture(background);
    
    if (flag != NULL)
        SDL_DestroyTexture(flag);
    
    if (bomb != NULL)
        SDL_DestroyTexture(bomb);
    
    if (cash != NULL)
        SDL_DestroyTexture(cash);
    
    if (carRight != NULL)
        SDL_DestroyTexture(carRight);

    if (carLeft != NULL)
        SDL_DestroyTexture(carLeft);

    if (carDown != NULL)
        SDL_DestroyTexture(carDown);

    if (carUp != NULL)
        SDL_DestroyTexture(carUp);

    return EXIT_SUCCESS;
}


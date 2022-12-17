#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "affichage.h"

void afficherVoitureUpDown(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer, int abscisse, int ordonnee) {
    SDL_Rect 
        source = {0},                      // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h);               // Récupération des dimensions de la fenêtre

    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);  // Récupération des dimensions de l'image 
    
    destination.w = 60;         // La destination est un zoom de la source
    destination.h = 80;         // La destination est un zoom de la source
    //destination.x = destination.x+100;
    //destination.y = destination.y -100;
    destination.x = abscisse;
    destination.y = ordonnee;

    SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                    &source,
                    &destination);
}

void afficherVoitureRightLeft(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer, int abscisse, int ordonnee) {
    SDL_Rect 
        source = {0},                      // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h);               // Récupération des dimensions de la fenêtre

    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);  // Récupération des dimensions de l'image 
    
    destination.w = 100;         // La destination est un zoom de la source
    destination.h = 50;         // La destination est un zoom de la source
    
    destination.x = abscisse;
    destination.y = ordonnee;

    SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                    &source,
                    &destination);
}


void afficherCash(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer, int abscisse, int ordonnee) {
    SDL_Rect 
        source = {0},                      // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h);               // Récupération des dimensions de la fenêtre

    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);  // Récupération des dimensions de l'image 
    
    destination.w = 80;         // La destination est un zoom de la source
    destination.h = 60;         // La destination est un zoom de la source
    destination.x = abscisse;
    destination.y = ordonnee;

    SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                    &source,
                    &destination);
}

void afficherBomb(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer, int abscisse, int ordonnee) {
    SDL_Rect 
        source = {0},                      // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h);               // Récupération des dimensions de la fenêtre

    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);  // Récupération des dimensions de l'image 
    
    destination.w = 80;         // La destination est un zoom de la source
    destination.h = 60;         // La destination est un zoom de la source
    destination.x = abscisse;
    destination.y = ordonnee;

    SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                    &source,
                    &destination);
}

void afficherFlag(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer, int abscisse, int ordonnee) {
    SDL_Rect 
        source = {0},                      // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h);               // Récupération des dimensions de la fenêtre

    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);  // Récupération des dimensions de l'image 
    
    destination.w = 100;         // La destination est un zoom de la source
    destination.h = 80;         // La destination est un zoom de la source
    destination.x = abscisse;
    destination.y = ordonnee;

    SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                    &source,
                    &destination);
}

void afficherBackground(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer) {
    SDL_Rect 
            source = {0},                         // Rectangle définissant la zone de la texture à récupérer
            window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
            destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);       // Récupération des dimensions de l'image

    destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

    SDL_RenderCopy(renderer, my_texture,
                    &source,
                    &destination);                 // Création de l'élément à afficher
}

void affficherTexteBienvenue(SDL_Window** window, SDL_Renderer** renderer, TTF_Font *font){

    SDL_Color color = {255, 0, 255, 255};
    SDL_Rect pos = {200, 260, 100};  
    int style = TTF_STYLE_BOLD;
    char txt[20];
    sprintf(txt,"Let's GOOOOOO!!");
    show_text(window,renderer,font,txt,color,pos,style);

} 

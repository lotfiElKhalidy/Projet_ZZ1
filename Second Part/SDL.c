#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "SDL.h"

void end_sdl(char ok, char const * msg, SDL_Window * window, SDL_Renderer * renderer) {
    char msg_formated[255];                                                         
    int l;                                                                          

    if (!ok) {
        strncpy(msg_formated, msg, 250);                                              
        l = strlen(msg_formated);                                                     
        strcpy(msg_formated + l, " : %s\n");                                          

        SDL_Log(msg_formated, SDL_GetError());                                        
    }
    
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (window != NULL)   {
        SDL_DestroyWindow(window);
        window= NULL;
    }

    SDL_Quit();                                                                     

    if (!ok) {               
        exit(EXIT_FAILURE);                                                           
    }                                                                               
}

void end_sdl_success(SDL_Window * window, SDL_Renderer * renderer) {
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (window != NULL)   {
        SDL_DestroyWindow(window);
        window= NULL;
    }

    SDL_Quit();                                                                            
}

SDL_Texture * load_texture_from_image(char * file_image_name, SDL_Window ** window, SDL_Renderer ** renderer ) {
    SDL_Surface * my_image = NULL;           // Variable de passage
    SDL_Texture * my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface
                                            // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                            // uniquement possible si l'image est au format bmp */

    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", *window, *renderer);

    my_texture = SDL_CreateTextureFromSurface(*renderer, my_image); // Chargement de l'image de la surface vers la texture
    
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", *window, *renderer);

    return my_texture;
}

void dessinerGrilleInitiale(int tailleCaseW, int tailleCaseH, SDL_Renderer * renderer) {
    int i = 100, j = 0;

    while (i < 800) {
        j = 20;
        
        while (j < 580) {
            SDL_Rect rectangle;

            /* On dessine sur le rendu un rectangle */
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            rectangle.x = i;
            rectangle.y = j;
            rectangle.w = tailleCaseW;
            rectangle.h = tailleCaseH;

            SDL_RenderFillRect(renderer, &rectangle);

            j += tailleCaseH;
        }
        i += tailleCaseW;
    }
}

void show_text(SDL_Window ** window,
              SDL_Renderer ** renderer,
              TTF_Font * font,
              char text[20],
              SDL_Color color,
              SDL_Rect pos,
              int style) {

    TTF_SetFontStyle(font, style);

    SDL_Surface* text_surface = NULL;         
    text_surface = TTF_RenderText_Blended(font, text, color); 
    if (text_surface == NULL) end_sdl(0, "Can't create text surface", *window, *renderer);

    SDL_Texture* text_texture = NULL;                            
    text_texture = SDL_CreateTextureFromSurface(*renderer, text_surface); 
    if (text_texture == NULL) end_sdl(0, "++ Can't create texture from surface", *window, *renderer);
    SDL_FreeSurface(text_surface);                               

    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);       
    SDL_RenderCopy(*renderer, text_texture, NULL, &pos);                
    SDL_DestroyTexture(text_texture);                                   

}

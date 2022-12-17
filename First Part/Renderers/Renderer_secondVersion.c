#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>

void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer) {              
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
    }

    SDL_Quit();                                                                     

    if (!ok) {              
        exit(EXIT_FAILURE);                                                           
    }                                                                               
}

void draw_move(SDL_Renderer * renderer) {
    // initialisation des quatre rectangles
    SDL_Rect rectangle[4];
    
    // abscisee et ordonee vont contenir la position des quatre rectangles 
    int abscisse[4]  = {0}, ordonee[4]  = {0};
    int cpt      = 0; // compteur

    /* On dessine sur le rendu quatre rectangles de taille 30px * 30px */
    for (int i=0; i<4; i++) {
        
        // paramètres de position
        rectangle[i].x = abscisse[i];
        rectangle[i].y = ordonee[i];

        // paramètres de taille
        rectangle[i].w = 30;
        rectangle[i].h = 30;
    }

    while (cpt < 50) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        
        for (int i=0; i<4; i++) {
            rectangle[i].x = abscisse[i];
            rectangle[i].y = ordonee[i] ;
            
            SDL_RenderFillRect(renderer, &rectangle[i]);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(30);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        
        ordonee[0] += 5;
        
        abscisse[1] += 10;
        ordonee[1] += 5;

        abscisse[2] += 5;
        ordonee[2] += 10;

        abscisse[3]+=5;

        cpt ++;
    }
}

int main(int argc, char **argv) {
    SDL_Window   * window = NULL;
    SDL_Renderer * renderer = NULL;

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    /* Création de la fenêtre */
    window = SDL_CreateWindow("Fenêtre", 350, 30, 800, 600, SDL_WINDOW_RESIZABLE);

    /* Création du rendu */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (window == NULL) {
        SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());
        SDL_Quit();    
        exit(EXIT_FAILURE);
    }

    if (renderer == NULL) {
        SDL_Log("Error : SDL renderer creation - %s\n", SDL_GetError());
        SDL_Quit();    
        exit(EXIT_FAILURE);
    }

    SDL_Delay(500);
     // La fonction crée les rectangles et les déplace sur la fenetre
    draw_move(renderer);

    SDL_Delay(500); 

    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);
    
    if (window != NULL)
        SDL_DestroyWindow(window);   

    SDL_Quit();

    return EXIT_SUCCESS;
}

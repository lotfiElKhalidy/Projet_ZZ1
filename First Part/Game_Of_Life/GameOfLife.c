#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

#define LIGNE 50
#define COLONNE 50

int survie[9]    = {0,0,1,1,0,0,0,0,0};
int naissance[9] = {0,0,0,1,0,0,0,0,0};

void end_sdl(char ok, char const* msg, SDL_Window * window, SDL_Renderer * renderer) {
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

// La fonction draw nous trace une grille de taille variable avec des cases toutes blanches au debut 
void draw(float tailleCase, SDL_Renderer * renderer) {
    int i = 0, j;

    while (i < 900) {
        j = 0;
        
        while (j < 900) {
            SDL_Rect rectangle;

            /* On dessine sur le rendu un rectangle */
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            rectangle.x = j;
            rectangle.y = i;
            rectangle.w = tailleCase;
            rectangle.h = tailleCase;

            SDL_RenderFillRect(renderer, &rectangle);

            j += tailleCase;
        }
        i += tailleCase;
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(0.1);
}

int ** allocationGrille(int ** grille){
    grille = malloc(LIGNE * sizeof(int *));

    if (grille == NULL){
        printf("Erreur : Allocation dynamique echoue");
        exit(0);
    } 

    for (int i = 0; i<LIGNE ; i++){

        grille[i] = malloc(COLONNE * sizeof(int)); 

        if (grille[i] == NULL){
            printf("Erreur : Allocation dynamique echoue");
            exit(0);
        }    
    } 

    return grille;
}

// On suppose que la matrice est carrée
int tailleGrille(int ** grille) {
    int taille = 0;

    for (int i=0; i<LIGNE; i++) {
        taille++;
    }

    return taille;
}
 
void libererGrille(int ** grille) {
    for (int i=0; i<LIGNE;i++) {
        free(grille[i]);
    } 
    free(grille);
} 

// Cette fonction nous permet d'initialiser la grille avec des 0 (cases blanches)
void initialiser(int ** grille) {

    for (int i=0; i<LIGNE; i++) {

        for (int j=0; j<COLONNE; j++) {

            grille[i][j] = 0;
        }   
    }
}

int est_vivante(int i, int j, int ** grille){
    if(grille[i][j] == 1){
        return 1;
    } 
    return 0;
} 

int modulo(int i, int j) {
    return (i+j)%j;
}

int calculerNbreVoisins(int ** grid, int i, int j) {
    int n_count = 0;
    int size  = tailleGrille(grid);

    if (i-1 >= 0 && j-1 >= 0) {
        if (grid[i-1][j-1] >= 1)
            n_count++;
    }

    if (i-1 >= 0) {
        if(grid[i-1][j] >= 1)
            n_count++;
    }

    if (i-1 >= 0 && j+1 < size) {
        if(grid[i-1][j+1] >= 1)
            n_count++;
    }

    if (j-1 >= 0) {
        if(grid[i][j-1] >= 1)
            n_count++;
    }

    if (j+1 < size) {
        if(grid[i][j+1] >= 1)
            n_count++;
    }

    if (i+1 < size && j-1 >=0) {
        if(grid[i+1][j-1] >= 1)
            n_count++;
    }

    if (i+1 < size) {
        if(grid[i+1][j] >= 1)
            n_count++;
    }

    if (i+1 < size && j+1 < size) {
        if(grid[i+1][j+1] >= 1)
            n_count++;
    }

    return n_count;
}

void updateGrille(int ** grille, int x, int y, int tailleCase) {
    int ligne = x/tailleCase, colonne = y/tailleCase;

    grille[ligne][colonne] = 1;
}

int estVideGrille(int** grille) {
    for(int i=0; i<LIGNE; i++) {
        for(int j=0; j<COLONNE; j++) {
            if (grille[i][j]==0) {
                return 1;
            }   
        } 
    }
    return 0;
}

void copieGrille(int ** grille, int ** grille1) {
    for (int i=0; i<LIGNE; ++i) {
        for (int j=0; j<COLONNE; j++) {
            grille[i][j] = grille1[i][j]; 
        }
    }

}

void mettreAjourGrille(int ** grille, int survie[9], int naissance[9]) {
    int nombreVoisins;

    int ** tabTmp = NULL;

    tabTmp = allocationGrille(tabTmp);

    initialiser(tabTmp);

    for (int i=0; i<LIGNE; i++) {

        for (int j=0; j<COLONNE; j++) {
        
            nombreVoisins = calculerNbreVoisins(grille, i, j);
    
            if (grille[i][j] == 1 ) {
        
                if (survie[nombreVoisins] == 0) {
                    tabTmp[i][j] = 0;
                } 
                else {
                    tabTmp[i][j] = 1;
                } 
            } 
            else {
                if (naissance[nombreVoisins] == 1) {
                    tabTmp[i][j] = 1;
                }
            }
        }
    }  
    copieGrille(grille, tabTmp);
    libererGrille(tabTmp);
}

void afficher (int ** grille) {
    for(int i=0; i<LIGNE; i++) {
        for (int j=0; j<COLONNE; j++) {
            printf("%d", grille[i][j]);
        }
        printf("\n");
    }
    printf("------------------------------\n");
}

void colorier(SDL_Renderer ** renderer, int x, int y, int tailleCase, int couleur) {
    SDL_Rect rectangle;
    int z = x/tailleCase, w = y/tailleCase;
    
    // paramètres de position
    rectangle.x = z*18 ;
    rectangle.y = w*18;

    // paramètres de taille
    rectangle.w = tailleCase;
    rectangle.h = tailleCase;

    if (couleur == 1) {
        SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);
    }
    else {
        if (couleur == 0) {
            SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
        }
    }
    SDL_RenderFillRect(*renderer, &rectangle);

    SDL_RenderPresent(*renderer);
    SDL_Delay(0.25);
}

void miseAjourGrilleSDL(int ** grille, SDL_Renderer ** renderer, int tailleCase, int survie[9], int naissance[9]) {
    int x, y;
    
    mettreAjourGrille(grille, survie, naissance);


    for (int i=0; i<LIGNE; i++) {

        for (int j=0; j<COLONNE; j++) {
            x = j*tailleCase;
            y = i*tailleCase;
      
            if (grille[i][j] == 0) {
                colorier(renderer, x, y, tailleCase, 0);
            }
            else {
                colorier(renderer, x, y, tailleCase, 1);
            }
            
        }
    }
}

int grillesEquals(int ** grille1, int ** grille2) {
    int taille1 = tailleGrille(grille1);
    int taille2 = tailleGrille(grille2);

    if (taille1 != taille2) {
        return 0;
    }
    else {
        for (int i=0; i<taille1; i++) {

            for (int j=0; j<taille1; j++) {

                if (grille1[i][j] != grille2[i][j]) {
                    return 0;
                }
            }
        }
    }
	return 1;
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


int main(int argc, char **argv) {
    SDL_Window   * window = NULL;
    SDL_Renderer * renderer = NULL;

    SDL_bool program_on = SDL_TRUE;
    SDL_Event event;

    int x, y;
    int ** grille = NULL;

    int i = 1;
    int tailleCase = 900/LIGNE;


    grille = allocationGrille(grille);
    initialiser(grille);

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        end_sdl(0, "Echec de l'initialisation de la SDL", window, renderer);
    }

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Jeu de la vie (Game Of Life)", 0, 0, 900, 900, SDL_WINDOW_RESIZABLE);

    /* Création du rendu */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (window == NULL) {
        end_sdl(0, "Echec de la création de la fenetre", window, renderer);
    }

    if (renderer == NULL) {
        end_sdl(0, "Echec de la création du rendu dans la fenetre", window, renderer);
    }
    
    draw(tailleCase, renderer);
  
    while (program_on) {
        if(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    program_on = SDL_FALSE;
                    break;
                
                case SDL_MOUSEBUTTONDOWN:  
                    if (SDL_GetMouseState(&x, &y) && SDL_BUTTON(SDL_BUTTON_LEFT)) {
                        colorier(&renderer, x, y, tailleCase, 1);
                        updateGrille(grille, x, y, tailleCase);
                    }
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_s:
                            while(i) {
                                miseAjourGrilleSDL(grille, &renderer, tailleCase, survie, naissance);
                                
                                if(SDL_PollEvent(&event)) {
                                    switch (event.type) {
                                        case SDL_KEYDOWN:
                                            switch (event.key.keysym.sym) {
                                                case SDLK_q:
                                                    i = 0;
                                                    program_on = SDL_FALSE;
                                                    end_sdl_success(window, renderer);
                                                    exit(0);
                                                    break;
                                                
                                                case SDLK_p:
                                                    i = 0;
                                                    break;
                                                
                                                default :
                                                    break;
                                                }
                                        
                                        default : 
                                            break;
                                    } 
                                } 
                            }
                            break;
                        
                        case SDLK_q:
                            program_on = SDL_FALSE;
                            end_sdl_success(window, renderer);
                            exit(0);
                            break;

                        default:
                            break;
                    }
                
                default:
                    break;
            }
        }
    } 

    end_sdl_success(window, renderer);

    libererGrille(grille);

    return EXIT_SUCCESS;
}

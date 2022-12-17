#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/* Chaine de Markov :
 ------------------------------------------------------------------------
|            |     Mur fixe     |    Mur en haut      |     Mur en bas   | 
 ------------------------------------------------------------------------
|  Fixe      |      20 %        |        40 %         |         40 %     |
 ------------------------------------------------------------------------
|  En haut   |      30 %        |        20 %         |         50 %     |
 ------------------------------------------------------------------------
|  En bas    |      30 %        |        50 %         |         20 %     |
 ------------------------------------------------------------------------
*/

// 0 : Mur fixe, 1: Mur qui monte en haut, 2: Mur qui descend en bas
int markov[3][3] =
{
    {20,60,100},
    {30,50,100},
    {30,80,100}    
};

// Affichage du tr�sor durant tout le jeu
int * afficherTresor(SDL_Texture * my_texture, SDL_Window* window, SDL_Renderer* renderer){
    SDL_Rect 
           source = {0},                      // Rectangle d�finissant la zone de la texture � r�cup�rer
           window_dimensions = {0},           // Rectangle d�finissant la fen�tre, on n'utilisera que largeur et hauteur
           destination = {0};                 // Rectangle d�finissant o� la zone_source doit �tre d�pos�e dans le renderer

    int * tab = malloc(2*sizeof(int));

    if (!tab) {
        printf("Erreur d'allocation\n");
        exit(0);
    }

     SDL_GetWindowSize(
         window, &window_dimensions.w,
         &window_dimensions.h);               // R�cup�ration des dimensions de la fen�tre
     SDL_QueryTexture(my_texture, NULL, NULL,
                      &source.w, &source.h);  // R�cup�ration des dimensions de l'image

     float zoom = 0.25;                        // Facteur de zoom � appliquer    
     destination.w = source.w * zoom -50;         // La destination est un zoom de la source
     destination.h = source.h * zoom -50;         // La destination est un zoom de la source

     destination.x =
       (window_dimensions.w - destination.w)- 25;     // La destination est au milieu de la largeur de la fen�tre
     destination.y =
         (window_dimensions.h - destination.h) / 2;  // La destination est au milieu de la hauteur de la fen�tre

    SDL_RenderCopy(renderer, my_texture,     // Pr�paration de l'affichage  
                    &source,
                    &destination);  

    tab[0] = destination.x;
    tab[1] = destination.y;

    return tab;                        
}

// Affichage du mur qui change sa position selon la chaine de Markov
int * afficherMur(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer, int etatSuivant) {

    SDL_Rect 
           source = {0},                      // Rectangle d�finissant la zone de la texture � r�cup�rer
           window_dimensions = {0},           // Rectangle d�finissant la fen�tre, on n'utilisera que largeur et hauteur
           destination = {0};                 // Rectangle d�finissant o� la zone_source doit �tre d�pos�e dans le renderer
    
    int * tab = malloc(3*sizeof(int));

    if (!tab) {
        printf("Erreur d'allocation\n");
        exit(0);
    }

    SDL_GetWindowSize(
         window, &window_dimensions.w,
         &window_dimensions.h);               // R�cup�ration des dimensions de la fen�tre
    SDL_QueryTexture(my_texture, NULL, NULL,
                      &source.w, &source.h);  // R�cup�ration des dimensions de l'image

    float zoom = 0.25;                        // Facteur de zoom � appliquer    
    destination.w = source.w * zoom -100;         // La destination est un zoom de la source
    destination.h = source.h * zoom - 50;         // La destination est un zoom de la source

    destination.x =
       (window_dimensions.w - destination.w) - 250;     // La destination est au milieu de la largeur de la fen�tre
    destination.y =
         (window_dimensions.h - destination.h) / 2 ;     // La destination est au milieu de la hauteur de la fen�tre
    
    SDL_QueryTexture(my_texture, NULL, NULL,
                      &source.w, &source.h);
    

    switch (etatSuivant) {
        case 1 :
            if (destination.y < 300) {
                destination.y += 50;
            }
            break;

        case 2 :
            if (destination.y > 0) {
                destination.y -= 50;
            }
            break;

        default :
            break;
    }

    *tab = destination.x;
    *(tab+1) = destination.y;
    
    // Pr�paration de l'affichage
    SDL_RenderCopy(renderer, my_texture, &source, &destination);            
    
    //SDL_RenderPresent(renderer);             
    SDL_Delay(300);

    return tab;
}

// Connaitre l'etat suivant en prenant en consideration les probabilites de la chaine de Markove
int etatSuivant(int etatPresent, int markov[3][3], int proba){
    int j = 0;

    while (j<3 && markov[etatPresent][j]<proba) {
        j++;
    } 
 
    return j;
}
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

    if (window != NULL) {
        SDL_DestroyWindow(window);
        window= NULL;
    }

    SDL_Quit();                                                                     

    if (!ok) {               
        exit(EXIT_FAILURE);                                                           
    }                                                                               
}

SDL_Texture * load_texture_from_image(char * file_image_name, SDL_Window ** window, SDL_Renderer ** renderer ) {
    SDL_Surface * my_image = NULL;           // Variable de passage
    SDL_Texture * my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface
                                            // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                            // uniquement possible si l'image est au format bmp */

    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", *window, *renderer);

    my_texture = SDL_CreateTextureFromSurface(*renderer, my_image); // Chargement de l'image de la surface vers la texture
    
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme �l�ment transitoire 
    
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", *window, *renderer);

    return my_texture;
}

void play_with_texture_1_1(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer) {
    SDL_Rect 
            source = {0},                         // Rectangle d�finissant la zone de la texture � r�cup�rer
            window_dimensions = {0},              // Rectangle d�finissant la fen�tre, on n'utilisera que largeur et hauteur
            destination = {0};                    // Rectangle d�finissant o� la zone_source doit �tre d�pos�e dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h);                    // R�cup�ration des dimensions de la fen�tre
    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);       // R�cup�ration des dimensions de l'image

    destination = window_dimensions;              // On fixe les dimensions de l'affichage �  celles de la fen�tre

    //On veut afficher la texture de fa�on � ce que l'image occupe la totalit� de la fen�tre 

    SDL_RenderCopy(renderer, my_texture,
                    &source,
                    &destination);                 // Cr�ation de l'�l�ment � afficher
}


int * play_with_texture_5_1(SDL_Texture  *bg_texture,
                           SDL_Texture  *my_texture,
                           SDL_Texture  *my_texture1,
                           SDL_Texture  *my_texture2,
                           SDL_Window   *window,
                           SDL_Renderer *renderer,
                           int ordonne, int abcisse, 
                           int etatPresent, int markov[3][3]) {

    SDL_Rect
        source = {0},                             // Rectangle d�finissant la zone de la texture � r�cup�rer
        window_dimensions = {0},                  // Rectangle d�finissant la fen�tre, on  n'utilisera que largeur et hauteur
        destination = {0};                        // Rectangle d�finissant o� la zone_source doit �tre d�pos�e dans le renderer

    int etatSuiv = 0, aleatoire = rand() % 100;
    
    int * tab   = malloc(3*sizeof(int));
    int * tab1  = malloc(5*sizeof(int));
    int * tab2  = malloc(2*sizeof(int));

    if (!tab) {
        printf("Erreur d'allocation\n");
        exit(0);
    }

    if (!tab1) {
        printf("Erreur d'allocation\n");
        exit(0);
    }

    if (!tab2) {
        printf("Erreur d'allocation\n");
        exit(0);
    }

    SDL_GetWindowSize(window,                   // R�cup�ration des dimensions de la fen�tre
                        &window_dimensions.w, 
                        &window_dimensions.h); 
    SDL_QueryTexture(my_texture, NULL, NULL,    // R�cup�ration des dimensions de l'image
                    &source.w, &source.h); 
    
    float zoom = 2;                             // zoom, car ces images sont un peu petites
    int offset_x = source.w / 8,                // La largeur d'une vignette de l'image
        offset_y = source.h / 4;                // La hauteur d'une vignette de l'image
    SDL_Rect state[8];                         // Tableau qui stocke les vignettes dans le bon ordre pour l'animation

    /* construction des diff�rents rectangles autour de chacune des vignettes de la planche */
    int i=0;
    for (int x = 0; x < source.w; x += offset_x) {
        state[i].x = x;
        state[i].y = 3*offset_y;
        state[i].w = offset_x;
        state[i].h = offset_y;
        ++i;
    }
    
    destination.w = offset_x * zoom;            // Largeur du sprite � l'�cran
    destination.h = offset_y * zoom;            // Hauteur du sprite � l'�cran
    destination.x = abcisse; // Position en x pour l'affichage du sprite
    destination.y = ordonne;  // Position en y pour l'affichage du sprite

    play_with_texture_1_1(bg_texture,         // identique � play_with_texture_1, o� on a enlev� l'affichage et la pause
                            window, renderer); 
    SDL_RenderCopy(renderer,                  // Pr�paration de l'affichage
                    my_texture, &state[abcisse%7], &destination);
                  // Passage � l'image suivante, le modulo car l'animation est cyclique 
    
    tab2 = afficherTresor(my_texture2, window, renderer);

    etatSuiv = etatSuivant(etatPresent, markov, aleatoire);
    //printf("etatSuiv = %d\n", etatSuiv);
    
    tab = afficherMur(my_texture1, window, renderer, etatSuiv);
    
    tab1[0] = tab[0];
    tab1[1] = tab[1];
    tab1[2] = etatSuiv;
    tab1[3] = tab2[0];
    tab1[3] = tab2[1];    
    
    SDL_RenderPresent(renderer);              // Affichage 
    SDL_Delay(5);                           // Pause en ms
    SDL_RenderClear(renderer);              // Effacer la fen�tre avant de rendre la main

    return tab1;
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

void RalphTheRunner(SDL_Texture  * background,
                           SDL_Texture  * avatar,
                           SDL_Texture  * mur,
                           SDL_Texture  * tresor,
                           SDL_Window   ** window,
                           SDL_Renderer ** renderer,
                           int markov[3][3]) {

    SDL_bool       program_on = SDL_TRUE;                  // Bool�en pour dire que le programme doit continuer
    SDL_Event      event;                                  // Ev�nement � traiter

    int avatarPositionX = 0, avatarPositionY = 0;

    int etatPresent = rand() % 3, etatSuiv = 0;
    int * tab1 = (int *) malloc(3*sizeof(int));

    if (!tab1) {
        printf("Erreur d'allocation\n");
        exit(0);
    }

    int mur_sourceX;
    int mur_sourceY;

    int tresor_sourceX;
    int tresor_sourceY;

    SDL_Rect
        avatar_source = {0};                  // Rectangle d�finissant la zone de la texture � r�cup�rer
    
    while (program_on) {                            // La boucle des �v�nements

        if(SDL_PollEvent(&event)) {   // Tant que la file des �v�nements stock�s n'est pas vide et qu'on n'a pas
                                                    // termin� le programme D�filer l'�l�ment en t�te de file dans 'event'
            switch (event.type) {                         // En fonction de la valeur du type de cet �v�nement
                case SDL_QUIT:                                // Un �v�nement simple, on a cliqu� sur la x de la // fen�tre
                    program_on = SDL_FALSE;                     // Il est temps d'arr�ter le programme
                    break;
                
                case SDL_KEYDOWN:                             // Le type de event est : une touche appuy�e
                                                        // comme la valeur du type est SDL_Keydown, dans la partie 'union' de
                                                        // l'event, plusieurs champs deviennent pertinents   
                    switch (event.key.keysym.sym) {             // la touche appuy�e est ..
                    
                        case SDLK_UP:
                            if (avatarPositionY > 0) avatarPositionY -= 20;
                            break;
                        
                        case SDLK_DOWN:
                            if (avatarPositionY < 300) avatarPositionY += 20;
                            break;

                        case SDLK_RIGHT:
                            if (avatarPositionX < 900) avatarPositionX += 20;
                            break;
                        
                        case SDLK_LEFT:
                            if (avatarPositionX > -10) avatarPositionX -= 20;
                            break;
                        
                        case SDLK_q:
                            program_on = SDL_FALSE;
                            printf("Vous avez quitt� le jeu\n");
                            end_sdl_success(*window, *renderer);
                            exit(0);
                            break;
                        
                        default:                           // Une touche appuy�e qu'on ne traite pas
                            break;
                    }

                default:
                    break;
            }
        }
    
        SDL_QueryTexture(avatar, NULL, NULL, &avatar_source.w, &avatar_source.h);
        
        tab1 = play_with_texture_5_1(background, avatar, mur, tresor, *window, *renderer, 
                                avatarPositionY, avatarPositionX, etatPresent, markov);


        etatSuiv    = tab1[2];
        etatPresent = etatSuiv;

        mur_sourceX = tab1 [0];
        mur_sourceY = tab1[1];

        tresor_sourceX = tab1[3];
        tresor_sourceY = tab1[4];  

        // Calul du centre de masse de mon avatar et mon obstacle
        int centreDeMasse_Avatar[2] = {avatarPositionX + 23, avatarPositionY + 25};
        int centreDeMasse_Mur[2]    = {mur_sourceX + 14, mur_sourceY + 39};  // � calculer � partir des dimensions du mur (affich� sur l'�cran)
        int centreDeMasse_Tresor[2] = {tresor_sourceX + 39, tresor_sourceY + 39};

   
        if( abs (centreDeMasse_Avatar[0] - centreDeMasse_Mur[0]) < 37 && abs(centreDeMasse_Avatar[1] - centreDeMasse_Mur[1]) < 64) {
            printf("Game Over !!!\n");
            program_on = SDL_FALSE;
            end_sdl_success(*window, *renderer);
            exit(0);
        }
    }
}

int main(int argc, char **argv) {

    SDL_Window   * window = NULL;
    SDL_Renderer * renderer = NULL;
    SDL_Texture  * avatar = NULL;
    SDL_Texture  * background = NULL;
    SDL_Texture  * mur = NULL;
    SDL_Texture  * tresor = NULL;
    
    srand(time(NULL));

    /* Initialisation de la SDL  + gestion de l'�chec possible */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        end_sdl(0, "Echec de l'initialisation de la SDL", window, renderer);
    }

    /* Cr�ation de la fen�tre */
    window = SDL_CreateWindow("Jeu : Ralph The Runner 2.0", 150, 70, 1000, 400, SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
        end_sdl(0, "Echec de la cr�ation de la fenetre", window, renderer);
    }

    /* Cr�ation du rendu */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        end_sdl(0, "Echec du la cr�ation du rendu  dans la fenetre", window, renderer);
    }
    
    /* Chargement d'une image dans une texture */
    avatar     = load_texture_from_image("./img/player.png", &window, &renderer);
    mur        = load_texture_from_image("./img/Barrière.jpg", &window, &renderer);
    tresor     = load_texture_from_image("./img/tresor.png", &window, &renderer);
    background = load_texture_from_image("./img/background.jpg", &window, &renderer);

    RalphTheRunner(background, avatar, mur, tresor, &window, &renderer, markov);

    if (background != NULL)
        SDL_DestroyTexture(background);

    if (tresor != NULL)
        SDL_DestroyTexture(tresor);
    
    if (mur != NULL)
        SDL_DestroyTexture(mur);

    if (avatar != NULL)
        SDL_DestroyTexture(avatar);

    end_sdl_success(window, renderer);

    return EXIT_SUCCESS;
}

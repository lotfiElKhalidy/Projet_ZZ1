#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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

SDL_Texture * load_texture_from_image(char * file_image_name, SDL_Window ** window, SDL_Renderer ** renderer ) {
    SDL_Surface * my_image = NULL;           // Variable de passage
    SDL_Texture * my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface
                                            // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                            // uniquement possible si l'image est au format bmp */
    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", *window, *renderer);

    my_texture = SDL_CreateTextureFromSurface(*renderer, my_image); // Chargement de l'image de la surface vers la texture
    
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme ??l??ment transitoire 
    
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", *window, *renderer);

    return my_texture;
}

void play_with_texture_1_1(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer, int position) {
    SDL_Rect 
            source = {0},                         // Rectangle d??finissant la zone de la texture ?? r??cup??rer
            window_dimensions = {0},              // Rectangle d??finissant la fen??tre, on n'utilisera que largeur et hauteur
            destination = {0};                    // Rectangle d??finissant o?? la zone_source doit ??tre d??pos??e dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h);
    

    // R??cup??ration des dimensions de la fen??tre
    
    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);       // R??cup??ration des dimensions de l'image

    destination = window_dimensions;              // On fixe les dimensions de l'affichage ??  celles de la fen??tre
    destination.x = position;
    //destination.y = 50;

    /* On veut afficher la texture de fa??on ?? ce que l'image occupe la totalit?? de la fen??tre */

    SDL_RenderCopy(renderer, my_texture,
                    &source,
                    &destination);                 // Cr??ation de l'??l??ment ?? afficher
    
    /* Il ne faut pas oublier d'afficher avec SDL_RenderPresent et de mettre une pause SDL_Delay si on esp??re voir quelque chose. */
    //SDL_Delay(10);                              // Pause en ms
}

void play_with_texture_1_2(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer, int position) {
    SDL_Rect 
            source = {0},                         // Rectangle d??finissant la zone de la texture ?? r??cup??rer
            window_dimensions = {0},              // Rectangle d??finissant la fen??tre, on n'utilisera que largeur et hauteur
            destination = {0};                    // Rectangle d??finissant o?? la zone_source doit ??tre d??pos??e dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h);
    

    // R??cup??ration des dimensions de la fen??tre
    
    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);       // R??cup??ration des dimensions de l'image

    destination = window_dimensions;              // On fixe les dimensions de l'affichage ??  celles de la fen??tre
    destination.x = position;
    destination.y = 50;

    /* On veut afficher la texture de fa??on ?? ce que l'image occupe la totalit?? de la fen??tre */

    SDL_RenderCopy(renderer, my_texture,
                    &source,
                    &destination);                 // Cr??ation de l'??l??ment ?? afficher
    
    /* Il ne faut pas oublier d'afficher avec SDL_RenderPresent et de mettre une pause SDL_Delay si on esp??re voir quelque chose. */
    //SDL_Delay(10);                              // Pause en ms
}

void play_with_texture_1_3(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer, int position) {
    SDL_Rect 
            source = {0},                         // Rectangle d??finissant la zone de la texture ?? r??cup??rer
            window_dimensions = {0},              // Rectangle d??finissant la fen??tre, on n'utilisera que largeur et hauteur
            destination = {0};                    // Rectangle d??finissant o?? la zone_source doit ??tre d??pos??e dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h);
    

    // R??cup??ration des dimensions de la fen??tre
    
    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);       // R??cup??ration des dimensions de l'image

    destination = window_dimensions;              // On fixe les dimensions de l'affichage ??  celles de la fen??tre
    destination.x = position;
    destination.y = 150;

    /* On veut afficher la texture de fa??on ?? ce que l'image occupe la totalit?? de la fen??tre */

    SDL_RenderCopy(renderer, my_texture,
                    &source,
                    &destination);                 // Cr??ation de l'??l??ment ?? afficher
    
    /* Il ne faut pas oublier d'afficher avec SDL_RenderPresent et de mettre une pause SDL_Delay si on esp??re voir quelque chose. */
    //SDL_Delay(10);                              // Pause en ms
}

void play_with_texture_5(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer, int ordonne, int abcisse,
                         int mountain, int tree, int sky) {

    SDL_Rect
        source = {0},                             // Rectangle d??finissant la zone de la texture ?? r??cup??rer
        window_dimensions = {0},                  // Rectangle d??finissant la fen??tre, on  n'utilisera que largeur et hauteur
        destination = {0};                        // Rectangle d??finissant o?? la zone_source doit ??tre d??pos??e dans le renderer

    SDL_GetWindowSize(window,                   // R??cup??ration des dimensions de la fen??tre
                        &window_dimensions.w, 
                        &window_dimensions.h); 
    SDL_QueryTexture(my_texture, NULL, NULL,    // R??cup??ration des dimensions de l'image
                    &source.w, &source.h); 

    //int nb_images = 40;                         //  Il y a 8 vignette dans la ligne qui nous int??resse
    //int nb_images_animation = 0 * nb_images;    // 
    
    float zoom = 2;                             // zoom, car ces images sont un peu petites
    
    int offset_x = source.w / 8,                // La largeur d'une vignette de l'image
        offset_y = source.h / 4;                // La hauteur d'une vignette de l'image
    
    SDL_Rect state[8];                         // Tableau qui stocke les vignettes dans le bon ordre pour l'animation

    /* construction des diff??rents rectangles autour de chacune des vignettes de la planche */
    int i = 0;                                   
    
    for (int x = 0; x < source.w; x += offset_x) {
        state[i].x = x;
        state[i].y = offset_y;
        state[i].w = offset_x;
        state[i].h = offset_y;
        ++i;
    }


    destination.w = offset_x * zoom;            // Largeur du sprite ?? l'??cran
    destination.h = offset_y * zoom;            // Hauteur du sprite ?? l'??cran
    destination.x = abcisse; // Position en x pour l'affichage du sprite
    destination.y = ordonne;  // Position en y pour l'affichage du sprite

    
    

    //play_with_texture_1_1(my_texturebg, window, renderer); 
    SDL_RenderCopy(renderer,                  // Pr??paration de l'affichage
                my_texture, &state[abcisse%7], &destination);
                    // Passage ?? l'image suivante, le modulo car l'animation est cyclique 
    SDL_RenderPresent(renderer);              // Affichage
    SDL_Delay(10);                           // Pause en ms
    SDL_RenderClear(renderer);                  // Effacer la fen??tre avant de rendre la main
}

void play_with_texture_5_1(SDL_Texture *bg_texture,
                           SDL_Texture *cg_texture,
                           SDL_Texture *dg_texture,
                           SDL_Texture *eg_texture,
                           SDL_Texture *my_texture,
                           SDL_Window *window,
                            SDL_Renderer *renderer, int ordonne, int abcisse, int mountain, int tree, int sky, int trees) {
    SDL_Rect
        source = {0},                             // Rectangle d??finissant la zone de la texture ?? r??cup??rer
        window_dimensions = {0},                  // Rectangle d??finissant la fen??tre, on  n'utilisera que largeur et hauteur
        destination = {0};                        // Rectangle d??finissant o?? la zone_source doit ??tre d??pos??e dans le renderer

    SDL_GetWindowSize(window,                   // R??cup??ration des dimensions de la fen??tre
                        &window_dimensions.w, 
                        &window_dimensions.h); 
    SDL_QueryTexture(my_texture, NULL, NULL,    // R??cup??ration des dimensions de l'image
                    &source.w, &source.h); 

    //int nb_images = 40;                         //  Il y a 8 vignette dans la ligne qui nous int??resse
    //int nb_images_animation = 1 * nb_images;    // 
    
    float zoom = 2;                             // zoom, car ces images sont un peu petites
    int offset_x = source.w / 5,                // La largeur d'une vignette de l'image
        offset_y = source.h / 5;                // La hauteur d'une vignette de l'image
    SDL_Rect state[5];                         // Tableau qui stocke les vignettes dans le bon ordre pour l'animation

    /* construction des diff??rents rectangles autour de chacune des vignettes de la planche */
    int i=0;
    for (int x = 0; x < source.w; x += offset_x) {
        state[i].x = x;
        state[i].y = 3*offset_y;
        state[i].w = offset_x;
        state[i].h = offset_y;
        ++i;
    }
    
    destination.w = offset_x * zoom;            // Largeur du sprite ?? l'??cran
    destination.h = offset_y * zoom;            // Hauteur du sprite ?? l'??cran
    destination.x = abcisse; // Position en x pour l'affichage du sprite
    destination.y = ordonne;  // Position en y pour l'affichage du sprite

    play_with_texture_1_1(bg_texture,         // identique ?? play_with_texture_1, o?? on a enlev?? l'affichage et la pause
                            window, renderer, sky); 
    play_with_texture_1_3(cg_texture,         // identique ?? play_with_texture_1, o?? on a enlev?? l'affichage et la pause
                            window, renderer, mountain);
    play_with_texture_1_2(dg_texture,         // identique ?? play_with_texture_1, o?? on a enlev?? l'affichage et la pause
                            window, renderer, tree);
    play_with_texture_1_2(eg_texture,         // identique ?? play_with_texture_1, o?? on a enlev?? l'affichage et la pause
                            window, renderer, trees);

    SDL_RenderCopy(renderer,                  // Pr??paration de l'affichage
                    my_texture, &state[abcisse%3], &destination);  // Passage ?? l'image suivante, le modulo car l'animation est cyclique 
    SDL_RenderPresent(renderer);              // Affichage
    SDL_Delay(10);                           // Pause en ms
    SDL_RenderClear(renderer);                  // Effacer la fen??tre avant de rendre la main
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
    
    SDL_Texture  * avatar = NULL;
    SDL_Texture  * sky = NULL;
    SDL_Texture  * mountain = NULL;
    SDL_Texture  * tree = NULL;
    SDL_Texture  * trees = NULL; 

    SDL_bool       program_on = SDL_TRUE;                       // Bool??en pour dire que le programme doit continuer
    SDL_Event      event;                                      // Ev??nement ?? traiter

    int avatarPositionX    = 0;
    int avatarPositionY    = 0;
    int treePositionX      = -20;
    int mountainsPositionX = 0;
    int skyPositionX       = 0;
    int treesPositionX     = -200;

    /* Initialisation de la SDL  + gestion de l'??chec possible */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        end_sdl(0, "Echec de l'initialisation de la SDL", window, renderer);
    }

    /* Cr??ation de la fen??tre */
    window = SDL_CreateWindow("Sprite : Flying bird", 350, 30, 1000, 400, SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
        end_sdl(0, "Echec de la cr??ation de la fenetre", window, renderer);
    }

    /* Cr??ation du rendu */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        end_sdl(0, "Echec du la cr??ation du rendu  dans la fenetre", window, renderer);
    }

    /* Chargement d'images dans des textures */
    avatar   = load_texture_from_image("./img/bird.png", &window, &renderer);
    sky      = load_texture_from_image("./img/sky.png", &window, &renderer);
    mountain = load_texture_from_image("./img/mountains.png", &window, &renderer);
    tree     = load_texture_from_image("./img/tree.png", &window, &renderer);
    trees    = load_texture_from_image("./img/trees.png", &window, &renderer);

    while (program_on) {                               // La boucle des ??v??nements
        if(SDL_PollEvent(&event)) {   // Tant que la file des ??v??nements stock??s n'est pas vide et qu'on n'a pas
                                                    // termin?? le programme D??filer l'??l??ment en t??te de file dans 'event'
            switch (event.type) {                         // En fonction de la valeur du type de cet ??v??nement
                case SDL_QUIT:                                // Un ??v??nement simple, on a cliqu?? sur la x de la // fen??tre
                    program_on = SDL_FALSE;                     // Il est temps d'arr??ter le programme
                    break;
                
                case SDL_KEYDOWN:                             // Le type de event est : une touche appuy??e
                                                        // comme la valeur du type est SDL_Keydown, dans la partie 'union' de
                                                        // l'event, plusieurs champs deviennent pertinents   
                    switch (event.key.keysym.sym) {             // la touche appuy??e est ..
                        case SDLK_UP:
                            if (avatarPositionY > 0) avatarPositionY -= 10;
                            break;
                        
                        case SDLK_DOWN:
                            if (avatarPositionY < 400) avatarPositionY += 10;
                            break;

                        case SDLK_RIGHT:
                            if (avatarPositionX < 1000) {
                                avatarPositionX += 10;
                                mountainsPositionX += 0.9;
                                skyPositionX += 0.9;
                                treePositionX += 1;
                                treesPositionX += 2;
                            }
                            break;
                        
                        case SDLK_LEFT:
                            if (avatarPositionX > -100) {
                                avatarPositionX -= 10;
                                mountainsPositionX -= 0.1;
                                skyPositionX -= 0.05;
                                treePositionX -= 1;
                                treesPositionX -= 2;
                            }
                            break;
                        
                        case SDLK_q:
                            program_on = SDL_FALSE;
                            end_sdl_success(window, renderer);
                            exit(0);
                            break;
                        
                        default:                                    // Une touche appuy??e qu'on ne traite pas
                            break;
                    }
                default:
                    break;
            }
        }
        
        if (avatarPositionX < 775 && avatarPositionY < 245) {
            play_with_texture_5_1(sky, mountain, tree, trees, avatar, window, renderer,
                                  avatarPositionY, avatarPositionX, mountainsPositionX, 
                                  treePositionX, skyPositionX, treesPositionX);
        }
        else {
            end_sdl_success(window, renderer);
            exit(0);
        }

        SDL_Delay(10);                                  // Petite pause
    }

    SDL_RenderPresent(renderer);

    end_sdl_success(window, renderer);

    return EXIT_SUCCESS;
}

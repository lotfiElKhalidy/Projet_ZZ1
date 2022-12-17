#ifndef SDL_H
#define SDL_H

#define LIGNE 7
#define COLONNE 7

void end_sdl(char ok, char const * msg, SDL_Window * window, SDL_Renderer * renderer);
void end_sdl_success(SDL_Window * window, SDL_Renderer * renderer);

SDL_Texture * load_texture_from_image(char * file_image_name, SDL_Window ** window, 
                                        SDL_Renderer ** renderer);

void dessinerGrilleInitiale(int, int, SDL_Renderer *);
void show_text(SDL_Window** window,
              SDL_Renderer** renderer,
              TTF_Font * font,
              char text[20],
              SDL_Color color,
              SDL_Rect pos,
              int style);

#endif

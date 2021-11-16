#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_video.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5\allegro_audio.h>

// metodos principais
void venceu(void);
void segunda(void);
void game(void);
void intro(void);
void menu(void);
void settings(int *cord_cursor_x, int *cord_cursor_y);
int verifyAllegroFunction(bool func, const char *message);

// setar cor dos botões de menu quando selecionado
void color_press(int *r, int *g, int *b, int selection, int max);

// variaveis globais
#define blocksize 40
#define fps 60
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_COLOR tint_color;
extern int width_display;
extern int height_display;
extern int color[];
extern int att_count;



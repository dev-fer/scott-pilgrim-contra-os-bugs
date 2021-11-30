#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void end(void);
void fase1(void);
void fase2(void);
void fase3(void);
void fase4(void);
void fase5(void);
void intro(void);
void tutorial(void);
void mathewintro(void);
void mathewfinal(void);
void lucasleeintro(void);
void lucasleefinal(void);
void roxanneintro(void);
void roxannefinal(void);
void toddintro(void);
void toddfinal(void);
void menu(void);
void settings(int *cord_cursor_x, int *cord_cursor_y);
int verifyAllegroFunction(bool func, const char *message);

void video_display_game(ALLEGRO_VIDEO *video);

// setar cor dos botões de menu quando selecionado
void color_press(int *r, int *g, int *b, int selection, int max);

typedef struct {
    ALLEGRO_BITMAP *card;
    int maxFrame;
    int currentFrame;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;
    int frameStartWidth;
    int frameStartHeight;
    int frameFinishWidth;
    int frameFinishHeight;
    float cardX;
    float cardY;
    char *urlMiniCard;
} Card;

typedef struct {
    ALLEGRO_BITMAP *card;
    float cardX;
    float cardY;
} EnemyCard, CharacterCard, MiniCard;

typedef struct {
    ALLEGRO_BITMAP *button;
    int maxFrame;
    int currentFrame;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;
    float buttonX;
    float buttonY;
} Button;

Card create_card(char *urlCard, int maxFrame, int frameDelay, int frameWidth, int frameHeight, int frameStartWidth, int frameStartHeight, int frameFinishWidth, int frameFinishHeight, float cardX, float cardY, char *urlMiniCard);
EnemyCard create_enemy_card(char *urlCard, float cardX, float cardY);
MiniCard create_mini_card(char *urlCard, float cardX, float cardY);
CharacterCard create_character_card(char *urlCard, float cardX, float cardY);
Button create_button(char *urlButton, int maxFrame, int frameDelay, int frameWidth, int frameHeight, float buttonX, float buttonY);

// variaveis globais
#define blocksize 40
#define fps 60
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_COLOR tint_color;
extern int width_display;
extern int height_display;
extern int color[];
extern int att_count;



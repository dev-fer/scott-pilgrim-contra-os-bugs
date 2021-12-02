#include "../../../headers.h"

ALLEGRO_SAMPLE *f2_themebackground = NULL;
ALLEGRO_SAMPLE_INSTANCE *f2_music = NULL;
ALLEGRO_BITMAP *f2_labirinto = NULL;
ALLEGRO_EVENT f2_event;

bool fase_tres_on = false;
bool f2_done = false;
bool f2_redraw = true;

bool f2_interacaoCard = false;
bool f2_interacaoButton = false;
bool f2_continueAnimacaoScott = true;
bool f2_continueAnimacaoBoss = true;
bool f2_travaCompilar = true;
bool f2_travaResetar = true;
bool f2_resultado = false;
bool f2_mouseRangeCard = false;
bool f2_mouseRangeButton = false;
bool f2_mostraGuia = false;

float f2_awaitAnimation = 0;
float f2_scottX = 596, f2_scottY = 626;
float f2_bossX = 1104, f2_bossY = 626;

float f2_x = 100, f2_y = 100;
float f2_dx = 0, f2_dy = 0;

int f2_positionMiniCardX = 614;
int f2_contMiniCard = 0;

int f2_resultadoFase[4] = {3, 0, 2, 1};
int f2_respostaJogador[4];

int f2_contAnimacaoScott = 0;
int f2_contAnimacaoEnemy = 0;

Card f2_cards[4];
MiniCard f2_miniCards[4];
EnemyCard f2_enemyCards[4];
Button f2_buttons[3];
Button f2_power[3];
CharacterCard f2_characterCards[4];
CharacterCard f2_cardText[2];
CharacterCard f2_guia[0];

void f2_mouseMove(void);
void f2_mouseRangeCards(int i);
void f2_mouseRangeButtons(int i);
void f2_powerFrames(int i);
bool f2_mouseRangeUpCard(int i) ;
bool f2_mouseRangeUpButton(int i);
void f2_animationsResult(void);
void f2_destroyFase(void);

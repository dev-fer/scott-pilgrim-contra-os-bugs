#include "../../../headers.h"

ALLEGRO_SAMPLE *themebackground = NULL;
ALLEGRO_SAMPLE_INSTANCE *music = NULL;
ALLEGRO_BITMAP *labirinto = NULL;
ALLEGRO_EVENT event;

bool fase_dois_on = false;
bool menu_on = false;
bool done = false;
bool redraw = true;

bool interacaoCard = false;
bool interacaoButton = false;
bool continueAnimacaoScott = true;
bool continueAnimacaoBoss = true;
bool travaCompilar = true;
bool travaResetar = true;
bool resultado = false;
bool mouseRangeCard = false;
bool mouseRangeButton = false;
bool mostraGuia = true;
bool mostraPause = false;
bool pauseContinuar = true;
bool pauseMenu = false;

float awaitAnimation = 700;
float scottX = 474, scottY = 700;
float bossX = 1498, bossY = 576;

float x = 100, y = 100;
float dx = 0, dy = 0;

int positionMiniCardX = 614;
int contMiniCard = 0;

int resultadoFase[3] = {0, 3, 1};
int respostaJogador[4];

int contAnimacaoScott = 0;
int contAnimacaoEnemy = 0;

Card cards[4];
MiniCard miniCards[4];
EnemyCard enemyCards[4];
Button buttons[3];
Button power[3];
CharacterCard pause[2];
CharacterCard characterCards[4];
CharacterCard cardText[2];
CharacterCard guia[0];

void mouseMove(void);
void mouseRangeCards(int i);
void mouseRangeButtons(int i);
void powerFrames(int i);
bool mouseRangeUpCard(int i) ;
bool mouseRangeUpButton(int i);
void animationsResult(void);
void destroyFase(void);

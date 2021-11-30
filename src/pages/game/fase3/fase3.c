#include "../../../headers.h"

void fase3(void) {
    lucasleefinal();
    roxanneintro();
    verifyAllegroFunction(al_init(), "allegro");
    verifyAllegroFunction(al_install_keyboard(), "keyboard");
    verifyAllegroFunction(al_install_mouse(), "mouse");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
    verifyAllegroFunction(timer, "timer");

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    verifyAllegroFunction(queue, "queue");

    bool faseQuatro_on = false;

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_FONT *font = al_create_builtin_font();
    verifyAllegroFunction(font, "font");

    ALLEGRO_FONT *botao = al_load_ttf_font("../src/assets/fonts/joystix.ttf", 30, 0);

    verifyAllegroFunction(al_init_image_addon(), "couldn't initialize image addon");
    ALLEGRO_BITMAP *bg = al_load_bitmap("../src/assets/images/bg.jpg");
    ALLEGRO_BITMAP *labirinto = al_load_bitmap("../src/assets/images/fase_um.png");
    ALLEGRO_BITMAP *painel = al_load_bitmap("../src/assets/images/painel.png");
    ALLEGRO_BITMAP *cursor = al_load_bitmap("../src/assets/images/cursor.png");

    verifyAllegroFunction(bg, "couldn't initialize player");
    verifyAllegroFunction(cursor, "couldn't initialize player");

    verifyAllegroFunction(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    bool active = true;
    bool interatividadeCorrer = false;
    bool interacaoCard = false;
    bool interacaoButton = false;
    ALLEGRO_EVENT event;

    Card cards[4];
    EnemyCard enemyCards[4];
    MiniCard miniCards[4];
    Button buttons[3];
    CharacterCard characterCards[4];
    Button arrows[3];

    cards[0] = create_card("../src/assets/images/correr_animacao.png", 21, 3, 247, 328, 16, 5, 35, 19, 440, 74, "../src/assets/images/minicard_correr.png");
    cards[1] = create_card("../src/assets/images/atacar_animacao.png", 30, 3, 374, 438, 61, 116, 116, 19, 642, -36, "../src/assets/images/minicard_atacar.png");
    cards[2] = create_card("../src/assets/images/defender_animacao.png", 28, 3, 205, 312, 3, 3, 5, 5, 947, 76, "../src/assets/images/minicard_defender.png");
    cards[3] = create_card("../src/assets/images/esquivar_animacao.png", 19, 3, 208, 363, 4, 54, 7, 5, 1193, 25, "../src/assets/images/minicard_esquivar.png");

    enemyCards[0] = create_enemy_card("../src/assets/images/card_run_inimigo.png", 639, 824);
    enemyCards[1] = create_enemy_card("../src/assets/images/card_shoot_inimigo.png", 829, 824);
    enemyCards[2] = create_enemy_card("../src/assets/images/card_run_inimigo.png", 1025, 824);
    enemyCards[3] = create_enemy_card("../src/assets/images/card_atk_inimigo.png", 1214, 824);

    buttons[0] = create_button("../src/assets/images/compilar.png", 8, 2, 49, 51, 105, 951);
    buttons[1] = create_button("../src/assets/images/reset.png", 8, 2, 49, 51, 164, 951);
    buttons[2] = create_button("../src/assets/images/dica.png", 8, 2, 49, 51, 223, 951);

    characterCards[0] = create_character_card("../src/assets/images/scott_perfil.png", 69, 97);
    characterCards[1] = create_character_card("../src/assets/images/scott_mini.png", 474, 700);
    characterCards[2] = create_character_card("../src/assets/images/roxanne_perfil.png", 1473, 720);
    characterCards[3] = create_character_card("../src/assets/images/roxanne_mini.png", 1498, 576);

    int resultadoFase[3] = {0, 3, 1};
    int respostaJogador[4];

    float x, y;
    x = 100;
    y = 100;

    int positionMiniCardX;
    positionMiniCardX = 614;

    int contMiniCard = 0;

#define KEY_SEEN 1
#define KEY_RELEASED 2

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    al_hide_mouse_cursor(display);

    float dx, dy;
    dx = 0;
    dy = 0;

    al_grab_mouse(display);

    al_start_timer(timer);

    while (!done) {
        al_wait_for_event(queue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                if (key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                x += dx;
                y += dy;

                if (x < 0) {
                    x *= -1;
                    dx *= -1;
                }
                if (x > width_display) {
                    x -= (x - width_display) * 2;
                    dx *= -1;
                }
                if (y < 0) {
                    y *= -1;
                    dy *= -1;
                }
                if (y > height_display) {
                    y -= (y - height_display) * 2;
                    dy *= -1;
                }

                dx *= 0.9;
                dy *= 0.9;

                for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;

                for (int i = 0; i < 4; i++) {
                    bool mouseRangeCard = x >= cards[i].cardX && x >= (cards[i].cardX + cards[i].frameStartWidth) && x <= (cards[i].cardX + cards[i].frameWidth - cards[i].frameFinishWidth) && y >= (cards[i].cardY + cards[i].frameStartHeight) && y <= (cards[i].cardY + cards[i].frameHeight - cards[i].frameFinishHeight);

                    if (mouseRangeCard && interacaoCard) {


                        if (contMiniCard < 4) {
                            miniCards[contMiniCard] = create_mini_card(cards[i].urlMiniCard, positionMiniCardX, 800);
                            respostaJogador[contMiniCard] = i;
                            positionMiniCardX += 192;
                            contMiniCard++;
                        }
                        interacaoCard = false;
                    }

                    if (mouseRangeCard) {
                        if (++cards[i].frameCount >= cards[i].frameDelay) {
                            if (++cards[i].currentFrame >= cards[i].maxFrame)
                                cards[i].currentFrame = 0;

                            cards[i].frameCount = 0;
                        }
                    } else {
                        cards[i].currentFrame = 0;
                        cards[i].frameCount = 0;
                    }
                }

                for (int i = 0; i < 3; i++) {
                    bool mouseRangeButton = x >= buttons[i].buttonX && x >= buttons[i].buttonX && x <= (buttons[i].buttonX + buttons[i].frameWidth) && y >= buttons[i].buttonY && y <= (buttons[i].buttonY + buttons[i].frameHeight);
                    bool mouseRangeCompilar = buttons[0].buttonX && x >= buttons[0].buttonX && x <= (buttons[0].buttonX + buttons[0].frameWidth) && y >= buttons[0].buttonY && y <= (buttons[0].buttonY + buttons[0].frameHeight);
                    bool mouseRangeResetar = buttons[1].buttonX && x >= buttons[1].buttonX && x <= (buttons[1].buttonX + buttons[1].frameWidth) && y >= buttons[1].buttonY && y <= (buttons[1].buttonY + buttons[1].frameHeight);

                    if (mouseRangeCompilar && interacaoButton) {
                        bool resultado = respostaJogador[0] == resultadoFase[0] && respostaJogador[1] == resultadoFase[1] && respostaJogador[2] == resultadoFase[2];

                        if (resultado) {
                            faseQuatro_on = true;
                            done = true;
                            characterCards[1].cardX += 128;
                            characterCards[1].cardY -= 128;
                            interacaoButton = false;
                            break;
                        } else {
                            printf("%s, Perdeu!");
                            interacaoButton = false;
                        }
                    }

                    if (mouseRangeResetar && interacaoButton) {
                            respostaJogador[0] = 0;
                            respostaJogador[1] = 0;
                            respostaJogador[2] = 0;
                            contMiniCard = 0;
                            positionMiniCardX = 614;
                            al_destroy_bitmap(miniCards[0].card);
                            al_destroy_bitmap(miniCards[1].card);
                            al_destroy_bitmap(miniCards[2].card);
                            al_destroy_bitmap(miniCards[3].card);
                            interacaoButton = false;
                            break;

                    }

                    if (mouseRangeButton) {
                        if (++buttons[i].frameCount >= buttons[i].frameDelay) {
                            if (++buttons[i].currentFrame >= buttons[i].maxFrame)
                                buttons[i].currentFrame = 0;

                            buttons[i].frameCount = 0;
                        }
                    } else {
                        buttons[i].currentFrame = 0;
                        buttons[i].frameCount = 0;
                    }
                }
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                dx += event.mouse.dx * 0.1;
                dy += event.mouse.dy * 0.1;
                al_set_mouse_xy(display, 320, 240);
                break;

                bool mouseRangeCard = false;
                bool mouseRangeButton = false;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                for (int i = 0; i < 4; i++) {
                    mouseRangeCard = x >= cards[i].cardX && x >= (cards[i].cardX + cards[i].frameStartWidth) && x <= (cards[i].cardX + cards[i].frameWidth - cards[i].frameFinishWidth) && y >= (cards[i].cardY + cards[i].frameStartHeight) && y <= (cards[i].cardY + cards[i].frameHeight - cards[i].frameFinishHeight);

                    if (mouseRangeCard) {
                        interacaoCard = true;
                        break;
                    }
                }

                for (int i = 0; i < 3; i++) {
                    mouseRangeButton = x >= buttons[i].buttonX && x >= buttons[i].buttonX && x <= (buttons[i].buttonX + buttons[i].frameWidth) && y >= buttons[i].buttonY && y <= (buttons[i].buttonY + buttons[i].frameHeight);

                    if (mouseRangeButton) {
                        interacaoButton = true;
                        break;
                    }
                }

                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(bg, 0, 0, 0);
            al_draw_filled_rectangle(639, 920, 1224, 926, al_map_rgb(237, 133, 71));

            al_draw_bitmap(labirinto, 450, 426, 0);
            al_draw_bitmap(painel, 75, 938, 0);

            for (int i = 0; i < 4; i++) {
                al_draw_bitmap_region(cards[i].card, cards[i].currentFrame * cards[i].frameWidth, 0, cards[i].frameWidth, cards[i].frameHeight, cards[i].cardX, cards[i].cardY, 0);
                al_draw_bitmap(enemyCards[i].card, enemyCards[i].cardX, enemyCards[i].cardY, 0);
                al_draw_bitmap(characterCards[i].card, characterCards[i].cardX, characterCards[i].cardY, 0);
            }

            if (contMiniCard > 0) {
                for (int i = 0; i < contMiniCard; i++) {
                    al_draw_bitmap(miniCards[i].card, miniCards[i].cardX, miniCards[i].cardY, 0);
                }
            }

            for (int i = 0; i < 3; i++) {
                al_draw_bitmap_region(buttons[i].button, buttons[i].currentFrame * buttons[i].frameWidth, 0, buttons[i].frameWidth, buttons[i].frameHeight, buttons[i].buttonX, buttons[i].buttonY, 0);
            }

            al_draw_bitmap(cursor, x, y, 0);

            al_flip_display();

            redraw = false;
        }
    }

    for (int i = 0; i < 4; i++) {
        al_destroy_bitmap(cards[i].card);
        al_destroy_bitmap(enemyCards[i].card);
        al_destroy_bitmap(characterCards[i].card);
    }

    if (contMiniCard > 0) {
        for (int i = 0; i < contMiniCard; i++) {
            al_destroy_bitmap(miniCards[i].card);
        }
    }

    for (int i = 0; i < 3; i++) {
        al_destroy_bitmap(buttons[i].button);
    }

    al_destroy_bitmap(bg);
    al_destroy_bitmap(labirinto);
    al_destroy_bitmap(painel);
    al_destroy_bitmap(cursor);

    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    if (faseQuatro_on == true)
        fase4();
}

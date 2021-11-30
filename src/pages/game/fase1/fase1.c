#include "../../../headers.h"

Card create_card(char *urlCard, int maxFrame, int frameDelay, int frameWidth, int frameHeight, int frameStartWidth, int frameStartHeight, int frameFinishWidth, int frameFinishHeight, float cardX, float cardY, char *urlMiniCard) {
    Card c;
    c.card = al_load_bitmap(urlCard);
    verifyAllegroFunction(c.card, "image not found");
    c.maxFrame = maxFrame;
    c.currentFrame = 0;
    c.frameCount = 0;
    c.frameDelay = frameDelay;
    c.frameWidth = frameWidth;
    c.frameHeight = frameHeight;
    c.frameStartWidth = frameStartWidth;
    c.frameStartHeight = frameStartHeight;
    c.frameFinishWidth = frameFinishWidth;
    c.frameFinishHeight = frameFinishHeight;
    c.cardX = cardX;
    c.cardY = cardY;
    c.urlMiniCard = urlMiniCard;
    return c;
}

EnemyCard create_enemy_card(char *urlCard, float cardX, float cardY) {
    EnemyCard ec;
    ec.card = al_load_bitmap(urlCard);
    verifyAllegroFunction(ec.card, "image not found");
    ec.cardX = cardX;
    ec.cardY = cardY;
    return ec;
}

MiniCard create_mini_card(char *urlCard, float cardX, float cardY) {
    MiniCard mc;
    mc.card = al_load_bitmap(urlCard);
    verifyAllegroFunction(mc.card, "image not found");
    mc.cardX = cardX;
    mc.cardY = cardY;
    return mc;
}

CharacterCard create_character_card(char *urlCard, float cardX, float cardY) {
    CharacterCard cc;
    cc.card = al_load_bitmap(urlCard);
    verifyAllegroFunction(cc.card, "image not found");
    cc.cardX = cardX;
    cc.cardY = cardY;
    return cc;
}

Button create_button(char *urlButton, int maxFrame, int frameDelay, int frameWidth, int frameHeight, float buttonX, float buttonY) {
    Button b;
    b.button = al_load_bitmap(urlButton);
    verifyAllegroFunction(b.button, "image not found");
    b.maxFrame = maxFrame;
    b.currentFrame = 0;
    b.frameCount = 0;
    b.frameDelay = frameDelay;
    b.frameWidth = frameWidth;
    b.frameHeight = frameHeight;
    b.buttonX = buttonX;
    b.buttonY = buttonY;
    return b;
}

void fase1(void) {
    tutorial();
    mathewintro();
    verifyAllegroFunction(al_init(), "allegro");
    verifyAllegroFunction(al_install_keyboard(), "keyboard");
    verifyAllegroFunction(al_install_mouse(), "mouse");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
    verifyAllegroFunction(timer, "timer");

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    verifyAllegroFunction(queue, "queue");

    bool fase_dois_on = false;

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

    ALLEGRO_SAMPLE *themebackground = al_load_sample("../src/assets/sounds/Matthew.ogg");
    ALLEGRO_SAMPLE_INSTANCE *music = al_create_sample_instance(themebackground);
    al_attach_sample_instance_to_mixer(music, al_get_default_mixer());

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
    bool mostraGuia = true;
    ALLEGRO_EVENT event;

    float scottX, scottY, scottT;
    scottX = 474;
    scottY = 700;
    scottT = 700;

    float bossX, bossY;
    bossX = 1498;
    bossY = 576;

    Card cards[4];
    EnemyCard enemyCards[4];
    MiniCard miniCards[4];
    Button buttons[3];
    CharacterCard characterCards[4];
    CharacterCard cardText[2];
    CharacterCard guia[0];
    Button power[2];

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

    power[0] = create_button("../src/assets/images/power.png", 60, 4, 640, 320, 720, 446);
    power[1] = create_button("../src/assets/images/attack.png", 7, 2, 298, 160, 860, 520);

    characterCards[0] = create_character_card("../src/assets/images/scott_perfil.png", 69, 97);
    characterCards[1] = create_character_card("../src/assets/images/matthew_perfil.png", 1473, 720);
    characterCards[2] = create_character_card("../src/assets/images/scott_mini.png", scottX, scottY);
    characterCards[3] = create_character_card("../src/assets/images/matthew_mini.png", bossX, bossY);

    cardText[0] = create_character_card("../src/assets/images/next_level.png", 650, 323);
    cardText[1] = create_character_card("../src/assets/images/repeat_level.png", 650, 323);

    guia[0] = create_character_card("../src/assets/images/guia.png", 0, 0);

    int resultadoFase[3] = {0, 3, 1};
    int respostaJogador[4];

    float x, y;
    x = 100;
    y = 100;

    bool resultado = false;
    bool continueAnimacaoScott = true;
    bool continueAnimacaoBoss = true;
    bool travaCompilar = true;

    int positionMiniCardX;
    positionMiniCardX = 614;

    int contMiniCard = 0;
    int animacao = 0;
    int animaboss = 0;

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
        al_play_sample_instance(music);

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                if (key[ALLEGRO_KEY_ESCAPE]) {
                }

                if (key[ALLEGRO_KEY_ENTER]) {
                    if (resultado && animaboss == 6) {
                        fase_dois_on = true;
                        done = true;
                        break;
                    }
                    if (!resultado && !travaCompilar) {
                        respostaJogador[0] = 0;
                        respostaJogador[1] = 0;
                        respostaJogador[2] = 0;
                        contMiniCard = 0;
                        positionMiniCardX = 614;

                        for (int i = 0; i < contMiniCard; i++) {
                            al_destroy_bitmap(miniCards[i].card);
                        }

                        interacaoButton = false;
                        travaCompilar = true;
                        break;
                    }
                }

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
                    bool mouseRangeGuia = buttons[2].buttonX && x >= buttons[2].buttonX && x <= (buttons[2].buttonX + buttons[2].frameWidth) && y >= buttons[2].buttonY && y <= (buttons[2].buttonY + buttons[2].frameHeight);

                    if (mouseRangeCompilar && interacaoButton && travaCompilar) {
                        resultado = respostaJogador[0] == resultadoFase[0] && respostaJogador[1] == resultadoFase[1] && respostaJogador[2] == resultadoFase[2];
                        interacaoButton = false;
                        travaCompilar = false;
                    }

                    if (mouseRangeResetar && interacaoButton && contMiniCard > 0) {
                        respostaJogador[0] = 0;
                        respostaJogador[1] = 0;
                        respostaJogador[2] = 0;
                        contMiniCard = 0;
                        positionMiniCardX = 614;

                        for (int i = 0; i < contMiniCard; i++) {
                            al_destroy_bitmap(miniCards[i].card);
                        }

                        interacaoButton = false;
                        break;
                    }

                    if (mouseRangeGuia && interacaoButton && !mostraGuia) {
                        mostraGuia = true;
                        interacaoButton = false;
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

                for (int i = 0; i < 2; i++) {
                    if (++power[i].frameCount >= power[i].frameDelay && animaboss == 3 || ++power[i].frameCount >= power[i].frameDelay && animaboss == 5) {
                        if (++power[i].currentFrame >= power[i].maxFrame)
                            power[i].currentFrame = 0;

                        power[i].frameCount = 0;
                    }
                }

                if (resultado && continueAnimacaoScott) {
                    if (animacao == 0) {
                        scottY -= 4;
                    } else if (animacao == 1) {
                        scottX += 4;
                    } else if (animacao == 2) {
                        scottY -= 6;
                    } else if (animacao == 3 && animaboss > 3) {
                        scottY += 4;
                    }
                }

                if (scottY < 700 - 128 && animacao == 0) {
                    animacao = 1;
                }

                if (scottX > 474 + 128 * 3 && animacao == 1) {
                    animacao = 2;
                }

                if (scottY < 700 - 124 * 2 && animacao == 2) {
                    animacao = 3;
                }

                if (animaboss == 3) {
                    scottT += 1;
                    if (scottT > 870) {
                        animaboss = 4;
                    }
                }

                if (animaboss == 5) {
                    scottT += 4;
                    if (scottT > 900) {
                        animaboss = 6;
                    }
                }

                if (scottY > 570 && animacao == 3) {
                    animacao = 4;
                }

                if (resultado && continueAnimacaoBoss) {
                    // fase_dois_on = true;
                    // done = true;
                    if (animaboss == 0) {
                        bossY -= 4;
                    } else if (animaboss == 1) {
                        bossX -= 4;
                    } else if (animaboss == 2) {
                        bossY += 4;
                    } else if (animaboss == 4) {
                        bossX -= 4;
                    }
                }

                if (bossY < 576 - 128 && animaboss == 0) {
                    animaboss = 1;
                }

                if (bossX < 1498 - 124 * 2 && animaboss == 1) {
                    animaboss = 2;
                }

                if (bossY > 576 && animaboss == 2) {
                    animaboss = 3;
                }

                if (bossX < 990 && animaboss == 4) {
                    continueAnimacaoBoss = false;
                    animaboss = 5;
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
                if (mostraGuia) {
                    mostraGuia = false;
                }

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
            }

            for (int i = 0; i < 2; i++) {
                al_draw_bitmap(characterCards[i].card, characterCards[i].cardX, characterCards[i].cardY, 0);
            }

            al_draw_bitmap(characterCards[2].card, scottX, scottY, 0);
            al_draw_bitmap(characterCards[3].card, bossX, bossY, 0);

            if (contMiniCard > 0) {
                for (int i = 0; i < contMiniCard; i++) {
                    al_draw_bitmap(miniCards[i].card, miniCards[i].cardX, miniCards[i].cardY, 0);
                }
            }

            for (int i = 0; i < 3; i++) {
                al_draw_bitmap_region(buttons[i].button, buttons[i].currentFrame * buttons[i].frameWidth, 0, buttons[i].frameWidth, buttons[i].frameHeight, buttons[i].buttonX, buttons[i].buttonY, 0);
            }

            if (animaboss == 3) {
                al_draw_bitmap_region(power[0].button, power[0].currentFrame * power[0].frameWidth, 0, power[0].frameWidth, power[0].frameHeight, power[0].buttonX, power[0].buttonY, 0);
            }

            if (animaboss == 5) {
                al_draw_bitmap_region(power[1].button, power[1].currentFrame * power[1].frameWidth, 0, power[1].frameWidth, power[1].frameHeight, power[1].buttonX, power[1].buttonY, 0);
            }

            if (resultado && animaboss == 6) {
                al_draw_bitmap(cardText[0].card, cardText[0].cardX, cardText[0].cardY, 0);
            }

              if (!resultado && !travaCompilar) {
                al_draw_bitmap(cardText[1].card, cardText[1].cardX, cardText[1].cardY, 0);
            }

            if(mostraGuia) {
            al_draw_bitmap(guia[0].card, guia[0].cardX, guia[0].cardY, 0);

            }

            al_draw_bitmap(cursor, x, y, 0);

            al_flip_display();

            redraw = false;
        }

        al_set_sample_instance_playing(music, 1);
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

    for (int i = 0; i < 2; i++) {
        al_destroy_bitmap(power[i].button);
        al_destroy_bitmap(cardText[i].card);
    }

    al_destroy_bitmap(bg);
    al_destroy_bitmap(labirinto);
    al_destroy_bitmap(painel);
    al_destroy_bitmap(cursor);

    al_destroy_sample_instance(music);

    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    if (fase_dois_on == true)
        fase2();
}

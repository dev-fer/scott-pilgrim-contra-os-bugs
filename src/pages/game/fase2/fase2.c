#include "fase2.h"

void fase2(void) {
    mathewfinal();
    lucasleeintro();

    initialize();

    f2_themebackground = al_load_sample("../src/assets/sounds/LucasLee.ogg");
    f2_music = al_create_sample_instance(f2_themebackground);
    al_attach_sample_instance_to_mixer(f2_music, al_get_default_mixer());

    f2_labirinto = al_load_bitmap("../src/assets/images/fase_dois.png");
    verifyAllegroFunction(f2_labirinto, "couldn't initialize labirinto");

    f2_cards[0] = create_card("../src/assets/images/correr_animacao.png", 21, 3, 247, 328, 16, 5, 35, 19, 440, 74, "../src/assets/images/minicard_correr.png");
    f2_cards[1] = create_card("../src/assets/images/atacar_animacao.png", 30, 3, 374, 438, 61, 116, 116, 19, 642, -36, "../src/assets/images/minicard_atacar.png");
    f2_cards[2] = create_card("../src/assets/images/defender_animacao.png", 28, 3, 205, 312, 3, 3, 5, 5, 947, 76, "../src/assets/images/minicard_defender.png");
    f2_cards[3] = create_card("../src/assets/images/esquivar_animacao.png", 19, 3, 208, 363, 4, 54, 7, 5, 1193, 25, "../src/assets/images/minicard_esquivar.png");

    f2_enemyCards[0] = create_enemy_card("../src/assets/images/card_shoot_inimigo.png", 639, 824);
    f2_enemyCards[1] = create_enemy_card("../src/assets/images/card_run_inimigo.png", 829, 824);
    f2_enemyCards[2] = create_enemy_card("../src/assets/images/card_atk_inimigo.png", 1025, 824);
    f2_enemyCards[3] = create_enemy_card("../src/assets/images/card_empty_inimigo.png", 1214, 824);

    f2_buttons[0] = create_button("../src/assets/images/compilar.png", 8, 2, 49, 51, 105, 951);
    f2_buttons[1] = create_button("../src/assets/images/reset.png", 8, 2, 49, 51, 164, 951);
    f2_buttons[2] = create_button("../src/assets/images/dica.png", 8, 2, 49, 51, 223, 951);

    f2_power[0] = create_button("../src/assets/images/power.png", 60, 4, 640, 320, 514, 526);
    f2_power[1] = create_button("../src/assets/images/attack.png", 7, 3, 298, 160, 860, 520);
    f2_power[2] = create_button("../src/assets/images/shield.png", 11, 3, 249, 274, 860, 420);

    f2_characterCards[0] = create_character_card("../src/assets/images/scott_perfil.png", 69, 97);
    f2_characterCards[1] = create_character_card("../src/assets/images/lucaslee_perfil.png", 1473, 720);
    f2_characterCards[2] = create_character_card("../src/assets/images/scott_mini.png", f2_scottX, f2_scottY);
    f2_characterCards[3] = create_character_card("../src/assets/images/lucaslee_mini.png", f2_bossX, f2_bossY);

    f2_cardText[0] = create_character_card("../src/assets/images/next_level.png", 650, 323);
    f2_cardText[1] = create_character_card("../src/assets/images/repeat_level.png", 650, 323);

    f2_guia[0] = create_character_card("../src/assets/images/guia.png", 0, 0);

    f2_pause[0] = create_character_card("../src/assets/images/pause_continuar.png", 0, 0);
    f2_pause[1] = create_character_card("../src/assets/images/pause_menu.png", 0, 0);

#define KEY_SEEN 1
#define KEY_RELEASED 2

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    al_start_timer(timer);

    while (!f2_done) {
        al_wait_for_event(queue, &f2_event);
        al_play_sample_instance(f2_music);

        switch (f2_event.type) {
            case ALLEGRO_EVENT_TIMER:
                if (key[ALLEGRO_KEY_ESCAPE]) {
                    if (!f2_mostraPause) {
                        f2_mostraPause = true;
                    }
                }
                if (key[ALLEGRO_KEY_DOWN]) {
                    if (f2_mostraPause && !f2_pauseMenu) {
                        f2_pauseMenu = true;
                        f2_pauseContinuar = false;
                    }
                }
                if (key[ALLEGRO_KEY_UP]) {
                    if (f2_mostraPause && !f2_pauseContinuar) {
                        f2_pauseContinuar = true;
                        f2_pauseMenu = false;
                    }
                }

                if (key[ALLEGRO_KEY_ENTER]) {
                    if (f2_mostraPause && f2_pauseContinuar) {
                        f2_mostraPause = false;
                        break;
                    }
                    if (f2_mostraPause && f2_pauseMenu) {
                        f2_mostraPause = false;
                        f2_pauseMenu = false;
                        f2_pauseContinuar = true;
                        f2_done = true;
                        f2_menu_on = true;
                        break;
                    }

                    if (f2_resultado && f2_contAnimacaoEnemy == 6) {
                        fase_tres_on = true;
                        f2_done = true;
                        break;
                    }
                    if (!f2_resultado && !f2_travaCompilar) {
                        f2_respostaJogador[0] = 0;
                        f2_respostaJogador[1] = 0;
                        f2_respostaJogador[2] = 0;
                        f2_respostaJogador[3] = 0;
                        f2_contMiniCard = 0;
                        f2_positionMiniCardX = 614;

                        for (int i = 0; i < f2_contMiniCard; i++) {
                            al_destroy_bitmap(f2_miniCards[i].card);
                        }

                        f2_interacaoButton = false;
                        f2_travaCompilar = true;
                        break;
                    }
                }

                f2_mouseMove();

                for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;

                for (int i = 0; i < 4; i++) {
                    if (i < 3) {
                        f2_mouseRangeButtons(i);
                        f2_powerFrames(i);
                    }
                    f2_mouseRangeCards(i);
                }

                f2_animationsResult();

                f2_redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                f2_dx += f2_event.mouse.dx * 0.1;
                f2_dy += f2_event.mouse.dy * 0.1;
                al_set_mouse_xy(display, 320, 240);
                break;

                bool mouseRangeCard = false;
                bool mouseRangeButton = false;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                for (int i = 0; i < 4; i++) {
                    bool resultRangeCard = f2_mouseRangeUpCard(i);
                    if (!resultRangeCard) {
                        break;
                    }

                    if (i < 3) {
                        bool resultRangeButton = f2_mouseRangeUpButton(i);
                        if (!resultRangeButton) {
                            break;
                        }
                    }
                }
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[f2_event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                key[f2_event.keyboard.keycode] &= KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                f2_done = true;
                break;
        }

        if (f2_done)
            break;

        if (f2_redraw && al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap(bg, 0, 0, 0);
            al_draw_filled_rectangle(639, 920, 1224, 926, al_map_rgb(237, 133, 71));

            al_draw_bitmap(f2_labirinto, 580, 490, 0);
            al_draw_bitmap(painel, 75, 938, 0);

            for (int i = 0; i < 4; i++) {
                if (i < 3) {
                    al_draw_bitmap_region(f2_buttons[i].button, f2_buttons[i].currentFrame * f2_buttons[i].frameWidth, 0, f2_buttons[i].frameWidth, f2_buttons[i].frameHeight, f2_buttons[i].buttonX, f2_buttons[i].buttonY, 0);
                }

                if (i < 2) {
                    al_draw_bitmap(f2_characterCards[i].card, f2_characterCards[i].cardX, f2_characterCards[i].cardY, 0);
                }

                al_draw_bitmap_region(f2_cards[i].card, f2_cards[i].currentFrame * f2_cards[i].frameWidth, 0, f2_cards[i].frameWidth, f2_cards[i].frameHeight, f2_cards[i].cardX, f2_cards[i].cardY, 0);
                al_draw_bitmap(f2_enemyCards[i].card, f2_enemyCards[i].cardX, f2_enemyCards[i].cardY, 0);
            }

            al_draw_bitmap(f2_characterCards[2].card, f2_scottX, f2_scottY, 0);
            al_draw_bitmap(f2_characterCards[3].card, f2_bossX, f2_bossY, 0);

            if (f2_contMiniCard > 0) {
                for (int i = 0; i < f2_contMiniCard; i++) {
                    al_draw_bitmap(f2_miniCards[i].card, f2_miniCards[i].cardX, f2_miniCards[i].cardY, 0);
                }
            }

            if (f2_contAnimacaoEnemy == 0 && f2_resultado) {
                al_draw_bitmap_region(f2_power[0].button, f2_power[0].currentFrame * f2_power[0].frameWidth, 0, f2_power[0].frameWidth, f2_power[0].frameHeight, f2_power[0].buttonX, f2_power[0].buttonY, 0);
            }

            if (f2_contAnimacaoEnemy == 4 && f2_resultado) {
                al_draw_bitmap_region(f2_power[2].button, f2_power[2].currentFrame * f2_power[2].frameWidth, 0, f2_power[2].frameWidth, f2_power[2].frameHeight, f2_power[2].buttonX, f2_power[2].buttonY, 0);
            }

            if (f2_contAnimacaoEnemy == 5) {
                al_draw_bitmap_region(f2_power[1].button, f2_power[1].currentFrame * f2_power[1].frameWidth, 0, f2_power[1].frameWidth, f2_power[1].frameHeight, f2_power[1].buttonX, f2_power[1].buttonY, 0);
            }

            if (f2_resultado && f2_contAnimacaoEnemy == 6) {
                al_draw_bitmap(f2_cardText[0].card, f2_cardText[0].cardX, f2_cardText[0].cardY, 0);
            }

            if (!f2_resultado && !f2_travaCompilar) {
                al_draw_bitmap(f2_cardText[1].card, f2_cardText[1].cardX, f2_cardText[1].cardY, 0);
            }

            if (f2_mostraGuia) {
                al_draw_bitmap(f2_guia[0].card, f2_guia[0].cardX, f2_guia[0].cardY, 0);
            }

            if (f2_mostraPause && f2_pauseContinuar) {
                al_draw_bitmap(f2_pause[0].card, f2_pause[0].cardX, f2_pause[0].cardY, 0);
            } else if (f2_mostraPause && f2_pauseMenu) {
                al_draw_bitmap(f2_pause[1].card, f2_pause[1].cardX, f2_pause[1].cardY, 0);
            }

            al_draw_bitmap(cursor, f2_x, f2_y, 0);

            al_flip_display();

            f2_redraw = false;
        }
        al_set_sample_instance_playing(f2_music, 1);
    }
    f2_destroyFase();
}

void f2_mouseMove(void) {
    f2_x += f2_dx;
    f2_y += f2_dy;

    if (f2_x < 0) {
        f2_x *= -1;
        f2_dx *= -1;
    }
    if (f2_x > width_display) {
        f2_x -= (f2_x - width_display) * 2;
        f2_dx *= -1;
    }
    if (f2_y < 0) {
        f2_y *= -1;
        f2_dy *= -1;
    }
    if (f2_y > height_display) {
        f2_y -= (f2_y - height_display) * 2;
        f2_dy *= -1;
    }

    f2_dx *= 0.9;
    f2_dy *= 0.9;
}

void f2_mouseRangeCards(int i) {
    f2_mouseRangeCard = f2_x >= f2_cards[i].cardX && f2_x >= (f2_cards[i].cardX + f2_cards[i].frameStartWidth) && f2_x <= (f2_cards[i].cardX + f2_cards[i].frameWidth - f2_cards[i].frameFinishWidth) && f2_y >= (f2_cards[i].cardY + f2_cards[i].frameStartHeight) && f2_y <= (f2_cards[i].cardY + f2_cards[i].frameHeight - f2_cards[i].frameFinishHeight);

    if (f2_mouseRangeCard && f2_interacaoCard) {
        if (f2_contMiniCard < 4) {
            f2_miniCards[f2_contMiniCard] = create_mini_card(f2_cards[i].urlMiniCard, f2_positionMiniCardX, 800);
            f2_respostaJogador[f2_contMiniCard] = i;
            f2_positionMiniCardX += 192;
            f2_contMiniCard++;
        }
        f2_interacaoCard = false;
    }

    if (f2_mouseRangeCard) {
        if (++f2_cards[i].frameCount >= f2_cards[i].frameDelay) {
            if (++f2_cards[i].currentFrame >= f2_cards[i].maxFrame)
                f2_cards[i].currentFrame = 0;

            f2_cards[i].frameCount = 0;
        }
    } else {
        f2_cards[i].currentFrame = 0;
        f2_cards[i].frameCount = 0;
    }
}

void f2_mouseRangeButtons(int i) {
    f2_mouseRangeButton = f2_x >= f2_buttons[i].buttonX && f2_x >= f2_buttons[i].buttonX && f2_x <= (f2_buttons[i].buttonX + f2_buttons[i].frameWidth) && f2_y >= f2_buttons[i].buttonY && f2_y <= (f2_buttons[i].buttonY + f2_buttons[i].frameHeight);
    bool mouseRangeCompilar = f2_buttons[0].buttonX && f2_x >= f2_buttons[0].buttonX && f2_x <= (f2_buttons[0].buttonX + f2_buttons[0].frameWidth) && f2_y >= f2_buttons[0].buttonY && f2_y <= (f2_buttons[0].buttonY + f2_buttons[0].frameHeight);
    bool mouseRangeResetar = f2_buttons[1].buttonX && f2_x >= f2_buttons[1].buttonX && f2_x <= (f2_buttons[1].buttonX + f2_buttons[1].frameWidth) && f2_y >= f2_buttons[1].buttonY && f2_y <= (f2_buttons[1].buttonY + f2_buttons[1].frameHeight);
    bool mouseRangeGuia = f2_buttons[2].buttonX && f2_x >= f2_buttons[2].buttonX && f2_x <= (f2_buttons[2].buttonX + f2_buttons[2].frameWidth) && f2_y >= f2_buttons[2].buttonY && f2_y <= (f2_buttons[2].buttonY + f2_buttons[2].frameHeight);

    if (mouseRangeCompilar && f2_interacaoButton && f2_travaCompilar) {
        f2_resultado = f2_respostaJogador[0] == f2_resultadoFase[0] && f2_respostaJogador[1] == f2_resultadoFase[1] && f2_respostaJogador[2] == f2_resultadoFase[2];
        f2_interacaoButton = false;
        f2_travaCompilar = false;
    }

    if (mouseRangeResetar && f2_interacaoButton && f2_contMiniCard > 0 && f2_travaResetar) {
        f2_respostaJogador[0] = 0;
        f2_respostaJogador[1] = 0;
        f2_respostaJogador[2] = 0;
        f2_respostaJogador[3] = 0;
        f2_positionMiniCardX = 614;

        for (int i = 0; i < f2_contMiniCard; i++) {
            al_destroy_bitmap(f2_miniCards[i].card);
        }

        f2_contMiniCard = 0;
        f2_interacaoButton = false;
        f2_travaResetar = false;
    }

    if (mouseRangeGuia && f2_interacaoButton && !f2_mostraGuia) {
        f2_interacaoButton = false;
        f2_mostraGuia = true;
    }

    if (f2_mouseRangeButton) {
        if (++f2_buttons[i].frameCount >= f2_buttons[i].frameDelay) {
            if (++f2_buttons[i].currentFrame >= f2_buttons[i].maxFrame)
                f2_buttons[i].currentFrame = 0;

            f2_buttons[i].frameCount = 0;
        }
    } else {
        f2_buttons[i].currentFrame = 0;
        f2_buttons[i].frameCount = 0;
    }
}

void f2_powerFrames(int i) {
    if (++f2_power[i].frameCount >= f2_power[i].frameDelay && f2_contAnimacaoEnemy == 0 && f2_resultado || ++f2_power[i].frameCount >= f2_power[i].frameDelay && f2_contAnimacaoEnemy == 4 && f2_resultado || ++f2_power[i].frameCount >= f2_power[i].frameDelay && f2_contAnimacaoEnemy == 5 && f2_resultado) {
        if (++f2_power[i].currentFrame >= f2_power[i].maxFrame)
            f2_power[i].currentFrame = 0;

        f2_power[i].frameCount = 0;
    }
}

bool f2_mouseRangeUpCard(int i) {
    f2_mouseRangeCard = f2_x >= f2_cards[i].cardX && f2_x >= (f2_cards[i].cardX + f2_cards[i].frameStartWidth) && f2_x <= (f2_cards[i].cardX + f2_cards[i].frameWidth - f2_cards[i].frameFinishWidth) && f2_y >= (f2_cards[i].cardY + f2_cards[i].frameStartHeight) && f2_y <= (f2_cards[i].cardY + f2_cards[i].frameHeight - f2_cards[i].frameFinishHeight);

    if (f2_mouseRangeCard) {
        f2_interacaoCard = true;
        f2_travaResetar = true;
        return false;
    }
    return true;
}

bool f2_mouseRangeUpButton(int i) {
    f2_mouseRangeButton = f2_x >= f2_buttons[i].buttonX && f2_x >= f2_buttons[i].buttonX && f2_x <= (f2_buttons[i].buttonX + f2_buttons[i].frameWidth) && f2_y >= f2_buttons[i].buttonY && f2_y <= (f2_buttons[i].buttonY + f2_buttons[i].frameHeight);

    if (f2_mostraGuia) {
        f2_mostraGuia = false;
    }

    if (f2_mouseRangeButton) {
        f2_interacaoButton = true;
        return false;
    }
    return true;
}

void f2_animationsResult(void) {
    if (f2_resultado && f2_continueAnimacaoScott) {
        if (f2_contAnimacaoScott == 0) {
            f2_scottY -= 4;
        } else if (f2_contAnimacaoScott == 1 && f2_contAnimacaoEnemy == 1) {
            f2_scottY += 4;
        } else if (f2_contAnimacaoScott == 2) {
            f2_scottX += 4;
        } else if (f2_contAnimacaoScott == 3) {
            f2_scottY -= 4;
        } else if (f2_contAnimacaoScott == 4) {
            f2_scottX += 4;
        }
    }

    if (f2_scottY < 628 - 128 && f2_contAnimacaoScott == 0) {
        f2_contAnimacaoScott = 1;
    }

    if (f2_scottY > 628 && f2_contAnimacaoScott == 1) {
        f2_contAnimacaoScott = 2;
    }

    if (f2_scottX > 596 + 128 * 2 && f2_contAnimacaoScott == 2) {
        f2_contAnimacaoScott = 3;
    }

    if (f2_scottY < 628 - 128 && f2_contAnimacaoScott == 3) {
        f2_contAnimacaoScott = 4;
    }

    if (f2_scottX > 596 + 128 * 3 && f2_contAnimacaoScott == 4) {
        f2_continueAnimacaoScott = false;
        f2_contAnimacaoScott = 5;
    }

    if (f2_contAnimacaoEnemy == 0 && f2_resultado) {
        f2_awaitAnimation += 1;
        if (f2_awaitAnimation > 100) {
            f2_contAnimacaoEnemy = 1;
        }
    }

    if (f2_contAnimacaoEnemy == 3 && f2_resultado) {
        f2_awaitAnimation += 3;
        if (f2_awaitAnimation > 330) {
            f2_contAnimacaoEnemy = 4;
        }
    }

    if (f2_contAnimacaoEnemy == 4 && f2_resultado) {
        f2_awaitAnimation += 3;
        if (f2_awaitAnimation > 400) {
            f2_contAnimacaoEnemy = 5;
        }
    }

    if (f2_contAnimacaoEnemy == 5) {
        f2_awaitAnimation += 4;
        if (f2_awaitAnimation > 460) {
            f2_contAnimacaoEnemy = 6;
        }
    }

    if (f2_resultado && f2_continueAnimacaoBoss) {
        if (f2_contAnimacaoEnemy == 1) {
            f2_bossX -= 4;
        }
        if (f2_contAnimacaoEnemy == 2) {
            f2_bossY -= 4;
        }
    }

    if (f2_bossX < 1104 - 124 * 2 && f2_contAnimacaoEnemy == 1) {
        f2_contAnimacaoEnemy = 2;
    }

    if (f2_bossY < 626 - 124 && f2_contAnimacaoEnemy == 2) {
        f2_continueAnimacaoBoss = false;
        f2_contAnimacaoEnemy = 3;
    }
}

void f2_destroyFase(void) {
    for (int i = 0; i < 4; i++) {
        if (i < 3) {
            al_destroy_bitmap(f2_buttons[i].button);
            al_destroy_bitmap(f2_power[i].button);
        }

        if (i < 2) {
            al_destroy_bitmap(f2_cardText[i].card);
        }

        al_destroy_bitmap(f2_cards[i].card);
        al_destroy_bitmap(f2_enemyCards[i].card);
        al_destroy_bitmap(f2_characterCards[i].card);
    }

    if (f2_contMiniCard > 0) {
        for (int i = 0; i < f2_contMiniCard; i++) {
            al_destroy_bitmap(f2_miniCards[i].card);
        }
    }

    al_destroy_bitmap(bg);
    al_destroy_bitmap(f2_labirinto);
    al_destroy_bitmap(painel);
    al_destroy_bitmap(cursor);
    al_destroy_bitmap(f2_guia[0].card);

    al_destroy_sample_instance(f2_music);

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    if (fase_tres_on == true) {
        lucasleefinal();
        final();
        menu();
    }
    if (f2_menu_on == true) {
        menu();
    }
}

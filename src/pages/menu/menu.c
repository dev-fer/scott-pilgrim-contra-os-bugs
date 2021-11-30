
#include "../../headers.h"
int color[] = {255, 255, 255};

void menu(void)
{
    int r[] = {255, 255, 255, 255, 255, 255}, g[] = {255, 255, 255, 255, 255, 255}, b[] = {255, 255, 255, 255, 255, 255};
    bool done = false;
    bool game_on = false;
    bool settings_on = false;

    int att_count = 0;
    int cord_cursor_x = 0;
    int cord_cursor_y = ((height_display / 2) - 4) + 30;

    ALLEGRO_BITMAP *cursor = al_load_bitmap("../src/assets/images/Cursor_small.png");
    ALLEGRO_BITMAP *menu_background = al_load_bitmap("../src/assets/images/background.jpg");
    ALLEGRO_BITMAP *scott_background = al_load_bitmap("../src/assets/images/scott_pilgrim_wp_1.png");
    ALLEGRO_FONT *menu_item = al_load_ttf_font("../src/assets/fonts/joystix.ttf", 24, 0);
    ALLEGRO_FONT *credit = al_load_ttf_font("../src/assets/fonts/joystix.ttf", 12, 0);
    ALLEGRO_BITMAP *logo = al_load_bitmap("../src/assets/images/logotipo.png");
    ALLEGRO_SAMPLE *click = al_load_sample("../src/assets/sounds/Click.ogg");
    ALLEGRO_SAMPLE *swish = al_load_sample("../src/assets/sounds/Swish.ogg");
    ALLEGRO_SAMPLE *themebackground = al_load_sample("../src/assets/sounds/theme_background.ogg");
    ALLEGRO_SAMPLE_INSTANCE *music = al_create_sample_instance(themebackground);
    al_attach_sample_instance_to_mixer(music, al_get_default_mixer());
    ALLEGRO_EVENT_QUEUE *menu_event_queue = al_create_event_queue();

    al_reserve_samples(1);

    al_register_event_source(menu_event_queue, al_get_keyboard_event_source());

    while (!done)
    {
        // posicao do cursor de menu
        if (cord_cursor_y == ((height_display / 2) - 4) + 30)
            color_press(r, g, b, 0, 4);
        if (cord_cursor_y == ((height_display / 2) - 4) + 60)
            color_press(r, g, b, 1, 4);
        if (cord_cursor_y == ((height_display / 2) - 4) + 90)
            color_press(r, g, b, 2, 4);
        if (cord_cursor_y == ((height_display / 2) - 4) + 120)
            color_press(r, g, b, 3, 4);

        // desenhando formas na tela
        al_draw_scaled_bitmap(menu_background, 0, 0, al_get_bitmap_width(menu_background), al_get_bitmap_height(menu_background), 0, 0, width_display, height_display, 0);
        al_draw_bitmap(cursor, cord_cursor_x, cord_cursor_y, 0);
        al_draw_bitmap(scott_background, -30, 280, 0);
        al_draw_scaled_bitmap(logo, 0, 0, al_get_bitmap_width(logo), al_get_bitmap_height(logo), width_display / 4, 0, width_display - (width_display / 2), height_display - (height_display / 2), 0);
        al_draw_text(menu_item, al_map_rgb(r[0], g[0], b[0]), width_display / 2, (height_display / 2) + 30, ALLEGRO_ALIGN_CENTRE, "NOVO JOGO");
        al_draw_text(menu_item, al_map_rgb(r[1], g[1], b[1]), width_display / 2, (height_display / 2) + 60, ALLEGRO_ALIGN_CENTRE, "CONTINUAR");
        al_draw_text(menu_item, al_map_rgb(r[2], g[2], b[2]), width_display / 2, (height_display / 2) + 90, ALLEGRO_ALIGN_CENTRE, "CONFIGURAÇÕES");
        al_draw_text(menu_item, al_map_rgb(r[3], g[3], b[3]), width_display / 2, (height_display / 2) + 120, ALLEGRO_ALIGN_CENTRE, "SAIR");
        al_draw_text(credit, al_map_rgb(color[0], color[1], color[2]), (width_display / 2) + 280, height_display - 20, ALLEGRO_ALIGN_LEFT, "DESENVOLVIDO POR FELIPE FERNANDES - PROJETO INTEGRADOR SENAC 2021");

        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_play_sample_instance(music);

        ALLEGRO_EVENT menu_ev;
        al_wait_for_event(menu_event_queue, &menu_ev);
        if (menu_ev.type == ALLEGRO_EVENT_KEY_DOWN)

        {
            switch (menu_ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
                al_stop_samples();
                al_play_sample(click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                if (cord_cursor_y > ((height_display / 2) - 4) + 30)
                    cord_cursor_y -= 30;
                break;
            case ALLEGRO_KEY_DOWN:
                al_stop_samples();
                al_play_sample(click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                if (cord_cursor_y < ((height_display / 2) - 4) + 120)
                    cord_cursor_y += 30;
                break;
            case ALLEGRO_KEY_ENTER:
                al_stop_samples();
                al_play_sample(click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                if (cord_cursor_y == ((height_display / 2) - 4) + 30)
                {
                    // fading da tela
                    al_stop_samples();
                    al_play_sample(swish, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                    al_rest(0.4);
                    // startar game
                    done = true;
                    game_on = true;
                    att_count = 1;
                }
                else if (cord_cursor_y == ((height_display / 2) - 4) + 90)
                {
                    // configuracao
                    settings_on = true;
                    done = true;
                    cord_cursor_x = (width_display / 2) - 120;
                    cord_cursor_y = ((height_display / 2) - 4) + 30;
                }
                else if (cord_cursor_y == ((height_display / 2) - 4) + 120)
                {
                    done = true;
                }
                break;
            case ALLEGRO_KEY_ESCAPE:
            {
                al_stop_samples();
                al_play_sample(click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                done = true;
                break;
            }
            }
        }

       al_set_sample_instance_playing(music, 1);
    }

    // destruindo objetos
    al_destroy_font(menu_item);
    al_destroy_font(credit);
    al_destroy_bitmap(menu_background);
    al_destroy_bitmap(scott_background);
    al_destroy_bitmap(cursor);
    al_destroy_bitmap(logo);
    al_destroy_event_queue(menu_event_queue);
    al_destroy_sample(click);
    al_destroy_sample(swish);
    al_destroy_sample_instance(music);
    if (game_on == true)
        fase1();
    if (settings_on == true)
        settings(&cord_cursor_x, &cord_cursor_y);
}

// setar cor dos botões de menu quando selecionado
void color_press(int *r, int *g, int *b, int selection, int max)
{
    for (int i = 0; i < max; ++i)
    {
        r[i] = color[0];
        g[i] = color[1];
        b[i] = color[2];
    }
    r[selection] = 204;
    g[selection] = 41;
    b[selection] = 94;
}

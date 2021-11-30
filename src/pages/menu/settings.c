#include "../../headers.h"

void settings(int *cord_cursor_x, int *cord_cursor_y) {
    int r[] = {255, 255, 255, 255, 255, 255}, g[] = {255, 255, 255, 255, 255, 255}, b[] = {255, 255, 255, 255, 255, 255};  // colors of pressed buttons
    bool menu_on = false;
    bool done = false;
    ALLEGRO_MONITOR_INFO info;
    ALLEGRO_BITMAP *cursor = al_load_bitmap("../src/assets/images/Cursor_small.png");
    ALLEGRO_BITMAP *menu_background = al_load_bitmap("../src/assets/images/background.jpg");
    ALLEGRO_FONT *menu_item = al_load_ttf_font("../src/assets/fonts/joystix.ttf", 18, 0);
    ALLEGRO_SAMPLE *click = al_load_sample("../src/assets/sounds/Click.ogg");
    ALLEGRO_EVENT_QUEUE *menu_event_queue = al_create_event_queue();
    ALLEGRO_FONT *settings_item = al_load_ttf_font("../src/assets/fonts/joystix.ttf", 24, 0);
    ALLEGRO_FONT *escape = al_load_ttf_font("../src/assets/fonts/joystix.ttf", 12, 0);

    *cord_cursor_x = (width_display / 2) - 120;
    *cord_cursor_y = ((height_display / 2) - 4) + 30;

    al_register_event_source(menu_event_queue, al_get_keyboard_event_source());

    while (!done) {
        // posicao do cursor de menu
        if (*cord_cursor_y == ((height_display / 2) - 4) + 30)
            color_press(r, g, b, 0, 4);
        else if (*cord_cursor_y == ((height_display / 2) - 4) + 60)
            color_press(r, g, b, 1, 4);
        // else if (*cord_cursor_y == ((height_display / 2) - 4) + 90)
        //     color_press(r, g, b, 2, 4);
        // else if (*cord_cursor_y == ((height_display / 2) - 4) + 120)
        //     color_press(r, g, b, 3, 4);

        // desenhando formas na tela
        al_draw_scaled_bitmap(menu_background, 0, 0, al_get_bitmap_width(menu_background), al_get_bitmap_height(menu_background), 0, 0, width_display, height_display, 0);
        al_draw_bitmap(cursor, 0, *cord_cursor_y, 0);
        al_draw_bitmap(cursor, 0, height_display - 30, ALLEGRO_FLIP_HORIZONTAL);
        al_draw_text(settings_item, al_map_rgb(r[0], g[0], b[0]), width_display / 2, (height_display / 2) + 30, ALLEGRO_ALIGN_CENTRE, "FULLSCREEN");
        al_draw_text(settings_item, al_map_rgb(r[1], g[1], b[1]), width_display / 2, (height_display / 2) + 60, ALLEGRO_ALIGN_CENTRE, "1920x1080");
        // al_draw_text(settings_item, al_map_rgb(r[1], g[1], b[1]), width_display / 2, (height_display / 2) + 60, ALLEGRO_ALIGN_CENTRE, "800x600");
        // al_draw_text(settings_item, al_map_rgb(r[2], g[2], b[2]), width_display / 2, (height_display / 2) + 90, ALLEGRO_ALIGN_CENTRE, "1280x720");
        // al_draw_text(settings_item, al_map_rgb(r[3], g[3], b[3]), width_display / 2, (height_display / 2) + 120, ALLEGRO_ALIGN_CENTRE, "1920x1080");
        al_draw_text(escape, al_map_rgb(color[0], color[1], color[2]), 30, height_display - 25, ALLEGRO_ALIGN_LEFT, "PRESSIONE ESC PARA VOLTAR AO MENU");
        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));

        ALLEGRO_EVENT settings_ev;
        al_wait_for_event(menu_event_queue, &settings_ev);

        if (settings_ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (settings_ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    al_stop_samples();
                    al_play_sample(click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                    if (*cord_cursor_y > ((height_display / 2) - 4) + 30)
                        *cord_cursor_y -= 30;
                    break;
                case ALLEGRO_KEY_DOWN:
                    al_stop_samples();
                    (click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                    if (*cord_cursor_y < ((height_display / 2) - 4) + 60)
                        *cord_cursor_y += 30;
                    break;
                case ALLEGRO_KEY_ENTER:
                    al_stop_samples();
                    al_play_sample(click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                    if (*cord_cursor_y == ((height_display / 2) - 4) + 30) {
                        // opcao 1
                        al_get_monitor_info(0, &info);
                        width_display = info.x2 - info.x1;
                        height_display = info.y2 - info.y1;
                        *cord_cursor_x = (width_display / 2) - 120;
                        *cord_cursor_y = ((height_display / 2) - 4) + 30;
                        al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, 1);
                    } else if (*cord_cursor_y == ((height_display / 2) - 4) + 60) {
                        // opcao 4
                        al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, 0);
                        width_display = 1920;
                        height_display = 1080;
                        *cord_cursor_x = (width_display / 2) - 120;
                        *cord_cursor_y = ((height_display / 2) - 4) + 30;
                        al_resize_display(display, width_display, height_display);
                        al_set_window_position(display, 0, 0);
                    }
                    // else if (*cord_cursor_y == ((height_display / 2) - 4) + 60)
                    // {
                    //     //opcao 2
                    //     al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, 0);
                    //     width_display = 800;
                    //     height_display = 600;
                    //     *cord_cursor_x = (width_display / 2) - 120;
                    //     *cord_cursor_y = ((height_display / 2) - 4) + 30;
                    //     al_resize_display(display, width_display, height_display);
                    //     al_set_window_position(display, 0, 0);
                    // }
                    // else if (*cord_cursor_y == ((height_display / 2) - 4) + 90)
                    // {
                    //     //opcao 3
                    //     al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, 0);
                    //     width_display = 1280;
                    //     height_display = 720;
                    //     *cord_cursor_x = (width_display / 2) - 120;
                    //     *cord_cursor_y = ((height_display / 2) - 4) + 30;
                    //     al_resize_display(display, width_display, height_display);
                    //     al_set_window_position(display, 0, 0);
                    // }
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    al_stop_samples();
                    al_play_sample(click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                    menu_on = true;
                    done = true;
                    break;
            }
        }
    }
    al_destroy_font(menu_item);
    al_destroy_bitmap(menu_background);
    al_destroy_bitmap(cursor);
    al_destroy_event_queue(menu_event_queue);
    al_destroy_sample(click);
    al_destroy_font(settings_item);
    al_destroy_font(escape);
    if (menu_on)
        return menu();
}

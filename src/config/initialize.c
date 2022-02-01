#include "../headers.h"

ALLEGRO_TIMER *timer = NULL;
ALLEGRO_EVENT_QUEUE *queue = NULL;
ALLEGRO_FONT *botao = NULL;
ALLEGRO_BITMAP *bg = NULL;
ALLEGRO_BITMAP *painel = NULL;
ALLEGRO_BITMAP *cursor = NULL;

void initialize(void) {
    verifyAllegroFunction(al_init(), "allegro");
    verifyAllegroFunction(al_install_keyboard(), "keyboard");
    verifyAllegroFunction(al_install_mouse(), "mouse");
    verifyAllegroFunction(al_init_image_addon(), "image addon");

    timer = al_create_timer(1.0 / 30.0);
    verifyAllegroFunction(timer, "timer");

    queue = al_create_event_queue();
    verifyAllegroFunction(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    bg = al_load_bitmap("../src/assets/images/bg.jpg");
    verifyAllegroFunction(bg, "couldn't initialize bg");

    painel = al_load_bitmap("../src/assets/images/painel.png");
    verifyAllegroFunction(painel, "couldn't initialize painel");

    cursor = al_load_bitmap("../src/assets/images/cursor.png");
    verifyAllegroFunction(cursor, "couldn't initialize cursor");

    verifyAllegroFunction(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_hide_mouse_cursor(display);
    al_grab_mouse(display);
}


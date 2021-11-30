#include "../../headers.h"

void end(void) {
    verifyAllegroFunction(al_init(), "allegro");
    verifyAllegroFunction(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
    verifyAllegroFunction(timer, "timer");

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    verifyAllegroFunction(queue, "queue");

    bool segunda_on = false;

    verifyAllegroFunction(al_init_image_addon(), "couldn't initialize image addon");
    ALLEGRO_BITMAP *cena = al_load_bitmap("../src/assets/images/end.png");

    verifyAllegroFunction(cena, "couldn't initialize player");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    bool active = true;

    ALLEGRO_EVENT event;

    float x, y;
    x = 100;
    y = 100;

    int sourceX, sourceY;
    sourceX = 0;
    sourceY = 0;

    al_start_timer(timer);

    while (!done) {
        al_wait_for_event(queue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                if (active) {
                    sourceX += al_get_bitmap_width(cena) / 29;
                } else {
                    sourceX = 640;
                }

                if (sourceX >= al_get_bitmap_width(cena)) {
                    sourceX = 0;
                }
                redraw = true;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap_region(cena, sourceX, sourceY, 640, 360, x, y, 0);

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(cena);
    if (segunda_on == true)
        fase1();
}

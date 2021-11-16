#include "../../headers.h"

void venceu(void)
{
    verifyAllegroFunction(al_init(), "allegro");
    verifyAllegroFunction(al_install_keyboard(), "keyboard");
    verifyAllegroFunction(al_install_mouse(), "mouse");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    verifyAllegroFunction(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    verifyAllegroFunction(queue, "queue");

    ALLEGRO_MOUSE_STATE state;

    bool venceu = false;

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_FONT* font = al_create_builtin_font();
    verifyAllegroFunction(font, "font");

    ALLEGRO_FONT *botao = al_load_ttf_font("../src/assets/fonts/joystix.ttf", 30, 0);

    verifyAllegroFunction(al_init_image_addon(), "couldn't initialize image addon");
    ALLEGRO_BITMAP *player = al_load_bitmap("../src/assets/images/player.png");
    ALLEGRO_BITMAP *cena = al_load_bitmap("../src/assets/images/venceu.jpg");
    ALLEGRO_BITMAP *atacar = al_load_bitmap("../src/assets/images/atacar.png");
    ALLEGRO_BITMAP *defender = al_load_bitmap("../src/assets/images/defender.png");
    ALLEGRO_BITMAP *correr = al_load_bitmap("../src/assets/images/correr.png");
    ALLEGRO_BITMAP *caixa = al_load_bitmap("../src/assets/images/caixa.png");
    ALLEGRO_BITMAP *compilar = al_load_bitmap("../src/assets/images/compilar.png");

    verifyAllegroFunction(player, "couldn't initialize player");
    verifyAllegroFunction(cena, "couldn't initialize player");
    verifyAllegroFunction(atacar, "couldn't initialize player");
    verifyAllegroFunction(defender, "couldn't initialize player");
    verifyAllegroFunction(correr, "couldn't initialize player");

    verifyAllegroFunction(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    bool active = false;
    bool interatividadeAtacar = true;
    bool interatividadeDefender = true;
    bool interatividadeCorrer = true;
    bool interacao = false;
    ALLEGRO_EVENT event;

    float x, y;
    x = 100;
    y = 100;

    int sourceX, sourceY;
    sourceX = 0;
    sourceY = 0;

    float atacarX, atacarY;
    atacarX = 25;
    atacarY = 250;

    float defenderX, defenderY;
    defenderX = 25;
    defenderY = 400;

    float correrX, correrY;
    correrX = 25;
    correrY = 550;

    float caixaX, caixaY;
    caixaX = 300;
    caixaY = 850;

    float compilarX, compilarY;
    compilarX = 1200;
    compilarY = 920;

    int primeiro, segundo, terceiro;
    primeiro = 0;
    segundo = 0;
    terceiro = 0;

    #define KEY_SEEN     1
    #define KEY_RELEASED 2

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    al_hide_mouse_cursor(display);

    float dx, dy;
    dx = 0;
    dy = 0;

    al_grab_mouse(display);

    al_start_timer(timer);

    while(!done)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
         {
            case ALLEGRO_EVENT_TIMER:
                if(key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                x += dx;
                y += dy;

                if(x < 0)
                {
                    x *= -1;
                    dx *= -1;
                }
                if(x > width_display)
                {
                    x -= (x - width_display) * 2;
                    dx *= -1;
                }
                if(y < 0)
                {
                    y *= -1;
                    dy *= -1;
                }
                if(y > height_display)
                {
                    y -= (y - height_display) * 2;
                    dy *= -1;
                }

                dx *= 0.9;
                dy *= 0.9;

                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;


                if (sourceX >= al_get_bitmap_width(player)) {
                    sourceX = 0;
                }


                al_get_mouse_state(&state);
                if (state.buttons & 1) {
                    interacao = true;
                } else {
                    interacao = false;
                }


                if (x >= atacarX && x <= (atacarX + 193) && y >= atacarY && y <= (atacarY + 97) && interatividadeAtacar && interacao) {
                     interatividadeAtacar = false;
                }

                if (!interatividadeAtacar && interacao) {
                    atacarX = (x - 50);
                    atacarY = (y - 50);
                    interatividadeAtacar = true;
                    primeiro = 1;

                }

                if (x >= defenderX && x <= (defenderX + 193) && y >= defenderY && y <= (defenderY + 97) && interatividadeDefender && interacao) {
                     interatividadeDefender = false;
                }

                if (!interatividadeDefender && interacao) {
                    defenderX = (x - 50);
                    defenderY = (y - 50);
                    interatividadeDefender = true;
                    segundo = 2;

                }

                if (x >= correrX && x <= (correrX + 193) && y >= correrY && y <= (correrY + 97) && interatividadeCorrer && interacao) {
                     interatividadeCorrer = false;
                }

                if (!interatividadeCorrer && interacao) {
                    correrX = (x - 50);
                    correrY = (y - 50);
                    interatividadeCorrer = true;
                    terceiro = 3;

                }

                if (x >= compilarX && x <= (compilarX + 193) && y >= compilarY && y <= (compilarY + 97) && interacao) {
                    if (primeiro == 1 && segundo == 2 && terceiro == 3) {
                         done = true;
                         venceu = true;

                    }
                }

                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                dx += event.mouse.dx * 0.1;
                dy += event.mouse.dy * 0.1;
                al_set_mouse_xy(display, 320, 240);
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

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(cena, 500, 400, 0);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", x, y);
            al_draw_filled_rectangle(x, y, x + 10, y + 10, al_map_rgb(255, 0, 0));

            al_draw_textf(botao, al_map_rgb(255, 255, 255), (width_display/2) - 400, 100, 0, "PARABÉNS VOCÊ VENCEU!!!");

            // al_draw_bitmap(player, 600, 530, 0);

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_bitmap(cena);
    al_destroy_bitmap(player);

    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}

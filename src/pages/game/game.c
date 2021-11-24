#include "../../headers.h"

void game(void)
{
    verifyAllegroFunction(al_init(), "allegro");
    verifyAllegroFunction(al_install_keyboard(), "keyboard");
    verifyAllegroFunction(al_install_mouse(), "mouse");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    verifyAllegroFunction(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    verifyAllegroFunction(queue, "queue");

    ALLEGRO_MOUSE_STATE state;

    bool segunda_on = false;

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_FONT* font = al_create_builtin_font();
    verifyAllegroFunction(font, "font");

    ALLEGRO_FONT *botao = al_load_ttf_font("../src/assets/fonts/joystix.ttf", 30, 0);

    verifyAllegroFunction(al_init_image_addon(), "couldn't initialize image addon");
    ALLEGRO_BITMAP *cena = al_load_bitmap("../src/assets/images/cena.png");
    ALLEGRO_BITMAP *player_bg = al_load_bitmap("../src/assets/images/player_bg.png");
    ALLEGRO_BITMAP *vida_completa = al_load_bitmap("../src/assets/images/vida_completa.png");
    ALLEGRO_BITMAP *inimigo_bg = al_load_bitmap("../src/assets/images/inimigo_1.png");
    ALLEGRO_BITMAP *inimigo_fugir = al_load_bitmap("../src/assets/images/inimigo_fugir.png");
    ALLEGRO_BITMAP *inimigo_defender = al_load_bitmap("../src/assets/images/inimigo_defender.png");
    ALLEGRO_BITMAP *inimigo_atacar = al_load_bitmap("../src/assets/images/inimigo_atacar.png");
    ALLEGRO_BITMAP *player = al_load_bitmap("../src/assets/images/player.png");
    ALLEGRO_BITMAP *atacar = al_load_bitmap("../src/assets/images/atacar.png");
    ALLEGRO_BITMAP *defender = al_load_bitmap("../src/assets/images/defender.png");
    ALLEGRO_BITMAP *correr = al_load_bitmap("../src/assets/images/correr.png");
    ALLEGRO_BITMAP *caixa = al_load_bitmap("../src/assets/images/caixa.png");
    ALLEGRO_BITMAP *compilar = al_load_bitmap("../src/assets/images/compilar.png");
    ALLEGRO_BITMAP *dot = al_load_bitmap("../src/assets/images/dot.png");

    verifyAllegroFunction(player, "couldn't initialize player");
    verifyAllegroFunction(vida_completa, "couldn't initialize player");
    verifyAllegroFunction(inimigo_bg, "couldn't initialize player");
    verifyAllegroFunction(inimigo_fugir, "couldn't initialize player");
    verifyAllegroFunction(inimigo_defender, "couldn't initialize player");
    verifyAllegroFunction(inimigo_atacar, "couldn't initialize player");
    verifyAllegroFunction(player_bg, "couldn't initialize player");
    verifyAllegroFunction(cena, "couldn't initialize player");
    verifyAllegroFunction(atacar, "couldn't initialize player");
    verifyAllegroFunction(defender, "couldn't initialize player");
    verifyAllegroFunction(correr, "couldn't initialize player");
    verifyAllegroFunction(dot, "couldn't initialize player");

    verifyAllegroFunction(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    bool active = false;
    bool interatividadeAtacar = false;
    bool interatividadeDefender = false;
    bool interatividadeCorrer = false;
    bool interacao = false;
    ALLEGRO_EVENT event;

    float x, y;
    x = 100;
    y = 100;

    int sourceX, sourceY;
    sourceX = 0;
    sourceY = 0;

    float atacarX, atacarY;
    atacarX = 70;
    atacarY = 400;

    float defenderX, defenderY;
    defenderX = 70;
    defenderY = 530;

    float correrX, correrY;
    correrX = 70;
    correrY = 660;

    float fugirX, fugirY;
    fugirX = (width_display - 170);
    fugirY = 420;

    float iniDefenderX, iniDefenderY;
    iniDefenderX = (width_display - 170);
    iniDefenderY = 700;

    float iniAtacarX, iniAtacarY;
    iniAtacarX = (width_display - 170);
    iniAtacarY = 560;

    float caixaX, caixaY;
    caixaX = 300;
    caixaY = 880;

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

                al_get_mouse_state(&state);
                if (state.buttons & 1) {
                    interacao = true;
                } else {
                    interacao = false;
                    interatividadeAtacar = false;
                    interatividadeDefender = false;
                    interatividadeCorrer = false;

                }

                if (x >= atacarX && x <= (atacarX + 193) && y >= atacarY && y <= (atacarY + 97) && interacao && !interatividadeDefender && !interatividadeCorrer) {
                     atacarX = (x - 50);
                     atacarY = (y - 50);
                     interatividadeAtacar = true;
                     primeiro = 1;
                }

                if (x >= defenderX && x <= (defenderX + 193) && y >= defenderY && y <= (defenderY + 97) && interacao &&  !interatividadeAtacar && !interatividadeCorrer) {
                    defenderX = (x - 50);
                    defenderY = (y - 50);
                    interatividadeDefender = true;
                    segundo = 2;
                }


                if (x >= correrX && x <= (correrX + 193) && y >= correrY && y <= (correrY + 97) && interacao && !interatividadeAtacar && !interatividadeDefender) {
                    correrX = (x - 50);
                    correrY = (y - 50);
                    interatividadeCorrer = true;
                    terceiro = 3;
                }

                if (x >= compilarX && x <= (compilarX + 193) && y >= compilarY && y <= (compilarY + 97) && interacao) {
                    if (primeiro == 1 && segundo == 2 && terceiro == 3) {
                         done = true;
                         segunda_on = true;

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
            al_draw_bitmap(cena, 0, 0, 0);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", x, y);
            al_draw_filled_rectangle(x, y, x + 10, y + 10, al_map_rgb(255, 0, 0));
             al_draw_bitmap(caixa, caixaX, caixaY, 0);
             al_draw_bitmap(compilar, compilarX, compilarY, 0);

            al_draw_bitmap(atacar, atacarX, atacarY, 0);
            al_draw_bitmap(defender, defenderX, defenderY, 0);
            al_draw_bitmap(correr, correrX, correrY, 0);

            al_draw_bitmap(inimigo_fugir, fugirX, fugirY, 0);
            al_draw_bitmap(dot, (width_display - 128), fugirY + 104, 0);
            al_draw_bitmap(inimigo_atacar, iniAtacarX, iniAtacarY, 0);
            al_draw_bitmap(dot, (width_display - 128), iniAtacarY + 104, 0);
            al_draw_bitmap(inimigo_defender, iniDefenderX, iniDefenderY, 0);

            al_draw_textf(botao, al_map_rgb(255, 255, 255), (width_display/2) - 400, 100, 0, "ACERTE A SEQUÊNCIA PARA PASSAR DE FASE");
            al_draw_textf(botao, al_map_rgb(255, 255, 255), (width_display/2), 160, 0, "FASE 1");

            al_draw_bitmap(player, 600, 530, 0);
            al_draw_bitmap(inimigo_bg, width_display - 330, 200, 0);
            al_draw_bitmap(player_bg, 80, 200, 0);
            al_draw_bitmap(vida_completa, 360, 280, 0);

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_bitmap(cena);
    al_destroy_bitmap(atacar);
    al_destroy_bitmap(defender);
    al_destroy_bitmap(correr);
    al_destroy_bitmap(caixa);
    al_destroy_bitmap(compilar);
    al_destroy_bitmap(player);
    al_destroy_bitmap(inimigo_bg);
    al_destroy_bitmap(inimigo_fugir);
    al_destroy_bitmap(inimigo_atacar);
    al_destroy_bitmap(inimigo_defender);
    al_destroy_bitmap(dot);
    al_destroy_bitmap(player_bg);
    al_destroy_bitmap(vida_completa);

    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    if (segunda_on == true) segunda();
}

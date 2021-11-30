#include "./headers.h"

ALLEGRO_DISPLAY *display;
ALLEGRO_MONITOR_INFO info;
int width_display = 800;
int height_display = 600;

int verifyAllegroFunction(bool func, const char *message)
{
    if (!func)
    {
        al_show_native_message_box(display, "scott-pilgrim-contra-os-bug", "ERROR", "ALLEGRO ERROR", message, ALLEGRO_MESSAGEBOX_WARN);
        return -1;
    }
}

int main(void)
{
    verifyAllegroFunction(al_init(), "falha na inicialização do allegro");

    ALLEGRO_MONITOR_INFO info;

    // chamando display do allegro
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(width_display, height_display);
    al_set_window_title(display, "scott-pilgrim-contra-os-bug");

    // escondendo cursor do mouse
	al_hide_mouse_cursor(display);

    // configurando display/tamanho da tela
    al_get_monitor_info(0, &info);
	width_display = info.x2 - info.x1; height_display = info.y2 - info.y1;
	al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, 1);
    verifyAllegroFunction(display, "falha na inicialização do display");

    // timer do allegro
    ALLEGRO_TIMER *fps_timer = al_create_timer(1.0 / fps);
    verifyAllegroFunction(fps_timer, "falha na inicialização do timer");
    al_start_timer(fps_timer);

    // plugins necessarios (audio, teclado, image, fonte, video..)
    al_install_audio();
    al_init_acodec_addon();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_video_addon();

    // intro();
    // menu();
    fase1();

	al_destroy_display(display);
	al_destroy_timer(fps_timer);
	return EXIT_SUCCESS;
}

#include "../../headers.h"

void video_display_tutorial(ALLEGRO_VIDEO *video) {
    ALLEGRO_BITMAP *frame = al_get_video_frame(video);

    const int width = 1280;
    const int height = 720;

    if (!frame)
        return;

    al_draw_scaled_bitmap(frame, 0, 0, al_get_bitmap_width(frame), al_get_bitmap_height(frame), (width_display / 2) - (width / 2), (height_display / 2) - (height / 2) - 10, width, height, 0);

    al_flip_display();
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void tutorial() {
    bool redraw = true;
    bool use_frame_events = false;

    al_reserve_samples(1);

    ALLEGRO_VIDEO *intro_vid = al_open_video("../src/assets/movies/tutorial.ogv");
    ALLEGRO_EVENT vid_ev;

    ALLEGRO_EVENT_QUEUE *vid_event_queue = al_create_event_queue();
    ALLEGRO_TIMER *fps_timer = al_create_timer(1.0 / fps);

    al_register_event_source(vid_event_queue, al_get_video_event_source(intro_vid));
    al_register_event_source(vid_event_queue, al_get_display_event_source(display));
    al_register_event_source(vid_event_queue, al_get_timer_event_source(fps_timer));

    al_start_timer(fps_timer);
    al_start_video(intro_vid, al_get_default_mixer());

    bool done = false;
    while (!done) {
        al_wait_for_event(vid_event_queue, &vid_ev);
        switch (vid_ev.type) {
            case ALLEGRO_EVENT_TIMER:
                video_display_tutorial(intro_vid);

                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                al_close_video(intro_vid);
                done = true;
                break;

            case ALLEGRO_EVENT_VIDEO_FRAME_SHOW:
                if (use_frame_events) {
                    redraw = true;
                }
                break;

            case ALLEGRO_EVENT_VIDEO_FINISHED:
                done = true;
                break;
        }
    }
    al_destroy_event_queue(vid_event_queue);
    al_destroy_timer(fps_timer);
}

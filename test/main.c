#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "../src/g.h"

ALLEGRO_FONT *font;

void render(G_NODE node) {
	G_RECT rect = g_get_rect(node);
	al_draw_filled_rectangle(rect.left, rect.top, rect.right, rect.bottom, al_map_rgb_f(1, 0, 0));	
	const char* text = g_get_attribute(node, "text");
	if(text != NULL) {
		ALLEGRO_COLOR white = al_map_rgb_f(1, 1, 1);
		al_draw_text(font, white, rect.left, rect.top, 0, text);
	}
}

int main() {
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *queue;
	ALLEGRO_EVENT event;

	if (!al_init()) {
		printf("Could not init Allegro.\n");
		return 0;
	}

	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_install_keyboard();

	al_set_new_display_flags(ALLEGRO_OPENGL);
	al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 24, ALLEGRO_REQUIRE);
	display = al_create_display(640, 480);
	if (!display) {
		printf("Error creating display\n");
		return 0;
	}

	font = al_load_font("data/DejaVuSans.ttf", 12, 0);

	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));

	ALLEGRO_COLOR black = al_map_rgb_f(0, 0, 0);
	ALLEGRO_COLOR white = al_map_rgb_f(1, 1, 1);

	g_init();

	G_RECT rect;
	G_NODE_OPS ops;
	ops.render = render;
	G_NODE menu = g_create_node(); //Pointer gets invalidated when nodes are reallocated
	printf("menu %i\n", menu);
	g_set_node_ops(menu, &ops);
	rect.top = 100;
	rect.left = 50;
	rect.bottom = 150;
	rect.right = 200;
	g_set_node_rect(menu, rect);

	G_NODE menu2 = g_create_node();
	printf("menu2 %i\n", menu2);
	g_set_node_ops(menu2, &ops);
	rect.top = 300;
	rect.left = 250;
	rect.bottom = 400;
	rect.right = 500;
	g_set_node_rect(menu2, rect);

	g_set_attribute(menu, "text", "Hello, world.");
	g_set_attribute(menu2, "text", "Hello, you.");
	g_set_attribute(menu, "text", "Hello, everybody.");

	int done = 0;
	while(!done) {
		while(al_get_next_event(queue, &event)) {
			switch(event.type) {
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					done = 1;
					break;
			}
		}

		al_clear_to_color(black);

		g_render_node(menu);
		g_render_node(menu2);

		al_flip_display();
	}

	g_shutdown();
	al_destroy_event_queue(queue);
	al_destroy_font(font);
	return 0;
}
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "../src/g.h"

ALLEGRO_FONT *font;
G_NODE hover;

void render(G_NODE node) {
	G_RECT rect = g_get_rect(node);
	G_STYLE style = g_get_style(g_get_attribute(node, "style"));
	G_RECT padding = g_get_style_padding(style);
	G_COLOR gcolor = g_get_style_color(style, G_BACKGROUND);
	ALLEGRO_COLOR bg_color = al_map_rgba_f(gcolor.r, gcolor.g, gcolor.b, gcolor.a);
	gcolor = g_get_style_color(style, G_TEXT);
	ALLEGRO_COLOR text_color = al_map_rgba_f(gcolor.r, gcolor.g, gcolor.b, gcolor.a);

	if(node == hover) {
		char hc[80];
		strncpy(hc, g_get_attribute(node, "style"), 79);
		strncat(hc, ":hover", 79-strlen(hc));
		style = g_get_style(hc);
		if(style > 0) {
			gcolor = g_get_style_color(style, G_BACKGROUND);
			bg_color = al_map_rgba_f(gcolor.r, gcolor.g, gcolor.b, gcolor.a);
		}
	}

	al_draw_filled_rectangle(rect.left, rect.top, rect.right, rect.bottom, bg_color);
	const char* text = g_get_attribute(node, "text");
	if(text != NULL) {
		al_draw_text(font, text_color, rect.left + padding.left, rect.top+padding.top+1, 0, text);
	}

	int line_height = al_get_font_line_height(font)+2;

	int top = rect.top;
	for(G_NODE child = g_get_child(node); child != 0; child = g_get_next_sibling(child)) {
		G_STYLE child_style = g_get_style(g_get_attribute(child, "style"));
		G_RECT child_padding = g_get_style_padding(child_style);
		G_RECT child_margin = g_get_style_margin(child_style);

		G_RECT crect = {
			top + padding.top + child_margin.top,
			rect.left + padding.left + child_margin.left,
			top + line_height + padding.top + child_padding.top + child_padding.bottom + child_margin.top,
			rect.right - padding.right - child_margin.right
		};
		top = crect.bottom + child_margin.bottom;

		if(child > 0) {
			g_set_node_rect(child, crect);
			g_render_node(child);
		}
	}
}

void find_node_at(G_NODE root, int x, int y) {
	G_NODE current_node = root;
	while(current_node > 0) {
		G_RECT r = g_get_rect(current_node);
		if(y > r.top && x > r.left && y < r.bottom && x < r.right) {
			hover = current_node;
			current_node = g_get_child(current_node);
			continue;
		}
		current_node = g_get_next_sibling(current_node);
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

	G_STYLE style = g_create_style("menu");
	g_set_style_color(style, G_BACKGROUND, (G_COLOR){1, 1, 1, 1});
	g_set_style_padding(style, (G_RECT){0, 0, 0, 0});
	G_STYLE style2 = g_create_style("option");
	g_set_style_color(style2, G_BACKGROUND, (G_COLOR){0.9, 0.9, 0.9, 1});
	g_set_style_color(style2, G_TEXT, (G_COLOR){0, 0, 0, 1});
	g_set_style_padding(style2, (G_RECT){2, 2, 2, 2});
	g_set_style_margin(style2, (G_RECT){2, 2, 2, 2});

	G_STYLE style2_hover = g_create_style("option:hover");
	g_set_style_color(style2_hover, G_BACKGROUND, (G_COLOR){0.7, 0.7, 0.7, 1});

	G_RECT rect;
	G_NODE_OPS ops;
	ops.render = render;
	G_NODE menu = g_create_node();
	g_set_node_ops(menu, &ops);
	rect.top = 100;
	rect.left = 50;
	rect.bottom = 250;
	rect.right = 200;
	g_set_node_rect(menu, rect);
	g_set_attribute(menu, "style", "menu");

	G_NODE option = g_create_node();
	g_set_node_ops(option, &ops);
	g_set_attribute(option, "style", "option");
	g_set_attribute(option, "text", "Hello, you. ÖÄÅÉÀ");
	g_create_relation(menu, option);
	option = g_create_node();
	g_set_node_ops(option, &ops);
	g_set_attribute(option, "style", "option");
	g_set_attribute(option, "text", "Next thing");
	g_create_relation(menu, option);

	hover = 0;

	int done = 0;
	while(!done) {
		while(al_get_next_event(queue, &event)) {
			switch(event.type) {
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					done = 1;
					break;
				case ALLEGRO_EVENT_MOUSE_AXES:
					find_node_at(menu, event.mouse.x, event.mouse.y);
					break;
			}
		}

		al_clear_to_color(black);

		g_render_node(menu);

		al_flip_display();
	}

	g_shutdown();
	al_destroy_event_queue(queue);
	al_destroy_font(font);
	return 0;
}
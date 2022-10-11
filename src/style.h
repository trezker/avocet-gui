#include "rect.h"

typedef int G_STYLE;

typedef struct {
	float r, g, b, a;
} G_COLOR;

typedef enum {
	G_BACKGROUND,
	G_TEXT,
	G_NUM_STYLE_COLORS
} G_STYLE_COLOR;

G_STYLE g_create_style(const char* name);
G_STYLE g_get_style(const char* name);

void g_set_style_color(G_STYLE style, G_STYLE_COLOR color, G_COLOR value);
G_COLOR g_get_style_color(G_STYLE style, G_STYLE_COLOR color);
void g_set_style_padding(G_STYLE style, G_RECT padding);
G_RECT g_get_style_padding(G_STYLE style);
void g_set_style_margin(G_STYLE style, G_RECT margin);
G_RECT g_get_style_margin(G_STYLE style);
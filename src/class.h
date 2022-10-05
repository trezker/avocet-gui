#include "rect.h"

typedef int G_CLASS;

typedef struct {
	float r, g, b, a;
} G_COLOR;

typedef enum {
	G_BACKGROUND,
	G_TEXT,
	G_NUM_CLASS_COLORS
} G_CLASS_COLOR;

G_CLASS g_create_class(const char* name);
G_CLASS g_get_class(const char* name);

void g_set_class_color(G_CLASS class, G_CLASS_COLOR color, G_COLOR value);
G_COLOR g_get_class_color(G_CLASS class, G_CLASS_COLOR color);
void g_set_class_padding(G_CLASS class, G_RECT padding);
G_RECT g_get_class_padding(G_CLASS class);
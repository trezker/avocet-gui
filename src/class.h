typedef int G_CLASS;

typedef struct {
	float r, g, b, a;
} G_COLOR;

G_CLASS g_create_class(const char* name);
G_CLASS g_get_class(const char* name);
void g_set_class_background_color(G_CLASS class, G_COLOR color);
G_COLOR g_get_class_background_color(G_CLASS class);

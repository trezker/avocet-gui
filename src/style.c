#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "style.h"

//Needs restructuring, styles will be very sparsely populated like this.
typedef struct {
	G_STYLE id;
	char* name;
	G_COLOR colors[G_NUM_STYLE_COLORS];
	G_RECT padding, margin;
} GI_STYLE;

GI_STYLE* styles;
static int allocated;
static int count;
static G_STYLE last_id;

void gi_init_style() {
	styles = malloc(sizeof(GI_STYLE));
	allocated = 1;
	count = 0;
	last_id = 0;
}

void gi_shutdown_style() {
	for(int i = 0; i < count; ++i) {
		free(styles[i].name);
	}
	free(styles);
}

G_STYLE g_create_style(const char* name) {
	if(count == allocated) {
		allocated *= 2;
		styles = realloc(styles, sizeof(GI_STYLE)*allocated);
	}
	styles[count].id = ++last_id;
	styles[count++].name = strdup(name);
	return last_id;
}

G_STYLE g_get_style(const char* name) {
	if(name == NULL) {
		return 0;
	}
	for(int i = 0; i<count; ++i) {
		if(strcmp(styles[i].name, name) == 0) {
			return styles[i].id;
		}
	}
	return 0;
}

void g_set_style_color(G_STYLE style, G_STYLE_COLOR color, G_COLOR value) {
	for(int i = 0; i<count; ++i) {
		if(styles[i].id == style) {
			styles[i].colors[color] = value;
		}
	}
}

G_COLOR g_get_style_color(G_STYLE style, G_STYLE_COLOR color) {
	for(int i = 0; i<count; ++i) {
		if(styles[i].id == style) {
			return styles[i].colors[color];
		}
	}
	return (G_COLOR){1, 1, 1, 1};
}

void g_set_style_padding(G_STYLE style, G_RECT padding) {
	for(int i = 0; i<count; ++i) {
		if(styles[i].id == style) {
			styles[i].padding = padding;
		}
	}
}

G_RECT g_get_style_padding(G_STYLE style) {
	for(int i = 0; i<count; ++i) {
		if(styles[i].id == style) {
			return styles[i].padding;
		}
	}
	return (G_RECT){0, 0, 0, 0};
}

void g_set_style_margin(G_STYLE style, G_RECT margin) {
	for(int i = 0; i<count; ++i) {
		if(styles[i].id == style) {
			styles[i].margin = margin;
		}
	}
}

G_RECT g_get_style_margin(G_STYLE style) {
	for(int i = 0; i<count; ++i) {
		if(styles[i].id == style) {
			return styles[i].margin;
		}
	}
	return (G_RECT){0, 0, 0, 0};
}
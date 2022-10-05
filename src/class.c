#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "class.h"

typedef struct {
	G_CLASS id;
	char* name;
	G_COLOR colors[G_NUM_CLASS_COLORS];
	G_RECT padding, margin;
} GI_CLASS;

GI_CLASS* classes;
static int allocated;
static int count;
static G_CLASS last_id;

void gi_init_class() {
	classes = malloc(sizeof(GI_CLASS));
	allocated = 1;
	count = 0;
	last_id = 0;
}

void gi_shutdown_class() {
	for(int i = 0; i < count; ++i) {
		free(classes[i].name);
	}
	free(classes);
}

G_CLASS g_create_class(const char* name) {
	if(count == allocated) {
		allocated *= 2;
		classes = realloc(classes, sizeof(GI_CLASS)*allocated);
	}
	classes[count].id = ++last_id;
	classes[count++].name = strdup(name);
	return last_id;
}

G_CLASS g_get_class(const char* name) {
	if(name == NULL) {
		return 0;
	}
	for(int i = 0; i<count; ++i) {
		if(strcmp(classes[i].name, name) == 0) {
			return classes[i].id;
		}
	}
	return 0;
}

void g_set_class_color(G_CLASS class, G_CLASS_COLOR color, G_COLOR value) {
	for(int i = 0; i<count; ++i) {
		if(classes[i].id == class) {
			classes[i].colors[color] = value;
		}
	}
}

G_COLOR g_get_class_color(G_CLASS class, G_CLASS_COLOR color) {
	for(int i = 0; i<count; ++i) {
		if(classes[i].id == class) {
			return classes[i].colors[color];
		}
	}
	return (G_COLOR){1, 1, 1, 1};
}

void g_set_class_padding(G_CLASS class, G_RECT padding) {
	for(int i = 0; i<count; ++i) {
		if(classes[i].id == class) {
			classes[i].padding = padding;
		}
	}
}

G_RECT g_get_class_padding(G_CLASS class) {
	for(int i = 0; i<count; ++i) {
		if(classes[i].id == class) {
			return classes[i].padding;
		}
	}
	return (G_RECT){0, 0, 0, 0};
}

void g_set_class_margin(G_CLASS class, G_RECT margin) {
	for(int i = 0; i<count; ++i) {
		if(classes[i].id == class) {
			classes[i].margin = margin;
		}
	}
}

G_RECT g_get_class_margin(G_CLASS class) {
	for(int i = 0; i<count; ++i) {
		if(classes[i].id == class) {
			return classes[i].margin;
		}
	}
	return (G_RECT){0, 0, 0, 0};
}
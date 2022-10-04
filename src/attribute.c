#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "node.h"
#include "attribute.h"

typedef struct {
	G_ATTRIBUTE id;
	G_NODE node;
	char* name;
	char* value;
} GI_ATTRIBUTE;

GI_ATTRIBUTE* attributes;
static int allocated;
static int count;
static G_ATTRIBUTE last_id;

void gi_init_attribute() {
	attributes = malloc(sizeof(GI_ATTRIBUTE));
	allocated = 1;
	count = 0;
	last_id = 0;
}

void gi_shutdown_attribute() {
	for(int i = 0; i < count; ++i) {
		free(attributes[i].name);
		free(attributes[i].value);
	}
	free(attributes);
}

void g_set_attribute(G_NODE node, const char* name, const char* value) {
	for(int i = 0; i<count; ++i) {
		if(node == attributes[i].node && strcmp(name, attributes[i].name) == 0) {
			free(attributes[i].value);
			attributes[i].value = strdup(value);
			return;
		}
	}

	if(count == allocated) {
		allocated *= 2;
		attributes = realloc(attributes, sizeof(GI_ATTRIBUTE)*allocated);
	}
	attributes[count].id = ++last_id;
	attributes[count].node = node;
	attributes[count].name = strdup(name);
	attributes[count].value = strdup(value);
	++count;
}

const char* g_get_attribute(G_NODE node, const char* name) {
	for(int i = 0; i<count; ++i) {
		if(node == attributes[i].node && strcmp(name, attributes[i].name) == 0) {
			return attributes[i].value;
		}
	}
	return NULL;
}

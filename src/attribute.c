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
int allocated;
int count;
G_ATTRIBUTE last_id;

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
	GI_ATTRIBUTE* a;
	if(false) {//TODO: Find existing node+name combo
	}
	else {
		if(count == allocated) {
			allocated *= 2;
			attributes = realloc(attributes, sizeof(GI_ATTRIBUTE)*allocated);
		}
		attributes[count].id = ++last_id;
		a = &attributes[count++];
	}
	a->value = strdup(value);
}
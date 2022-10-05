#include <stdlib.h>
#include "node.h"
#include "relation.h"

typedef struct {
	G_RELATION id;
	G_NODE parent;
	G_NODE child;
} GI_RELATION;

GI_RELATION* relations;
static int allocated;
static int count;
static G_RELATION last_id;

void gi_init_relation() {
	relations = malloc(sizeof(GI_RELATION));
	allocated = 1;
	count = 0;
	last_id = 0;
}

void gi_shutdown_relation() {
	free(relations);
}

G_RELATION g_create_relation(G_NODE parent, G_NODE child) {
	if(parent <= 0 || child <= 0) {
		return 0;
	}

	if(count == allocated) {
		allocated *= 2;
		relations = realloc(relations, sizeof(GI_RELATION)*allocated);
	}
	relations[count].parent = parent;
	relations[count].child = child;
	relations[count++].id = ++last_id;
	return last_id;
}

G_NODE g_get_child(G_NODE parent) {
	for(int i = 0; i<count; ++i) {
		if(relations[i].parent == parent) {
			return relations[i].child;
		}
	}
	return 0;
}

G_NODE g_get_next_sibling(G_NODE node) {
	G_NODE parent = 0;
	for(int i = 0; i<count; ++i) {
		if(relations[i].parent == parent) {
			return relations[i].child;
		}
		if(relations[i].child == node) {
			parent = relations[i].parent;
		}
	}
	return 0;
}

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "node.h"

typedef struct {
	G_NODE id;
	G_RECT rect;
	G_NODE_OPS* ops;
} GI_NODE;

GI_NODE* nodes;
static int allocated;
static int count;
static G_NODE last_id;

void gi_init_node() {
	nodes = malloc(sizeof(GI_NODE));
	allocated = 1;
	count = 0;
	last_id = 0;
}

void gi_shutdown_node() {
	free(nodes);
}

G_NODE g_create_node() {
	if(count == allocated) {
		allocated *= 2;
		nodes = realloc(nodes, sizeof(GI_NODE)*allocated);
	}
	nodes[count++].id = ++last_id;
	return last_id;
}

GI_NODE* gi_get_node(G_NODE id) {
	for(int i = 0; i<count; ++i) {
		if(nodes[i].id == id)
			return &nodes[i];
	}
	return NULL;
}

void g_destroy_node(G_NODE node) {
	*gi_get_node(node) = nodes[--count];
}

void g_render_node(G_NODE node) {
	gi_get_node(node)->ops->render(node);
}

void g_set_node_ops(G_NODE node, G_NODE_OPS* ops) {
	gi_get_node(node)->ops = ops;
}

void g_set_node_rect(G_NODE node, G_RECT rect) {
	gi_get_node(node)->rect = rect;
}

G_RECT g_get_rect(G_NODE node) {
	return gi_get_node(node)->rect;
}

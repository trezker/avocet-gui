#include <stddef.h>
#include <stdlib.h>
#include "node.h"

typedef struct {
	G_NODE* node;
	char* name;
	char* value;
} Attribute;

typedef struct {
	G_NODE* parent;
	G_NODE* child;
} Child;

struct G_NODE{
	G_RECT rect;
	G_NODE_OPS* ops;
};

G_NODE* g_create_node() {
	return malloc(sizeof(G_NODE));
}

G_NODE* g_destroy_node(G_NODE* node) {
	free(node);
	return NULL;
}

void g_render_node(G_NODE* node) {
	node->ops->render(node);
}

void g_set_node_ops(G_NODE* node, G_NODE_OPS* ops) {
	node->ops = ops;
}

void g_set_node_rect(G_NODE* node, G_RECT rect) {
	node->rect.top = 100;
	node->rect.left = 50;
	node->rect.bottom = 150;
	node->rect.right = 200;
}

G_RECT g_get_rect(G_NODE* node) {
	return node->rect;
}

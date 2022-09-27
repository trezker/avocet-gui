#include <stddef.h>
#include <stdlib.h>
#include "node.h"

Node* g_create_node() {
	return malloc(sizeof(Node));
}

Node* g_destroy_node(Node* node) {
	free(node);
	return NULL;
}

void g_render_node(Node* node) {
	node->ops->render(node);
}

void g_set_node_ops(Node* node, Node_ops* ops) {
	node->ops = ops;
}

void g_set_node_rect(Node* node, Rect rect) {
	node->rect.top = 100;
	node->rect.left = 50;
	node->rect.bottom = 150;
	node->rect.right = 200;
}

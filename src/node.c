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
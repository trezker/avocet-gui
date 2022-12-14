#include "rect.h"

typedef struct G_NODE_OPS G_NODE_OPS;
typedef int G_NODE;

struct G_NODE_OPS {
	void (*render)(G_NODE);
};

G_NODE g_create_node();
void g_destroy_node(G_NODE node);

void g_render_node(G_NODE node);

void g_set_node_ops(G_NODE node, G_NODE_OPS* ops);
void g_set_node_rect(G_NODE node, G_RECT rect);
G_RECT g_get_rect(G_NODE node);
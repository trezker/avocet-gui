typedef struct Node_ops Node_ops;
typedef struct Node Node;

typedef struct {
	int top, left, bottom, right;
} Rect;

struct Node_ops {
	void (*render)(Node*);
};

Node* g_create_node();
Node* g_destroy_node(Node* node);

void g_render_node(Node* node);

void g_set_node_ops(Node* node, Node_ops* ops);
void g_set_node_rect(Node* node, Rect rect);
Rect g_get_rect(Node* node);
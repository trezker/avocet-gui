typedef struct Node_ops Node_ops;

typedef struct {
	Node_ops* ops;
} Node;

struct Node_ops {
	void (*render)(Node*);
};


Node* g_create_node();
Node* g_destroy_node(Node* node);
void g_render_node(Node* node);
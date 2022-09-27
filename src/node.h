typedef struct Node_ops Node_ops;

typedef struct {
	int top, left, bottom, right;
} Rect;

typedef struct {
	Rect rect;
	Node_ops* ops;
} Node;

struct Node_ops {
	void (*render)(Node*);
};


Node* g_create_node();
Node* g_destroy_node(Node* node);
void g_render_node(Node* node);
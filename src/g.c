void gi_init_node();
void gi_shutdown_node();
void gi_init_attribute();
void gi_shutdown_attribute();
void gi_init_class();
void gi_shutdown_class();

void g_init() {
	gi_init_node();
	gi_init_attribute();
	gi_init_class();
}

void g_shutdown() {
	gi_shutdown_node();
	gi_shutdown_attribute();
	gi_shutdown_class();
}
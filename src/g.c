void gi_init_node();
void gi_shutdown_node();
void gi_init_attribute();
void gi_shutdown_attribute();

void g_init() {
	gi_init_node();
	gi_init_attribute();
}

void g_shutdown() {
	gi_shutdown_node();
	gi_init_attribute();
}
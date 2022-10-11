void gi_init_node();
void gi_shutdown_node();
void gi_init_attribute();
void gi_shutdown_attribute();
void gi_init_style();
void gi_shutdown_style();
void gi_init_relation();
void gi_shutdown_relation();

void g_init() {
	gi_init_node();
	gi_init_attribute();
	gi_init_style();
	gi_init_relation();
}

void g_shutdown() {
	gi_shutdown_node();
	gi_shutdown_attribute();
	gi_shutdown_style();
	gi_shutdown_relation();
}

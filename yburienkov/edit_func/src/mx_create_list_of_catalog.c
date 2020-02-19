#include "uls.h"

static void set_start_val(t_catalog *head) {
	head->c_name = NULL;
	head->max_size_ofdir = 0;
	head->max_size_oflink = 0;
	head->lng_max_minor = 0;
	head->max_length = 0;
	head->max_lnght_namedir = 0;
	head->max_lnght_grpdir = 0;
	head->size_of_block = 0;
	head->am_data = 0;
	head->am_files = 0;
}

t_catalog *mx_create_list_of_catalog(int amount) {
	t_catalog *head = (t_catalog *)malloc(sizeof(t_catalog));
	t_catalog *node = head;

	set_start_val(head);
	head->c_next = NULL;
	for(int i = 1; i < amount; i++) {
		node->c_next = (t_catalog *)malloc(sizeof(t_catalog));
		set_start_val(head);
		node = node->c_next;
		node->c_next = NULL;
	}
	return head;
}

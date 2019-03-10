#include "tree.h"

#define MAX_LEVEL 4

int Tree::read(const char * name) {
	Node curr, * child;
	FILE * fp;
	int res;

	if (!(fp = fopen(name, "r"))) return -3;

	if (!(res = curr.read(fp))) {
		root = new Node;
		if (!root) {
			fclose(fp);
			return -1;
		}
		*root == curr;
		goto_root();
		curr.clear();
		while (!(res = curr.read(fp))) {
			child = new Node;
			if (!child) {
				fclose(fp);
				return -1;
			}
			*child == curr;
			add(child);
			curr.clear();
		}
	}
	if (!feof(fp)) { fclose(fp); return res; }
	fclose(fp);
	if (!root->get_name()) return -2;
	return 0;
}

void Tree::print(Node * r, int level) {
	if (!r) r = root;
	if (!r) return;
	if (level > MAX_LEVEL) return;
	for (int i = 0; i < level; i++) printf("    ");
	r->print();
	if (r->get_left()) print(r->get_left(), level + 1);
	if (r->get_right()) print(r->get_right(), level + 1);
}

void Tree::print_(Node * r, int level) {
	if (!r) r = root;
	if (level > MAX_LEVEL) return;
	if (r->get_right()) print_(r->get_right(), level + 1);
	for (int i = 0; i < level; i++) printf("    ");
	r->print();
	if (r->get_left()) print_(r->get_left(), level + 1);
}

int Tree::search(const char * filename) {
	Student s;
	int res = 0;
	int i = 0;
	FILE * fp;

	if (!(fp = fopen(filename, "r"))) return -1;

	while (!(res = s.read(fp))) {
		curr = root;
		while (curr && (i = (s < *curr))) {
			if (i < 0) curr = curr->get_left();
			else curr = curr->get_right();
		}
	}

	if (!feof(fp)) { fclose(fp); return res; }
	fclose(fp);

	return 0;
}



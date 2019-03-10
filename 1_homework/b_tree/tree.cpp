#include "tree.h"

#define MAX_LEVEL 2
#define MAX_PRINT 5

int bin_search(Student *, Student *, int);

int Tree::read(const char * name, int mm) {
	Student c;
	BNode * node = 0;
	FILE * fp = 0;
	int res = 0;
	m = mm;

	if (!(fp = fopen(name, "r"))) return -3;

	while (!(res = c.read(fp))) {
		node = add(&c, root);
		if (!node) {
			fclose(fp);
			return -1;
		}
		if (node != root) {
			BNode * new_root = new BNode;
			if (!new_root) {
				fclose(fp);
				return -1;
			}
			if (new_root->alloc_mem_data(m)) {
				fclose(fp);
				delete new_root;
				return -1;
			}
			if (new_root->alloc_mem_child(m)) {
				fclose(fp);
				delete [] new_root->get_data();
				delete new_root;
				return -1;
			}
			new_root->get_data()[0] == c;
			new_root->get_child()[0] == *root;
			new_root->get_child()[1] == *node;
			delete root;
			delete node;
			curr = root = new_root;
			root->set_len(1);
		}
		c.clear();
	}

	if (!feof(fp)) { fclose(fp); return res; }
	fclose(fp);

//	if (!root->get_name()) return -2;
	return 0;
}

int Tree::print_(BNode * r, int level) {
	int i = 0;
	if (!r) r = root;
	if (!r) return 0;
	if (level > MAX_LEVEL) return 0;
	for (i = 0; i < level; i++) printf("    ");
	for (i = 0; i < r->get_len() && i <= MAX_PRINT; i++) r->get_data()[i].print_();
	if (i < r->get_len()) printf("...\n");
	else printf("\n");
	if (r->get_child()) {
		for (i = 0; i <= r->get_len() && i <= MAX_PRINT; i++) print_(r->get_child() + i, level + 1);
		if (i < r->get_len() && level + 1 <= MAX_LEVEL) {
			for (i = 0; i < level + 1; i++) printf("    ");
			printf("...\n");
		}
	}
	return 1;
}
void Tree::print(BNode * r, int level) {
	int i = 0;
	if (!r) r = root;
	if (!r) return;
	if (level > MAX_LEVEL) return;
	for (i = 0; i < level; i++) printf("    ");
	for (i = 0; i < r->get_len() && i <= MAX_PRINT; i++) r->get_data()[i].print_();
	if (i < r->get_len()) printf("...\n");
	else printf("\n");
	if (r->get_child()) {
		for (i = 0; i <= r->get_len() && i <= MAX_PRINT; i++) print(r->get_child() + i, level + 1);
		if (i < r->get_len() && level + 1 <= MAX_LEVEL) {
			for (i = 0; i < level + 1; i++) printf("    ");
			printf("...\n");
		}
	}
}

int Tree::search(const char * filename) {
	Student s;
	int res = 0;
	int i = 0;
	FILE * fp;

	if (!(fp = fopen(filename, "r"))) return -1;

	while (!(res = s.read(fp))) {
		curr = root;
		while (curr->get_child()) {
			i = bin_search(&s, curr->get_data(), curr->get_len());
			if (i < curr->get_len() && (curr->get_data()[i] < s) == 0) break;
			curr = curr->get_child() + i;
		}
//		s.print_(); curr->get_data()[0].print_();
//		printf("%d\n", bin_search(&s, curr->get_data(), curr->get_len()));
		bin_search(&s, curr->get_data(), curr->get_len());
	}

	if (!feof(fp)) { fclose(fp); return res; }
	fclose(fp);

	return 0;
}

int bin_search(Student * a, Student * data, int len) {
	int i = 0, j = len, k = 0;
	if ((*a < data[0]) <= 0) return 0;
	while (i != j && i != j - 1) {
		k = (i + j) >> 1;
		if ((*a < data[k]) <= 0) j = k;
		else i = k;
	}
	return j;
}


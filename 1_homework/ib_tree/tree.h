#include <stdio.h>
#include <time.h>
#include "bnode.h"

#define MIN_LEVEL 1

class Tree
{
private:
	BNode * root, * curr;
	int m;

	void delete_tree(BNode * r) {
		if (r->get_child()) {
			for (int i = 0; i <= r->get_len(); i++) {
				delete_tree(r->get_child() + i);
			}
			delete [] r->get_child();
		}
		delete [] r->get_data();
	}

public:
	Tree() { root = curr = 0; m = 0; }
	~Tree() {
		if (root) {
			delete_tree(root);
			delete root;
		}
		curr = root = 0;
	}

	// returns
	//	root: all is good
	//	0: memory allocation error
	//	some_node: cut node, ...
	BNode * add(Student * a, BNode * r) {
		if (!root) {
			root = new BNode;
			if (!root) return 0;
			if (root->alloc_mem_data(m)) {
				delete root;
				return 0;
			}
			curr = root;
			root->add(a, m);
		} else {
			if (r->get_child()) {
				int i = 0;
				BNode * res = add(a, r->find_child(a, &i));
				if (!res) return 0;
				else if (res == root) return root;
				else {
					if (r->add(a, m, i, res)) {
						return r->cut(a, m, i, res);
					}
				}
			} else if (r->add(a, m)) {
				// all bad, r is full
				return r->cut(a, m);
			}
		}
		return root;
	}
	
	int read(const char *, int);
	void print(BNode * = 0, int level = 0);
	int print_(BNode * = 0, int level = 0);

	void goto_root() { curr = root; }
	BNode * get() const { return curr; }
	BNode * get_root() const { return root; }
	void set(BNode * c) { curr = c; }
	void set_root(BNode * r) { root = r; }

	int search(const char *);
};
	


#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <time.h>
#include "node.h"

class Tree
{
private:
	Node * root, * curr;

	void delete_tree(Node * r) {
		if (r->get_left()) delete_tree(r->get_left());
		if (r->get_right()) delete_tree(r->get_right());
		delete r;
	}
public:
	Tree() { root = curr = 0; }
	~Tree() { if (root) delete_tree(root); }
	int read(const char *);
	void print(Node * = 0, int level = 0);
	void print_(Node * = 0, int level = 0);

	void add(Node * a, Node * r = 0) {
		if (!r) r = root;
		if ((*a < *r) < 0) {
			if (r->get_left()) add(a, r->get_left());
			else r->set_left(a);
		} else {
			if (r->get_right()) add(a, r->get_right());
			else r->set_right(a);
		}
	}
	
	void goto_root() { curr = root; }
	void goto_left() { curr = curr->get_left(); }
	void goto_right() { curr = curr->get_right(); }
	Node * get() const { return curr; }
	Node * get_root() const { return root; }
	Node * get_left() const { return curr->get_left(); }
	Node * get_right() const { return curr->get_right(); }
	void set(Node * c) { curr = c; }
	void set_left(Node * l) { curr->set_left(l); }
	void set_right(Node * r) { curr->set_right(r); }
	void add_left(Node * l) { curr->set_left(l); }
	void add_right(Node * r) { curr->set_right(r); }
	void del_left() { delete curr->get_left(); }
	void del_right() { delete curr->get_right(); }
	void del_left_subtree() { delete_tree(curr->get_left()); }
	void del_right_subtree() { delete_tree(curr->get_right()); }

	int search(const char *);
};
	
#endif


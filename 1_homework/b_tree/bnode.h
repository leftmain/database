#ifndef BNODE_H
#define BNODE_H

#include "student.h"

#define RIGHT 0

class BNode {
private:
	Student * data;
	BNode * child;
	int len;
public:
	BNode() { data = 0; child = 0; len = 0; }
	~BNode() {
		data = 0; child = 0;
	}

	void operator==(const BNode& b) {
		data = b.data;
		child = b.child;
		len = b.len;
	}
	void clear() { data = 0; child = 0; len = 0; }
	int bin_search_l(Student * a) {
		int i = 0, j = len, k;
		if ((*a < data[0]) <= 0) return 0;
		while (i != j && i != j - 1) {
			k = (i + j) >> 1;
			if ((*a < data[k]) <= 0) j = k;
			else i = k;
		}
		return j;
	}
	int bin_search_r(Student * a) {
		int i = 0, j = len, k;
		if ((*a < data[0]) < 0) return 0;
		while (i != j && i != j - 1) {
			k = (i + j) >> 1;
			if ((*a < data[k]) < 0) j = k;
			else i = k;
		}
		return j;
	}

	int alloc_mem_data(int m) {
		data = new Student[2 * m];
		if (!data) return 1;
		return 0;
	}
	int alloc_mem_child(int m) {
		child = new BNode[2 * m + 1];
		if (!child) return 1;
		return 0;
	}
// --------------------------------------------------------
	int add(Student * a, int m) {
		if (len == 2 * m) return 1;
		int i = 0;
		if (RIGHT) i = bin_search_r(a);
		else i = bin_search_l(a);
//		while (i < len && (*a < data[i]) > 0) i++;
		for (int j = len; j > i; j--) data[j] = data[j-1];
		data[i] = *a;
		len++;
		return 0;
	}
	BNode * cut(Student * a, int m) {
		BNode * new_node = new BNode;
		if (!new_node) return 0;
		if (new_node->alloc_mem_data(m)) {
			delete new_node;
			return 0;
		}
		Student tmp;
		int j = 0, i = 0;
		if (RIGHT) i = bin_search_r(a);
		else i = bin_search_l(a);
//		while (i < len && (*a < data[i]) > 0) i++;
		if (i < m) {
			tmp = data[m-1];
			for (j = m-1; j > i; j--) data[j] = data[j-1];
			data[i] = *a;
			for (j = m; j < len; j++) {
				new_node->data[j-m] = data[j];
				data[j].clear();
			}
			new_node->len = len = m;
		} else if (i == m) {
			tmp = *a;
			for (j = m; j < len; j++) {
				new_node->data[j-m] = data[j];
				data[j].clear();
			}
			new_node->len = len = m;
		} else {
			tmp = data[m];
			data[m].clear();
			for (j = m+1; j < i; j++) {
				new_node->data[j-m-1] = data[j];
				data[j].clear();
			}
			new_node->data[i-m-1] = *a;
			for (j = i; j < len; j++) {
				new_node->data[j-m] = data[j];
				data[j].clear();
			}
			new_node->len = len = m;
		}
		*a = tmp;
		tmp.clear();
		return new_node;
	}
// --------------------------------------------------------
	int add(Student * a, int m, int i, BNode * new_node) {
		if (len == 2 * m) return 1;
		for (int j = len; j > i; j--) {
			data[j] = data[j-1];
			child[j+1] == child[j];
		}
		data[i] = *a;
		child[i+1] == *new_node;
		new_node->clear();
		delete new_node;
		len++;
		return 0;
	}

	BNode * cut(Student * a, int m, int i, BNode * res) {
		BNode * new_node = new BNode;
		if (!new_node) return 0;
		if (new_node->alloc_mem_data(m)) {
			delete new_node;
			return 0;
		}
		if (new_node->alloc_mem_child(m)) {
			delete [] new_node->data;
			delete new_node;
			return 0;
		}
		int j;
		if (i < m) {
			Student tmp; tmp = data[m-1];
			BNode n_tmp; n_tmp == child[m];
			for (j = m-1; j > i; j--) {
				data[j] = data[j-1];
				child[j+1] == child[j];
			}
			data[i] = *a;
			child[i+1] == *res;
			*a = tmp; tmp.clear();
			*res == n_tmp; n_tmp.clear();
		} else if (i > m) {
			new_node->child[0] == child[m+1];
			child[m+1].clear();
			for (j = m+1; j < i; j++) {
				new_node->data[j-m-1] = data[j];
				data[j].clear();
				new_node->child[j-m] == child[j+1];
				child[j+1].clear();
			}
			new_node->data[i-m-1] = *a;
			new_node->child[i-m] == *res; delete res;
			for (j = i; j < len; j++) {
				new_node->data[j-m] = data[j];
				data[j].clear();
				new_node->child[j-m+1] == child[j+1];
				child[j+1].clear();
			}
			new_node->len = len = m;
			*a = data[m]; data[m].clear();
			return new_node;
		}
		new_node->child[0] == *res; delete res;
		for (j = m; j < len; j++) {
			new_node->data[j-m] = data[j];
			data[j].clear();
			new_node->child[j-m+1] == child[j+1];
			child[j+1].clear();
		}
		new_node->len = len = m;
		return new_node;
	}

	BNode * find_child(Student * a, int * ii) {
/*
		int i = 0, j = len, k;
		if ((*a < data[0]) < 0) { *ii = 0; return child; }
		while (i != j && i != j - 1) {
			k = (i + j) >> 1;
			if ((*a < data[k]) < 0) j = k;
			else i = k;
		} *ii = j;
		return child + j;
*/
		if (RIGHT) *ii = bin_search_r(a);
		else *ii = bin_search_l(a);
		return child + *ii;
/*
		int i = 0;
		while (i < len && (*a < data[i]) >= 0) i++;
		*ii = i;
		return child + i;
*/
	}

	Student * get_data() const { return data; }
	BNode * get_child() const { return child; }
	int get_len() const { return len; }
	void set_len(int l) { len = l; }
};

#endif


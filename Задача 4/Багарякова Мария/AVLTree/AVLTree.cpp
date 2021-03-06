#include "pch.h"
#include <iostream>

class Tree {
	struct node {
		int key;
		unsigned char height;
		node* left;
		node* right;
		node(int k) { 
			key = k; 
			left = right = 0; 
			height = 1; 
		}
	};

	node* root = NULL;

	unsigned char height(node* p) {
		return p ? p->height : 0;
	}

	int balanceFactor(node* p) {
		return height(p->right) - height(p->left);
	}

	void fixHeight(node* p) {
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

	node* rotateToRight(node* p) {
		node* q = p->left;
		p->left = q->right;
		q->right = p;
		fixHeight(p);
		fixHeight(q);
		return q;
	}

	node* rotateToLeft(node* q) {
		node* p = q->right;
		q->right = p->left;
		p->left = q;
		fixHeight(q);
		fixHeight(p);
		return p;
	}
	
	node* findMin(node* p) {
		return p->left ? findMin(p->left) : p;
	}

	node* removeMin(node* p) {
		if (p->left == 0)
			return p->right;
		p->left = removeMin(p->left);
		return balance(p);
	}

	node* balance(node* p) {
		fixHeight(p);
		if (balanceFactor(p) == 2) {
			if (balanceFactor(p->right) < 0)
				p->right = rotateToRight(p->right);
			return rotateToLeft(p);
		}
		if (balanceFactor(p) == -2) {
			if (balanceFactor(p->left) > 0)
				p->left = rotateToLeft(p->left);
			return rotateToRight(p);
		}
		return p;
	}

	node* insert(node* p, int k) {
		if (!p)
			return new node(k);
		if (k < p->key)
			p->left = insert(p->left, k);
		else
			p->right = insert(p->right, k);
		return balance(p);
	}

	node* remove(node* p, int k) {
		if (!p) return 0;
		if (k < p->key)
			p->left = remove(p->left, k);
		else if (k > p->key)
			p->right = remove(p->right, k);
		else {
			node* q = p->left;
			node* r = p->right;
			delete p;
			if (!r) return q;
			node* min = findMin(r);
			min->right = removeMin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}

	void dump(node* node, int indent = 0) {
		if (node) {
			for (int i = 0; i < indent; i++)
				printf("%s", " ");
			printf("%i", node->key);
			printf("%s", "\n");
			if (node->left)
				dump(node->left, indent + 4);
			if (node->right)
				dump(node->right, indent + 4);

		}
	}

	
public:
	
	node* balance() {
		root = balance(root);
	}
	
	void insert(int key) {
		root = insert(root, key);
	}
	
	void remove(int key) {
		root = remove(root, key);
	}

	void dump() {
		dump(root);
	}
	
};

int main() {
	auto tree = new Tree();
	for (int i = 0; i < 7; i++)
		tree->insert(i);
	printf("%s", "initial tree:\n");
	tree->dump();
	tree->insert(10);
	printf("%s", "\nadd new element:\n");
	tree->dump();
	tree->remove(3);
	printf("%s", "\nremove element 3:\n");
	tree->dump();
	tree->remove(5);
	printf("%s", "\nremove element 5:\n");
	tree->dump();
}
#include <iostream>


using namespace std;

struct Node {
	int value;
	Node* left;
	Node* right;
};

void init(Node*& root) {
	root = NULL;
}

Node* createNode(int x) {
	Node* p = new Node;
	p->value = x;
	p->left = NULL;
	p->right = NULL;
	return p;
}

void addNode(Node*& root ,int x) {
	if (root == NULL) {
		root = createNode(x);
	}
	else {
		Node* p = root;
		Node* parent = NULL;
		while (p != NULL && p->value != x) {
			parent = p;
			if (x > p->value) {
				p = p->right;
			}
			else {
				p = p->left;
			}
		}
		if (p == NULL) {
			p = createNode(x);
			if (x > parent->value) {
				parent->right = p;
			}
			else {
				parent->left = p;
			}
		}
	}
}

Node* search(Node* root, int x) {
	Node* p = root;
	while (p != NULL && p->value != x) {
		if (x > p->value)
			p = p->right;
		else
			p = p->left;
	}
	return p;
}

void searchLeftFinal(Node*& p, Node*& q,Node* parent) {
	if (q->left == NULL) {
		p->value = q->value;
		
	}
	else
		searchLeftFinal(p, q->left, q);
}


void delNode(Node*& root, int x) {
	if (root != NULL) {
		Node* p = root;
		Node* parent = NULL;
		while (p != NULL && p->value != x) {
			parent = p;
			if (x > p->value)
				p = p->right;
			else
				p = p->left;
		}
		if (p != NULL) {
			if (parent != NULL) {
				//delete node la, node bac 0
				if (p->left == NULL && p->right == NULL) {
					if (p->value > parent->value) {
						parent->right = NULL;
					}
					else
						parent->left = NULL;
				}
				else if (parent->right != NULL && p->value > parent->value) {
					//delete node bac 1
					if (p->left == NULL) {
						parent->right = p->right;
						p->right = NULL;
					}
					//delete node bac 1
					else if(p->right == NULL) {
						parent->right = p->left;
						p->left = NULL;
					}
					else {
						/*Node* tmp = p;
						searchLeftFinal(tmp, p->right);*/
						Node* tmp = p->right;
						Node* prev = NULL;
						while (tmp->left != NULL) {
							prev = tmp;
							tmp = tmp->left;
						}
						if (prev != NULL) {
							p->value = tmp->value;
							if (tmp->right != NULL)
							{
								prev->left = tmp->right;
								tmp->right = NULL;
							}
							delete tmp;
							return;
						}
					}
				}
				else if (parent->left != NULL && p->value < parent->value) {
					//delete node bac 1
					if (p->left == NULL) {
						parent->left = p->right;
						p->right = NULL;
					}
					//delete node bac 1
					else if(p->right == NULL) {
						parent->left = p->left;
						p->left = NULL;
					}
					else {
						Node* tmp = p->right;
						Node* prev = NULL;
						while (tmp->left != NULL) {
							prev = tmp;
							tmp = tmp->left;
						}
						if (prev != NULL) {
							p->value = tmp->value;
							if (tmp->right != NULL)
							{
								prev->left = tmp->right;
								tmp->right = NULL;
							}
							delete tmp;
							return;
						}
					}
				}
				delete p;
			}
			else {
				Node* tmp = p->right;
				Node* prev = NULL;
				while (tmp->left != NULL) {
					prev = tmp;
					tmp = tmp->left;
				}
				if (prev != NULL) {
					p->value = tmp->value;
					if (tmp->right != NULL)
					{
						prev->left = tmp->right;
						tmp->right = NULL;
					}
					delete tmp;
					return;
				}
			}
		}
	}
}

void lnr(Node* root) {
	if (root != NULL) {
		lnr(root->left);
		cout << root->value << " ";
		lnr(root->right);
	}
}

int main() {
	Node* root;
	init(root);
	addNode(root, 40);
	addNode(root, 20);
	addNode(root, 50);
	addNode(root, 10);
	addNode(root, 15);
	addNode(root, 7);
	addNode(root, 5);
	addNode(root, 25);
	addNode(root, 30);
	addNode(root, 23);
	addNode(root, 21);
	addNode(root, 22);
	addNode(root, 55);
	addNode(root, 43);
	addNode(root, 47);
	addNode(root, 60);
	lnr(root);
	cout << endl;
	cout << "=======DELETE NODE=======\n";
	delNode(root, 40);
	lnr(root);
	cout << endl;
	return 1;
}

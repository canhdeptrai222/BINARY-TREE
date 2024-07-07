#include <iostream>

using namespace std;

struct Node
{
	int value;
	Node *left;
	Node *right;
};

void init(Node *&root)
{
	root = NULL;
}

Node *createNode(int x)
{
	Node *p = new Node;
	p->value = x;
	p->left = NULL;
	p->right = NULL;
	return p;
}
// khong de quy!!!!!!!!!!!
void addNode(Node *&root, int x)
{
	if (root == NULL)
	{
		root = createNode(x);
	}
	else
	{
		Node *p = root;
		Node *parent = NULL;
		while (p != NULL && p->value != x)
		{
			parent = p;
			if (x > p->value)
			{
				p = p->right;
			}
			else
			{
				p = p->left;
			}
		}
		if (p == NULL)
		{
			p = createNode(x);
			if (x > parent->value)
			{
				parent->right = p;
			}
			else
			{
				parent->left = p;
			}
		}
	}
}
void addNodeRecursion(Node *&root, int x)
{
	if (root == NULL)
		root = createNode(x);
	else
	{
		if (root->value == x)
			return;
		else if (x > root->value)
			return addNodeRecursion(root->right, x);
		else
			return addNodeRecursion(root->left, x);
	}
}
// khong de quy!!!!!!!!!!!
Node *search(Node *root, int x)
{
	Node *p = root;
	while (p != NULL && p->value != x)
	{
		if (x > p->value)
			p = p->right;
		else
			p = p->left;
	}
	return p;
}
Node *searchRecursion(Node *root, int x)
{
	if (root != NULL)
	{
		if (root->value == x)
			return root;
		else if (root->value < x)
			searchRecursion(root->right, x);
		else
			searchRecursion(root->left, x);
	}
	return NULL;
}
// khong de quy!!!!!!!!!!!
void searchLeftFinal(Node *&p)
{
	Node *tmp = p->right;
	Node *prev = NULL;
	while (tmp->left != NULL)
	{
		prev = tmp;
		tmp = tmp->left;
	}
	if (prev != NULL)
	{
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

// khong de quy!!!!!!!!!!!
void delNode(Node *&root, int x)
{
	if (root != NULL)
	{
		Node *p = root;
		Node *parent = NULL;
		while (p != NULL && p->value != x)
		{
			parent = p;
			if (x > p->value)
				p = p->right;
			else
				p = p->left;
		}
		if (p != NULL)
		{
			if (parent != NULL)
			{
				// delete node la, node bac 0
				if (p->left == NULL && p->right == NULL)
				{
					if (p->value > parent->value)
					{
						parent->right = NULL;
					}
					else
						parent->left = NULL;
				}
				else if (p->value > parent->value)
				{
					// delete node bac 1
					if (p->left == NULL)
					{
						parent->right = p->right;
						p->right = NULL;
					}
					// delete node bac 1
					else if (p->right == NULL)
					{
						parent->right = p->left;
						p->left = NULL;
					} // delete node bac 2
					else
					{
						searchLeftFinal(p);
					}
				}
				else
				{
					// delete node bac 1
					if (p->left == NULL)
					{
						parent->left = p->right;
						p->right = NULL;
					}
					// delete node bac 1
					else if (p->right == NULL)
					{
						parent->left = p->left;
						p->left = NULL;
					} // delete node bac 2
					else
					{
						searchLeftFinal(p);
					}
				}
				delete p;
			}
			else
			{
				searchLeftFinal(p);
			}
		}
	}
}
/**
 * Recursively deletes a node with a given value in a binary search tree
 * @param root pointer to the root of the tree
 * @param x the value to be deleted
 * @return 1 if the node is deleted successfully, 0 otherwise
 */
void leftFinalNode(Node*& p, Node*& q) {
	if (q->left == NULL) {
		//change value with root has x value
		p->value = q->value;
		//update node thế mạng
		p = q;
		q = q->right;
	}
	else
		leftFinalNode(p, q->left);
}
int delNodeRecursion(Node *&root, int x)
{
	// If the root is NULL, no node can be deleted
	if (root == NULL)
		return 0;
	// If the root's value is equal to x, delete the root node
	if (root->value == x)
	{
		Node *p = root;
		// If the root has no left child, make its right child the new root
		if (root->left == NULL)
			root = root->right;
		// If the root has no right child, make its left child the new root
		else if (root->right == NULL)
			root = root->left;
		else
			leftFinalNode(p, root->right);

		delete p;
		p = NULL;
		return 1;
	}
	// If the root's value is less than x, search in its right subtree
	if (root->value < x)
		return delNodeRecursion(root->right, x);
	// If the root's value is greater than x, search in its left subtree
	if (root->value > x)
		return delNodeRecursion(root->left, x);
}

Node* nodeMax(Node* root) {
	if (root->right == NULL)
		return root;
	else
		return nodeMax(root->right);
}
int countNode(Node* root) {
	if (root == NULL)
		return 0;
  /*else
		return 1 + countNode(root->left) + countNode(root->right);*/
  /*else
	    return countNode(root->left) + 1 + countNode(root->right);*/
    else return countNode(root->left) + countNode(root->right) + 1;
}
//NO UNDERSTADNDING
//int sum(Node* root) {
//	if (root == NULL)
//		return 0;
//	int leftValue = sum(root->left);
//	int rightValue = sum(root->right);
//	return root->value + leftValue + rightValue;
//}
int sum(Node* root) {

}
void lnr(Node *root)
{
	if (root != NULL)
	{
		lnr(root->left);
		cout << root->value << " ";
		lnr(root->right);
	}
}
void nlr(Node *root)
{
	if (root != NULL)
	{
		cout << root->value << " ";
		nlr(root->left);
		nlr(root->right);
	}
}
void lrn(Node *root)
{
	if (root != NULL)
	{
		lrn(root->left);
		lrn(root->right);
		cout << root->value << " ";
	}
}
int main()
{
	Node *root;
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
	addNode(root, 43);
	addNode(root, 47);
	addNode(root, 60);
	addNode(root, 45);
	// cout << countNode(root) << endl;
	/*addNodeRecursion(root, 40);
	addNodeRecursion(root, 20);
	addNodeRecursion(root, 50);*/
	lnr(root);
	cout << endl;
	//// cout << searchRecursion(root, 210)<< endl;
	//cout << "=============DELETE============\n";
	//delNodeRecursion(root, 40);
	//lnr(root);
	//cout << endl;
	/*cout << "========MAX===========\n";
	cout << nodeMax(root)->value << endl;*/
	cout << "===============AVERAGE===============\n"; //31
	/*int tb = sum(root) / countNode(root);
	cout << tb << endl; */
	return 0;
}

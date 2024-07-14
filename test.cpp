#include <iostream>
#include <queue>
#include <stack>
#define MAX 100
using namespace std;

struct Stack {
	int a[MAX];
	int top;
};
void init(Stack& s) {
	s.top = -1;
}
bool isEmpty(Stack s) {
	return s.top < 0;
}
bool isFull(Stack s) {
	return s.top == MAX;
}
void push(Stack& s, int x) {
	s.a[++s.top] = x;
}
int pop(Stack& s) {
	return s.a[s.top--];
}
struct Queue {
	int a[MAX];
	int front;
	int rear;
};
void init(Queue& q) {
	q.front = q.rear = -1;
}
bool isEmpty(Queue q) {
	return q.front < 0;
}
bool isFull(Queue q) {
	return q.rear == MAX;
}
void enQueue(Queue& q, int x) {
	if (isEmpty(q) == true) {
		q.a[++q.front] = x;
		q.rear++;
	}
	else {
		q.a[++q.rear] = x;
	}
}
int deQueue(Queue& q) {
	return q.a[q.front++];
}



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
int countNodeBac2(Node* root) {
	if (root == NULL)
		return 0;
	if (root->left != NULL && root->right != NULL)
		return 1 + countNodeBac2(root->left) + countNodeBac2(root->right);
	else
		return countNodeBac2(root->left) + countNodeBac2(root->right);
}
void outputNode2Children(Node* root) {
	if (root == NULL)
		return ;
	if (root->left != NULL && root->right != NULL) {
		cout << root->value << " ";
	}
	outputNode2Children(root->left);
	outputNode2Children(root->right);
}
void searchStack(Node* root, int x, Stack& s) {
	Node* p = root;
	while (p != NULL && p->value != x) {
		if (x > p->value)
		{
			push(s, p->value);
			p = p->right;
		}
		else {
			push(s, p->value);
			p = p->left;
		}
	}
	if (p != NULL)
		push(s, p->value);
}
void searchQueue(Node* root, int y, Queue& q) {
	Node* p = root;
	while (p != NULL && p->value != y) {
		if (y > p->value)
		{
			enQueue(q, p->value);
			p = p->right;
		}
		else {
			enQueue(q, p->value);
			p = p->left;
		}
	}
	if (p != NULL)
		enQueue(q, y);
}
void pathFromNodeAToB(Node* root, int x, int y) {
	Stack s; init(s);
	Queue q; init(q);
        while(x > root->value && y > root->value || x < root-> value && y < root->value){
            if(x > root->value && y > root->value)
                root= root->right;
            else 
		root=root->left;
        }
	searchStack(root, x, s);
	searchQueue(root, y, q);
	/*while (!isEmpty(s)) {
		int step1 = pop(s);
		int step2 = pop(s);
		cout << "(" << step1 << ", " << step2 << ")" << endl;
		push(s, step2);
		if (s.top == 0)
			break;
	}
	Queue tmp; init(tmp); int temp;
	int step1 = deQueue(q);
	int step2 = deQueue(q);
	do {
		cout << "(" << step1 << ", " << step2 << ")" << endl;
		enQueue(tmp, step2);
		step1 = deQueue(tmp);
		step2 = deQueue(q);
	} while (q.front <= q.rear + 1);*/
	while (!isEmpty(s)) {
		cout << pop(s) << "->";
		if (s.top == 0)
			break;
	}
	while (q.front <= q.rear) {
		cout << deQueue(q);
		if (q.front <= q.rear)
			cout << "->";
		else
			break;
	}
}
//NO UNDERSTADNDING???
int sum(Node* root) {
	if (root == NULL)
		return 0;
	int leftValue = sum(root->left);
	int rightValue = sum(root->right);
	return root->value + leftValue + rightValue;
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
/*//void nlrStack(Node* root,Stack s) {
//	init(s);
//	Node* p = root;
//
//}
//void inorderStack(Node* root) {
//	if (root == nullptr) return;
//
//	stack<Node*> s;
//	Node* current = root;
//
//	while (s.size() > 0 || current != nullptr) {
//		if (current != nullptr) {
//			s.push(current);
//			current = current->left;
//		}
//		else {
//			current = s.top();
//			s.pop();
//			cout << current->value << " ";
//			current = current->right;
//		}
//	}
//}*/

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
	pathFromNodeAToB(root, 5, 21);
	//nlr(root);
	//cout << endl;
	//inorderStack(root);
	//cout << endl;
	//cout << countNode(root) << endl;
	/*addNodeRecursion(root, 40);
	addNodeRecursion(root, 20);
	addNodeRecursion(root, 50);*/
	
	//// cout << searchRecursion(root, 210)<< endl;
	//cout << "=============DELETE============\n";
	//delNodeRecursion(root, 40);
	//lnr(root);
	//cout << endl;
	/*cout << "========MAX===========\n";
	cout << nodeMax(root)->value << endl;*/
	//cout << "===============AVERAGE===============\n"; //31
	/*int tb = sum(root) / countNode(root);
	cout << tb << endl; */
	/*cout << countNodeBac2(root) << endl;
	outputNode2Children(root);*/
	return 0;
}

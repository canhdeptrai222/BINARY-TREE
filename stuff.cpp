#include <iostream>
#include <queue>
#include <stack>
#define MAX 100
using namespace std;
template <typename T>
struct Stack {
	T a[MAX];
	int top;
};
template <typename T>
void init(Stack<T>& s) {
	s.top = -1;
}
template <typename T>
bool isEmpty(Stack<T> s) {
	return s.top < 0;
}
template <typename T>
bool isFull(Stack<T> s) {
	return s.top == MAX;
}
template <typename T>
void push(Stack<T>& s, T x) {
	s.a[++s.top] = x;
}
template <typename T>
T pop(Stack<T>& s) {
	return s.a[s.top--];
}
template <typename T>
T geek(Stack<T> s) {
	return s.a[s.top];
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
		/*Node *parent = NULL;*/
		while (p->value != x)
		{
			//parent = p;
			if (x > p->value)
			{
				if (p->right == NULL) {
					p->right = createNode(x);
					break;
				}
				p = p->right;
			}
			else
			{
				if (p->left == NULL) {
					p->left = createNode(x);
					break;
				}
				p = p->left;
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
				Node* tmp = NULL;
				if (p->left == NULL)
					tmp = p->right;
				else
					tmp = p->left;
				if (p->value > parent->value)
				{
					// delete node bac 2
					if (p->left != NULL && p->right != NULL)
						searchLeftFinal(p);
					else
					{
						// delete node bac 1 va 0
						parent->right = tmp;
						delete p;
					}
				}
				else if(p->value < parent->value)
				{
					// delete node bac 2
					if (p->left != NULL && p->right != NULL)
						searchLeftFinal(p);
					else
					{
						// delete node bac 1 va 0
						parent->left = tmp;
						delete p;
					}
				}
				else{
					searchLeftFinal(p);
				}
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
template <typename T>
void searchStack(Node* root, int x, Stack<T>& s) {
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
	Stack<int> s; init(s);
	Queue q; init(q);
	while (x > root->value && y > root->value || x < root->value && y < root->value) {
		if (x > root->value && y > root->value)
			root = root->right;
		else
			root = root->left;
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
		if (s.top == 0)
			break;
		cout << pop(s) << "->";
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
void inorderStack(Node* root) {
	if (root == nullptr) return;

	stack<Node*> s;
	Node* current = root;

	while (s.size() > 0 || current != nullptr) {
		if (current != nullptr) {
			s.push(current);
			current = current->left;
		}
		else {
			current = s.top();
			s.pop();
			cout << current->value << " ";
			current = current->right;
		}
	}
}
void lnrStack(Node* root) {
	Stack<Node*> s;
	init(s);
	Node* p = root;
	while (p != NULL || !isEmpty(s)) {
		if (p != NULL) {
			push(s, p);
			p = p->left;
		}
		else {
			p = pop(s);
			cout << p->value << " ";
			p = p->right;
		}
	}
}
//template <typename T>
void nlrStack(Node* root) {
	Stack<Node*> s;
	init(s);
	push(s, root);
	while (!isEmpty(s)) {
		Node* p = pop(s);
		cout << p->value << " ";
		if (p->right != NULL)
			push(s, p->right);
		if (p->left != NULL)
			push(s, p->left);
	}
}
void lrnUsing2Stack(Node* root) {
	Stack<Node*> s1; init(s1);
	Stack<Node*> s2; init(s2);
	push(s1, root);
	while (!isEmpty(s1)) {
		Node* cur = pop(s1);
		push(s2, cur);
		if (cur->left != NULL) {
			push(s1, cur->left);
		}
		if (cur->right != NULL) {
			push(s1, cur->right);
		}
	}
	while (!isEmpty(s2))
		cout << pop(s2)->value << " ";
	cout << endl;
}
void lrnUsing1Stack(Node* root) {
	Stack<Node*>s;
	init(s);
	Node* current = root;
	while (true) {
		if (current != NULL) {
			push(s, current);
			current = current->left;
		}
		else {
			if (isEmpty(s))
				break;
			if (geek(s)->right == NULL) {
				current = pop(s);
				cout << current->value << " ";
				while (current == geek(s)->right) {
					cout << geek(s)->value << " ";
					current = pop(s);
					if(isEmpty(s))
						break;
				}
			}
			if (!isEmpty(s))
				current = geek(s)->right;
			else
				current = NULL;
		}
	}
}
void NLR(Node* root) {
	if (root == nullptr) return;

	stack<Node*> s;
	s.push(root);

	while (!s.empty()) {
		Node* current = s.top();
		s.pop();

		cout << current->value << " ";

		if (current->right != nullptr) {
			s.push(current->right);
		}

		if (current->left != nullptr) {
			s.push(current->left);
		}
	}
}
void deleteAllNodes(Node*& root) {
	if (root == nullptr) return;

	deleteAllNodes(root->left);
	deleteAllNodes(root->right);

	delete root;
	root = nullptr;
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
	lrnUsing2Stack(root);
	lrnUsing1Stack(root);
	
	deleteAllNodes(root);
	cout << "\n=========clear==========\n";
	lnr(root);
	return 0;
}

#include <iostream>
#include <stack>
#include <queue>
#include <math.h>
using namespace std;

struct Node {
	int value;
	Node* left;
	Node* right;
	int height;
};

void init(Node*& root) {
	root = NULL;
}

Node* createNode(int x) {
	Node* p = new Node;
	p->value = x;
	p->left = NULL;
	p->right = NULL;
	p->height = 1;
	return p;
}

int height(Node* root) {
	if (root == NULL)
		return 0;
	return root->height;
}
int max(int a, int b) {
	return a > b ? a : b;
}
void rightRotate(Node*& root) {
	Node* x = root->left;
	root->left = x->right;
	x->right = root;
	root->height = max(height(root->left), height(root->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	root = x;
}
void leftRotate(Node*& root) {
	Node* x = root->right;
	root->right = x->left;
	x->left = root;
	root->height = max(height(root->left), height(root->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	root = x;
}
bool isBalanced(Node* node) {
	// Cây rỗng hoặc cây chỉ có một nút luôn cân bằng
	if (node == NULL || (node->left == NULL && node->right == NULL)) {
		return true;
	}

	// Tính toán độ cao của cây con trái và cây con phải
	int leftHeight = height(node->left);
	int rightHeight = height(node->right);

	// Kiểm tra độ chênh lệch chiều cao và đệ quy kiểm tra các cây con
	if (abs(leftHeight - rightHeight) <= 1 &&
		isBalanced(node->left) &&
		isBalanced(node->right)) {
		return true;
	}

	return false;

}
void makeBalance(Node*& root, int x) {
	int balance = height(root->left) - height(root->right);
	if (balance > 1 && root->left->value > x) {
		rightRotate(root);
	}
	else if (balance < -1 && root->right->value < x) {
		leftRotate(root);
	}
	else if (balance > 1 && root->left->value < x) {
		leftRotate(root->left);
		rightRotate(root);
	}
	else if (balance < -1 && root->right->value > x) {
		rightRotate(root->right);
		leftRotate(root);
	}
}
int getBalance(Node* root) {
	return height(root->left) - height(root->right);
}
void addNode(Node*& root, int x) {
	if (root == NULL)
		root = createNode(x);
	else {
		if (x > root->value)
			addNode(root->right, x);
		else if (x < root->value)
			addNode(root->left, x);
		else
			return;
		root->height = 1 + max(height(root->left), height(root->right));
		makeBalance(root, x);
	}
}
void leftNodeFinal(Node*& p, Node*& q) {
	if (q->left == NULL) {
		p->value = q->value;
		p = q;
		q = q->right;
	}
	else{
		leftNodeFinal(p, q->left);
		if(q != NULL)
			q->height = 1 + max(height(q->left), height(q->right));
	}
}
void delNode(Node*& root, int x) {
	if (root == NULL)
		return;
	else {
		if (x > root->value)
			delNode(root->right, x);
		else if (x < root->value)
			delNode(root->left, x);
		else if (x == root->value) {
			//luu node can xoa
			Node* p = root;
			if (root->left == NULL)
				root = root->right;
			else if (root->right == NULL)
				root = root->left;
			else
				leftNodeFinal(p, root->right);
			delete p;
			p = NULL;
		}
		if (root != NULL) {
			root->height = 1 + max(height(root->left), height(root->right));
			int balance = getBalance(root);
			if (balance > 1 && getBalance(root->left) >= 0) {
				rightRotate(root);
			}
			else if (balance < -1 && getBalance(root->right) <= 0) {
				leftRotate(root);
			}
			else if (balance > 1 && getBalance(root->left) <= 0) {
				leftRotate(root->left);
				rightRotate(root);
			}
			else if (balance < -1 && getBalance(root->right) >= 0) {
				rightRotate(root->right);
				leftRotate(root);
			}
		}
	}
}
void BFS(Node* root) {
	if (root == NULL)
		return;
	queue<Node*> q;
	Node* p = root;
	q.push(p);
	while (!q.empty()) {
		Node* cur = q.front();
		cout << cur->value << "(" << cur->height << ") ";
		q.pop();
		if (cur->left != NULL) {
			q.push(cur->left);
		}
		if (cur->right != NULL) {
			q.push(cur->right);
		}
	}cout << endl;
}
void deleteALLNode(Node*& root) {
	if (root == NULL)
		return;
	deleteALLNode(root->left);
	deleteALLNode(root->right);
	delete root;
	root = NULL;
}
int main() {
	Node* root;
	init(root);
	//case 1
	/*addNode(root,20);
	addNode(root, 4);
	addNode(root, 26);
	addNode(root, 3);
	addNode(root, 9);*/
	//before add 20(3) 4(2) 26(1) 3(1) 9(1)
	//addNode(root, 15);
	//after add 9(3) 4(2) 20(2) 3(1) 15(1) 26(1)
	//case 2
	/*addNode(root,20);
	addNode(root, 4);
	addNode(root, 26);
	addNode(root, 3);
	addNode(root, 9);
	addNode(root, 21);
	addNode(root, 30);
	addNode(root, 2);
	addNode(root, 7);
	addNode(root, 11);*/
	//before add 20(4) 4(3) 26(2) 3(2) 9(2) 21(1) 30(1) 2(1) 7(1) 11(1)
	//addNode(root, 15);
	//after add 9(4) 4(3) 20(3) 3(2) 7(1) 11(2) 26(2) 2(1) 15(1) 21(1) 30(1)
	//case 3
	/*addNode(root, 2);
	addNode(root, 1);
	addNode(root, 4);
	addNode(root, 3);
	addNode(root, 5);
	delNode(root, 1);*/
	//res = 4(3) 2(2) 5(1) 3(1)
	//case 4
	/*addNode(root, 6);
	addNode(root, 9);
	addNode(root, 2);
	addNode(root, 1);
	addNode(root, 4);
	addNode(root, 8);
	addNode(root, 11);
	addNode(root, 3);
	addNode(root, 5);
	addNode(root, 7);
	addNode(root, 10);
	addNode(root, 12);
	addNode(root, 13);
	delNode(root, 1);*/
	//res = 6(5) 4(3) 9(4) 2(2) 5(1) 8(2) 11(3) 3(1) 7(1) 10(1) 12(2) 13(1)
	//case 5
	/*addNode(root, 5);
	addNode(root, 2);
	addNode(root, 8);
	addNode(root, 1);
	addNode(root, 3);
	addNode(root, 7);
	addNode(root, 10);
	addNode(root, 4);
	addNode(root, 6);
	addNode(root, 9);
	addNode(root, 11);
	addNode(root, 12);
	delNode(root, 1);*/
	//res = 8(4) 5(3) 10(3) 3(2) 7(2) 9(1) 11(2) 2(1) 4(1) 6(1) 12(1)
	//case 6
	addNode(root, 8);
	addNode(root, 3);
	addNode(root, 10);
	addNode(root, 2);
	addNode(root, 5);
	addNode(root, 9);
	addNode(root, 12);
	addNode(root, 1);
	addNode(root, 4);
	addNode(root, 6);
	addNode(root, 11);
	addNode(root, 7);
	delNode(root, 10);
	/*if (isBalanced(root))
		cout << "1";*/
	BFS(root);
	deleteALLNode(root);
	BFS(root);
	return 1;
}

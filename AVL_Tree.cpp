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

struct AVLTree {
	Node* root;
};

void init(AVLTree& r) {
	r.root = NULL;
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

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

int getBalance(Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

Node* insert(Node* node, int key) {
    /* 1. Perform normal BST insertion */
    if (node == NULL)
        return createNode(key);

    if (key < node->value)
        node->left = insert(node->left, key);
    else if (key > node->value)
        node->right = insert(node->right, key); 

    else // Equal keys not allowed
        return node;

    /* 2. Update height   
 */
    node->height = 1 + max(height(node->left), height(node->right));

    /* 3. Get the balance factor of this ancestor */
    int balance = getBalance(node); 


    // Balancing using a loop to avoid recursion
    while (abs(balance) > 1) {
        // Left Left Case
        if (balance > 1 && key < node->left->value) {
            node = rightRotate(node);
            balance = getBalance(node);
        }

        // Right Right Case
        if (balance < -1 && key > node->right->value) {
            node = leftRotate(node);
            balance = getBalance(node);
        }

        // Left Right Case
        if (balance > 1 && key > node->left->value) {
            node->left = leftRotate(node->left);
            node = rightRotate(node);
            balance = getBalance(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->value) {
            node->right = rightRotate(node->right);
            node = leftRotate(node);
            balance = getBalance(node);
        }
    }

    /* return the (unchanged) node pointer */
    return node;
}


//int max(int a, int b) {
//	return a > b ? a : b;
//}
//Node* max(Node* a, Node* b) {
//	if (a->height > b->height)
//		return a;
//	return b;
//}
//bool getBalance(Node* q) {
//	if (abs(height(q->left) - height(q->right)) > 1)
//		return false;
//	return true;
//}
//Node* checkBalance(AVLTree r) {
//	queue<Node*> q;
//	Node* p = r.root;
//	q.push(p);
//	while (!q.empty()) {
//		Node* cur = q.front();
//		q.pop();
//		if (!getBalance(cur))
//			return cur;
//		if (cur->left != NULL)
//			q.push(cur->left);
//		if (cur->right != NULL)
//			q.push(cur->right);
//	}
//	return NULL;
//}
//void rightRotate(Node*& tmp, Node* parent) {
//	Node* p = tmp;
//	Node* q = tmp->left;
//	if (parent == NULL) {
//		p->left = q->right;
//		q->right = p;
//	}
//	else {
//		p->left = q->right;
//		q->right = p;
//		if (tmp->value < parent->value)
//			parent->left = q;
//		else
//			parent->right = q;
//	}
//	tmp->height = max(height(p->left), height(p->right)) + 1;
//	q->height = max(height(q->left), height(q->right)) + 1;
//}
//void addNode(AVLTree& r, int x) {
//	stack<Node*> update;
//	stack<Node*> check;
//	if (r.root == NULL)
//		r.root = createNode(x);
//	else {
//		Node* p = r.root;
//		Node* parent = NULL;
//		while (p != NULL && p->value != x) {
//			update.push(p);
//			parent = p;
//			//p->height = max(height(parent->left), height(parent->right)) + 1;
//			if (x > p->value)
//				p = p->right;
//			else
//				p = p->left;
//		}
//		if (p == NULL) {
//			if (x > parent->value)
//				parent->right = createNode(x);
//			else
//				parent->left = createNode(x);
//			//update height
//			while (!update.empty()) {
//				update.top()->height = max(height(update.top()->left), height(update.top()->right)) + 1;
//				check.push(update.top());
//				update.pop();
//			}
//			//cout << 1 << endl;
//			Node* tmp = NULL;
//			while (!check.empty()) {
//				if (getBalance(check.top()) == false) {
//					tmp = check.top();
//					check.pop();
//					break;
//				}
//				check.pop();
//			}
//			if (tmp != NULL) {
//				rightRotate(tmp, check.top());
//			}
//		}
//		
//	}
//}

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

void addNode(AVLTree& r, int x) {
    r.root = insert(r.root, x);
}


Node* search(Node* root, int x)
{
	Node* p = root;
	while (p != NULL && p->value != x)
	{
		if (x > p->value)
			p = p->right;
		else
			p = p->left;
	}
	return p;
}
int main() {
	Node* r = NULL;
	AVLTree root;
	init(root);
	addNode(root, 40);
	addNode(root, 20);
	addNode(root, 60);
	addNode(root, 25);
	addNode(root, 15);
	addNode(root, 10);
	if (isBalanced(root.root))
		cout << "balance" << endl;
	else
		cout << "not balance" << endl;
	cout << search(root.root, 40)->height << endl;
	cout << search(root.root, 20)->height << endl;
	return 1;
}
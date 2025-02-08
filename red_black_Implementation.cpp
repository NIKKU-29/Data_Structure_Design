#include <iostream>
using namespace std;

// Red-Black Tree Node Structure
struct Node {
    int data;
    Node *parent, *left, *right;
    bool isRed; // true = red, false = black

    Node(int val) {
        data = val;
        parent = left = right = nullptr;
        isRed = true; // New nodes are always red
    }
};

class RedBlackTree {
private:
    Node* root;

    // Left Rotate
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // Right Rotate
    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nullptr)
            y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    // Fix Red-Black Tree violations after insertion
    void fixInsert(Node* z) {
        while (z->parent != nullptr && z->parent->isRed) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right; // Uncle node
                if (y != nullptr && y->isRed) {
                    z->parent->isRed = false;
                    y->isRed = false;
                    z->parent->parent->isRed = true;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->isRed = false;
                    z->parent->parent->isRed = true;
                    rightRotate(z->parent->parent);
                }
            } else { 
                Node* y = z->parent->parent->left;
                if (y != nullptr && y->isRed) {
                    z->parent->isRed = false;
                    y->isRed = false;
                    z->parent->parent->isRed = true;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->isRed = false;
                    z->parent->parent->isRed = true;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->isRed = false;
    }

public:
    RedBlackTree() { root = nullptr; }

    // Insert a new node
    void insert(int data) {
        Node* newNode = new Node(data);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (newNode->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        newNode->parent = y;
        if (y == nullptr)
            root = newNode;
        else if (newNode->data < y->data)
            y->left = newNode;
        else
            y->right = newNode;

        fixInsert(newNode);
    }

    // Inorder traversal (sorted order)
    void inorder(Node* node) {
        if (node == nullptr)
            return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void printTree() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    RedBlackTree rbt;
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(15);
    rbt.insert(5);

    cout << "Red-Black Tree (Inorder Traversal): ";
    rbt.printTree();

    return 0;
}

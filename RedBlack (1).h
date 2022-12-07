
#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int ID;
    float score;
    Node* parent;
    Node* left;
    Node* right;
    int color;
};

typedef Node* NodePtr;

class RedBlackTree {
private:
    NodePtr root;
    NodePtr TNULL;
    int size;
    float sum;
    float avg;

    void initializeNULLNode(NodePtr node, NodePtr parent) {
        node->score = 0;
        node->ID = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }

    // Preorder
    void preOrderHelper(NodePtr node) {
        if (node != TNULL) {
            cout << node->ID << " " << node->score << endl;
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    // Inorder
    void inOrderHelper(NodePtr node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
            cout << node->ID << " " << node->score << endl;
            inOrderHelper(node->right);
        }
    }

    // Post order
    void postOrderHelper(NodePtr node) {
        if (node != TNULL) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->ID << " " << node->score << endl;
        }
    }


    // For balancing the tree after deletion
    void rbTransplant(NodePtr u, NodePtr v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    // For balancing the tree after insertion
    void insertFix(NodePtr k) {
        NodePtr u;
        while (k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            }
            else {
                u = k->parent->parent->right;

                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }



    void printHelper(NodePtr root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            }
            else {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = root->color ? "RED" : "BLACK";
            cout << root->ID << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

public:
    RedBlackTree() {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
        sum = 0;
        size = 0;
        avg = 0;
    }

    void preorder() {
        preOrderHelper(this->root);
    }

    void inorder() {
        inOrderHelper(this->root);
    }

    void postorder() {
        postOrderHelper(this->root);
    }

    NodePtr searchTree(int k) {
        return searchTreeHelper(this->root, k);
    }

    void searchIDTree(int key) {
        searchIDTreeHelper(this->root, key);
    }
    void searchIDTreeHelper(NodePtr node, int key) {
        if (node == TNULL) {
            return;
        }
        if (node->ID == key) {
            cout << "ID: " << node->ID << "  Score: " << node->score << endl;
        }
        else {
            searchIDTreeHelper(node->left, key);
            searchIDTreeHelper(node->right, key);
        }
    }

    NodePtr searchTreeHelper(NodePtr node, int ID) {
        if (node == TNULL || ID == node->score) {
            return node;
        }

        if (ID < node->score) {
            return searchTreeHelper(node->left, ID);
        }
        return searchTreeHelper(node->right, ID);
    }
    NodePtr minimum(NodePtr node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    NodePtr maximum(NodePtr node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

    NodePtr successor(NodePtr x) {
        if (x->right != TNULL) {
            return minimum(x->right);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    NodePtr predecessor(NodePtr x) {
        if (x->left != TNULL) {
            return maximum(x->left);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->left) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void leftRotate(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(NodePtr x) {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Inserting a node
    void insert(int identification, float score) {
        NodePtr node = new Node;
        node->parent = nullptr;
        node->ID = identification;
        node->score = score;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;
        size++;
        sum += score;

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->score < x->score) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        }
        else if (node->score < y->score) {
            y->left = node;
        }
        else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        insertFix(node);
    }

    NodePtr getRoot() { // Get function return root
        return this->root;
    }

    float getAverage() { // Get function returns average applicant score
        avg = sum / (float)size;
        return avg;
    }

    // Print Tree
    void printTree() {
        if (root) {
            printHelper(this->root, "", true); // Calls print helper function
        }
    }

    // Function adds top applicants to queue
    queue<pair<int, float>> topNodes(int size) { // Returns updated queue
        queue <pair <int, float>> result;
        topNodesHelper(size, result, this->root); // Calls helper recursive function
        return result;
    }

    // Helper function for Top Applicants method
    void topNodesHelper(int size, queue<pair<int, float>>& result, NodePtr node) { // Adds top applicants to queue
        if (node != TNULL) {
            topNodesHelper(size, result, node->left);
            result.emplace(node->ID, node->score);
            if (result.size() > size) {
                result.pop();
            }
            topNodesHelper(size, result, node->right); // Recursive Function
        }
    }
};



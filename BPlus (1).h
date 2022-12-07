// Searching on a B+ tree in C++

#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
using namespace std;
//int 3 = 3;

// BP node
class NodeB {
    bool IS_LEAF;
    float* key;
    int* ID;
    int size;
    NodeB** ptr;
    friend class BPTree;

public:
    NodeB();
};

// BP tree
class BPTree {
    int size = 0;
    float sum = 0.0;
    NodeB* root;
    NodeB* parent;
    void insertInternal(float score, int ID, NodeB*, NodeB*);
    NodeB* findParent(NodeB*, NodeB*);


public:
    BPTree();
    void search(int);
    void searchID(int key);
    void searchIDHelper(NodeB* cursor, int key);
    void insert(int ID, float score);
    void display(NodeB*);
    NodeB* getRoot();
    float getAverage();
    void findTopsHelper(NodeB* cursor, queue<pair<int, float>>& result, int size);
    queue <pair<int, float>> findTops(int size);
};

NodeB::NodeB() {
    key = new float[3];
    ptr = new NodeB * [3 + 1];
    ID = new int[3];
}

BPTree::BPTree() {
    parent = NULL;
    root = NULL;
}

// Search operation
void BPTree::search(int x) {
    if (root == NULL) {
        cout << "Tree is empty\n";
    }
    else {
        NodeB* cursor = root;
        while (cursor->IS_LEAF == false) {
            for (int i = 0; i < cursor->size; i++) {
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        for (int i = 0; i < cursor->size; i++) {
            if (cursor->key[i] == x) {
                cout << "Found\n";
                return;
            }
        }
        cout << "Not found\n";

    }
}
void BPTree::searchID(int find) {
    NodeB* cursor = this->root;
    searchIDHelper(cursor, find);
}
void BPTree::searchIDHelper(NodeB* cursor, int find) {
    if (cursor != NULL) {
        for (int i = 0; i < cursor->size; i++) {
            if (cursor->ID[i] == find) {
                cout << "ID: " << cursor->ID[i] << "  Score: " << cursor->key[i] << endl;
            }
        }
        if (cursor->IS_LEAF != true) {
            for (int i = 0; i < cursor->size + 1; i++) {
                searchIDHelper(cursor->ptr[i], find);
            }
        }
    }
}
// Insert Operation
void BPTree::insert(int ID, float score) {
    size++;
    sum += score;
    if (root == NULL) {
        root = new NodeB;
        root->key[0] = score;
        root->ID[0] = ID;
        root->IS_LEAF = true;
        root->size = 1;
    }
    else {
        NodeB* cursor = root;
        //NodeB* parent = NULL;
        while (cursor->IS_LEAF == false) {
            parent = cursor;
            for (int i = 0; i < cursor->size; i++) {
                if (score < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        if (cursor->size < 3) {
            int i = 0;
            while (score > cursor->key[i] && i < cursor->size)
                i++;
            for (int j = cursor->size; j > i; j--) {
                cursor->key[j] = cursor->key[j - 1];
            }
            cursor->key[i] = score;
            cursor->size++;
            cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size - 1] = NULL;
        }
        else {
            NodeB* newLeaf = new NodeB;
            float virtualNode[3 + 1];
            for (int i = 0; i < 3; i++) {
                virtualNode[i] = cursor->key[i];
            }
            int i = 0, j;
            while (score > virtualNode[i] && i < 3)
                i++;
            for (int j = 3 + 1; j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
            }
            virtualNode[i] = score;
            newLeaf->IS_LEAF = true;
            cursor->size = (3 + 1) / 2;
            newLeaf->size = 3 + 1 - (3 + 1) / 2;
            cursor->ptr[cursor->size] = newLeaf;
            newLeaf->ptr[newLeaf->size] = cursor->ptr[3];
            cursor->ptr[3] = NULL;
            for (i = 0; i < cursor->size; i++) {
                cursor->key[i] = virtualNode[i];
            }
            for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
                newLeaf->key[i] = virtualNode[j];
            }
            if (cursor == root) {
                NodeB* newRoot = new NodeB;
                newRoot->ID[0] = ID;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newLeaf;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            }
            else {
                insertInternal(newLeaf->key[0], newLeaf->ID[0], parent, newLeaf);
            }
        }
    }
}

float BPTree::getAverage() {
    return sum / (float)size;
}

// Insert Operation
void BPTree::insertInternal(float score, int ID, NodeB* cursor, NodeB* child) {
    if (cursor->size < 3) {
        int i = 0;
        while (score > cursor->key[i] && i < cursor->size)
            i++;
        for (int j = cursor->size; j > i; j--) {
            cursor->key[j] = cursor->key[j - 1];
        }
        for (int j = cursor->size + 1; j > i + 1; j--) {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->key[i] = score;
        cursor->size++;
        cursor->ptr[i + 1] = child;
    }
    else {
        NodeB* newInternal = new NodeB;
        float virtualKey[3 + 1];
        NodeB* virtualPtr[3 + 2];
        for (int i = 0; i < 3; i++) {
            virtualKey[i] = cursor->key[i];
        }
        for (int i = 0; i < 3 + 1; i++) {
            virtualPtr[i] = cursor->ptr[i];
        }
        int i = 0, j;
        while (score > virtualKey[i] && i < 3)
            i++;
        for (int j = 3 + 1; j > i; j--) {
            virtualKey[j] = virtualKey[j - 1];
        }
        virtualKey[i] = score;
        for (int j = 3 + 2; j > i + 1; j--) {
            virtualPtr[j] = virtualPtr[j - 1];
        }
        virtualPtr[i + 1] = child;
        newInternal->IS_LEAF = false;
        cursor->size = (3 + 1) / 2;
        newInternal->size = 3 - (3 + 1) / 2;
        for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
            newInternal->key[i] = virtualKey[j];
        }
        for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
            newInternal->ptr[i] = virtualPtr[j];
        }
        if (cursor == root) {
            NodeB* newRoot = new NodeB;
            newRoot->ID[0] = ID;
            newRoot->key[0] = cursor->key[cursor->size];
            newRoot->ptr[0] = cursor;
            newRoot->ptr[1] = newInternal;
            newRoot->IS_LEAF = false;
            newRoot->size = 1;
            root = newRoot;
        }
        else {
            insertInternal(cursor->key[cursor->size], ID, findParent(root, cursor), newInternal);
        }
    }
}

// Find the parent
NodeB* BPTree::findParent(NodeB* cursor, NodeB* child) {
    //NodeB* parent = NULL;
    if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF) {
        return NULL;
    }
    for (int i = 0; i < cursor->size + 1; i++) {
        if (cursor->ptr[i] == child) {
            parent = cursor;
            return parent;
        }
        else {
            parent = findParent(cursor->ptr[i], child);
            if (parent != NULL)
                return parent;
        }
    }
    return parent;
}

// Print the tree
void BPTree::display(NodeB* cursor) {
    if (cursor != NULL) {
        for (int i = 0; i < cursor->size; i++) {
            cout << cursor->ID << " " << cursor->key[i] << endl;
        }
        cout << "\n";
        if (cursor->IS_LEAF != true) {
            for (int i = 0; i < cursor->size + 1; i++) {
                display(cursor->ptr[i]);
            }
        }
    }
}

// Get the root
NodeB* BPTree::getRoot() {
    return root;
}

void BPTree::findTopsHelper(NodeB* cursor, queue<pair<int, float>>& result, int size) {
    if (cursor != NULL) {
        for (int i = 0; i < cursor->size; i++) {
            result.emplace(cursor->ID[i], cursor->key[i]);
            if (result.size() > size) {
                result.pop();
            }
        }
        if (cursor->IS_LEAF != true) {
            for (int i = 0; i < cursor->size + 1; i++) {
                findTopsHelper(cursor->ptr[i], result, size);
            }
        }
    }
}

queue<pair<int, float>> BPTree::findTops(int size) {
    queue<pair<int, float>> result;
    findTopsHelper(this->root, result, size);
    return result;
}

#include <vector>
#include "Applicant.h"
#include "BPlus.h"
#include "RedBlack.h"
struct manager{
    vector<Applicant> data;
    BPTree BPlusTree;
    RedBlackTree RBTtree;
    void buildBPlusTree();
    void buildRedBlackTree();
};
void manager::buildBPlusTree() {

}
void manager::buildRedBlackTree() {
    
}


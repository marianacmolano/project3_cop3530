#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Applicant struct- Creates nodes for Trees
struct Applicant {
    string applName;
    Applicant* left;
    Applicant* right;
    Applicant* parent;
    float score;
    int applicantID;


    Applicant() { // Default constructor
        score = 0;
        applicantID = 00000000; // 8 digit ID num
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    Applicant(int id, float scr) {
        applicantID = id;
        score = scr;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    int getScore(Applicant* node) {
        if(node == nullptr)
            return 0;
        else {
            //return score
            return node->score;
        }
    }
};
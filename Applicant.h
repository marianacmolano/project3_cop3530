#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Applicant struct- Creates nodes for Trees
struct Applicant{
    int applicantID;
    float score;


    Applicant() { // Default constructor
        applicantID = 00000000; // 8 digit ID num
        score = 0.0;
    }

    Applicant(int id, float scr) {
        applicantID = id;
        score = scr;
    }
};

//main.cpp
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "manager.h"
#include <string>
#include "Applicant.h";
using namespace std;

// Function calculates applicant score
float calcluateScore(int degs, float gpa, int experience, int diverse, int letter, int time, int interview);

// Function Reads in data
manager ReadFile(string file);

int main() { 
	
    string fileName;
    int choice;

    cout << setw() << "Candidate Selection Database" << endl;
    cout << "Select applicant dataset (.csv): " << endl;
    cin >> fileName;

    manager manage = ReadFile(fileName);
    manage.buildBPlusTree();
    manage.buildRedBlackTree();
    cout << "Menu" << endl;
    cout << "1. See individual applicant score" << endl;
    cout << "2 Generate applicant score sheet" << endl;
    cout << "3. Display top 50 applicants" << endl;

    cin >> choice;

    if (choice == 1) {  // See individual applicant score
        string in;
        cout << "Input applicant ID: " << endl;
        cin >> in;
        int find = stoi(in);
    }
    else if (choice == 2) { // Generate applicant score sheet


    }
    else if (choice == 3) // display top 50


}

float calcluateScore(int degs, float gpa, int experience, int diverse, int letter, int time, int interview) {
    float score;
    score = experience*20 + gpa*5 + time*5 + degs*20 + letter*10 + interview*25 + diverse*15;
    return score;
}

manager ReadFile(string file) {
    manager manage;
    ifstream inFile(file);
    int id;
    int degs;
    int interview;
    float gpa;
    int experience;
    int diverse;
    int letter;
    int time; // in min? or seconds?

    if (!inFile.is_open()) {
        cout << "Could not open " << file << "!!!" << endl;
        return manager();
    }

    // Read Data
    string temp;

    // Reads in header
    getline(inFile, temp);

    while (getline(inFile, temp)) {
        stringstream stream(temp);

        getline(stream, temp, ',');
        id = stoi(temp);

        getline(stream, temp, ',');
        degs = stoi(temp);

        getline(stream, temp, ',');
        gpa = stof(temp);

        getline(stream, temp, ',');
        experience = stoi(temp);

        getline(stream, temp, ',');
        letter = stoi(temp);

        getline(stream, temp, ',');
        time = stoi(temp);
	
        getline(stream, temp, ',');
        interview = stoi(temp);
	
	getline(stream, temp, ',');
        diverse = stoi(temp);


        int score = calcluateScore(degs, gpa, experience, diverse, letter, time, interview);

        if (score > 50) {
            Applicant person(id, score);
            manage.data.push_back(person);
        }

    }
    return manage;
}

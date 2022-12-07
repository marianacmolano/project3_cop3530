//main.cpp
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include "RedBlack (1).h"
#include "BPlus (1).h"
using namespace std;

// Function calculates applicant score
float calcluateScore(int degs, float gpa, int experience, int diverse, int letter, int time, int interview);


int main() {

    // Initialize variables
    string fileName;
    int choice;
    int dataStruct;

    cout << setw(40);
    cout << "Candidate Selection Database" << endl;
    cout << setw(20);
    cout << "Use this tool to help narrow down your applicant pool!" << endl;
    cout << "\nSelect applicant dataset (.csv): " << endl;
    cin >> fileName;

    cout << "\nSelect Datastructure:" << endl;
    cout << "1 = Red-Black Tree" << endl;
    cout << "2 = B-Plus Tree" << endl;
    cin >> dataStruct;

    // Intitalize Tree Objects
    RedBlackTree rt;
    BPTree bt;

     // R E A D - I N  D A T A
         ifstream inFile(fileName);
         int id;
         int degs;
         int interview;
         float gpa;
         int experience;
         int diverse;
         int letter;
         int time;

         // Check if file is open
         if (!inFile.is_open()) {
             cout << "Could not open " << fileName << "!!!" << endl;
             return 0;
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

             float score = calcluateScore(degs, gpa, experience, diverse, letter, time, interview);
             if (score > 50){
                 //cout << id << ", " << score << endl;
                 switch (dataStruct) {
                 case 1:
                     rt.insert(id, score);
                     break;
                 case 2:
                     bt.insert(id, score);
                     break;
                 }
             }

         }
        
        //  U S E R  M E N U 
        cout << "\nMenu" << endl;
        cout << "1. Display individual applicant score" << endl;
        cout << "2. Display average score" << endl;
        cout << "3. Display top # of applicants" << endl;
    
        cin >> choice;

        if (choice == 1) {  // See individual applicant score
            string temp;
            cout << "\nInput applicant ID: ";
            cin >> temp;
            int in = stoi(temp);
            switch (dataStruct) {
            case 1:
                rt.searchIDTree(in);
                break;
            case 2:
                bt.searchID(in);
                break;
            }
        }
        else if (choice == 2) { // Display average score
            cout << "\nAverage Score: ";
            switch (dataStruct) {
            case 1:
                cout << rt.getAverage() << endl;
                break;
            case 2:
                cout << bt.getAverage() << endl;
                break;
            }
        }
        else if (choice == 3) { // Display top 50
            cout << "\nTop Applicants/Scores: " << endl;
            switch (dataStruct) {
            case 1: {
                string size;
                cout << "How many of the top applicants would you like?" << endl;
                cin >> size;
                queue<pair<int, float>> tops = rt.topNodes(stoi(size));
                while (!tops.empty()) {
                    cout << "ID: " << tops.front().first << "   Score: " << tops.front().second << endl;
                    tops.pop();
                }
                break;
            }
            case 2:
                string size;
                cout << "How many of the top applicant scores would you like?" << endl;
                cin >> size;
                queue<pair<int, float>> tops = bt.findTops(stoi(size));
                while (!tops.empty()) {
                    cout << "Score: " << tops.front().second << endl;
                    tops.pop();
                }
                break;
            }
        }
        else {
            cout << "Invalid option detected..." << endl;
            cout << "Try again later!" << endl;
            cout << "Bye, bye, nowww" << endl;
        }
        return 0;
};

float calcluateScore(int degs, float gpa, int experience, int diverse, int letter, int time, int interview) {
    float score;
    score = experience * 200 + gpa * 50 + time * 50 + degs * 200 + letter * 100 + interview * 250 + diverse * 150;
    score = score / 500;
    return score;
}
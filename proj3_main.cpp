//main.cpp
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

//#include "Applicant.h";
using namespace std;

float calcluateScore(int degs, float gpa, int experience, int diverse, int letter, int time, int interview) {
	float score;
	score = experience*20 + gpa*5 + time*5 + degs*20 + letter*10 + interview*25 + diverse*15;
	return score;
}

void ReadFile(string file) {
	ifstream inFile(file);
	string name;
	int id;
	int degs;
	float gpa;
	int experience;
	int diverse;
	int letter;
	int time; // in min? or seconds?

	if (!inFile.is_open()) {
		cout << "Could not open " << file << "!!!" << endl;
		return 0;		
	}
	
	// Read Data
	string temp;
	
	// Reads in header
	getline(inFile, temp);
	
	while (getline(inFile, temp)) {
		istringstram stream(temp);
		
		getline(stream, name, ',');
		
		getline(stream, temp, ',');
		id = stoi(temp);
		
		getline(stream, temp, ',');
		degs = stoi(temp); 
		
		getline(stream, temp, ',');
		gpa = stof(temp);
		
		getline(stream, temp, ',');
		experience = stoi(temp);
		
		getline(stream, temp, ',');
		diverse = stoi(temp);
		
		getline(stream, temp, ',');
		letter = stoi(temp);
		
		getline(stream, temp, ',');
		time = stoi(temp);
		
		getline(stream, temp, ',');
		interview = stoi(temp);
		
		int score = calcluateScore(degs, gpa, experience, diverse, letter, time, interview);
		
		if (score > 50) {
			Applicant person(name, id, score);
		}
		
	}
	
}

int main() {

// Print Input
string dataSet;
int choice;

cout << setw(40) << "Candidate Selection Database" << endl;
cout << "Select applicant dataset (.csv): " << endl;
cin >> dataSet;

ReadFile(string dataSet);

cout << "Menu" << endl;
cout << "1. See individual applicant score" << endl;
cout << "2 Generate applicant score sheet" << endl;
cout << "3. Display top 50 applicants" << endl;

cin >> choice;

if (choice == 1)  // See individual applicant score

else if (choice == 2)  // Generate applicant score sheet
		
		
else if (choice == 3) // display top 50 




}


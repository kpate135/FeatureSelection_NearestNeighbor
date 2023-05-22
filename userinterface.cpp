#include <iostream>
#include <string>
using namespace std;

void introduction(){
    int feNum;
    int choice;
    cout << "Welcome to Group 3's CS170 Project 2 - Machine Learning Feature Selection Algorithm." << endl;
    cout << "Please enter the total number of features: ";
    cin >> feNum; 
    cout << endl;
    cout << "Please pick from the following algorithms to run." << endl; 
    cout << "\t 0 - Forward Selection" << endl;
    cout << "\t 1 - Backward Elimination" << endl;
    //cout << "\t 2 - Group 3 Algorithm";
    cout << endl;
    cout << "User Choice: ";
    cin >> choice;
}
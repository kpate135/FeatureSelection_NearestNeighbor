#include <iostream>
#include "part1.cpp"
#include <string>
#include <cmath>
#include <time.h>
using namespace std;

void introduction(){
    srand(time(0));
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
    if(choice != 0 && choice != 1){
        cout << "User Choice is not accepted...Restarting Programs..." << endl;
        introduction();
    }
    else if(choice == 0){
     cout << "Calling Forward Selection Search" << endl;
     forward_selection_search(feNum);
     cout << endl;       
    }
    else if(choice == 1){
     cout << "Calling Backward Elimination Search" << endl;
     backward_elimination_search(feNum);
     cout << endl;
    }

    cout << "Ending Program..." << endl;
}
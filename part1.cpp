#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <cmath>
#include <time.h>

using namespace std;


int leave_one_out_cross_validation() {
    int value;
    value = rand() % 101;

    return value;
}

//greedy forward selection search
void forward_selection_search(int N) { //for part 1 instead of passing in data we pass in N (num of features)
    unordered_set<int> current_set_of_features;
    unordered_set<int> bestOverallSet;
    int bestOverallAccuracy; //accuracy may be a float in later parts
    
    int initialAccuracy = leave_one_out_cross_validation();
    cout << "Using no features and \"random\" evaluation, I get an accuracy of " << initialAccuracy << "%" << endl; //default rate
    bestOverallAccuracy = initialAccuracy;

    cout << endl << "Beginning search" << endl;
    for (int i = 1; i <= N; ++i) { //level of the search tree
        //cout << "On the " << i << "'th level of the search tree" << endl;
        cout << endl;
        int feature_to_add_at_this_level;
        int best_so_far_accuracy = 0;

        for (int k = 1; k <= N; ++k) { //find which feature we add to give current_set highest accuracy
            if (current_set_of_features.find(k) == current_set_of_features.end()) { //Only consider adding a feature to the set, if not already added.
                //cout << "--Considering adding the " << k << " feature";
                //unordered_set<int> new_set = current_set_of_features;
                //new_set.insert(k); //pass in data and new_set (with k feature) to leave_one_out_cross_validation() 
                int accuracy = leave_one_out_cross_validation(); //pass in data, current_set_of_features, k (current feature). Tests {current_set + kth feature} accuracy
                //cout << " with accuracy " << accuracy << "%" << endl;
                cout << "\t Using feature(s) {" << k;
                for (int num : current_set_of_features) {
                    cout << "," << num;
                }
                cout << "} accuracy is " << accuracy << "%" << endl;
                if (accuracy > best_so_far_accuracy) {
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level = k; //.push_back(k); 
                }
            }
        }
        current_set_of_features.insert(feature_to_add_at_this_level);
        //cout << "On level " << i << " I added feature " << feature_to_add_at_this_level << " to current set" << endl;
        cout << endl;
        cout << "Feature set {";
        for (int num : current_set_of_features) {
            cout << num << ",";
        }
        cout << '\b';
        cout << "} was best, accuracy is " << best_so_far_accuracy << "%" << endl;

        //check if found a new highest overall accuracy, store the feature and accuracy
        if (best_so_far_accuracy > bestOverallAccuracy) {
            bestOverallSet = current_set_of_features;
            bestOverallAccuracy = best_so_far_accuracy;
        }
        //check if accuracy has decreased at current level
        else if (best_so_far_accuracy < bestOverallAccuracy) {
            break;
        }
    }
    cout << endl;
    cout << "(Warning, Accuracy has decreased!)" << endl;
    cout << "Finished Search!! The best features subset is {";
    for (int num : bestOverallSet) {
        cout << num << ",";
    }
    if (bestOverallSet.size() > 0) {
        cout << '\b';
    }
    cout << "}, which has an accuracy of " << bestOverallAccuracy << "%" << endl;
    
}

//greedy backward elimination search
void backward_elimination_search(int N) { //starts with full set of features and removes one feature at a time.
    unordered_set<int> current_set_of_features;
    for (int i = 1; i <= N; ++i) { //insert every feature from 1 to N to the current_set_of_features
        current_set_of_features.insert(i);
    }
    unordered_set<int> bestOverallSet = current_set_of_features;
    int bestOverallAccuracy; 

    int initialAccuracy = leave_one_out_cross_validation(); //find initial accurracy when passing in current_set (all features)
    cout << "Using all features and \"random\" evaluation, I get an accuracy of " << initialAccuracy << "%" << endl; //default rate
    bestOverallAccuracy = initialAccuracy; 

    cout << endl << "Beginning search" << endl;
    for (int i = 1; i <= N; ++i) { //level of the search tree
        //cout << "On the " << i << "'th level of the search tree" << endl;
        cout << endl;
        int feature_to_remove_at_this_level;
        int best_so_far_accuracy = 0;

        for (int k = 1; k <= N; ++k) { //find which feature we remove to give current_set highest accuracy
            if (current_set_of_features.find(k) != current_set_of_features.end()) { //Only consider removing, if not already removed.
                //cout << "--Considering adding the " << k << " feature";
                //unordered_set<int> new_set = current_set_of_features;
                //new_set.erase(k); //pass in data and new_set (set without k feature) to leave_one_out_cross_validation()
                int accuracy = leave_one_out_cross_validation(); //pass in data, current_set_of_features, k (current feature). Tests {current_set - kth feature} accuracy
                //cout << " with accuracy " << accuracy << "%" << endl;
                cout << "\t Removing {" << k << "}, ";
                cout << "Using feature(s) {";
                for (int num : current_set_of_features) {
                    if (num == k) continue; 
                    cout << num << ",";
                }
                cout << '\b';
                cout << "} accuracy is " << accuracy << "%" << endl;
                if (accuracy > best_so_far_accuracy) {
                    best_so_far_accuracy = accuracy;
                    feature_to_remove_at_this_level = k; 
                }
            }
        }
        current_set_of_features.erase(feature_to_remove_at_this_level); //remove the feature from current set
        //cout << "On level " << i << " I added feature " << feature_to_add_at_this_level << " to current set" << endl;
        cout << endl;
        cout << "Feature set {"; 
        for (int num : current_set_of_features) {
            cout << num << ",";
        }
        cout << '\b';
        cout << "} was best, accuracy is " << best_so_far_accuracy << "%" << endl;

        //check if found a new highest overall accuracy, store the feature and accuracy
        if (best_so_far_accuracy > bestOverallAccuracy) {
            bestOverallSet = current_set_of_features;
            bestOverallAccuracy = best_so_far_accuracy;
        }
        //check if accuracy has decreased at current level
        else if (best_so_far_accuracy < bestOverallAccuracy) {
            break;
        }
    }
    cout << endl;
    cout << "(Warning, Accuracy has decreased!)" << endl;
    cout << "Finished Search!! The best features subset is {";
    for (int num : bestOverallSet) {
        cout << num << ",";
    }
    if (bestOverallSet.size() > 0) {
        cout << '\b';
    }
    cout << "}, which has an accuracy of " << bestOverallAccuracy << "%" << endl;    
}



int main() {
    /*
    cout << "Testing Accuracy function 10 times" << endl;
    for (int i = 0; i < 10; ++i) {
        cout << "Accuracy 1: " << leave_one_out_cross_validation() << endl;
    }
    */
    srand(time(0));
    int features;
    cout << "Welcome to Group 3's CS170 Project 2 - Machine Learning Feature Selection Algorithm" << endl;
    cout << "Please enter the total number of features: ";
    cin >> features;
    cout << endl << "Type the number of the algorithm you want to run." << endl;
    cout << endl << "\t 1) Forward Selection" << endl << "\t 2) Backward Elimination" << endl << "\n\n";
    int algorithmChoice;
    cin >> algorithmChoice;
    while ((algorithmChoice != 1) && (algorithmChoice != 2)) {
        cout << "Invalid choice, please try again" << endl;
        cin >> algorithmChoice;
    }
    switch(algorithmChoice) {
        case 1:
            cout << "Calling Forward Selection Search" << endl;
            forward_selection_search(features);
            break;
        case 2:
            cout << "Calling Backward Elimination Search" << endl;
            backward_elimination_search(features);
            break;
    }
    
    return 0;
}
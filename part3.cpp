#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <cmath>
#include <time.h>
#include <fstream>
#include <sstream>

using namespace std;

class Classifier {
    public:
        void Train(vector<vector<double>> train_data) { //input is the current set of training instances (class label and features)
            this->train_data = train_data;            
        }

        double Test(vector<double> test_instance) { //input is test instance (row of dataset: class label + features for the instance)
            vector<double> object_to_classify(test_instance.begin() + 1, test_instance.end()); //all the features that make up the object (2nd col to last col)
            double label_object_to_classify = test_instance[0]; //class label

            double nearest_neighbor_distance = INT_MAX;
            double nearest_neighbor_location = INT_MAX;
            double nearest_neighbor_label;
            for (int k = 0; k < this->train_data.size(); ++k) { //find nearest neighbor (comparing distance to all objects in training data)
                //if (k == i) continue; //don't compare object to itself

                vector<double> k_object_row(this->train_data[k].begin() + 1, this->train_data[k].end()); //all the features for the k-th object 
                double sum = 0;
                for (int q = 0; q < object_to_classify.size(); ++q) {
                    sum += pow(object_to_classify[q] - k_object_row[q], 2);
                }
                double distance = sqrt(sum);
                if (distance < nearest_neighbor_distance) {
                    nearest_neighbor_distance = distance;
                    nearest_neighbor_location = k;
                    nearest_neighbor_label = this->train_data[nearest_neighbor_location][0];
                }

            }
            return nearest_neighbor_label; //predicted class label
        }

        vector<vector<double>> load(string fileName) {
            vector<vector<double>> data;
            //string fileName = "small-test-dataset.txt";
            string line;
            double number;
            ifstream fin(fileName);

            while (getline(fin, line)) {
                stringstream ss(line);
                vector<double> row;
                while (ss >> number) {
                    //push data to matrix
                    row.push_back(number);
                }
                data.push_back(row);
            }

            fin.close();
            return data;
        }

    private:
        vector<vector<double>> train_data;
};

class Validator {
    public:
        double leave_one_out_cross_validation(vector<vector<double>> data, unordered_set<int> current_set, int feature_to_add) { //returns accuracy
            Classifier classifier;
            
            unordered_set<int> features = current_set;
            if (feature_to_add != 0) {
                features.insert(feature_to_add);
            }
            data = get_data_for_specific_features(data, features);

            int number_correctly_classified = 0;

            for (int i = 0; i < data.size(); ++i) { //loop through each row (each object class label and it's features)
                vector<vector<double>> train_data = data;
                vector<double> test_instance = data[i];
                double label_object_to_classify = test_instance[0];
                train_data.erase(train_data.begin()+i);
                
                classifier.Train(train_data);
                double nearest_neighbor_label = classifier.Test(test_instance);

                if (label_object_to_classify == nearest_neighbor_label) {
                    ++number_correctly_classified;
                }
            }
            double accuracy = double(number_correctly_classified) / data.size();
            //cout << "accuracy: " << accuracy*100 << "%" << endl;
            return accuracy;
        }        

        vector<vector<double>> get_data_for_specific_features(vector<vector<double>> data, unordered_set<int> features) {
            //Ex: features = {1, 3, 7}
            //we want to get a copy of our dataset with all objects but only including features 1, 3, 7 (col's 1, 3, 7)
            vector<vector<double>> newData;
            for (int i = 0; i < data.size(); ++i) { //for each row of data
                //only select the columns (features) we want
                vector<double> newRow;
                newRow.push_back(data[i][0]); //add class label
                for (int j = 1; j < data[i].size(); ++j) { //construct new row with only the features we want
                    if (features.find(j) != features.end()) { //if feature in curr row of data is in the list of features we want 
                        newRow.push_back(data[i][j]);
                    }
                }
                newData.push_back(newRow);
            }
            return newData;
        }

    private:

};

double get_default_rate(vector<vector<double>> data) {
    int class1 = 0;
    int class2 = 0;
    int mostProbableClassSize;
    for (int i = 0; i < data.size(); ++i) {
        if (data[i][0] == 1) {
            ++class1;
        }
        else if (data[i][0] == 2) {
            ++class2;
        }
    }
    if (class1 > class2) {
        mostProbableClassSize = class1;
    }
    else {
        mostProbableClassSize = class2;
    }
    return double(mostProbableClassSize) / double(data.size()); //default rate = most probable class / num of instances    
}

//greedy forward selection search
void forward_selection_search(vector<vector<double>> data) { //for part 1 instead of passing in data we pass in N (num of features)
    int N = data[0].size() - 1; //num of features
    Validator validator;
    
    unordered_set<int> current_set_of_features;
    unordered_set<int> bestOverallSet;
    double bestOverallAccuracy; //accuracy may be a float in later parts
    
    //find default rate
    double initialAccuracy = get_default_rate(data);//leave_one_out_cross_validation();
    cout << "Running nearest neighbor with no features (default rate), using \"leaving-one-out\" evaluation, I get an accuracy of " << initialAccuracy*100 << "%" << endl; //default rate
    bestOverallAccuracy = initialAccuracy;

    cout << endl << "Beginning search" << endl;
    for (int i = 1; i <= N; ++i) { //level of the search tree
        //cout << "On the " << i << "'th level of the search tree" << endl;
        cout << endl;
        int feature_to_add_at_this_level; //index of the feature to add
        double best_so_far_accuracy = 0;

        for (int k = 1; k <= N; ++k) { //find which feature we add to give current_set highest accuracy
            if (current_set_of_features.find(k) == current_set_of_features.end()) { //Only consider adding a feature to the set, if not already added.
                //cout << "--Considering adding the " << k << " feature";
                double accuracy = validator.leave_one_out_cross_validation(data, current_set_of_features, k); //pass in data, current_set_of_features, k (current feature). Tests {current_set + kth feature} accuracy
                //cout << " with accuracy " << accuracy << "%" << endl;
                cout << "\t Using feature(s) {" << k;
                for (int num : current_set_of_features) {
                    cout << "," << num;
                }
                cout << "} accuracy is " << accuracy*100 << "%" << endl;
                if (accuracy > best_so_far_accuracy) {
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level = k; 
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
        if (current_set_of_features.size() > 0) { //bestOverallSet.size() > 0
            cout << '\b';
        }
        cout << "} was best, accuracy is " << best_so_far_accuracy*100 << "%" << endl;

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
    cout << "}, which has an accuracy of " << bestOverallAccuracy*100 << "%" << endl;
    
}

//greedy backward elimination search
void backward_elimination_search(vector<vector<double>> data) { //starts with full set of features and removes one feature at a time.
    int N = data[0].size() - 1; //num of features
    Validator validator;

    unordered_set<int> current_set_of_features;
    for (int i = 1; i <= N; ++i) { //insert every feature from 1 to N to the current_set_of_features
        current_set_of_features.insert(i);
    }
    unordered_set<int> bestOverallSet = current_set_of_features;
    double bestOverallAccuracy; 

    double initialAccuracy = validator.leave_one_out_cross_validation(data, current_set_of_features, 0); //find initial accurracy when passing in current_set (all features)
    cout << "Using all features {";
    for (int num : bestOverallSet) {
        cout << num << ",";
    }
    if (bestOverallSet.size() > 0) {
        cout << '\b';
    }
    cout << "}, I get an accuracy of " << initialAccuracy*100 << "%" << endl; //all features
    bestOverallAccuracy = initialAccuracy; 

    cout << endl << "Beginning search" << endl;
    for (int i = 1; i <= N; ++i) { //level of the search tree
        //cout << "On the " << i << "'th level of the search tree" << endl;
        cout << endl;
        int feature_to_remove_at_this_level; //index of the feature to remove
        double best_so_far_accuracy = 0;

        for (int k = 1; k <= N; ++k) { //find which feature we remove to give current_set highest accuracy
            if (current_set_of_features.find(k) != current_set_of_features.end()) { //Only consider removing, if not already removed.
                //cout << "--Considering adding the " << k << " feature";
                unordered_set<int> features_to_test = current_set_of_features;
                features_to_test.erase(k);
                double accuracy = validator.leave_one_out_cross_validation(data, features_to_test, 0); //pass in data, current_set_of_features, k (current feature). Tests {current_set - kth feature} accuracy
                //cout << " with accuracy " << accuracy << "%" << endl;
                cout << "\t Removing {" << k << "}, ";
                cout << "Using feature(s) {";
                for (int num : current_set_of_features) {
                    if (num == k) continue; 
                    cout << num << ",";
                }
                cout << '\b';
                cout << "} accuracy is " << accuracy*100 << "%" << endl;
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
        if (current_set_of_features.size() > 0) { //bestOverallSet.size() > 0
            cout << '\b';
        }
        cout << "} was best, accuracy is " << best_so_far_accuracy*100 << "%" << endl;

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
    cout << "}, which has an accuracy of " << bestOverallAccuracy*100 << "%" << endl;    
}

int main() {
    srand(time(0));
    string fileName;
    cout << "Welcome to Group 3's CS170 Project 2 - Machine Learning Feature Selection Algorithm" << endl;
    cout << "Type in the name of the file to test: ";
    cin >> fileName;
    cout << endl << "Type the number of the algorithm you want to run." << endl;
    cout << endl << "\t 1) Forward Selection" << endl << "\t 2) Backward Elimination" << endl << "\n\n";
    int algorithmChoice;
    cin >> algorithmChoice;
    while ((algorithmChoice != 1) && (algorithmChoice != 2)) {
        cout << "Invalid choice, please try again" << endl;
        cin >> algorithmChoice;
    }
    Classifier classifier;
    vector<vector<double>> data = classifier.load(fileName); //"small-test-dataset.txt"
    cout << "This dataset has " << data[0].size() - 1 << " features (not including the class attribute), with " << data.size() << " instances." << endl << endl;
    
    switch(algorithmChoice) {
        case 1:
            cout << "Calling Forward Selection Search" << endl << endl;
            forward_selection_search(data);
            break;
        case 2:
            cout << "Calling Backward Elimination Search" << endl << endl;
            backward_elimination_search(data);
            break;
    }

    return 0;
}
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
        void Train(vector<double> train_data) {

        }

        double Test(double test_instance) { 
            double predictedClass;


            return predictedClass;
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

        void classification(vector<vector<double>> data) { //UPDATE: once done, put code within the correct classes with modular design
            //vector<vector<double>> data = load("small-test-dataset.txt");
            int number_correctly_classified = 0;

            for (int i = 0; i < data.size(); ++i) { //loop through each row (each object class label and it's features)
                vector<double> object_to_classify(data[i].begin() + 1, data[i].end()); //all the features that make up the object (2nd col to last col)
                double label_object_to_classify = data[i][0]; //class label

                //cout << "Looping over i, at the " << i+1 << " location" << endl;
                //cout << "The " << i+1 << "'th object is in class " << label_object_to_classify << endl;

                double nearest_neighbor_distance = INT_MAX;
                double nearest_neighbor_location = INT_MAX;
                double nearest_neighbor_label;
                for (int k = 0; k < data.size(); ++k) { //find nearest neighbor (comparing distance to all other objects)
                    if (k == i) continue; //don't compare object to itself
                    //cout << "Ask if " << i+1 << " is nearest neighor with " << k+1 << endl;

                    vector<double> k_object_row(data[k].begin() + 1, data[k].end()); //all the features for the k-th object 
                    double sum = 0;
                    for (int q = 0; q < object_to_classify.size(); ++q) {
                        sum += pow(object_to_classify[q] - k_object_row[q], 2);
                    }
                    double distance = sqrt(sum);
                    if (distance < nearest_neighbor_distance) {
                        nearest_neighbor_distance = distance;
                        nearest_neighbor_location = k;
                        nearest_neighbor_label = data[nearest_neighbor_location][0];
                    }

                }
                //cout << "Object " << i+1 << " is class " << label_object_to_classify << endl;
                //cout << "Its nearest neighbor is " << nearest_neighbor_location << " which is in class " << nearest_neighbor_label << endl;
                if (label_object_to_classify == nearest_neighbor_label) {
                    ++number_correctly_classified;
                }
            }
            double accuracy = double(number_correctly_classified) / data.size();
            cout << "accuracy: " << accuracy*100 << "%" << endl;
        }

    private:
        //vector<vector<double>> data;
};

class Validator {
    public:
        double leave_one_out_cross_validation(vector<vector<double>> data, vector<double> current_set, double feature_to_add) { //returns accuracy
            double accuracy;
            //store the class labels, and the current_set of features + the feature to add columns in a smaller matrix (same # of rows but less columns)


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

int main() {
    Classifier classifier;
    vector<vector<double>> data = classifier.load("small-test-dataset.txt");

    Validator validator;
    unordered_set<int> features = {3, 5, 7};
    cout << "Using features: {";
    for (auto num : features) {
        cout << num << ",";
    }
    cout << '\b' << "}" << endl;
    data = validator.get_data_for_specific_features(data, features);
    classifier.classification(data);

    return 0;
}
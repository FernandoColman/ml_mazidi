//
//  main.cpp
//  Mazidi_Hw2
//
//  Created by Fernando Colman on 9/6/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void print_stats(vector<double> vec);
string covar(vector<double> vec1, vector<double> vec2);
string cor(vector<double> vec1, vector<double> vec2);

double findSum(vector<double> vec);
double findMean(vector<double> vec);
double findMedian(vector<double> vec);
double findRange(vector<double> vec);

int main(int argc, const char * argv[]) {
  string inputLine, rm_in, medv_in;
  ifstream fileIn;
  
  const int MAX_LENGTH = 1000;
  vector<double> rm(MAX_LENGTH);
  vector<double> medv(MAX_LENGTH);
  
  
  // Open Boston.csv
  cout << "Opening Boston.csv" << endl;
  
  fileIn.open("Boston.csv");
  if(!fileIn.is_open()) {
    cout << "Failed to open Boston.csv" << endl;
    return 1;
  }
  
  // Read headings from Boston.csv
  cout << "Reding line 1";
  getline(fileIn, inputLine);
  
  cout << "\nHeadings: " << inputLine << endl;
  
  // Populate vectors with Boston.csv data
  
  int numRows = 0;
  while(fileIn.good()) {
    getline(fileIn, rm_in, ',');        // read until ,
    getline(fileIn, medv_in, '\n');     // read until newline
    
    rm.at(numRows) = stof(rm_in);       // convert strings -> floats, store in vector
    medv.at(numRows) = stof(medv_in);
    
    numRows++;
  }
  
  rm.resize(numRows);      // deallocates empty memory in vector
  medv.resize(numRows);
  
  cout << "New Length: " << rm.size() << endl;
  
  
  // Close Boston.csv
  cout << "Closing file Boston.csv" << endl;
  fileIn.close();
  cout << "Number of records: " << numRows << endl;
  
  // Print summaries of rm and medv
  cout << "\nStats for rm feature" << endl;
  print_stats(rm);
  
  cout << "\nStats for medv" << endl;
  print_stats(medv);
  
  // Print covariance and correlation
  cout << "\n Covariance = " << covar(rm, medv);
  cout << "\n Correlation = " << cor(rm, medv) << endl;
  
  cout << "\n Program finished." << endl;
  
  return 0;
  
}

void print_stats(vector<double> vec) {
  cout << "\tSum: " << findSum(vec) << endl;
  cout << "\tMean: " << findMean(vec) << endl;
  cout << "\tMedian: " << findMedian(vec) << endl;
  cout << "\tRange: " << findRange(vec) << endl;
}

double findSum(vector<double> vec) {
  double ans = 0;
  for(double d:vec)
    ans += d;
  return ans;
}

double findMean(vector<double> vec) {
  double ans = 0;
  for(double d:vec)
    ans += d;
  return ans/vec.size();
}

double findMedian(vector<double> vec) {
  double ans = -1;
  int vSize = vec.size()-1;
  
  sort(vec.begin(),vec.end());
  
  if(vSize % 2 == 0)
    ans = (vec.at(vSize/2) + vec.at((vSize/2) + 1))/2;
  else
    ans = vec.at(vSize/2);
  
  return ans;
}

double findRange(vector<double> vec) {
  double max = *max_element(vec.begin(), vec.end());
  double min = *min_element(vec.begin(), vec.end());
  return max - min;
}

string covar(vector<double> vec1, vector<double> vec2) {
  double mean1 = findMean(vec1);
  double mean2 = findMean(vec2);
  
  double diff1 = 0;
  double diff2 = 0;
  double sumDiff = 0;
  
  for(int i = 0; i < vec1.size(); i++) {
    diff1 = vec1.at(i) - mean1;
    diff2 = vec2.at(i) - mean2;
    sumDiff += diff1 * diff2;
  }
  
  
  double ans = sumDiff / (vec1.size()-1);
  return to_string(ans);
}


string cor(vector<double> vec1, vector<double> vec2) {
  double mean1 = findMean(vec1);
  double mean2 = findMean(vec2);
  
  double diff1 = 0;
  double diff2 = 0;
  
  for(int i = 0; i < vec1.size(); i++) {
    diff1 += pow(vec1.at(i) - mean1, 2);
    diff2 += pow(vec2.at(i) - mean2, 2);
  }
  
  double var1 = diff1 / (vec1.size()-1);
  double var2 = diff2 / (vec2.size()-1);
  
  double sigmas = sqrt(var1) * sqrt(var2);
  double covariance = stod(covar(vec1, vec2));
  double correlation = covariance / sigmas;
  return to_string(correlation);
}





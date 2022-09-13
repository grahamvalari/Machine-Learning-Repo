// Valari Graham 
// CS 4375 - Dr. Mazidi 

// Portfolio C++ Assignment 

#include <iostream>
#include <vector> 
#include <string>
#include <fstream> 
#include <algorithm> 
#include <cmath> 

using namespace std; 

// Function to find the sum of a numeric vector 
double sum(vector<double> x) {
   double sum = 0.0; 
   // Finds the summation of the entire vector 
   for(int i = 0; i < x.size(); i ++){
      sum += x[i];
   }
   return sum; 
}

// Function to find the mean of a numeric vector 
double mean(vector<double> x){

   double finalSum = sum(x);

   double size = x.size(); 

   // Divides the total summation by the size of the vector to find the mean 
   double avg = finalSum / size; 

   return avg; 
}

// Function to find the median of a numeric vector 
double med(vector<double> x){
   int size = x.size(); 

   double median; 

   // Sorts the elements from beginning to end in ascending order 
   sort(x.begin(), x.end());

   // If the number of observations is even, 
   if(size % 2 == 0){
      median = (x[size / 2 - 1] + x[size / 2]) / 2; 
   }
   // If the number of observations is odd 
   else {
      median = x[size / 2]; 
   }

   return median; 
}

// Function to find the range of a numeric vector 
double range(vector<double> x){
   double max = 0; 
   double min = 0; 

   double range; 

   // For loop to parse through the function and find the min and max 
   for(int i = 0; i < x.size(); i ++){
      // If the element is larger than the max, then it becomes the new max
      if (x[i] > max) {
         max = x[i];
      // If the element is smaller than the min, then it becomes the new min
      } else if (x[i] < min){ 
         min = x[i]; 
      }
   }
   // Equation to calculate the range of the vector 
   range = max - min; 
   return range; 
}

// Function to solve the covariance between rm and medv
double covar(vector<double> x, vector<double> y){
   double avg_x = mean(x); 
   double avg_y = mean(y); 

   double num = 0.0; 

   // Numerator of covariance equation 
   for(int i = 0; i <x.size(); i++){

      num += (x[i] - avg_x) * (y[i] - avg_y);
   }

   // Denominator of covariance equation 
   double den = x.size() - 1; 

   // Covariance equation 
   double covariance = num / den; 

   return covariance; 

}

// Function to solve the correlation between rm and medv 
double cor(vector<double> x, vector<double> y){
   // Find the variance of x
   double var_x = covar(x, x);
   // Find the sigma of x 
   double s_x = sqrt(var_x); 

   // Find the variance of y 
   double var_y = covar(y, y); 
   // Find the sigma of y 
   double s_y = sqrt(var_y); 


   // Covariance function 
   double cov = covar(x, y); 
   // Correlation formula 
   double correlation = cov / (s_x * s_y); 

   return correlation; 
}


// Print function to show results of stats 
double print_stats(vector<double> vect){
   // Sum 
   cout << "Sum: " << sum(vect) << endl; 

   // Mean
   cout << "Mean: " << mean(vect) << endl; 

   // Median
   cout << "Median: "<< med(vect) << endl; 

   // Range 
   cout << "Range: " << range(vect) << endl; 

   return 0; 
}


int main(int argc, char** argv) {
   ifstream inFS; 
   string line; 
   string rm_in, medv_in; 
   const int MAX_LEN = 1000; 
   vector<double> rm(MAX_LEN); 
   vector<double> medv(MAX_LEN); 
   
   // Attempt to open file 
   cout << "Opening file Boston.csv" << endl; 
   
   inFS.open("Boston.csv");
   if(!inFS.is_open()) {
      cout << "Could not open file Boston.csv" << endl; 
      return 1; 
   }

   // Can now use inFS as cin 
   // Boston.csv has two doubles 

   cout << "Reading line 1" << endl; 
   getline(inFS, line); 

   // Echo heading 
   cout << "Heading: " << line << endl; 

   int numObservations = 0; 
   while (inFS.good()) {
      getline(inFS, rm_in, ',');
      getline(inFS, medv_in, '\n');

      rm.at(numObservations) = stof(rm_in); 
      medv.at(numObservations) = stof(medv_in); 

      numObservations++; 

   } 

   rm.resize(numObservations); 
   medv.resize(numObservations); 

   cout << "New length: " << rm.size() << endl; 

   cout << "Closing file Boston.csv" << endl; 
   inFS.close(); 

   cout << "Number of records: " << numObservations << endl; 

   cout << "\nStat results for rm: " << endl; 
   print_stats(rm); 

   cout << "\nStat results for medv: " << endl; 
   print_stats(medv); 

   cout << "\n Covariance = " << covar(rm, medv) << endl; 

   cout << "\n Correlation = " << cor(rm, medv) << endl; 

   cout << "\nProgram termianted."; 

   return 0; 

}
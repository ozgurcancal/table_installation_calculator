
#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <functional>
#include <string>
#include <sstream>
#include <iostream>
#include <random>
#include <iomanip>
#include <map>

class Table {

private:

    const int SIZE = 8; // number of legs in x axis. 
    double m=0,c=0;    // parameters of the straight line
    double lower_cutoff = 0, higher_cutoff = 0;
    double x_length = 53.15; //vertical length of the table  

    std::vector<double> best_linear_line;
    std::vector<double> leg_heights;
    std::vector<double> required_dust{ 0,0,0,0,0,0,0,0 };
    std::vector<double> required_leg_length{ 0.98,0.98,0.98,0.98,0.98,0.98,0.98,0.98 }; //
    std::vector<double> x_points{ 0,0,0,0,0,0,0,0 }; //vector which holds the leg points on x axes
    std::map<int, double> mp; // container which holds outlier's index and value

    void generate_x_points(); 
    double find_median(std::vector<double> tvec);
    void find_cutoff();
    void fix_outliers();
    void initialize_best_linear_line(std::vector<double> best_approx_line);  
    void find_linear_mc(int len);
    void required_leg_length_and_soil();

public:
    
    Table(double start_altitude=900.0,double end_altitude=910.0); // Default constructor with configurable start and end altitudes
    Table(std::initializer_list<double> ilist); // Contructor for user given inputs

    std::vector<double> y_points{ 0,0,0,0,0,0,0,0 };

    void generate_random_y_points(double min_alt, double max_alt);
    void run();

};

template<class T>
void print(const T& container) {
    for (const auto& i : container) {
        std::cout << std::setw(10) << std::left << i << " ";
    }
    std::cout << "\n";
}



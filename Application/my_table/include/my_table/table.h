
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
    double m=0,c=0;    // m is the slope
    double lower_cutoff = 0, higher_cutoff = 0;
    double x_length = 53.15; //vertical length of the table  

    std::vector<double> best_linear_line;
    std::vector<double> leg_heights;
    std::vector<double> required_dust{ 0,0,0,0,0,0,0,0 };
    std::vector<double> required_leg_length{ 0.98,0.98,0.98,0.98,0.98,0.98,0.98,0.98 };
    std::vector<double> x_axis{ 0,0,0,0,0,0,0,0 }; //vector which holds the leg points on x axes
    std::map<int, double> mp;  //it holds outlier's index and value 

    double find_median(std::vector<double> tvec);
    void find_cutoff();
    void fix_outliers();
    void initialize_best_linear_line(std::vector<double> best_approx_line);  
    void find_lineer_mc(int len);
    void required_leg_length_and_soil();

public:
    
    std::vector<double> y_axis{ 0,0,0,0,0,0,0,0 };

    void generate_random_floor(double min_alt, double max_alt);
    void run();

};

template<class T>
void print(const T& container) {
    for (const auto& i : container) {
        std::cout << std::setw(8) << std::left << i << " ";
    }
    std::cout << "\n";
}



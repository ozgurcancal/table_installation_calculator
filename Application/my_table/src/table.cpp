
#include "my_table/table.h"


Table::Table(std::initializer_list<double> ilist):y_points(ilist) {}

Table::Table(double start_altitude, double end_altitude) {

    generate_random_y_points(start_altitude,end_altitude);

}

void Table::generate_x_points(){

    int i = 0;
    std::generate(begin(x_points), end(x_points), [this, &i]() {return (i++ * (x_length / (double)(SIZE-1))); }); 

}

//Produces a 53.15 meter long serrated random floor with positive slope and height is defined by the user.
void Table::generate_random_y_points(double start_altitude, double end_altitude) {

    y_points.reserve(SIZE);

    double height = abs(end_altitude - start_altitude);
    std::default_random_engine generator(std::random_device{}()); 
    double min_range=0, max_range=0;
    int i = 0;
    auto f = [this, &generator, &min_range, &max_range,&i,start_altitude,height]()
    {
        min_range = start_altitude - 0.35 + i * (height / (double)(SIZE-1));
        max_range = start_altitude + 0.35 + i * (height / (double)(SIZE-1));
        std::uniform_real_distribution<double> dist(min_range, max_range); 

#ifdef _DEBUG
        
        std::cout <<"min_range: "<< min_range << " " << "max_range: "<<max_range << " " << "i: "<<i << "\n";

#endif // _DEBUG

        ++i;
        return dist(generator);
    };
    
    generate(begin(y_points), end(y_points), f);

}



void Table::initialize_best_linear_line(std::vector<double> y_points)  
{

    int i = 0;
    for (size_t i = 0; i < y_points.size(); i++) {
       best_linear_line.emplace_back(m * x_points[i] + c);
    }    

#ifdef _DEBUG  // test the lineerization algorithm

    std::cout << "m =" << m << " c =" << c << "\n";

    int x = 0;
    std::cout << "enter a x value, press '0' to exit\n";
    std::cin >> x;
    while (x!=0) {
        std::cout << "intersection point with y axis" << m * x + c<<"\n";
        std::cout << "enter an x value\n";
        std::cin >> x;
    }

#endif // DEBUG
  
}

double Table::find_median(std::vector<double> tvec) {

    return (SIZE % 2 == 0) ? ((tvec[SIZE / 2] + tvec[SIZE / 2 - 1]) / 2) : (tvec[SIZE / 2]);
    
}

//BoxPlot method is used for detecting outliers.
void Table::find_cutoff() {

    std::vector<double> temp_vec(begin(y_points), end(y_points));
    std::sort(begin(temp_vec), end(temp_vec));

    double median = find_median(temp_vec);    
    double quartile_range = ((y_points.size() + 1) / 2 + 1) / 2;
    double interquartile_max = median + quartile_range;
    double interquartile_min = median - quartile_range;
    double interquartile_range = interquartile_max - interquartile_min;

    lower_cutoff = interquartile_min - 1.5 * interquartile_range;
    higher_cutoff = interquartile_max + 1.5 * interquartile_range;

}

// The equation of the straight line: y=mx+c
// function to calculate m and c that best fit to our surface 
void Table::find_linear_mc(int len) {
    
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    for (int i = 0; i < len; i++) {
        sum_x += x_points[i];
        sum_y += y_points[i];
        sum_xy += x_points[i] * y_points[i];
        sum_x2 += pow(x_points[i], 2);
    }

    m = (static_cast<double>(len) * sum_xy - sum_x * sum_y) / (static_cast<double>(len) * sum_x2 - pow(sum_x, 2));
    c = (sum_y - m * sum_x) / len;
    
}

void Table::fix_outliers() {  
    
    int i = 0;
    std::vector<int> ivec;
    find_cutoff();

    int index = 0;
    double old_value = 0;
    double new_value = 0;

    y_points.erase(std::remove_if(begin(y_points), end(y_points), [this, &i,&index,&old_value](double x) {i++; if (x<lower_cutoff || x>higher_cutoff) { index = i - 1; old_value = y_points[i - 1]; mp.insert({ index,old_value }); return 1; } else return 0; }), end(y_points));  //remove_if geri dönüş değeri it yeni end e ya da first e eşit

    for (const auto& j:mp) {  
        new_value = (y_points[j.first-1] + y_points[j.first])/2;
        auto position = begin(y_points) + j.first;
        y_points.insert(position,new_value);  
    }

    find_linear_mc(y_points.size()); 

}

void Table::required_leg_length_and_soil() {

    double fit = 0;
    //The foot length can change by a maximum of 0.2 meters. For this reason, for differences larger than 0.2 meters, it is necessary to dig or add to that area. 
    for (int i = 0; i < SIZE; i++) {

        fit = best_linear_line[i] - y_points[i];

        if (fit > 0.2) {          
            y_points[i] += fit;
            required_dust[i]=fit;
        }
        else if (fit < -0.2) {       
            y_points[i] += fit;
            required_dust[i]=fit;
        }
        else if (fit == 0) { // if point is already fixed use the value before fixing.
            required_dust[i] = y_points[i]- mp.begin()++->second;
        }
        else {  // no addition or substraction is required. Playing with leg heights shall be enough
            required_dust[i]=0;
            required_leg_length[i] += fit;
        }
    }

}

void Table::run() {
   
    std::cout <<std::setw(26) <<std::left<< "y_points: ";
    print(y_points);

    generate_x_points();
    std::cout <<std::setw(26) <<std::left<< "x_points: ";
    print(x_points);

    fix_outliers();
    std::cout <<std::setw(26) << std::left << "y_points with no outlier: " ;
    print(y_points);

    initialize_best_linear_line(y_points);
    std::cout <<std::setw(26) << std::left << "best linear line: ";
    print(best_linear_line);

    required_leg_length_and_soil();
    std::cout << std::setw(26) << std::left<< "final floor: ";
    print(y_points);

    std::cout << std::setw(26) << std::left<< "required soil: ";
    print(required_dust);

    std::cout << std::setw(26) << std::left<< "required leg length: ";
    print(required_leg_length);
  
}





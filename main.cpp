#include <iostream>
#include "TextTable.h"
#include <cmath>
#include <random>

double func_uni(double x){
    return std::sqrt(x) * std::sin(x * 0.5) * (-2);
}

double func_multi(double x){
     return std::sqrt(x) * std::sin(x * 0.5) * (-2) * std::sin(x * 5);
}

int main(int argc, const char * argv[]) {
    TextTable t_n('-', '|', '+');
    TextTable t_x('-', '|', '+');
    TextTable t_x_m('-', '|', '+');
    t_n.add("q\\p");
    t_x.add("q\\p");
    t_x_m.add("q\\p");
    double a = 2.0;
    double b = 6.0;
    for (auto p = 0.9; p <= 0.991; p += 0.01){
        t_n.add(std::to_string(p));
        t_x.add(std::to_string(p));
        t_x_m.add(std::to_string(p));
    }
    t_n.endOfRow();
    t_x.endOfRow();
    t_x_m.endOfRow();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(a, b);
    for (auto q = 0.005; q <= 0.101; q += 0.005){
        t_n.add(std::to_string(q));
        t_x.add(std::to_string(q));
        t_x_m.add(std::to_string(q));
        for (auto p = 0.9; p <= 0.991; p += 0.01){
            int n = ceil(log(1 - p) / log(1 - q));
            t_n.add(std::to_string(n));
            double f_min = func_uni(a);
            for (auto i = 0; i < n; i++){
                double x = dis(gen);
                double f_cur = func_uni(x);
                if (f_cur < f_min){
                    f_min = f_cur;
                }
            }
            t_x.add(std::to_string(f_min));
            f_min = func_multi(a);
            for (auto i = 0; i < n; i++){
                double x = dis(gen);
                double f_cur = func_multi(x);
                if (f_cur < f_min){
                    f_min = f_cur;
                }
            }
            t_x_m.add(std::to_string(f_min));
        }
        t_n.endOfRow();
        t_x.endOfRow();
        t_x_m.endOfRow();
    }
    std::cout << t_n << std::endl;
    std::cout << t_x << std::endl;
    std::cout << t_x_m << std::endl;
    return 0;
}

#include "candidate.h"
#include <omp.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <random>

Candidate::Candidate(int d) 
    : dim(d) {
    points.resize(d);

    #pragma omp parallel for schedule(static, 1)
    for (unsigned int i = 0; i < points.size(); ++i) {
        points[i] = randomDouble(LOWER_BOUND, UPPER_BOUND);
    }
    this->calc_fit();
}

void Candidate::calc_fit() {
        double sum(0.0),
               product(1.0);
    #pragma omp parallel
    {
        #pragma omp for reduction(*:product) schedule(static, 1) nowait
        for (unsigned int i = 0; i < points.size(); ++i) {
            product *= std::cos(points[i]/(i + 1));
        }
        #pragma omp for reduction(+:sum) schedule(static, 1) nowait
        for (unsigned int j = 0; j < points.size(); ++j) {
            sum += points[j] * points[j];
        }
        this->fit = (1.0/40.0) * sum + 1 - product;
    }
}

void Candidate::mutate(const double &prob) {
    //jak rozwiązać losowanie? kazdy wątek powinien mieć swój engine
    #pragma omp parallel for schedule(static, 1)
    for (unsigned int i = 0; i < points.size(); ++i) {
        if (randomDouble(0.0, 1.0) <= prob) {
            points[i] += randomDouble(-points[i]/5, points[i]/5);
        }
    }
}

void Candidate::show() {
    std::cout << "[";
    for (const auto& point : points)
    {
        std::cout << point << ", ";
    }
    std::cout << "\b\b]" << std::endl;
}

double randomDouble(const double& min, const double& max) {
    static thread_local std::mt19937 engine(omp_get_wtime() + 
                                            omp_get_thread_num());
    std::uniform_real_distribution<double> dist(min, max);
    return dist(engine);
}

int randomInt(const int& min, const int& max) {
    thread_local std::mt19937 engine(omp_get_wtime() + 
                                            omp_get_thread_num());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine);
}


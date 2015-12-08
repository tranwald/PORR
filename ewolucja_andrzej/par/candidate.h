#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <omp.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <random>

constexpr long n = 100000;
constexpr double LOWER_BOUND = -40.0;
constexpr double UPPER_BOUND = 40.0;
constexpr double PROB_MUT_POINT = 0.3;
constexpr double PROB_MUT_IND = 0.3;

double randomDouble(const double& min, const double& max);
int randomInt(const int& min, const int& max);

struct Candidate
{
    std::vector<double> points;
    int dim;
    double fit;
    bool operator<(Candidate const &rhs) const {
        return (this->fit < rhs.fit);
    }
    void calc_fit();
    void mutate(const double &prob);
    void show();
    Candidate() {};
    Candidate(int d);
    
};

#endif //CANDIDATE_H
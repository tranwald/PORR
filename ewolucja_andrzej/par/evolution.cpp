#include "evolution.h"
#include <omp.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <random>
#include <tuple>
#include <algorithm>

Evolution::Evolution(const int &m, const int &l, const int &d)
    : mi(m), lambda(l), dim(d) {
    pop_p.resize(mi, Candidate(d));
    pop_t.resize(lambda + mi, Candidate(d));

    //#pragma omp parallel for schedule(static, 1)
    for (unsigned int i = 0; i < pop_p.size(); ++i) {
        pop_p[i] = Candidate(d);
        pop_p[i].calc_fit();
    }
}

void Evolution::show_all() {
    unsigned int i = 0;
    for (auto it = pop_p.begin(); it != pop_p.end(); ++it, ++i) {
        std::cout << "C" << i << ": ";
        it->show();
    }
    std::cout << std::endl;
}

Candidate Evolution::reproduce() {
    int rd = randomInt(0, mi - 1);
    return pop_p[rd];
}

Evolution::Pair Evolution::cross(Candidate &fst, Candidate &snd) {
    int locus = dim/2;
    Candidate fst_child(fst), snd_child(snd);
    fst_child.points.erase(fst_child.points.begin() + locus,
                           fst_child.points.end());
    snd_child.points.erase(snd_child.points.begin() + locus,
                           snd_child.points.end());
    fst_child.points.insert(fst_child.points.end(),
                            snd.points.begin() + locus,
                            snd.points.end());
    snd_child.points.insert(snd_child.points.end(),
                            fst.points.begin() + locus,
                            fst.points.end());
    return Pair(fst_child, snd_child);
}

void Evolution::mutate(Candidate &ind, const double &prob) {
    if (randomDouble(0.0, 1.0) <= prob) {
        ind.mutate(PROB_MUT_POINT);
    }
}

void Evolution::evolve() {
    // #pragma omp parallel
    // {
        Candidate fst, snd, fst_child, snd_child;
        // #pragma omp for schedule(static, 1)
        for (int i = 0; i < lambda; ++i) {
            fst = reproduce();
            snd = reproduce();
            std::tie(fst_child, snd_child) = cross(fst, snd);
            mutate(fst_child, PROB_MUT_IND);
            mutate(snd_child, PROB_MUT_IND);
            fst_child.calc_fit();
            snd_child.calc_fit();
            pop_t[i] = fst_child;
            pop_t[i + 1] = snd_child;
        }
    // }
    pop_t.insert(pop_t.begin() + lambda, pop_p.begin(), pop_p.end());
    std::sort(pop_t.begin(), pop_t.end());
}
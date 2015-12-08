#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "candidate.h"
#include <vector>
#include <tuple>

class Evolution
{
    typedef std::tuple<Candidate, Candidate> Pair;
  public:
    Evolution(const int &m, const int &l, const int &d);
    ~Evolution() {};
    void show_all();
    void evolve();
  private:
    int mi;
    int lambda;
    int dim;
    //Candidate* fittest;
    std::vector<Candidate> pop_p;
    std::vector<Candidate> pop_t; 
    std::vector<Candidate> pop_r;
    Candidate reproduce();
    Pair cross(Candidate &fst, Candidate &snd);
    void mutate(Candidate &ind, const double &prob);
};

#endif //CANDIDATE_H
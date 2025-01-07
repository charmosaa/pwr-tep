#pragma once

#include <vector>
#include <random>
#include "GroupingEvaluator.h"

namespace NGroupingChallenge
{
    class Individual
    {
    private:
        double fitness;
        std::mt19937 randomNumberGenerator;
        CGroupingEvaluator& evaluator;
        int numGenes;
        std::vector<int> genotype; 

    public:
        Individual(const Individual& other);
        Individual(CGroupingEvaluator& evaluator); //random genotype
        void mutate(double mutProb, int numGroups);
        std::pair<Individual, Individual> crossover(const Individual &other, double CrossProb);
        double evaluate();
        double getFitness() const;
        std::vector<int> getSolution() const;
        void printGenotype() const;
        Individual& operator=(const Individual &other);
    };
}


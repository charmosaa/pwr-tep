#pragma once

#include <vector>
#include <random>
#include "GroupingEvaluator.h"

#define SEED 12345

namespace NGroupingChallenge
{
    class Individual
    {
    private:
        double fitness;
        std::vector<int> genotype;  
        std::mt19937 randomNumberGenerator;
        CGroupingEvaluator* evaluator;
        int numGenes;
    public:
        Individual(const Individual& other);
        Individual(CGroupingEvaluator* evaluator); //random 
        Individual(std::vector<int>& genotype, CGroupingEvaluator* evaluator); //with genotype
        ~Individual();
        void mutate(double mutProb, int numGroups);
        std::pair<Individual, Individual> crossover(const Individual &other, double CrossProb);
        
        
        double evaluate();
        
        double getFitness() const;
        //const std::vector<int>& getGenotype() const;
        void printGenotype() const;
    };
}


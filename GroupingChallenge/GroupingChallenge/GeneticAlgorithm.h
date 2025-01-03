#pragma once

#include <vector>
#include "Individual.h"
#include "GroupingEvaluator.h"

#define NUM_GENES 180
#define NUM_GROUPS 4
#define SEED 12345

namespace NGroupingChallenge
{

    class GeneticAlgorithm
    {
        public:
            GeneticAlgorithm(double popSize, double crossProb, double mutProb, CGroupingEvaluator* evaluator);
            ~GeneticAlgorithm();
            double crossProb, mutProb;
            int popSize;
            std::vector<Individual*> population;
            Individual getBestSolution();
            std::pair <Individual*, Individual*> selectParents();
        private:
            void populate();
            CGroupingEvaluator* evaluator;
            std::mt19937 randomNumberGenerator;


    };
}
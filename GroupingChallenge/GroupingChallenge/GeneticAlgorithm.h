#pragma once

#include <vector>
#include "Individual.h"
#include "GroupingEvaluator.h"

#define TOURNAMENT_SIZE 10

namespace NGroupingChallenge
{

    class GeneticAlgorithm
    {
        public:
            GeneticAlgorithm(CGroupingEvaluator& evaluator);
            ~GeneticAlgorithm();
            void run(int numIterations);
            void runIteration();
            Individual& getBestIndividual();
            const double crossProb = 0.7f;
            const double mutProb = 0.15;
            const int popSize = 20;
            void printPopulation();
        private:
            void populate();
            CGroupingEvaluator& evaluator;
            std::mt19937 randomNumberGenerator;
            Individual& selectParent();
            std::vector<Individual> population;
            Individual& tournamentSelection();
            void evaluatePopulation();
    };
}
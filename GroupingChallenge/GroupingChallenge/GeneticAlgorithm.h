#pragma once

#include <vector>
#include "Individual.h"
#include "GroupingEvaluator.h"

#define NUM_GENES 180
#define NUM_GROUPS 4
#define TOURNAMENT_SIZE 4
#define SEED 12345

namespace NGroupingChallenge
{

    class GeneticAlgorithm
    {
        public:
            GeneticAlgorithm(int popSize, double crossProb, double mutProb, CGroupingEvaluator& evaluator);
            ~GeneticAlgorithm();
            void run(int numIterations);
            void runIteration();
            Individual& getBestIndividual();
            double crossProb, mutProb;
            int popSize;
            void printPopulation();
        private:
            void populate();
            CGroupingEvaluator& evaluator;
            std::mt19937 randomNumberGenerator;
            Individual& selectParent();
            std::vector<Individual*> population;
            Individual* tournamentSelection();
            void deletePopulation();
    };
}
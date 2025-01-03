#include "GeneticAlgorithm.h"

using namespace NGroupingChallenge;

GeneticAlgorithm::GeneticAlgorithm(double popSize, double crossProb, double mutProb, CGroupingEvaluator* evaluator): popSize(popSize),crossProb(crossProb), mutProb(mutProb),evaluator(evaluator),randomNumberGenerator(SEED)
{
    populate();
}

void GeneticAlgorithm::populate()
{
    population.clear();
    for(int i=0;i<popSize;i++)
    {
        population.push_back(new Individual(evaluator));   
    }
}

std::pair <Individual*, Individual*> GeneticAlgorithm::selectParents()
{
    std::uniform_int_distribution<int> parentDist(0, popSize - 1);

    int firstParentPosition = parentDist(randomNumberGenerator);
    int firstSecondParentPosition = parentDist(randomNumberGenerator);
    Individual* parent1 = population[firstParentPosition];
    Individual* parent12 = population[firstSecondParentPosition];

    if(parent1->getFitness() < parent12->getFitness())
    {
        parent1 = parent12;
        firstParentPosition = firstSecondParentPosition;
    }   

    int secondParentPosition = parentDist(randomNumberGenerator);
    int secondSecondParentPosition = parentDist(randomNumberGenerator);
    Individual* parent2 = population[secondParentPosition];
    Individual* parent22 = population[secondSecondParentPosition];

    if((parent2->getFitness() < parent22->getFitness() && secondSecondParentPosition != firstParentPosition) || secondParentPosition == firstParentPosition)
        parent2 = parent22;

    return {
        parent1,
        parent2
    };
}

Individual GeneticAlgorithm::getBestSolution()
{
    Individual* bestSolution = population[0];
    for(int i=1;i<popSize;i++)
    {
        if(population[i]->getFitness() > bestSolution->getFitness())
            bestSolution = population[i];
    }

    return *bestSolution;
}
#include "Individual.h"
#include <iostream>

using namespace NGroupingChallenge;

Individual::Individual(CGroupingEvaluator &evaluator): evaluator(evaluator), randomNumberGenerator(std::random_device{}())
{
    numGenes = evaluator.iGetNumberOfPoints();
    std::uniform_int_distribution<int> dist(evaluator.iGetLowerBound(), evaluator.iGetUpperBound());

    for (int i = 0; i < numGenes; ++i) {
        genotype.push_back(dist(randomNumberGenerator));
    }
    evaluate();
}


Individual::Individual(const Individual &other) : evaluator(other.evaluator), randomNumberGenerator(other.randomNumberGenerator), numGenes(other.numGenes)
{
    genotype = other.genotype;
}

Individual& Individual::operator=(const Individual &other)
{
    genotype = other.genotype;
    numGenes = other.numGenes;
    fitness = other.fitness;
    return *this;
}


double Individual::evaluate()
{
    fitness = evaluator.dEvaluate(genotype);
    return fitness;
}

void Individual::mutate(double mutProb, int numGroups)
{
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    std::uniform_int_distribution<int> groupDist(1, numGroups);

    for(int& gene : genotype)
    {
        if(probDist(randomNumberGenerator) < mutProb)
            gene = groupDist(randomNumberGenerator);
    }

    evaluate();
}

std::pair<Individual, Individual> Individual::crossover(const Individual &other, double crossProb)
{
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    
    Individual child1(*this);
    Individual child2(other);

    if(probDist(randomNumberGenerator) < crossProb)
    {
        for(int i = 0;i<numGenes;i++)
        {
            if(probDist(randomNumberGenerator) > 0.5)
                std::swap(child1.genotype[i],child2.genotype[i]);
        }   
    }

    return {
        std::move(child1),
        std::move(child2)
    };
    
}
        

double Individual::getFitness() const
{
    return fitness;
}

std::vector<int> Individual::getSolution() const
{
    return genotype;
}

void Individual::printGenotype() const
{
    for(int i=0;i<numGenes;i++)
    {
        std::cout<<genotype[i];
    }
    std::cout<<"\tfitness: "<<fitness;
}
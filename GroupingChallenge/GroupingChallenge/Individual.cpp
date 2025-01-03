#include "Individual.h"

using namespace NGroupingChallenge;

Individual::Individual(CGroupingEvaluator* evaluator): evaluator(evaluator), randomNumberGenerator(SEED)
{
    numGenes = evaluator->iGetNumberOfPoints();
    std::uniform_int_distribution<int> dist(evaluator->iGetLowerBound(), evaluator->iGetUpperBound());

    for (int i = 0; i < numGenes; ++i) {
        genotype.push_back(dist(randomNumberGenerator));
    }
    
    evaluate();
}

Individual::Individual(std::vector<int>& genotype, CGroupingEvaluator* evaluator): genotype(genotype) ,evaluator(evaluator),randomNumberGenerator(SEED), numGenes(numGenes)
{
    evaluate();
}

Individual::Individual(const Individual& other) : genotype(other.genotype), evaluator(other.evaluator), randomNumberGenerator(other.randomNumberGenerator), numGenes(numGenes)
{
   
}


double Individual::evaluate()
{
    fitness = evaluator->dEvaluate(genotype);
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
        std::uniform_int_distribution<int> dist(0, genotype.size() - 1);
        int crossoverPoint = dist(randomNumberGenerator);

        for(int i = crossoverPoint;i<numGenes;i++)
            std::swap(child1.genotype[i],child2.genotype[i]);
    }

    return {
        child1,
        child2
    };
    
}
        
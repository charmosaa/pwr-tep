#include "GeneticAlgorithm.h"
#include <iostream>
#include <omp.h>

using namespace NGroupingChallenge;

GeneticAlgorithm::GeneticAlgorithm( CGroupingEvaluator& evaluator): evaluator(evaluator),randomNumberGenerator(std::random_device{}())
{
    populate();
    evaluatePopulation();
    printPopulation();
}

 GeneticAlgorithm::~GeneticAlgorithm()
 {
 }

void GeneticAlgorithm::populate()
{
    population.clear();
    for(int i=0;i<popSize;i++)
        population.emplace_back(evaluator);   
}

Individual& GeneticAlgorithm::tournamentSelection()
{
    std::uniform_int_distribution<int> dist(0, popSize - 1);
    Individual& best = population[dist(randomNumberGenerator)];

    for (int i = 1; i < TOURNAMENT_SIZE; ++i) {
        int index = dist(randomNumberGenerator);
        if (population[index].getFitness() < best.getFitness()) {
            best = population[index];
        }
    }
    return best;
}


Individual& GeneticAlgorithm::selectParent() //idk if needed
{
    Individual& parent = tournamentSelection();
    return parent;
}

Individual& GeneticAlgorithm::getBestIndividual()
{
    Individual& bestIndividual = population[0];
    for (size_t i = 1; i < popSize; ++i)
    {
        if (population[i].getFitness() < bestIndividual.getFitness())
            bestIndividual = population[i];
        
    }

    return bestIndividual;
}


void GeneticAlgorithm::run(int numIterations)
{
    for(int i=0;i<numIterations;i++)
        runIteration();
}

void GeneticAlgorithm::runIteration()
{
    vector<Individual>newPopulation;
    newPopulation.reserve(popSize);
    newPopulation.push_back(getBestIndividual());

    while(newPopulation.size()<popSize)
    {
        Individual& p1  = tournamentSelection();
        Individual& p2 = tournamentSelection();

        std::pair<Individual, Individual> children = p1.crossover(p2,crossProb);

        children.first.mutate(mutProb, evaluator.iGetUpperBound());
        newPopulation.push_back(std::move(children.first));

        if(newPopulation.size()<popSize)
        {
            children.second.mutate(mutProb, evaluator.iGetUpperBound());
            newPopulation.push_back(std::move(children.second));
        }

        // std::cout<<"patrent1: ";
        // p1->printGenotype();
        // std::cout<<"\npatrent2: ";
        // p2->printGenotype();
        // std::cout<<"\n\n";

        // std::cout<<"child1: ";
        // child1->printGenotype();
        // std::cout<<"\nchild2: ";
        // child2->printGenotype();
        // std::cout<<"\n\n";
    }
    population = std::move(newPopulation);
    evaluatePopulation();
}

void GeneticAlgorithm::printPopulation()
{
    int i=0;
    for (auto& individual : population) {
        i++;
        std::cout << i << ": ";
        individual.printGenotype();
        std::cout << std::endl;
    }
    std::cout<<"----------------------"<<std::endl;
}    

void GeneticAlgorithm::evaluatePopulation()
{
    #pragma omp parallel for
    for (int i = 0; i < popSize; ++i) {
        population[i].evaluate();
    }
}
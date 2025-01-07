#include "GeneticAlgorithm.h"
#include <iostream>

using namespace NGroupingChallenge;

GeneticAlgorithm::GeneticAlgorithm(int popSize, double crossProb, double mutProb, CGroupingEvaluator& evaluator): popSize(popSize),crossProb(crossProb), mutProb(mutProb),evaluator(evaluator),randomNumberGenerator(std::random_device{}())
{
    populate();
    printPopulation();
}

 GeneticAlgorithm::~GeneticAlgorithm()
 {
    deletePopulation();
 }

void GeneticAlgorithm::populate()
{
    population = vector<Individual*>(popSize, nullptr);
    for(int i=0;i<popSize;i++)
    {
        population[i] = new Individual(evaluator);   
    }
}

Individual* GeneticAlgorithm::tournamentSelection()
{
    std::uniform_int_distribution<int> dist(0, popSize - 1);
    Individual* best = nullptr;

        for (int i = 0; i < TOURNAMENT_SIZE; ++i)
        {
            int index = dist(randomNumberGenerator);
            Individual* candidate = population[index];

            if (best == nullptr || candidate->getFitness() > best->getFitness())
                best = candidate;
        }
    return best;
}

Individual& GeneticAlgorithm::selectParent()
{
    Individual& parent = *tournamentSelection();
    return parent;
}

Individual& GeneticAlgorithm::getBestIndividual()
{
    Individual* bestIndividual = population[0];
    for(int i=1;i<popSize;i++)
    {
        if(population[i]->getFitness() > bestIndividual->getFitness())
            bestIndividual = population[i];
    }

    return *bestIndividual;
}

void GeneticAlgorithm::run(int numIterations)
{
    for(int i=0;i<numIterations;i++)
        runIteration();
}

void GeneticAlgorithm::runIteration()
{
    vector<Individual*>newPopulation(popSize,nullptr);
    int newSize = 0;
    while(newSize<popSize)
    {
        Individual* p1  = tournamentSelection();
        Individual* p2 = tournamentSelection();

        std::pair<Individual, Individual> children = p1->crossover(*p2,crossProb);

        Individual* child1 = new Individual(children.first);
        child1->mutate(mutProb, NUM_GROUPS);
        newPopulation[newSize] = child1;
        newSize++;

        // if(newSize<popSize)
            Individual* child2 = new Individual(children.second);
            child2->mutate(mutProb, NUM_GROUPS);
            newPopulation[newSize] = child2;
            newSize++;
        

        std::cout<<"patrent1: ";
        p1->printGenotype();
        std::cout<<"\npatrent2: ";
        p2->printGenotype();
        std::cout<<"\n\n";

        std::cout<<"child1: ";
        child1->printGenotype();
        std::cout<<"\nchild2: ";
        child2->printGenotype();
        std::cout<<"\n\n";
    }
    deletePopulation();
    population = newPopulation;//std::move
}

void GeneticAlgorithm::deletePopulation()//check that
{
    for(int i=0;i<popSize;i++)
        delete population[i];
    population.clear();
    population = vector<Individual*>(popSize, nullptr);
}

void GeneticAlgorithm::printPopulation()
{
    for(int i=0;i<popSize;i++)
    {
        std::cout<<i<<": ";
        population[i]->printGenotype();
        std::cout<<std::endl;
    }
    std::cout<<"----------------------"<<std::endl;
}    
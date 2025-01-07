#include "Optimizer.h"
#include <iostream>

using namespace NGroupingChallenge;

COptimizer::COptimizer(CGroupingEvaluator& cEvaluator)
	: c_evaluator(cEvaluator), geneticAlgorithm(10, 0.7, 0.1, cEvaluator)
{
	random_device c_seed_generator;
	c_random_engine.seed(c_seed_generator());
}

void COptimizer::vInitialize()
{

}

void COptimizer::vRunIteration()
{
	geneticAlgorithm.runIteration();
	v_current_best = geneticAlgorithm.getBestIndividual().getSolution();
	geneticAlgorithm.printPopulation();
	std::cout<<geneticAlgorithm.getBestIndividual().getFitness();
}
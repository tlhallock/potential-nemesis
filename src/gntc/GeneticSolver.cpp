/*
 * GeneticSolver.cpp
 *
 *  Created on: Sep 9, 2014
 *      Author: thallock
 */

#include "gntc/GeneticSolver.h"

#include "opt/RandomGeneratorSolver.h"

#include "opt/Cost.h"

#include <chrono>
#include <iostream>

Mutator::Mutator() {}
Mutator::~Mutator() {}
void Mutator::mutate(const City& c, individual child) {}

Breeder::Breeder() {}
Breeder::~Breeder() {}
individual Breeder::breed(const City& c, individual p1, individual p2) { return p1; }

Selector::Selector() {}
Selector::~Selector() {}
void Selector::select(const City& c, std::vector<individual>& population, individual new_child, int pop_size)
{
	population.push_back(new_child);

	std::sort(population.begin(), population.end(), [] (const individual &i1, const individual &i2)
	{
		return Cost{i1} < Cost{i2};
	});

	while ((int) population.size() > pop_size - 1)
	{
		population.erase(population.end());
	}
}
individual Selector::get_best(const City& city, std::vector<individual>& population)
{
	individual best {population.front()};
	Cost c {best};

	// not sure which is faster...
#if 1
	std::sort(population.begin(), population.end(), [] (const individual &i1, const individual &i2)
	{
		return Cost{i1} < Cost{i2};
	});
	return population.front();
#else
	auto end = population.end();
	for (auto it = population.begin(); it != end; ++it)
	{
		if (Cost{*it} < c)
		{
			best = *it;
			c = Cost{best};
		}
	}

	return best;
#endif
}

GeneticSolver::GeneticSolver(const Parameters &p,
		int stable_threshold_,
		Solver *delegate_,
		int population_size_,
		Breeder *b,
		Mutator *m,
		Selector *s) :
	Solver(p),
	population_size(population_size_),
	stable_threshold(stable_threshold_),
	delegate(delegate_),
	mutator(m),
	breeder(b),
	selector(s)
{
	if (population_size <= 0)
	{
		population_size = 50;
	}
	if (delegate == nullptr)
	{
		delegate = new RandomGeneratorSolver{p};
	}
	if (mutator == nullptr)
	{
		mutator = new Mutator {};
	}
	if (breeder == nullptr)
	{
		breeder = new Breeder {};
	}
	if (selector == nullptr)
	{
		selector = new Selector {};
	}
}

GeneticSolver::~GeneticSolver()
{
	delete delegate;
	delete mutator;
	delete breeder;
	delete selector;
}

std::string GeneticSolver::get_name() const
{
	return "genetic[" + delegate->get_name() + "]";
}

Solution GeneticSolver::solve(const City& city)
{
	population.clear();
//	std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now() + std::chrono::seconds(3);

	// should be a metric!!!
	int num_serviced = -1;
	int count = 0;

	while (count < stable_threshold/*std::chrono::steady_clock::now() < end_time*/)
	{
		while ((int) population.size() < population_size)
		{
			Solution news = delegate->solve(city);
			population.push_back(individual {new Solution {news}});
		}

		individual p1 = population.at(rand() % population.size());
		individual p2 = population.at(rand() % population.size());
		individual child = breeder->breed(city, p1, p2);
		mutator->mutate(city, child);
		selector->select(city, population, child, population_size);

		count++;
		int ns = Cost{selector->get_best(city, population)}.get_number_serviced();
		if (ns > num_serviced)
		{
			num_serviced = ns;
			count = 0;
		}
	}

	return *selector->get_best(city, population).get();
}


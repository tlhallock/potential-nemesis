/*
 * SubcycleBreeder.cpp
 *
 *  Created on: Sep 10, 2014
 *      Author: thallock
 */

#include "gntc/SubcycleBreeder.h"

#include "SvgPrinter.h"

#include <map>

namespace
{
	class Codon
	{
	public:
		Codon() {}
		~Codon() {}
		int route;
		int begin;
		int end;

		friend std::ostream& operator<<(std::ostream& os, const Codon &codon)
		{
			return os << "r[" << codon.route << "]b[" << codon.begin << "]e[" << codon.end << "]";
		}
	};

	inline bool is_cycle_node(Operation o)
	{
		return o == Dump /*Store, Unstore*/;
	}

	int get_landfill_idx(const City &city, const Action &a)
	{
		if (!is_cycle_node(a.get_operation()))
		{
			return -1;
		}

		int num = city.get_num_land_fills();
		for (int i=0; i<num; i++)
		{
			const Landfill &l = city.get_land_fill(i);
			if (a.get_x() != l.get_x())
			{
				continue;
			}
			if (a.get_y() != l.get_y())
			{
				continue;
			}
			return i;
		}
		return -1;
	}


	void insert_dis(std::map<int, std::vector<Codon> > &codons, Codon &codon, int landfill)
	{
		if (landfill < 0)
		{
			return;
		}

		auto it = codons.find(landfill);
		if (it == codons.end())
		{
			codons.insert(std::pair<int, std::vector<Codon> > {landfill, std::vector<Codon>{}});
			it = codons.find(landfill);
		}

		it->second.push_back(codon);
	}

	void get_codons(const City &city, individual p, std::map<int,std::vector<Codon> > &codons)
	{
		int num_drivers = p->get_num_drivers();

		for (int r = 0; r < num_drivers; r++)
		{
			Route &route = p->get_route(r);

			int num_landfills = city.get_num_land_fills();
			for (int landfill = 0; landfill < num_landfills; landfill++)
			{

				int nactions = route.get_num_actions();
				for (int i = 0; i < nactions; i++)
				{
					const Action& a1 = route.get_action(i);
					if (get_landfill_idx(city, a1) != landfill)
					{
						continue;
					}

					for (int j = i-1; j >= 0; j--)
					{
						const Action& a2 = route.get_action(j);
						if (get_landfill_idx(city, a2) != landfill)
						{
							continue;
						}

						Codon c;
						c.route = r;
						c.begin = j;
						c.end = i;

						insert_dis(codons, c, landfill);

						// Only find the shortest paths...
						break;
					}
				}
			}
		}
	}
}

SubcycleBreeder::SubcycleBreeder() {}
SubcycleBreeder::~SubcycleBreeder() {}

individual SubcycleBreeder::breed(const City& c, individual p1, individual p2)
{
	// land fills to codons
	std::map<int,std::vector<Codon> > i1codons;
	get_codons(c, p1, i1codons);
	std::map<int,std::vector<Codon> > i2codons;
	get_codons(c, p2, i2codons);


#if 0

	Parameters p;
	svg_print_solution("my_test", *p1.get(), p);

	auto end = i1codons.end();
	for (auto it = i1codons.begin(); it != end; ++it)
	{
		std::cout << it->first << std::endl;

		auto iend = it->second.end();
		for (auto iit = it->second.begin(); iit != iend; ++iit)
		{
			std::cout << "\t" << *iit << std::endl;
		}
	}
	std::cout << "====================================================" << std::endl;
#endif
	return p1;
}

/*
 * SvgPrinter.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#include "SvgPrinter.h"

#include "common.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

namespace
{
	constexpr double scale_factor = 7.5;

	std::string black  {"#000000"};
	std::string red    {"#ff0000"};
	std::string yellow {"#ffff00"};
	std::string green  {"#00ff00"};
	std::string lblue  {"#00ffff"};
	std::string blue   {"#0000ff"};
	std::string pink   {"#ff00ff"};
	std::string white  {"#ffffff"};

	std::string hex {"0123456789abcdef"};
	std::string letter_width{"1"};
	std::string line_width{"1"};
	std::string font_size{"7"};

	int inc_y_iter = 10;

	double print_unit(double a_number)
	{
		return scale_factor * a_number;
	}

	std::string next_color()
	{
		std::stringstream stream;
		stream << "#";
		for (int i = 0; i < 6; i++)
		{
			stream << (char) (hex.at(rand() % hex.size()));
		}
		return stream.str();
	}

	std::string next_id()
	{
		static int next;
		std::stringstream stream;
		stream << "id_" << next++;
		return stream.str();
	}

	void print_line(std::ofstream &svg_stream, const Location &location1, const Location &location2, const std::string &color)
	{
		svg_stream << "\t\t<line id=\"" << next_id() << "\" "
				<< "y2=\"" << print_unit(location2.get_y()) << "\" x2=\"" << print_unit(location2.get_x()) << "\" "
				<< "y1=\"" << print_unit(location1.get_y()) << "\" x1=\"" << print_unit(location1.get_x()) << "\" "
				<< "stroke-width=\"" << line_width << "\" stroke=\"" << color << "\" fill=\"none\"/>" << std::endl;
	}

	std::string get_color(const std::string &s)
	{
		switch (s.at(0))
		{
			case 'L':
				return black;
			case 'P':
				return blue;
			case 'D':
				return green;
			case '?':
				return red;
			case 'S':
				return yellow;
			case 'U':
				return pink;
			case 'R':
				return red;
			default:
				return black;
		}
	}

	namespace
	{
		// move down each time a request at the same loc is printed...
		std::map<Location, int> counts;
		int adjustment_for_already_printed(const Location &old)
		{
			auto it = counts.find(old);
			if (it == counts.end())
			{
				counts.insert(std::pair<Location, int> {Location {old}, 1});
				return 0;
			}
			else
			{
				return it->second++ * inc_y_iter;
			}
		}
	}

	void print_string(std::ofstream &svg_stream, const Location &location, const std::string &str)
	{

		std::string color = get_color(str);
		svg_stream << "\t\t<text xml:space=\"preserve\" text-anchor=\"middle\" font-family=\"Sans\" font-weight=\"lighter\" font-size=\"" << font_size << "\" "
				<< "id=\"" << next_id()
				<< "\" y=\"" << (print_unit(location.get_y()) + adjustment_for_already_printed(location)) << "\" x=\"" << print_unit(location.get_x()) << "\""
				<< " stroke-width=\"" << letter_width << "\" stroke=\"" << color << "\" fill=\"" << color << "\">"
				<< str << "</text>" << std::endl;
	}

	/** These could both implement the same interface at least. **/
	std::string action_text(const Action* a)
	{
		return operation_to_svg(a->get_operation()) + get_size_text(a->get_input_dumpster_size())
							 + get_size_text(a->get_output_dumpster_size());
	}

	void print_stop(std::ofstream &svg_stream, const City* city, const Action* solution)
	{
		print_string(svg_stream, city->get_location(solution->get_location()), action_text(solution));
	}

	void print_stops(std::ofstream &svg_stream, const City *city)
	{
		int size = city->get_num_stops();
		for (int i = 0; i < size; i++)
		{
			print_stop(svg_stream, city, city->get_stop(i));
		}
	}

	void print_route(std::ofstream &svg_stream, const Route &solution, const std::string &color)
	{
		const City* city = solution.get_city();

		int size = solution.get_num_actions();
		for (int i = 0; i < size - 1; i++)
		{
			const Location& l1 = city->get_location(solution.get_action(i  )->get_location());
			const Location& l2 = city->get_location(solution.get_action(i+1)->get_location());

			print_line(svg_stream, l1, l2, color);

			std::stringstream ss;
			ss << i << ":" ;
			ss << action_text(solution.get_action(i+1));
			print_string(svg_stream, l2, ss.str());
		}
	}

	void print_solution(std::ofstream &svg_stream, const Solution &solution)
	{
		int drivers = solution.get_num_drivers();
		for (int i = 0; i < drivers; i++)
		{
			print_route(svg_stream, solution.get_route(i), next_color());
		}
	}

	void print_preamble(std::ofstream &svg_stream, const std::string &title, const Parameters &p)
	{
		svg_stream << "<svg width=\"" << print_unit(p.get_scale()) << "\" height=\"" << print_unit(p.get_scale()) << "\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;
		svg_stream << "\t<g>" << std::endl;
		svg_stream << "\t\t<title>" + title + "</title>" << std::endl;
	}

	void print_postamble(std::ofstream &svg_stream)
	{
		svg_stream << "\t</g>" << std::endl;
		svg_stream << "</svg>" << std::endl;
	}
}

void svg_print_city(const std::string &filename, const City *city, const Parameters &p)
{
	std::ofstream svg_stream { filename + ".req.svg" };
	print_preamble(svg_stream, "requests", p);
	print_stops(svg_stream, city);
	print_postamble(svg_stream);
}

void svg_print_solution(const std::string &filename, const Solution &solution, const Parameters &p)
{
	counts.clear(); // reset state

	std::ofstream svg_stream { filename + ".sol.svg" };
	print_preamble(svg_stream, filename, p);
	print_solution(svg_stream, solution);
	print_postamble(svg_stream);
}


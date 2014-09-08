/*
 * SvgPrinter.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#include "SvgPrinter.h"

#include "common.h"
#include "model/Landfills.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace
{
	constexpr double scale_factor = 5;

	std::string black  {"#000000"};
	std::string red    {"#ff0000"};
	std::string yellow {"#ffff00"};
	std::string green  {"#00ff00"};
	std::string lblue  {"#00ffff"};
	std::string blue   {"#0000ff"};
	std::string pink   {"#ff00ff"};
	std::string white  {"#ffffff"};

	std::string hex {"0123456789abcdef"};
	std::string letter_width{"2"};
	std::string line_width{"1"};
	std::string font_size{"10"};

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

	std::string get_color(char c)
	{
		switch (c)
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

	void print_letter(std::ofstream &svg_stream, const Location &location, char c)
	{
		std::string color = get_color(c);
		svg_stream << "\t\t<text xml:space=\"preserve\" text-anchor=\"middle\" font-family=\"serif\" font-size=\"" << font_size << "\" "
				<< "id=\"" << next_id()
				<< "\" y=\"" << print_unit(location.get_y()) << "\" x=\"" << print_unit(location.get_x()) << "\""
				<< " stroke-width=\"" << letter_width << "\" stroke=\"" << color << "\" fill=\"" << color << "\">"
				<< c << "</text>" << std::endl;
	}

	void print_request(std::ofstream &svg_stream, const Request &solution)
	{
		print_letter(svg_stream, solution, operation_to_svg(solution.get_operation()));
	}

	void print_requests(std::ofstream &svg_stream, const City &city)
	{
		int size = city.get_num_requests();
		for (int i = 0; i < size; i++)
		{
			print_request(svg_stream, city.get_request(i));
		}
	}

	void print_route(std::ofstream &svg_stream, const Route &solution, const std::string &color)
	{
		int size = solution.get_num_actions();
		for (int i = 0; i < size - 1; i++)
		{
			const Action& a1 = solution.get_action(i);
			const Action& a2 = solution.get_action(i + 1);

			print_line(svg_stream, a1, a2, color);
			print_letter(svg_stream, a2, operation_to_svg(a2.get_operation()));
			// print number (order) = i
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

	void print_land_fills(std::ofstream &svg_stream, const City &city)
	{
		int size = city.get_num_land_fills();
		for (int i=0; i<size;i++)
		{
			print_letter(svg_stream, city.get_land_fill(i), 'L');
		}
	}

	void print_staging_areas(std::ofstream &svg_stream, const City &city)
	{
		int size = city.get_num_staging_areas();
		for (int i=0; i<size;i++)
		{
			print_letter(svg_stream, city.get_staging_area(i), 'S');
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

void svg_print_city(const std::string &filename, const City &city, const Parameters &p)
{
	std::ofstream svg_stream { filename + ".req.svg" };
	print_preamble(svg_stream, "requests", p);
	print_requests(svg_stream, city);
	print_land_fills(svg_stream, city);
	print_staging_areas(svg_stream, city);
	// print staging areas
	print_postamble(svg_stream);
}

void svg_print_solution(const std::string &filename, const Solution *solution, const Parameters &p)
{
	std::ofstream svg_stream { filename + ".sol.svg" };
	print_preamble(svg_stream, "solution", p);
	print_solution(svg_stream, *solution);
	print_postamble(svg_stream);
}


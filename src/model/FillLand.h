/*
 * Dump.h
 *
 *  Created on: Sep 8, 2014
 *      Author: thallock
 */

#ifndef FillLand_H_
#define FillLand_H_

#include "model/Action.h"
#include "model/Landfills.h"

class FillLand : public Action
{
public:
	FillLand(const Landfill &l, DumpsterSize size);
	virtual ~FillLand();

	virtual sh_time_t get_time_taken(sh_time_t start_time, const Location &from) const;
	virtual DumpsterSize get_output_dumpster_size() const;
	virtual DumpsterSize get_input_dumpster_size() const;

	friend std::ostream& operator<<(std::ostream& os, const Action& a);
	void loadXml(const tinyxml2::XMLElement* landfill_list);
private:
	virtual void child_save_xml(std::ostream& out) const;
	virtual std::string get_xml_name() const;

	sh_time_t landfill_cost;
	DumpsterSize size;
};

#endif /* DUMP_H_ */

/*
	==================================================
	Project - Milestone #3
	==================================================
	Name   : Thi Hong Minh Le (Melanie)
	ID     : 103087201
	Email  : thmle@myseneca.ca
	Section: BTP305NAA
	Date   : December 1th, 2021

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <vector>
#include "Workstation.h"
// manage an assembly line of active stations
namespace sdds {
	class LineManager {
		std::vector<Workstation*> activeLine{};	// workstations for the current assembly line
		size_t m_cntCustomerOrder{};		// total number of CustomerOrder objects
		Workstation* m_firstStation = nullptr;	// first active station on the current line

	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void linkStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;

	};
}

#endif // !SDDS_LINEMANAGER_H


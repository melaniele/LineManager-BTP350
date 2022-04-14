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

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <iostream>
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"
namespace sdds {
	// accessible outside this Workstation
	extern std::deque<CustomerOrder> pending;
	extern std::deque<CustomerOrder> completed;
	extern std::deque<CustomerOrder> incomplete;

	class Workstation : public Station {
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation;	// pointer to the next workstation on the assembly line

	public:
		Workstation(const std::string& aStation);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);

		//avoid move and copy operators:
		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;
	};
}
#endif // !SDDS_WORKSTATION_H


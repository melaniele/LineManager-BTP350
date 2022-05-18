/*
	==================================================
	Project - Milestone #3
	==================================================
	Name   : Thi Hong Minh Le (Melanie)
	ID     : 103087201
	Email  : thmle@myseneca.ca
	Section: BTP305NAA
	Date   : December 1st, 2021

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include <iostream>
#include <deque>
#include "Workstation.h"
#include "CustomerOrder.h"
#include "Station.h"
using namespace std;

namespace sdds {
	Workstation::Workstation(const std::string& aStation) : Station(aStation)
	{
		m_pNextStation = nullptr;
	}

	void Workstation::fill(std::ostream& os)
	{
		if (m_orders.size() > 0) {
			m_orders.front().fillItem(*this, os);	// fill the order at the front of the queue
		}
	}

	// move the order at the front of the queue to the next station in the assembly line
	bool Workstation::attemptToMoveOrder()
	{
		bool moved = false;
		if (m_orders.size() > 0) {
			// require no more service || not enough inventory
			if (m_orders.front().isItemFilled(getItemName()) || this->getQuantity() == 0) {	
				if (m_pNextStation == nullptr) {		// no next station
					if (m_orders.front().isFilled())	// check each item in the first order
						completed.push_back(move(m_orders.front()));
					else
						incomplete.push_back(move(m_orders.front()));
				}
				else {
					// move to the next station:
					*m_pNextStation += std::move(m_orders.front());	// dereference the pointer aka the actual value
				}
				m_orders.pop_front();	// remove
				moved = true;
			}
		}

		return moved;
	}

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const
	{
		os << getItemName() << " --> ";
		if (m_pNextStation == nullptr)
			os << "End of Line" << endl;
		else
			os << m_pNextStation->getItemName() << endl;
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}

}

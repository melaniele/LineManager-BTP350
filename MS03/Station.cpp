/*
	==================================================
	Project - Milestone #1
	==================================================
	Name   : Thi Hong Minh Le (Melanie)
	ID     : 103087201
	Email  : thmle@myseneca.ca
	Section: BTP305NAA
	Date   : November 15th, 2021

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#include <iostream>
#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	size_t Station::m_widthField = 0u;
	size_t Station::id_generator = 0u;

	Station::Station()	{}

	Station::Station(const std::string& str)
	{
		Utilities temp;
		bool more = true;
		size_t next_pos = 0;

		// update id:
		m_id = ++Station::id_generator;
		
		m_itemName = temp.extractToken(str, next_pos, more);
		m_serialNum = stoi(temp.extractToken(str, next_pos, more));
		m_quantity = stoi(temp.extractToken(str, next_pos, more));

		// update the maximum of Station::m_widthField
		if (m_itemName.size() > Station::m_widthField)
			Station::m_widthField = m_itemName.size();
		if (to_string(m_serialNum).size() > Station::m_widthField)
			Station::m_widthField = to_string(m_serialNum).size();
		if (to_string(m_quantity).size() > Station::m_widthField)
			Station::m_widthField = to_string(m_quantity).size();

		m_description = temp.extractToken(str, next_pos, more);
	}

	const std::string& Station::getItemName() const
	{
		return this->m_itemName;
	}

	size_t Station::getNextSerialNumber()
	{
		size_t nextSerialNum = m_serialNum;
		++m_serialNum;
		return nextSerialNum;
	}

	size_t Station::getQuantity() const
	{
		return m_quantity;
	}

	void Station::updateQuantity()
	{
		if (m_quantity > 0)
			--m_quantity;
	}

	void Station::display(std::ostream& os, bool full) const
	{
		
		os << '[' << setw(3) << right << setfill('0') << m_id << setfill(' ') << "] " ;
		os << "Item: " << left << setw(Station::m_widthField) << m_itemName;
		os << " [" << setw(6) << setfill('0') << right << m_serialNum << setfill(' ') << ']';
		
		if (full) {
			os << " Quantity: " << left << setw(Station::m_widthField) << m_quantity
				<< " Description: " << m_description;
		}

		os << endl;
		
	}

}
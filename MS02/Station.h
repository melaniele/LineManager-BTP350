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
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
namespace sdds {
	class Station {
		/*Class Variables*/
		static size_t m_widthField;	// maximum size for all objects
		static size_t id_generator;	// increment whenever a new instance is created

		/*Instance Variables*/
		int m_id{};
		std::string m_itemName{};
		std::string m_description{};
		size_t m_serialNum{};
		size_t m_quantity{};	// number of items in stock

	public:
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;

	};
	
}

#endif // !SDDS_STATION_H


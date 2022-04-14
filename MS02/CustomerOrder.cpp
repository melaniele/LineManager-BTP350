/*
	==================================================
	Project - Milestone #2
	==================================================
	Name   : Thi Hong Minh Le (Melanie)
	ID     : 103087201
	Email  : thmle@myseneca.ca
	Section: BTP305NAA
	Date   : November 23th, 2021

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include <iostream>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
#include "Station.h"

using namespace std;

namespace sdds {
	size_t CustomerOrder::m_widthField = 0u;

	CustomerOrder::CustomerOrder() {}

	CustomerOrder::CustomerOrder(const std::string& aStr)
	{
		Utilities m_util;
		bool more = true;
		size_t next_pos = 0u;

		m_name = m_util.extractToken(aStr, next_pos, more);
		m_product = m_util.extractToken(aStr, next_pos, more);

		while (more) {
			Item** temp = new Item * [m_cntItem + 1];
			if (m_cntItem > 0) {
				for (auto i = 0u; i < m_cntItem; ++i)
					temp[i] = m_lstItem[i];
			}
			delete[] m_lstItem;
			Item* newItem = new Item(m_util.extractToken(aStr, next_pos, more));
			temp[m_cntItem] = newItem;

			m_lstItem = temp;
			++m_cntItem;	//update the size
		}

		if (CustomerOrder::m_widthField < m_util.getFieldWidth())
			CustomerOrder::m_widthField = m_util.getFieldWidth();

	}

	CustomerOrder::CustomerOrder(const CustomerOrder& src)
	{
		throw 0;
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
	{
		this->m_lstItem = nullptr;
		*this = move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept
	{
		if (this != &src) {
			//clean up
			for (auto i = 0u; i < m_cntItem; ++i) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			// shallow
			this->m_name = src.m_name;
			this->m_product = src.m_product;
			this->m_cntItem = src.m_cntItem;

			// steal the resource
			this->m_lstItem = src.m_lstItem;

			// delete dying resource
			src.m_name = "";
			src.m_product = "";
			src.m_cntItem = 0u;
			src.m_lstItem = nullptr;
		}

		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		for (auto i = 0u; i < m_cntItem; ++i) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	bool CustomerOrder::isFilled() const
	{
		for (auto i = 0u; i < m_cntItem; ++i) {
			if (!m_lstItem[i]->m_isFilled)
				return false;
		}
		return true;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool allFilled = true;
		for (auto i = 0u; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == itemName) {
				if (!m_lstItem[i]->m_isFilled) {
					allFilled = false;
					i = m_cntItem;	// stop immediately when an item is not filled
				}
			}
		}
		
		return allFilled;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (auto i = 0u; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == station.getItemName()){
				if (station.getQuantity() > 0) {
					station.updateQuantity();	// subtract the inventory
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled " << this->m_name << ", " << this->m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
				else if (!m_lstItem[i]->m_isFilled && station.getQuantity() < 0) {
					os << "    Unable to fill " << this->m_name << ", " << this->m_product << m_lstItem[i]->m_itemName << "]" << endl;
				}
			}

		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << this->m_name << " - " << this->m_product << endl;
		for (auto i = 0u; i < m_cntItem; ++i) {
			os << "[" << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << setfill(' ') << "] ";
			os << setw(m_widthField) << left << m_lstItem[i]->m_itemName << " - ";
			(m_lstItem[i]->m_isFilled) ? (os << "FILLED" << endl) : (os << "TO BE FILLED" << endl);
		}
	}

}
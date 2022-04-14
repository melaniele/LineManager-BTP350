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
#include "Utilities.h"
using namespace std;

namespace sdds {
	char Utilities::m_delimiter{};

	void Utilities::setFieldWidth(size_t newWidth)
	{
		this->m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return this->m_widthField;
	}

	//extract token string 'str'
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		size_t lastDelim = str.find_last_of(m_delimiter);
		string extractedToken;

		// check if it's the last string to extract
		if (next_pos - 1 == lastDelim && more) {
			extractedToken = str.substr(next_pos, str.find('\n') - next_pos);
			more = false;
		}

		else if (more){
			size_t found = str.find(m_delimiter, next_pos);

			// reports an exception if a delimiter is found at 'next_pos' & stops
			if (found == next_pos) {
				more = false;
				throw 0;
			}
				
			else
			{
				// 'found - next pos': the size of the string to be extracted
				extractedToken = str.substr(next_pos, found - next_pos);	
				next_pos = found + 1;
			}

		}
		
		// updates the current object m_widthField
		if (m_widthField < extractedToken.size())
			m_widthField = extractedToken.size();

		return extractedToken;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		Utilities::m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return Utilities::m_delimiter;
	}
}
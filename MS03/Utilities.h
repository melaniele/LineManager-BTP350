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

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

namespace sdds {
	class Utilities {
		/*Class Variable: all objects/instances share the same delimiter*/
		static char m_delimiter;

		/*Instance variable: length of the token extracted*/
		size_t m_widthField = 1;

	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		/*Class functions*/
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};

}

#endif // !SDDS_UTILITIES_H

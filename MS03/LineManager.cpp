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

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <deque>
#include "Workstation.h"
#include "LineManager.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	// definition for the global containers
	std::deque<CustomerOrder> pending;
	std::deque<CustomerOrder> completed;
	std::deque<CustomerOrder> incomplete;

	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		ifstream filename(file);
		// stores the workstations into the "activeLine"
		// load all contents of the file -> store the address of the next workstation in each element of the collection
		if (filename) {
			while (!filename.eof()) {
				Workstation* tempWS;
				Utilities util;
				std::string str{}, currentStation{};	// str will also be the next station
				bool more = true;
				size_t pos = 0;
				util.setDelimiter('|');

				std::getline(filename, str);
				currentStation = util.extractToken(str, pos, more);
				str = util.extractToken(str, pos, more);	// next station

				// check if the extracted station is in the "stations"
				// tempWS is a pointer -> *find_if(...)
				tempWS = *find_if(stations.begin(), stations.end(), [=](const Workstation* thisStation) {return (thisStation->getItemName() == currentStation); });

				// check if the next station is in the `stations` only when next station is extracted
				if (str != "") {
					auto nextStt = find_if(stations.begin(), stations.end(), [=](const Workstation* thisStation) 
						{return (thisStation->getItemName() == str); });
					tempWS->setNextStation(*nextStt);
				}
				// else nextStation will be nullptr
				activeLine.push_back(std::move(tempWS));
			}

			// identify the m_firstStation: 
			// find if any workstation doesn't have next station is THAT WORKSTATION
			m_firstStation = *find_if(activeLine.begin(), activeLine.end(), [&](const Workstation* s1)
				{return (none_of(activeLine.begin(), activeLine.end(), [&](const Workstation* s2)
					{return (s2->getNextStation() == s1); })); });

			m_cntCustomerOrder = pending.size();
			filename.close();
		}
		else
			throw string("Can't open file: " + file);

	}
	
	// reorders the workstations in `activeLine` -> store again in the instance variable
	// start with m_firstStation
	void LineManager::linkStations()
	{
		auto temp = this->m_firstStation;
		std::vector<Workstation*> result;
		while (temp != nullptr) {
			result.push_back(temp);
			temp = temp->getNextStation();
		}

		this->activeLine = result;
	}
	
	bool LineManager::run(std::ostream& os)
	{
		static size_t m_runtime = 0;
		os << "Line Manager Iteration: " << ++m_runtime << endl;

		// if `pending` has a Customer order object -> move the order to the firstStation of `activeLine` -> remove from `pending`
		if (pending.size() > 0) {
			*m_firstStation += move(pending.front());
			pending.pop_front();
		}
		// for each station on `activeLine`, execute 1 fill
		for_each(activeLine.begin(), activeLine.end(), [&](Workstation* aWorkStt) {aWorkStt->fill(os); });
		
		// for each station on `activeLine`, attemptToMoveOrder to the next station
		for_each(activeLine.begin(), activeLine.end(), [&](Workstation* aWorkStt)
			{ aWorkStt->attemptToMoveOrder();});

		// true if all customers in m_cntCustomerOrder have been filled
		return (m_cntCustomerOrder == (completed.size() + incomplete.size()));
	}
	
	void LineManager::display(std::ostream& os) const
	{
		for_each(activeLine.begin(), activeLine.end(), [&](Workstation* aWorkStt)
			{aWorkStt->display(os); });
	}
}
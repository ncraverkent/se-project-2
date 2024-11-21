#pragma once
#include <string>
#include <vector>
#include "Guest.h"

namespace WEP
{
	/**
	* A business that is holding an event
	*/
	class Business
	{
	public:
		/**
		* @returns The name of the Business
		*/
		const std::string& getName() const { return this->name; }
		/**
		* @returns The guess list of this Business
		*/
		const std::vector<Guest>& getGuestList() const { return this->guestList; }

	private:
		std::string name;
		std::vector<Guest> guestList;
	};
}



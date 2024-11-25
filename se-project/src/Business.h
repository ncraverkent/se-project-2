#pragma once
#include <string>
#include <vector>
#include "Guest.h"
#include "Defs.h"
#include "Utils/UUID.h"

namespace WEP
{
	/**
	* A business that is holding an event
	*/
	class Business
	{
	public:
		Business(const String& name) : name(name), guestList({}), id(generateUUID()) {}

		/**
		* @returns The name of the Business
		*/
		const std::string& getName() const { return this->name; }
		/**
		* @returns The guest list of this Business
		*/
		const std::vector<Guest>& getGuestList() const { return this->guestList; }
		/**
		* @returns The id of this Business
		*/
		const UUID& getId() const { return this->id; }

		/**
		* Gives the user a series of prompts to create new buisness
		*/
		static Option<Business> promptUserNew();


	private:
		std::string name;
		std::vector<Guest> guestList;
		UUID id;
	};
}



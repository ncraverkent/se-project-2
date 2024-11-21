#pragma once
#include "Event.h"

namespace WEP
{	/**
	* @breif A Funeral event
	* 
	* A class that represents a funeral, with all its associated details.
	*/
	class Funeral : public Event
	{
	public:
		/**
		*	@returns The deceased persons name
		*/
		const std::string& getDeceasedName() const { return this->deceasedName; }

		/**
		*	@returns The deceased persons birth date
		*/
		const Date& getBirthDate() const { return this->birthDate; }

		/**
		*	@returns The deceased persons deat date
		*/
		const Date& getDeathDate() const { return this->deathDate; }

		/**
		* @brief Implements the getDetails function from the Event class
		*/
		std::string getDetails() const override;
	private:
		std::string deceasedName;
		Date birthDate;
		Date deathDate;
	};
}
#pragma once
#include "Event.h"
#include "Defs.h"

namespace WEP
{
	/**
	* @breif A birthday party event
	* 
	* A class that represents a birthday party, with all its associated details.
	*/
	class Birthday : public Event
	{
	public:
		/**
		* Constructs the birthday class
		* @todo Implement
		*/
		Birthday(std::string name, unsigned int age, Date date, std::vector<Activity> activities, List<Guest> guests, UUID businessId) :
			subjectName(name), subjectAge(age), 
			Event("Birthday for " + name, date, activities, guests, businessId)
		{}

		/**
		* @returns The subjects name
		*/
		const std::string& getSubjectName() const { return this->subjectName; }
		/**
		* @returns The subjects age
		*/
		unsigned int getSubjectAge() const { return this->subjectAge; }

		/**
		* @brief Implements the getDetails function from the Event class
		*/
		std::string getDetails() const override;

		/*
		* Promps the user to create a Birthday event, and fill out all the data for it
		* @param businessId The id for the owning business
		* @returns An invalid option if the creation was cancled, or a valid one if the creation was not
		*/
		static Option<Arc<Event>> promptCreateEvent(UUID businessId);

	private:
		std::string subjectName;
		unsigned int subjectAge;
	};
}

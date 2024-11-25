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
		Birthday(std::string name, unsigned int age, Date date, std::vector<Activity> activities, UUID businessId) :
			subjectName(name), subjectAge(age), 
			Event("Birthday for " + name, date, activities, businessId)
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

		static Option<Arc<Event>> promptCreateEvent(UUID businessId);

	private:
		std::string subjectName;
		unsigned int subjectAge;
	};
}

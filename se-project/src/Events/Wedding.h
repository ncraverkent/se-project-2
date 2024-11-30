#pragma once
#include <string>
#include "Event.h"
#include "Defs.h"
#include "Guest.h"

namespace WEP
{
	/**
	* @breif A Wedding event
	*
	* A class that represents a Wedding, with all its associated details.
	*/
	class Wedding : public Event
	{
	public:
		Wedding(String partnerA, String partnerB, Date date, List<Arc<Activity>> activities, List<Guest> guests, UUID businessId) :
			partnerA(partnerA), partnerB(partnerB), 
			Event(("Marrage between " + partnerA + " and " + partnerB), date, activities, guests, businessId)
		{}

		/**
		*	@returns the first partners name
		*/
		const std::string& getPartnerAName() const { return this->partnerA; }
		/**
		*	@returns the second partners name
		*/
		const std::string& getPartnerBName() const { return this->partnerB; }

		/**
		* @brief Implements the getDetails function from the Event class
		*/
		std::string getDetails() const override;

		/*
		* Promps the user to create a Wedding event, and fill out all the data for it
		* @param businessId The id for the owning business
		* @returns An invalid option if the creation was cancled, or a valid one if the creation was not
		*/
		static Option<Arc<Event>> promptCreateEvent(UUID businessId);
	private:

		std::string partnerA;
		std::string partnerB;
	};
}
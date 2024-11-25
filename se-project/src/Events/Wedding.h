#pragma once
#include <string>
#include "Event.h"
#include "Defs.h"

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
		Wedding(String partnerA, String partnerB, Date date, List<Activity> activities, UUID businessId) :
			partnerA(partnerA), partnerB(partnerB), 
			Event(("Marrage between" + partnerA + " and " + partnerB), date, activities, businessId)
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

		static Option<Arc<Event>> promptCreateEvent(UUID businessId);
	private:

		std::string partnerA;
		std::string partnerB;
	};
}
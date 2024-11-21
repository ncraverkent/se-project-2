#pragma once
#include <string>
#include "Event.h"

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
	private:

		std::string partnerA;
		std::string partnerB;
	};
}
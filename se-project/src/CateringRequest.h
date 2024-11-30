#pragma once
#include <string>
#include "Utils/UUID.h"

namespace WEP
{
	/*
	* A catering request for an activity
	* @note Not all events require catering
	*/
	class CateringRequest
	{
	public:
		/**
		* Creates an instance of the catering request
		* @param id The id of the catering request
		* @param company The name of the catering company
		* @param guestCount the number of guests that is being requested to cater to
		* @param cateringCost the available funds for catering
		*/
		CateringRequest(String company, unsigned int guestCount, float cateringCost) :
			requestId(generateUUID()), cateringCompany(company), numberOfGuests(guestCount), 
			cateringCost(cateringCost)
		{}

		/**
		* @returns The id of this catering request
		*/
		const std::string& getId() const { return this->requestId; }
		
		/**
		* @returns The company name for this catering request
		*/
		const std::string& getCompany() const { return this->cateringCompany; }
		
		/**
		* @returns The guest count required for catering
		*/
		u32 getGuestCount() const { return this->numberOfGuests; }
		
		/**
		* @returns The cost this the catering request
		*/
		float getCost() const { return this->cateringCost; }

		/**
		* Formats the catering request to make it look pretty
		*/
		String getDetails() const;

		/**
		* Prompts the user to create a catering request. It may be none, as a catering request might not have been wanted
		*/
		static Option<CateringRequest> promptCreateCateringRequest();

	private:
		UUID requestId;
		String cateringCompany;
		u32 numberOfGuests;
		float cateringCost;
	};
}
#pragma once
#include <string>
#include "Activity.h"

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
		* @param activity The activity of the catering request @warning is a reference, so the activity cannot go out of scope before this request does
		* @param company The name of the catering company
		* @param guestCount the number of guests that is being requested to cater to
		* @param cateringCost the available funds for catering
		*/
		CateringRequest(std::string id, Activity* activity, std::string company, unsigned int guestCount, float cateringCost) :
			requestId(id), activity(activity), cateringCompany(company), numberOfGuests(guestCount), cateringCost(cateringCost) {}

		/**
		* @returns The id of this catering request
		*/
		const std::string& getId() const { return this->requestId; }
		/**
		* @returns The activity of this catering request
		*/
		const Activity& getActivity() const { return *this->activity; }
		/**
		* @returns The company name for this catering request
		*/
		const std::string& getCompany() const { return this->cateringCompany; }
		/**
		* @returns The guest count required for catering
		*/
		unsigned int getGuestCount() const { return this->numberOfGuests; }
		/**
		* @returns The cost this the catering request
		*/
		float getCost() const { return this->cateringCost; }

	private:
		std::string requestId;
		Activity* activity;
		std::string cateringCompany;
		unsigned int numberOfGuests;
		float cateringCost;
	};
}
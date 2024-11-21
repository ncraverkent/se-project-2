#pragma once
#include "Guest.h"
#include "Activity.h"
#include "Utils/Date.h"

namespace WEP
{
	/**
	* A registration for a guest for a given activity
	* @warning the guest and activity here are pointers, and so cannot go out of scope before this class
	*/
	class Registration
	{
	public:
		/**
		* Constructs an instance of the registration class
		* @param guest A pointer to the guest that is being registered
		* @param activity A pointer to the activity that the guest is being registered to
		* @param date The date that the registration took place
		*/
		Registration(Guest* guest, Activity* activity, Date date) :
			guest(guest), activity(activity), date(date) {}

		/**
		* @returns The guest that is being registered
		*/
		const Guest& getGuest() const { return *this->guest; }
		/**
		* @returns The activity that the guest is being registered for
		*/
		const Activity& getActivity() const { return *this->activity; }
		/**
		* @returns The date of the registration
		*/
		const Date& getDate() const { return this->date; }

	private:
		Guest* guest;
		Activity* activity;
		Date date;
	};
}
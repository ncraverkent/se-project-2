#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Utils/Date.h"
#include "Activity.h"

namespace WEP
{
	/**
	* @breif The base class for all of the different types of Events
	* 
	* Is an abstract class which can be overriden by different derived classes to add extra information about the event
	*/
	class Event
	{
	public:
		/**
		*	Constructs an instance of the event class
		*/
		Event(std::string name, Date date, std::vector<Activity> activities) : 
			name(name), date(date), activities(activities) {}

		/**
		*	Adds an activity to the event
		*	@param activity The activity to be added
		*	@returns wether or not the activity was successfully added
		*/
		bool addActivity(Activity activity);

		/**
		*	@Returns the name of the Event
		*/
		const std::string& getName() const { return this->name; }

		/**
		* @returns The date of the event
		*/
		const Date& getDate() const { return this->date; }

		/**
		* @returns The activities of the event
		*/
		const std::vector<Activity> getActivities() const { return this->activities; }

		/**
		* Calculates the cost of the event
		* @returns The cost of the event
		*/
		float getCost() const;

		/**
		*	Logs if the event was successfully booked?
		*	@todo Remember why this was added
		*/
		void confirmBooking() const;
		
		/**
		* @returns The formatted data of the event, which can be logged
		*/
		virtual std::string getDetails() const = 0;

	private:
		std::string name;
		Date date;
		std::vector<Activity> activities;

	};
}
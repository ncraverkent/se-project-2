#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Utils/Date.h"
#include "Activity.h"
#include "Defs.h"
#include "Utils/UUID.h"

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
		Event(String name, Date date, List<Activity> activities, UUID businessId) : 
			name(name), date(date), activities(activities), businessId(businessId) ,
			eventId(generateUUID())
		{}

		/**
		*	Adds an activity to the event
		*	@param activity The activity to be added
		*	@returns wether or not the activity was successfully added
		*/
		bool addActivity(Activity activity);

		/**
		*	@Returns the name of the Event
		*/
		const String& getName() const { return this->name; }

		/**
		* @returns The date of the event
		*/
		const Date& getDate() const { return this->date; }

		/**
		* @returns The activities of the event
		*/
		const List<Activity> getActivities() const { return this->activities; }

		/**
		* @returns The id of the business that this event is organized by
		*/
		const UUID& getBusinessId() const { return this->businessId; }

		/**
		* @returns The id of this event
		*/
		const UUID& getId() const { return this->eventId; }

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
		virtual String getDetails() const = 0;

		static Option<Arc<Event>> promptCreateEvent(UUID businessId);

	private:
		String name;
		Date date;
		List<Activity> activities;
		UUID businessId;
		UUID eventId;
	};
}
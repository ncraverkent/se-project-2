#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Utils/Date.h"
#include "Activity.h"
#include "Defs.h"
#include "Utils/UUID.h"
#include "Guest.h"

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
		Event(String name, Date date, List<Arc<Activity>> activities, List<Guest> guests, UUID businessId) :
			name(name), date(date), activities(activities), businessId(businessId),
			eventId(generateUUID()), guests(guests)
		{}

		/**
		*	Adds an activity to the event
		*	@param activity The activity to be added
		*	@returns wether or not the activity was successfully added
		*/
		bool addActivity(Activity activity);

		/**
		* @returns the list of guests for this event
		*/
		const List<Guest>& getGuests() const { return this->guests; }

		/**
		*	@returns the name of the Event
		*/
		const String& getName() const { return this->name; }

		/**
		* @returns The date of the event
		*/
		const Date& getDate() const { return this->date; }

		/**
		* @returns The activities of the event
		*/
		List<Arc<Activity>> getActivities() const { return this->activities; }

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
		List<Pair<String, Cost>> getCosts() const;

		/**
		*	Logs if the event was successfully booked?
		*	@todo Remember why this was added
		*/
		void confirmBooking() const;
		
		/**
		* @returns The formatted data of the event, which can be logged
		*/
		virtual String getDetails() const = 0;

		/*
		* Promps the user to create an event, and fill out all the data for it
		* @param businessId The id for the owning business
		* @returns An invalid option if the creation was cancled, or a valid one if the creation was not
		*/
		static Option<Arc<Event>> promptCreateEvent(UUID businessId);

	private:
		String name;
		Date date;
		List<Arc<Activity>> activities;
		List<Guest> guests;
		UUID businessId;
		UUID eventId;
	};
}
#pragma once
#include <string>
#include <vector>
#include "Events/Event.h"

namespace WEP
{
	/**
	* The primary class for planning events
	*/
	class WeddingEventCenter
	{
	public:
		/*
		* Tries to scheduel an event
		* @returns false if the event was failed to be scheduled
		* @param event The event to be scheduled
		*/
		bool scheduleEvent(Event& event);
		/*
		* Returns the list of events that are currently scheduled
		*/
		std::vector<Event> getEvents();
		/**
		* @returns All the available days that events can take place in
		*/
		std::vector<Date> getAvailableSlots();
		/**
		* Allocates resources for an event
		* @returns False not enouph resources were allocated
		*/
		bool allocateResources(const Event& event);
		/*
		* @returns The aproximate cost of the event
		*/
		float calculateCost(const Event& event);
		/**
		* Confirms the booking of the event
		*/
		void confirmBooking(const Event& event);
			
	private:
		std::string name;
		static const int MAX_PARALLEL_EVENTS = 3;
	};
}

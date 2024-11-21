#pragma once
#include <vector>
#include "Utils/Date.h"
#include "Events/Event.h"

namespace WEP
{
	/**
	* Represents the Events that are to take place on a given day
	*/
	class Schedule
	{
	public:
		/**
		* Constructs a instance of the Schedule class
		* @param date The date that the events are Scheduled to take place
		* @param events the Events that are schedueld to take place
		*/
		Schedule(Date date, std::vector<Event> events) :
			date(date), events(events) {}

		/**
		* @returns The Date of this schedule
		*/
		const Date& getDate() const { return this->date; }
		/**
		* @returns The evebts if this schedule
		*/
		const std::vector<Event> getEvents() const { return this->events; }
	private:
		Date date;
		std::vector<Event> events;
	};
}
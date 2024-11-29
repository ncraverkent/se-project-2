#pragma once
#include "Defs.h"
#include "Utils/UUID.h"
#include <string>

namespace WEP
{
	class Activity;

	/**
	* A guest to an event
	*/
	class Guest
	{
	public:
		/**
		* @param name the name of the guest
		* @param id The id of the guest
		*/
		Guest(String name, List<UUID> activities, UUID id = generateUUID()) :
			name(name), activites(activities), registrationId(id)
		{}

		/**
		* @returns The name of this Guest
		*/
		const String& getName() { return name; }
		/**
		* @returns The id of this Guest
		*/
		const UUID& getId() { return registrationId; }

		const List<UUID>& getActivities() const { return activites; }

		/**
		* Formats the guest information into a string
		* @returns The formatted guest information
		*/
		String getDetails() const;

		/**
		* Prompts the user to create a guest
		*/
		static Guest promptCreateGuest(const List<Activity>& activities);

		/**
		* Prompts the user to create a guest list
		*/
		static List<Guest> promptCreateGuestList(const List<Activity>& activities);

		/**
		* Formats the guest list
		* @returns the given guest list in a printable string formatted like:
		* "
		* - Guest List:
		*	 - Guest Name: [Guest Id]
		*	...
		* "
		*/
		static String formatGuestList(const List<Guest>& guests);

	private:
		static List<UUID> registerGuestForActivities(const List<Activity> activites);

	private:
		String name;
		UUID registrationId;
		List<UUID> activites;
	};
}
#pragma once

#include <string>
#include "Activity.h"

namespace WEP
{
	/**
	* A guest to an event
	*/
	class Guest
	{
	public:
		/**
		* @returns The name of this Guest
		*/
		const std::string& getName();
		/**
		* @returns The id of this Guest
		*/
		const std::string& getId();

		/**
		* Attempts to register a guest for an activity
		* @returns True if was successfully registered
		*/
		bool registerForActivity(Activity activity);

	private:
		const std::string name;
		const std::string registrationId;
	};
}
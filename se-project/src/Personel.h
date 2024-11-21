#pragma once
#include <string>
#include "Activity.h"
#include "Problem.h"

namespace WEP
{
	/**
	* Personel who oversee activities
	*/
	class Personel
	{
	public:
		/**
		* @returns The name of this personel
		*/
		const std::string& getName() const { return this->name; }
		/**
		* Logs an issue from this personel
		* @param issue The Problem that is to be logged
		*/
		void reportIssue(Problem issue);

	private:
		std::string name;
		Activity* assignedActivity;
	};
}
#pragma once
#include <string>

namespace WEP
{
	/**
	* @enum Month
	* @breif Represents the 12 months in the year
	* 
	* Makes it easier to work with then using the intagers 1 through 12, or using strings, as enum classes are typed
	*/
	enum class Month
	{
		Jan,
		Feb,
		Mar,
		Apr,
		May,
		Jun,
		Jul,
		Aug,
		Sep,
		Oct,
		Nov,
		Dec,
	};

	/**
	* Represents a date in time
	*/
	struct Date
	{
		int day; ///< The current month (based on month)
		Month month; ///< The current month
		int year; ///< The current year

		/**
		* Constructs the Date class with a month day and year
		* @warning this is unchecked, so a day could be set that is over the number of days in a given month
		* @todo make this check days, and account for leap years
		*/
		Date(int day, Month month, int year) :
			day(day), month(month), year(year) {}

		/**
		* @returns True if two dates are equal
		*/
		bool operator==(const Date&) const;
		/**
		* @returns Ffalse if two dates are equal
		*/
		bool operator!=(const Date&) const;

		/**
		* Parses a string into a date
		* @param str the string to parse
		* @returns The parsed date
		* @todo this does not have any error checking for date formating, so we may need to fix
		*/
		static Date fromString(const std::string& str);
	};
}


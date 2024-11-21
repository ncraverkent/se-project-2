#pragma once
#include <string>


namespace WEP
{
	/**
	* @breif Represents a point in time
	* Can be any particular day
	* @warning Both hour and minute are currently unchecked
	* @todo Make both the hour and minute clamped to their highest value
	*/
	struct Time
	{
		unsigned int hour;
		unsigned int minute;
	};

	/**
	* A class representing a range in time
	* @warning The start and end time ranges are unchecked, and may be swapped around
	* @todo Make the time ranges swappable, and automatically sorted into their minimum and maximum values
	*/
	struct TimeRange
	{
		Time start;
		Time end;

		/**
		* Constructs a time range from a start and end values
		* @param start The starting time point, must be less than end
		* @param end The ending time point, must be greater than start
		*/
		TimeRange(Time start, Time end) :
			start(start), end(end) {}

		/**
		* @returns True if this time range overlaps with a different one
		*/
		bool overlaps(const TimeRange& other) const;
		/**
		* @returns True if the time ranges are equal
		*/
		bool operator==(const TimeRange& other) const;
		/**
		* @returns False if the time ranges are equal
		*/
		bool operator!=(const TimeRange& other) const;

		/**
		* Parses a string into a TimeRange
		* @param str the string to parse
		* @returns The parsed TimeRange
		* @todo this does not have any error checking for time formating, so we may need to fix
		*/
		static TimeRange fromString(const std::string& str);
	};
}



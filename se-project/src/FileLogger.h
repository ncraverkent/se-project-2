#pragma once
#include <string>
#include "Events/Event.h"
#include "Problem.h"

namespace WEP
{
	/**
	* A static class for logging data to files
	*/
	class DataLogger
	{
	public:
		/**
		* Logs the data for an event
		*/
		static void logEvent(const Event& event);
		/**
		* Logs the data for a problem
		*/
		static void logProblem(const Problem& problem);

	private:
		static const char* BASE_FILE_PATH;
	};
}
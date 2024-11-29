#pragma once
#include <string>
#include "Defs.h"
#include <functional>
#include <cctype>
#include <iostream>
#include "Date.h"
#include <utility>

namespace WEP
{
	/**
	* @returns True if the string contains only a-zA-Z0-9' and spaces
	*/
	bool isName(const String& str);

	/**
	* @breif A class with many static functions for console manipulation
	*/
	struct Console
	{
		/**
		* Runs a basic prompt with a question message, error message, and a get input function
		*/
		template<typename T>
		static T prompt(const String& msg, const String& err, std::function<Option<T>()> getInput)
		{
			while (true)
			{
				std::cout << msg;
				auto input = getInput();
				if (input.has_value())
				{
					return input.value();
				}
				else
				{
					std::cout << err << '\n';
				}
			}
		}
		/**
		* Runs a basic prompt for a number with a message
		*/
		static size_t promptNumber(const String& msg);

		/**
		* Runs a basic prompt for a line of text with a message
		*/
		static String promptLine(const String& msg);

		/**
		* Runs a basic prompt for a name, using the `isName` function
		*/
		static String promptName(const String& msg);

		/**
		* Runs a basic prompt for a date, with a message
		*/
		static Date promptDate(const String& msg);

		/**
		* Runs a basic confirmation prompt with a message
		*/
		static bool promptConfirm(String message);

		/**
		* Prompts the user for a list of commands
		*/
		static List<String> promptCommands(String message);

		static void printHelpCommands(const String& message, const List<Pair<String, String>>&);
	};
}
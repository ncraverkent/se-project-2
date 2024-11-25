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
	bool isName(const String& str)
	{
		for (auto c : str)
		{
			if (!(std::isalpha(c) || std::isdigit(c) || std::isspace(c) || c == '\'')) 
				return false;
		}

		return true;
	}

	struct Console
	{
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

		static size_t promptNumber(const String& msg);
		static String promptLine(const String& msg);
		static String promptName(const String& msg);
		static Date promptDate(const String& msg);
		static bool promptConfirm(String message);
	};
}
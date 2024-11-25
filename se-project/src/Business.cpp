#include "Business.h"
#include "Utils/Prompts.h"
#include <sstream>

namespace WEP
{
	Option<Business> Business::promptUserNew()
	{
		String name = Console::promptName("Please enter the buisness' name:");

		std::stringstream ss;
		ss << "Do you want to create a new buisness with:\n"
			<< " - name = '" << name << "'" << "\n";

		if (Console::promptConfirm(ss.str()))
		{
			return Business(name);
		}
		else
		{
			return {};
		}
	}
}

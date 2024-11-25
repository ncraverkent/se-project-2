#include "Business.h"
#include "Utils/Prompts.h"
#include <sstream>

namespace WEP
{
	Option<Business> Business::promptUserNew()
	{
		String name = Console::promptName("Please the buisness' name:");
		
		std::stringstream ss;
		ss << "Do you want to create a new buisness with:\n"
		   << " - name = '" << name << "'"
	}
}

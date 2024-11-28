#include "Guest.h"
#include "Utils/Prompts.h";
#include <sstream>

const char* NEW_GUEST_COMMAND = "new";
const char* CANCEL_COMMAND = "cancel";
const char* HELP_COMMAND = "help";
const char* END_COMMAND = "end";
const char* REDO_COMMAND = "redo";

namespace WEP
{
	String Guest::getDetails() const
	{
		return name + ": [" + registrationId + "]";
	}

	Guest Guest::promptCreateGuest()
	{
		String name = Console::promptName("Please enter the guests name: ");
		return Guest(name);
	}

	List<Guest> Guest::promptCreateGuestList()
	{
		List<Guest> guests = {};
		while (true)
		{
			List<String> commands = Console::promptCommands("Please enter a guest command: ");
			if (commands.size() == 0)
			{
				continue;
			}
			else if(commands[0] == NEW_GUEST_COMMAND)
			{
				guests.push_back(Guest::promptCreateGuest());
			}
			else if (commands[0] == END_COMMAND)
			{
				return guests;
			}
			else if (commands[0] == CANCEL_COMMAND)
			{
				return {};
			}
			else if (commands[0] == REDO_COMMAND)
			{
				guests = {};
			}
			else if (commands[0] == HELP_COMMAND)
			{
				Console::printHelpCommands("List of Guest commands:", {
					{ NEW_GUEST_COMMAND, "Create a new guest in the list" },
					{ END_COMMAND, "Ends the creation of the list" },
					{ CANCEL_COMMAND, "Cancels the construction of the guest list" },
					{ REDO_COMMAND, "Clears the guest list so that you can reenter them" },
					{ HELP_COMMAND, "Prints out an array of command descriptions" },
				});
			}
		}
	}

	String Guest::formatGuestList(const List<Guest>& guests)
	{
		std::stringstream ss = {};
		ss << " - Guest List:\n";
		for (const Guest& guest : guests)
		{
			ss << "\t - " << guest.getDetails() << "\n";
		}

		return ss.str();
	}
}


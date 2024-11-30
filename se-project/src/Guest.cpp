#include "Guest.h"
#include "Utils/Prompts.h";
#include <sstream>
#include "Activity.h"

const char* NEW_GUEST_COMMAND = "new";
const char* CANCEL_COMMAND = "cancel";
const char* HELP_COMMAND = "help";
const char* END_COMMAND = "end";
const char* REDO_COMMAND = "redo";
const char* NEW_ACTIVITY_REGISTRATION_COMMAND = "reg";

namespace WEP
{
	String Guest::getDetails() const
	{
		String details =  name + ": [activities = ";
		for (size_t i = 0; i < activites.size(); i++)
		{
			if (i != 0) details += ", ";
			details += activites[i];
		}

		details += "; id = " + registrationId + "]";
		return details;
	}

	Guest Guest::promptCreateGuest(const List<Arc<Activity>>& activities)
	{
		String name = Console::promptName("Please enter the guests name: ");
		List<UUID> registered = registerGuestForActivities(activities);
		return Guest(name, registered);
	}

	List<Guest> Guest::promptCreateGuestList(const List<Arc<Activity>>& activities)
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
				guests.push_back(Guest::promptCreateGuest(activities));
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

	List<UUID> Guest::registerGuestForActivities(const List<Arc<Activity>>& activites)
	{
		Map<UUID, const Activity*> activityMap = {}; // DONT DO THIS
		for (const auto& activity : activites)
		{
			activityMap.insert({ activity->getId(), activity.get()});
		}

		List<UUID> registeredActivities = {};
		while (true)
		{
			List<String> commands = Console::promptCommands("Please enter a guest registration command: ");
			if (commands.size() == 0)
			{
				continue;
			}
			else if (commands[0] == NEW_ACTIVITY_REGISTRATION_COMMAND)
			{
				String activityName = Console::promptName("Please enter activity name: ");
				for (size_t i = 0; true; i++)
				{
					if (i >= activites.size())
					{
						std::cout << "Activity named '" << activityName << "' does not exist.\n";
						break;
					}

					if (activites[i]->getName() == activityName)
					{
						if (std::find(registeredActivities.begin(), registeredActivities.end(), activites[i]->getId()) != registeredActivities.end())
						{
							std::cout << "Already registered for activity '" << activityName << "'\n";
							break;
						}

						const auto& registeringActivity = activites[i];
						bool overlaps = false;
						for (const auto& id : registeredActivities)
						{
							const auto& registered = activityMap[id];
							if (registered->getTime().overlaps(registeringActivity->getTime()))
							{
								overlaps = true;
							}
						}

						if (overlaps)
						{
							std::cout << "Chosen activity '" << activityName << "' overlaps with another activity\n";
							break;
						}
						else
						{
							std::cout << "Registered guest for activity '" << activityName << "'\n";
							registeredActivities.push_back(registeringActivity->getId());
							break;
						}
					}
				}
			}
			else if (commands[0] == END_COMMAND)
			{
				return registeredActivities;
			}
			else if (commands[0] == CANCEL_COMMAND)
			{
				return {};
			}
			else if (commands[0] == REDO_COMMAND)
			{
				registeredActivities = {};
			}
			else if (commands[0] == HELP_COMMAND)
			{
				Console::printHelpCommands("List of Guest Registration commands:", {
					{ NEW_ACTIVITY_REGISTRATION_COMMAND, "Allows you to register a guest for an activity" },
					{ END_COMMAND, "Ends the registration of the guest to activities" },
					{ CANCEL_COMMAND, "Cancels the registering the guest for activities" },
					{ REDO_COMMAND, "Clears the guest registration list so that you can reenter them" },
					{ HELP_COMMAND, "Prints out an array of command descriptions" },
				});
			}
		}
	}
}


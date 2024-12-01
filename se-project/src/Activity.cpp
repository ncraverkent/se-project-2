#include "Activity.h"
#include "Utils/Prompts.h"
#include <sstream>

namespace WEP
{
	static const char* NEW_ACTIVITY_COMMAND = "new";
	static const char* CANCEL_COMMAND = "cancel";
	static const char* HELP_COMMAND = "help";
	static const char* END_COMMAND = "end";
	static const char* REDO_COMMAND = "redo";

	Option<Activity> Activity::promptCreateActivity()
	{
		String name = Console::promptName("Please enter the Activity's name: ");
		TimeRange timeRange = Console::promptTimeRange("Please enter the time range of the activity: ");
		Arc<Room> room = Room::promptSelectRoom();
		float registrationCost = Console::promptFloat("Please enter the registration cost for the Activity: ");
		List<Equipment> equipment = Equipment::promptEquipmentList();
		Option<CateringRequest> catering = CateringRequest::promptCreateCateringRequest();

		std::stringstream ss;
		ss << "Do you want to create a Activity with:\n"
			<< " - name = " << name << "\n"
			<< " - time range = " << timeRange.toString() << "\n"
			<< " - room = " << room->getName() << "\n"
			<< " - registration cost = $" << std::to_string(registrationCost) << "\n"
			<< Equipment::formatEquipmentList(equipment) << "\n"
			<< " - catering request = " << (catering.has_value() ? catering.value().getDetails() : "None") << "\n";

		if (Console::promptConfirm(ss.str()))
		{
			return Activity(name, timeRange, std::move(room), registrationCost, equipment, catering);
		}
		else
		{
			return {};
		}
	}

	List<Arc<Activity>> Activity::promptCreateActivityList()
	{
		List<Arc<Activity>> activities = {};
		while (true)
		{
			List<String> commands = Console::promptCommands("Please enter a activity command: ");
			if (commands.size() == 0)
			{
				continue;
			}
			else if (commands[0] == NEW_ACTIVITY_COMMAND)
			{
				auto activity = Activity::promptCreateActivity();
				if (activity.has_value())
					activities.push_back(std::make_shared<Activity>(activity.value()));
			}
			else if (commands[0] == END_COMMAND)
			{
				return activities;
			}
			else if (commands[0] == CANCEL_COMMAND)
			{
				return {};
			}
			else if (commands[0] == REDO_COMMAND)
			{
				activities = {};
			}
			else if (commands[0] == HELP_COMMAND)
			{
				Console::printHelpCommands("List of Activity commands:", {
					{ NEW_ACTIVITY_COMMAND, "Create a new Activity in the list" },
					{ END_COMMAND, "Ends the creation of the list" },
					{ CANCEL_COMMAND, "Cancels the construction of the Activity list" },
					{ REDO_COMMAND, "Clears the Activity list so that you can reenter them" },
					{ HELP_COMMAND, "Prints out an array of command descriptions" },
				});
			}
		}
	}

	String Activity::formatActivityList(const List<Arc<Activity>>& activites)
	{
		std::stringstream ss = {};
		ss << " - Activity List:\n";
		for (const auto& activity : activites)
		{
			ss << "\t - Activity:\n"
			   << "\t\t - name = " << activity->name << "\n"
			   << "\t\t - id = " << activity->id << "\n"
			   << "\t\t - time range = " << activity->time.toString() << "\n"
			   << "\t\t - room = " << activity->room->getName() << "\n"
			   << "\t\t - registration cost = $" << std::to_string(activity->registrationCost) << "\n"
			   << Equipment::formatEquipmentList(activity->equipment, "\t\t\t") << "\n"
			   << "\t\t - catering request = " << (activity->catering.has_value() ? activity->catering.value().getDetails() : "None") << "\n";
		}

		return ss.str();
	}

	Cost Activity::getCost() const
	{
		Cost cost = {};
		for (const auto& e : equipment)
		{
			cost.addCost(e.getName(), e.getCost());
		}

		cost.addCost("Room: " + room->getName(), room->getCost());

		if (catering.has_value())
		{
			cost.addCost("Catering: " + catering->getCompany(), catering->getCost());
		}

		return cost;
	}
}

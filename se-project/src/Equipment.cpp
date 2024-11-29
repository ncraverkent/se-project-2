#include "Equipment.h"
#include "Utils/Prompts.h"
#include <sstream>

namespace WEP
{
	const char* NEW_EQUIPMENT_COMMAND = "new";
	const char* CANCEL_COMMAND = "cancel";
	const char* HELP_COMMAND = "help";
	const char* END_COMMAND = "end";
	const char* REDO_COMMAND = "redo";

	Option<Equipment> Equipment::promptCreateEquipment()
	{
		String name = Console::promptName("Please enter the name of the equipment: ");
		String type = Console::promptName("Please enter the type of the equipment: ");
		float cost = Console::promptFloat("Please enter the cost of the equipment in dollars: ");

		std::stringstream ss;
		ss << "Do you want to create a peice of Equipment with:\n"
			<< " - name = " << name << "\n"
			<< " - type = " << type << "\n"
			<< " - cost = $" << cost << "\n";

		if (Console::promptConfirm(ss.str()))
		{
			return Equipment(name, type, cost);
		}
		else
		{
			return {};
		}
	}

	List<Equipment> Equipment::promptEquipmentList()
	{
		List<Equipment> equipment = {};
		while (true)
		{
			List<String> commands = Console::promptCommands("Please enter a equipment command: ");
			if (commands.size() == 0)
			{
				continue;
			}
			else if (commands[0] == NEW_EQUIPMENT_COMMAND)
			{
				auto e = Equipment::promptCreateEquipment();
				if(e.has_value()) 
					equipment.push_back(e.value());
			}
			else if (commands[0] == END_COMMAND)
			{
				return equipment;
			}
			else if (commands[0] == CANCEL_COMMAND)
			{
				return {};
			}
			else if (commands[0] == REDO_COMMAND)
			{
				equipment = {};
			}
			else if (commands[0] == HELP_COMMAND)
			{
				Console::printHelpCommands("List of Equipment commands:", {
					{ NEW_EQUIPMENT_COMMAND, "Create a new Equipment in the list" },
					{ END_COMMAND, "Ends the creation of the list" },
					{ CANCEL_COMMAND, "Cancels the construction of the Equipment list" },
					{ REDO_COMMAND, "Clears the Equipment list so that you can reenter them" },
					{ HELP_COMMAND, "Prints out an array of command descriptions" },
				});
			}
		}
	}

	String Equipment::getDetails() const
	{
		return name + " [type = " + type + ", cost = $" + std::to_string(rentalCost) + "]";
	}

	String Equipment::formatEquipmentList(const List<Equipment>& equipment, String tab)
	{
		std::stringstream ss = {};

		String equipmentTab = tab;
		if (!equipmentTab.empty())
			equipmentTab.erase(0, 1);

		ss << equipmentTab << " - Equipment List:\n";
		for (const Equipment& e : equipment)
		{
			ss << tab + " - " << e.getDetails() << "\n";
		}

		return ss.str();
	}
}

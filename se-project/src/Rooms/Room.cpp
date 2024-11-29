#include "Room.h"
#include "Utils/Prompts.h"

namespace WEP
{
	Arc<Room> Room::promptSelectRoom()
	{
		while (true)
		{
			String name = Console::promptName("Please enter the name of the room: ");
			if (name == RomeRoom().getName())
			{
				return Arc<Room>(new RomeRoom());
			}
			else if (name == LasVegasRoom().getName())
			{
				return Arc<Room>(new LasVegasRoom());
			}
			else if (name == ParisRoom().getName())
			{
				return Arc<Room>(new ParisRoom());
			}
			else 
			{
				std::cout << "Unknown room name '" << name << "'; please try again\n";
			}
		}
	}
}

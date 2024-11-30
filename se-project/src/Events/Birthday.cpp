#include "Birthday.h"
#include "Utils/Prompts.h"
#include <sstream>
#include "Guest.h"

namespace WEP
{
	std::string Birthday::getDetails() const
	{
		std::stringstream ss;
		ss << this->getName() << " on " << this->getDate().toString() << "\n" 
			<< Guest::formatGuestList(this->getGuests()) 
			<< Activity::formatActivityList(this->getActivities()) 
			<< "\n";
		return ss.str();
	}

	Option<Arc<Event>> Birthday::promptCreateEvent(UUID businessId)
	{
		String name = Console::promptName("Enter the birthday girl/boys name: ");
		size_t age = Console::promptNumber("Please enter the age of the birthday boy/girl: ");
		Date date = Console::promptDate("Enter the party birthday date: ");
		List<Arc<Activity>> activities = Activity::promptCreateActivityList();
		List<Guest> guestList = Guest::promptCreateGuestList(activities);

		std::stringstream ss;
		ss << "Do you want to create a Wedding Event with:\n"
			<< " - name = " << name << "\n"
			<< " - age = " << age << "\n"
			<< " - date = " << date.toString() << "\n"
			<< Activity::formatActivityList(activities) << "\n"
			<< Guest::formatGuestList(guestList) << "\n";

		if (Console::promptConfirm(ss.str()))
		{
			return std::make_shared<Birthday>(name, age, date, activities, guestList, businessId);
		}
		else
		{
			return {};
		}

	}
}

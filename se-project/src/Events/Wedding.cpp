#include "Wedding.h"
#include "Utils/Prompts.h"
#include <sstream>

namespace WEP
{
	std::string Wedding::getDetails() const
	{
		std::stringstream ss;
		ss << this->getName() << " on " << this->getDate().toString() << "\n" 
			<< Guest::formatGuestList(this->getGuests())
			<< Activity::formatActivityList(this->getActivities())
			<< "\n";
		return ss.str();
	}

	Option<Arc<Event>> Wedding::promptCreateEvent(UUID businessId)
	{
		String partnerA = Console::promptName("Please enter partnerA name: ");
		String partnerB = Console::promptName("Please enter partnerB name: ");
		Date date = Console::promptDate("Please enter wedding date: ");
		List<Activity> activities = Activity::promptCreateActivityList();
		List<Guest> guestList = Guest::promptCreateGuestList(activities);

		std::stringstream ss;
		ss << "Do you want to create a Wedding Event with:\n"
			<< " - partnerA = " << partnerA << "\n"
			<< " - partnerB = " << partnerB << "\n"
			<< " - date = " << date.toString() << "\n"
			<< Activity::formatActivityList(activities) << "\n"
			<< Guest::formatGuestList(guestList) << "\n";

		if (Console::promptConfirm(ss.str()))
		{
			return std::make_shared<Wedding>(partnerA, partnerB, date, activities, guestList, businessId);
		}
		else
		{
			return {};
		}
	}
}

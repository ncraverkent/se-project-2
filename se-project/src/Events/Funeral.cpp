#include "Funeral.h"
#include "Utils/Prompts.h"
#include <sstream>
#include "Guest.h"

namespace WEP
{
	std::string Funeral::getDetails() const
	{
		std::stringstream ss;
		ss << this->getName() << " on " << this->getDate().toString() << "\n" 
			<< Guest::formatGuestList(this->getGuests())
			<< Activity::formatActivityList(this->getActivities())
			<< "\n";
		return ss.str();
	}

	Option<Arc<Event>> Funeral::promptCreateEvent(UUID businessId)
	{
		String name = Console::promptName("Please enter the deseased name: ");
		Date birthDate = Console::promptDate("Please enter their date of birth: ");
		Date deathDate = Console::promptDate("Please enter their date of death: ");
		Date date = Console::promptDate("Please enter the date of the funeral: ");
		List<Activity> activities = Activity::promptCreateActivityList();
		List<Guest> guestList = Guest::promptCreateGuestList(activities);

		std::stringstream ss;
		ss << "Do you want to create a Wedding Event with:\n"
			<< " - name = " << name << "\n"
			<< " - birth date = " << birthDate.toString() << "\n"
			<< " - death date = " << deathDate.toString() << "\n"
			<< " - funeral date = " << date.toString() << "\n"
			<< Activity::formatActivityList(activities) << "\n"
			<< Guest::formatGuestList(guestList) << "\n";

		if (Console::promptConfirm(ss.str()))
		{
			return std::make_shared<Funeral>(name, birthDate, deathDate, date, activities, guestList, businessId);
		}
		else
		{
			return {};
		}
	}
}

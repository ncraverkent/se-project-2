#include "Event.h"
#include <iostream>

#include "Wedding.h"
#include "Funeral.h"
#include "Birthday.h"

namespace WEP
{
    bool Event::addActivity(Activity activity)
    {
        return false;
    }

    float Event::getCost() const
    {
        return 0.0f;
    }

    void Event::confirmBooking() const
    {
    }

    Option<Arc<Event>> Event::promptCreateEvent(UUID businessId)
    {
        const char* WEDDING_NAME = "wedding";
        const char* BIRTHDAY_NAME = "birthday";
        const char* FUNERAL_NAME = "funeral";
        const char* CANCEL_COMMAND = "cancel";

        while (true)
        {
            std::cout << "Please enter what type of event you want: [wedding, birthday, funeral, cancel]\n";
            String eventName;
            std::cin >> eventName;
            if (eventName == WEDDING_NAME)
            {
                return Wedding::promptCreateEvent(businessId);
            }
            else if (eventName == BIRTHDAY_NAME)
            {
                return Birthday::promptCreateEvent(businessId);
            }
            else if (eventName == FUNERAL_NAME)
            {
                return Funeral::promptCreateEvent(businessId);
            }
            else if (eventName == CANCEL_COMMAND)
            {
                return {};
            }
            else
            {
                std::cout << "Uknown event name or command, please try again\n";
            }
        }
    }
}

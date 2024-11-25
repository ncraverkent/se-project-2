#include <iostream>
#include "Business.h"
#include "Events/Event.h"
#include "Defs.h"

using namespace WEP;

int main()
{
    String id = "fffffffffff";
    Option<Arc<Event>> event = Event::promptCreateEvent(id);
    if (event.has_value())
    {
        std::cout << event.value()->getDetails();
    }
    else
    {
        std::cout << "Did not create an event";
    }
}
#include "DisplayMannager.h"
#include "Utils/Prompts.h"

namespace WEP
{
	void DisplayMannager::run()
	{
        while (true)
        {
            auto commands = Console::promptCommands("Please enter a command: ");

            if (commands.size() == 0)
            {
                printError("Unknown command");
            }

            if (commands[0] == QUIT_COMMAND)
            {
                break;
            }
            else if (commands[0] == SIGN_IN_COMMAND)
            {
                runSignInCommand(commands);
            }
            else if (commands[0] == SIGN_OUT_COMMAND)
            {
                eventCenter.signOut();
            }
            else if (commands[0] == CREATE_COMMAND)
            {
                runCreateCommand(commands);
            }
            else if (commands[0] == PRINT_COMMAND)
            {
                runPrintCommand(commands);
            }
            else if (commands[0] == HELP_COMMAND)
            {
                printHelpCommandList();
            }
            else
            {
                std::cout << "Unknown command: `" << commands[0] << "`\n";
            }
        }
	}

	void DisplayMannager::runPrintCommand(const List<String>& commands)
	{
        if (commands.size() < 2)
        {
            std::cout << "`print` command must have an argument\n";
        }
        else if (commands[1] == PRINT_EVENTS_ARG)
        {
            auto events = eventCenter.getEvents();
            for (const auto& event : events)
            {
                std::cout << event->getDetails() << "\n";
            }
        }
        else if (commands[1] == PRINT_BUSINESSES_ARG)
        {
            auto businesses = eventCenter.getBusinesses();
            for (const auto& business : businesses)
            {
                std::cout << " - " << business->getName() << ": [" << business->getId() << "]\n";
            }
        }
        else if (commands[1] == PRINT_SIGN_IN_ARG)
        {
            const auto& id = eventCenter.getSignIn();
            if (id.has_value())
            {
                std::cout << "Signed in Business: " << eventCenter.getBusiness(*id).value()->getName() << "\n";
            }
            else
            {
                std::cout << "No business signed in\n";
            }
        }
        else
        {
            std::cout << "Unknown print command `" << commands[1] << "`\n";
        }
	}

	void DisplayMannager::runCreateCommand(const List<String>& commands)
	{
        if (commands.size() < 2)
        {
            std::cout << "`" << CREATE_COMMAND << "` must have a creation type argument\n";
            return;
        }

        if (commands[1] == CREATE_BUSINESS_ARG)
        {
            auto b = Business::promptUserNew();
            if (b.has_value())
            {
                bool succseeded = eventCenter.addBusiness(b.value());
                if (!succseeded)
                {
                    std::cout << "Error: buisness with given name already exists\n";
                }
            }
        }
        else if (commands[1] == CREATE_EVENT_ARG)
        {
            if (!eventCenter.getSignIn().has_value())
            {
                std::cout << "A business must be signed in to create an event\n";
            }

            Option<Arc<Event>> event = Event::promptCreateEvent(eventCenter.getSignIn().value());
            if (event.has_value())
            {
                eventCenter.scheduleEvent(event.value());
            }
        }
        else
        {
            std::cout << "Error: unknown argument `" << commands[1] << "`\n";
        }
	}

	void DisplayMannager::runSignInCommand(const List<String>& commands)
	{
        if (commands.size() < 2)
        {
            std::cout << "`" << SIGN_IN_COMMAND << "` must have a business name argument\n";
            return;
        }

        const String& name = commands[1];
        auto businesses = eventCenter.getBusinesses();
        auto it = std::find_if(businesses.begin(), businesses.end(), [&name](const Arc<Business>& b) {
            return b->getName() == name;
            });

        if (it == businesses.end())
        {
            std::cout << "No business registered with name '" << name << "'\n";
        }

        eventCenter.signIn(it->get()->getId()); // should return true anyways
        std::cout << "Signed into business: '" << name << "'\n";
	}

	void DisplayMannager::printError(const String& msg)
	{
        std::cout << "Error: '" << msg << "'\n";
	}

	void DisplayMannager::printHelpCommandList()
	{
        std::cout << "List of commands:\n";

        Console::printHelpCommands("List of commands:", {
            { HELP_COMMAND, "Prints a list of commands and what they do" },
            { SIGN_IN_COMMAND + " business_name", "Signs in a business" },
            { SIGN_OUT_COMMAND, "Signs out a business" },
            { PRINT_COMMAND + " " + PRINT_BUSINESSES_ARG, "Prints all the registered businesses" },
            { PRINT_COMMAND + " " + PRINT_EVENTS_ARG, "Prints all the created events" },
            { PRINT_COMMAND + " " + PRINT_SIGN_IN_ARG, "Prints the currently signed in business" },
            { CREATE_COMMAND + " " + CREATE_BUSINESS_ARG, "Creates/registers a new business" },
            { CREATE_COMMAND + " " + CREATE_EVENT_ARG, "Creates a new event. A business needs to be signed in to do this" }
        });

        std::cout << "\n\n";
	}
}
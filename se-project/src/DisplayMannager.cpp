#include "DisplayMannager.h"
#include "Utils/Prompts.h"
#include "Problem.h"

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
            else if (commands[0] == REPORT_COMMAND)
            {
                reportIssueCommand(commands);
            }
            else if (commands[0] == ASSIGN_COMMAND)
            {
                runAssignPersonnelCommand();
            }
            else
            {
                std::cout << "Unknown command: `" << commands[0] << "`\n";
            }

            std::cout << "\n";
        }
	}

	void DisplayMannager::runPrintCommand(const List<String>& commands)
	{
        if (commands.size() < 2)
        {
            std::cout << "`print` command must have an argument\n";
        }
        else if (commands[1] == PRINT_PERSONNEL_ARG)
        {
            for (const auto& personnel : eventCenter.getAllPersonnel())
            {
                std::cout << personnel->getDetails() << "\n";
            }
        }
        else if (commands[1] == PRINT_EVENTS_ARG)
        {
            if (commands.size() >= 3 && commands[2] == PRINT_EVENTS_IDS_ARG_ARG)
            {
                auto events = eventCenter.getEvents();
                for (const auto& event : events)
                {
                    if (commands.size() >= 4 && event->getBusinessId() != commands[3])
                        continue;

                    std::cout << event->getName() << ": [" << event->getId() << "]\n";
                }
            }
            else
            {
                auto events = eventCenter.getEvents();
                for (const auto& event : events)
                {
                    std::cout << event->getDetails() << "\n";
                }
            }
        }
        else if (commands[1] == PRINT_EVENT_ARG)
        {
            if (commands.size() < 3)
            {
                std::cout << "This command requires a event id argument\n";
                return;
            }

            auto event = eventCenter.getEvent(commands[2]);
            if (event.has_value())
            {
                std::cout << event.value()->getDetails() << "\n";
            }
            else
            {
                std::cout << "No event with id '" << commands[2] << "'\n";
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
                else
                {
                    std::cout << "Successfully created a new business!\n";
                }
            }
        }
        else if (commands[1] == CREATE_PERSONNEL_ARG)
        {
            auto p = Personnel::promptCreatePersonel();
            if (!eventCenter.addPersonnel(p))
            {
                std::cout << "Error: personnel already exists with the given name\n";
            }
            else
            {
                std::cout << "Successfully created a new personnel!\n";
            }
        }
        else if (commands[1] == CREATE_EVENT_ARG)
        {
            if (!eventCenter.getSignIn().has_value())
            {
                std::cout << "A business must be signed in to create an event\n";
                return;
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

    void DisplayMannager::runAssignPersonnelCommand()
    {
        String name = Console::promptName("Please enter the name of the personnel to assign: ");
        auto personnel = eventCenter.getPersonnel(name);
        if (personnel.has_value())
        {
            List<Arc<Activity>> activities = {};
            for (auto& event : eventCenter.getEvents())
            {
                for (auto& activity : event->getActivities())
                {
                    activities.push_back(activity);
                }
            }

            personnel.value()->promptAssignActivity(activities);
        }
        else
        {
            std::cout << "There is no registered personnel with name `" << name << "'\n";
            return;
        }
    }

    void DisplayMannager::reportIssueCommand(const List<String>& commands)
    {
        String name = Console::promptName("Please enter the name of the personnel to assign: ");
        auto personnel = eventCenter.getPersonnel(name);
        if (personnel.has_value())
        {
            String desc = Console::promptLine("Please enter the problem description: ");
            Date date = Console::promptDate("Please enter the date of the problem: ");
            
            Problem problem = Problem(desc, name, ProblemStatus::InProgress, date);
            personnel.value()->reportIssue(problem);
        }
        else
        {
            std::cout << "There is no registered personnel with name `" << name << "'\n";
            return;
        }
    }

	void DisplayMannager::printError(const String& msg)
	{
        std::cout << "Error: '" << msg << "'\n";
	}

	void DisplayMannager::printHelpCommandList()
	{
        Console::printHelpCommands("List of commands:", {
            { HELP_COMMAND, "Prints a list of commands and what they do" },
            { SIGN_IN_COMMAND + " business_name", "Signs in a business" },
            { SIGN_OUT_COMMAND, "Signs out a business" },
            { PRINT_COMMAND + " " + PRINT_BUSINESSES_ARG, "Prints all the registered businesses" },
            { PRINT_COMMAND + " " + PRINT_EVENTS_ARG, "Prints all the created events" },
            { PRINT_COMMAND + " " + PRINT_EVENTS_ARG + " " + PRINT_EVENTS_IDS_ARG_ARG + " ?(business id)", "Prints all events with just their names and ids, with an optional business id arg that will print out only the events with the given id"},
            { PRINT_COMMAND + " " + PRINT_SIGN_IN_ARG, "Prints the currently signed in business" },
            { PRINT_COMMAND + " " + PRINT_PERSONNEL_ARG, "Prints the list of all registered personnel" },
            { CREATE_COMMAND + " " + CREATE_BUSINESS_ARG, "Creates/registers a new business" },
            { CREATE_COMMAND + " " + CREATE_EVENT_ARG, "Creates a new event. A business needs to be signed in to do this" },
            { CREATE_COMMAND + " " + CREATE_PERSONNEL_ARG, "Creates a new personnel." },
            { REPORT_COMMAND, "Reports a problem" },
            { ASSIGN_COMMAND, "Assigns a personnel to a activity"}
        });

        std::cout << "\n\n";
	}
}
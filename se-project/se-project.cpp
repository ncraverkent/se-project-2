#include <iostream>
#include "Business.h"
#include "Events/Event.h"
#include "Utils/UUID.h"
#include "Defs.h"
#include "Utils/Prompts.h"
#include <sstream>
#include "WeddingEventCenter.h"

using namespace WEP;

const String QUIT_COMMAND = "quit";
const String SIGN_IN_COMMAND = "signin";
const String SIGN_OUT_COMMAND = "signout";

const String PRINT_SIGN_IN_COMMAND = "psignin";

const String CREATE_COMMAND = "create";
const String CREATE_BUSINESS_ARG = "business";
const String CREATE_EVENT_ARG = "event";

const String PRINT_COMMAND = "print";
const String PRINT_EVENTS_ARG = "events";
const String PRINT_BUSINESSES_ARG = "businesses";

const String HELP_COMMAND = "help";

/**
* @returns The list of whitespace seperated commands entered by the user
*/
static List<String> getCommands()
{
    String text = Console::promptLine("Please enter a command: ");
    std::istringstream iss(text);
    List<String> commands;

    String word;
    while (iss >> word)
        commands.push_back(word);

    return commands;
}

/**
* A simple helper function for generating command descriptions
*/
static void printHelpCommand(const char* name, const char* desc)
{
    std::cout << " - `" << name << "` --> \"" << desc << "\"\n";
}

int main()
{
    WeddingEventCenter eventCenter = {};

    while (true)
    {
        auto commands = getCommands();

        if (commands.size() == 0)
        {
            std::cout << "Unknown command\n";
        }

        if (commands[0] == QUIT_COMMAND)
        {
            break;
        }
        else if (commands[0] == SIGN_IN_COMMAND)
        {
            if (commands.size() < 2)
            {
                std::cout << "`" << SIGN_IN_COMMAND << "` must have a business name argument\n";
                continue;
            }

            const String& name = commands[1];
            auto businesses = eventCenter.getBusinesses();
            auto it = std::find_if(businesses.begin(), businesses.end(), [&name](const Arc<Business>& b) {
                return b->getName() == name;
            });

            if (it == businesses.end())
            {
                std::cout << "No business registered with name '" << name << "'\n";
                continue;
            }

            eventCenter.signIn(it->get()->getId()); // should return true anyways
            std::cout << "Signed into business: '" << name << "'\n";
        }
        else if (commands[0] == SIGN_OUT_COMMAND)
        {
            eventCenter.signOut();
        }
        else if (commands[0] == PRINT_SIGN_IN_COMMAND)
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
        else if (commands[0] == CREATE_COMMAND)
        {
            if (commands.size() < 2)
            {
                std::cout << "`" << CREATE_COMMAND << "` must have a creation type argument\n";
                continue;
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
                    continue;
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
        else if (commands[0] == PRINT_COMMAND)
        {
            if (commands.size() < 2)
            {
                std::cout << "`print` command must have an argument\n";
                continue;
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
            else
            {
                std::cout << "Unknown print command `" << commands[1] << "`\n";
            }
        }
        else if (commands[0] == HELP_COMMAND)
        {
            std::cout << "List of commands:\n";
            printHelpCommand(HELP_COMMAND.c_str(), "Prints a list of commands and what they do");
            printHelpCommand(SIGN_IN_COMMAND.c_str(), "Signs in a business, requires a second argument which is the name of the business");
            printHelpCommand(SIGN_OUT_COMMAND.c_str(), "Signs out the business");
            printHelpCommand(PRINT_SIGN_IN_COMMAND.c_str(), "Prints the name of the business that is signed in");
            std::cout << "Printing Commands:\n";
            printHelpCommand((PRINT_COMMAND + " " + PRINT_BUSINESSES_ARG).c_str(), "Prints all the business with there ids and names");
            printHelpCommand((PRINT_COMMAND + " " + PRINT_EVENTS_ARG).c_str(), "Prints all the events with there data");
            std::cout << "Creation Commands:\n";
            printHelpCommand((CREATE_COMMAND + " " + CREATE_BUSINESS_ARG).c_str(), "Creates a business");
            printHelpCommand((CREATE_COMMAND + " " + CREATE_EVENT_ARG).c_str(), "Creates a event");


            std::cout << "\n\n";
        }
        else
        {
            std::cout << "Unknown command: `" << commands[0] << "`\n";
        }
    }
}
#include "Prompts.h"
#include <sstream>

namespace WEP
{
    size_t Console::promptNumber(const String& msg)
    {
        return Console::prompt<size_t>(msg, "Error: not a number, please enter again.", []() {
            std::string num = {};
            std::cin >> num;
            size_t number = 0;
            
            try {
                // Try converting the string to size_t
                size_t number = std::stoul(num); // Converts string to unsigned long
                return Option<size_t>{number};  // Return the number wrapped in Option
            }
            catch (const std::invalid_argument&) {
                // Conversion failed due to invalid input
                std::cerr << "Invalid input: not a number." << std::endl;
            }
            catch (const std::out_of_range&) {
                // Conversion failed due to overflow
                std::cerr << "Invalid input: number out of range." << std::endl;
            }
        });
    }

    std::string Console::promptLine(const String& msg)
    {
        std::cout << msg << '\n';
        String line = "";
        if (std::cin.peek() == '\n') {
            std::cin.ignore();
        }
        std::getline(std::cin, line);
        return line;
    }

    std::string Console::promptName(const String& msg)
    {
        return Console::prompt<String>(msg, "That is an invalid name, please try again.", []() {
            String line;

            if (std::cin.peek() == '\n') {
                std::cin.ignore();
            }

            std::getline(std::cin, line);
            if (isName(line))
            {
                return Option<String> { line };
            }
            else
            {
                return Option<String> { };
            }
        });
    }

    Date Console::promptDate(const String& msg)
    {
        return Console::prompt<Date>(msg + " (MM-DD-YYYY): ", "Invalid date, please try again.", []() {
            String text;
            std::cin >> text;
            return Date::fromString(text);
        });
    }

    bool Console::promptConfirm(String message)
    {
        std::cout << message << " [y/n]: ";
        char c;
        std::cin >> c;
        return c == 'y' || c == 'n';
    }

    List<String> Console::promptCommands(String message)
    {
        String text = Console::promptLine(message);
        std::istringstream iss(text);
        List<String> commands;

        String word;
        while (iss >> word)
            commands.push_back(word);

        return commands;
    }

    void Console::printHelpCommands(const String& message, const List<Pair<String, String>>& commands)
    {
        std::cout << message << "\n";
        for (const auto& [command, desc] : commands)
        {
            std::cout << " - `" << command << "` --> " << desc << "\n";
        }
    }

    bool isName(const String& str)
    {
        for (auto c : str)
        {
            if (!(std::isalpha(c) || std::isdigit(c) || std::isspace(c) || c == '\'' || c == '.'))
                return false;
        }

        return true;
    }
}


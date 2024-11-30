#include "Personel.h"
#include <iostream>
#include <sstream>
#include <limits>
#include "Defs.h"

namespace WEP
{
    Personnel::Personnel(const std::string& name)
        : name(name), assignedActivity({}) {
    }

    void Personnel::reportIssue(Problem issue)
    {
        reportedIssues.push_back(issue);
        std::cout << "Issue reported by " << name << ": " << issue.getDescription() << "\n";
    }

    void Personnel::assignActivity(Arc<Activity> activity)
    {
        assignedActivity = std::move(activity);
        std::cout << "Assigned activity \"" << assignedActivity.value()->getName() << "\" to " << name << ".\n";
    }

    std::string Personnel::getDetails() const
    {
        std::stringstream details;
        details << "Personnel Name: " << name << "\n";

        if (assignedActivity)
            details << " - Assigned Activity: " << assignedActivity.value()->getName() << "\n";
        else
            details << " - Assigned Activity: None\n";

        details << " - Reported Issues:\n";
        for (const auto& issue : reportedIssues)
        {
            details << "\t - " << issue.getDescription() << "\n";
        }
        return details.str();
    }

    Personnel Personnel::promptCreatePersonel()
    {
        std::string name;
        std::cout << "Enter personnel name: ";
        std::getline(std::cin >> std::ws, name);  // std::ws skips leading whitespace
        return Personnel(name);
    }

    void Personnel::promptAssignActivity(List<Arc<Activity>>& availableActivities)
    {
        if (availableActivities.empty())
        {
            std::cout << "No activities available to assign.\n";
            return;
        }

        std::cout << "Available Activities:\n";
        for (size_t i = 0; i < availableActivities.size(); ++i)
        {
            std::cout << i + 1 << ". " << availableActivities[i]->getName() << "\n";
        }

        while (true)
        {
            int choice;
            std::cout << "Enter the number of the activity to assign: ";

            if (!(std::cin >> choice))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            if (choice > 0 && choice <= static_cast<int>(availableActivities.size()))
            {
                size_t index = static_cast<size_t>(choice - 1);
                assignActivity(std::move(availableActivities[index]));
                availableActivities.erase(availableActivities.begin() + index);
                break;
            }
            else
            {
                std::cout << "Invalid selection. Please try again.\n";
            }
        }
    }
}




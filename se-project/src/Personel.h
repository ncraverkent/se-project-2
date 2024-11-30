#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Activity.h"
#include "Problem.h"

namespace WEP
{
    /**
    * @brief The Personel class
    * A class that represents the WEP's personel who oversee activites
    */
    class Personnel
    {
    public:
        // Constructor
        explicit Personnel(const std::string& name);

        
        /**
        * @returns The name of this Personnel
        */
        const std::string& getName() const { return name; }

        /**
        * @returns The reference of the assigned activity that this personell is overseeing, if they are overseeing any
        */
        Option<const Arc<Activity>> getAssignedActivity() const {
            return assignedActivity.has_value() ? assignedActivity : Option<Arc<Activity>> {};
        }

        /**
        * Reports an issue
        */
        void reportIssue(Problem issue);

        /**
        * @returns A formatted string of the data of this personnel
        */
        std::string getDetails() const;

        /**
        * Prompts the user to create a new personnel
        */
        static Personnel promptCreatePersonel();

        /*
        * Promptes the user to be assigned an activity
        */
        void promptAssignActivity(List<Arc<Activity>>& availableActivities);

    private:

        void assignActivity(Arc<Activity> activity);

        String name;
        Option<Arc<Activity>> assignedActivity;
        std::vector<Problem> reportedIssues;

    };
}
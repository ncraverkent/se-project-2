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

        // Getters
        const std::string& getName() const { return name; }
        Option<const Arc<Activity>> getAssignedActivity() const {
            return assignedActivity.has_value() ? assignedActivity : Option<Arc<Activity>> {};
        }

        // Core functionality
        void reportIssue(Problem issue);
        std::string getDetails() const;

        // Static 
        static Personnel promptCreatePersonel();

        // Activity assignment
        void promptAssignActivity(List<Arc<Activity>>& availableActivities);

    private:

        void assignActivity(Arc<Activity> activity);

        String name;
        Option<Arc<Activity>> assignedActivity;
        std::vector<Problem> reportedIssues;

    };
}
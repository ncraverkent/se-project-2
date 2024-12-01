//Cost.h
#pragma once
#include <string>
#include <sstream>
#include <map>
#include <iomanip>

namespace WEP
{
    /**
    * Manages and formats costs for various activities and resources.
    */
    class Cost
    {
    public:
        /**
        * Default constructor initializes total cost to zero.
        */
        Cost() : totalCost(0.0f) {}

        /**
        * Add a new cost category or update an existing one.
        * @param category The name of the cost category.
        * @param amount The amount to add or update for the category.
        */
        void addCost(const std::string& category, float amount);

        /**
        * Remove a cost category.
        * @param category The name of the cost category to remove.
        */
        void removeCost(const std::string& category);

        /**
        * Get the total cost.
        * @returns The total cost across all categories.
        */
        float getTotalCost() const;

        /**
        * Format the cost breakdown as a string.
        * @returns A string representation of the cost breakdown.
        */
        std::string formatCostBreakdown() const;

        /**
        * Reset all costs.
        */
        void reset();

    private:
        std::map<std::string, float> costBreakdown; // Map to store category-wise costs
        float totalCost;                            // Cached total cost

        /**
        * Recalculate the total cost.
        */
        void recalculateTotal();
    };
}



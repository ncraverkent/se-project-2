#include "Cost.h"

namespace WEP
{
    void Cost::addCost(const std::string& category, float amount)
    {
        costBreakdown[category] = amount; // Add or update the category cost
        recalculateTotal();
    }

    void Cost::removeCost(const std::string& category)
    {
        costBreakdown.erase(category); // Remove the category
        recalculateTotal();
    }

    float Cost::getTotalCost() const
    {
        return totalCost;
    }

    std::string Cost::formatCostBreakdown() const
    {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        oss << "Cost Breakdown:\n";

        for (const auto& [category, amount] : costBreakdown)
        {
            oss << " - " << category << ": $" << amount << "\n";
        }

        oss << "Total: $" << totalCost << "\n";
        return oss.str();
    }

    void Cost::reset()
    {
        costBreakdown.clear();
        totalCost = 0.0f;
    }

    void Cost::recalculateTotal()
    {
        totalCost = 0.0f;
        for (const auto& [_, amount] : costBreakdown)
        {
            totalCost += amount;
        }
    }
}
#include "Date.h"
#include "Defs.h"
#include <string>
#include <sstream>
#include <iomanip>


static bool isLeapYear(size_t year);
static bool parseDate(const std::string& dateStr, size_t& year, size_t& month, size_t& day);
static bool isValidDate(size_t year, size_t month, size_t day);

namespace WEP
{
	bool Date::operator==(const Date& other) const
	{
        return this->month == other.month && this->day == other.day && this->year == other.year;
	}

	bool Date::operator!=(const Date& other) const
	{
        return !(*this == other);
	}

	Option<Date> Date::fromString(const String& str)
	{
        size_t year, month_num, day = 0;
        if (parseDate(str, year, month_num, day)) 
        {
            auto month = getMonthFromNumber(month_num);
            if (!month.has_value()) return {};

            return Date(day, month.value(), year);
        }

        return {};
	}

	String Date::toString() const
	{
        std::stringstream ss = {};
        ss << static_cast<size_t>(this->month) << "-" << this->day << "-" << this->year;
        return ss.str();
	}

    Option<Month> getMonthFromNumber(size_t n)
    {
        if (n > 0 && n < 13)
        {
            return static_cast<Month>(n);
        }

        return {};
    }
}

static bool isLeapYear(size_t year) 
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static bool isValidDate(size_t year, size_t month, size_t day) 
{
    if (month < 1 || month > 12 || day < 1) {
        return false;
    }

    std::vector<size_t> daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (isLeapYear(year)) {
        daysInMonth[1] = 29; // Adjust for February in a leap year
    }

    return day <= daysInMonth[month - 1];
}

static bool parseDate(const std::string& dateStr, size_t& year, size_t& month, size_t& day) 
{
    std::istringstream iss(dateStr);
    char delimiter1, delimiter2;

    // Extract components in MM-DD-YYYY format
    if (!(iss >> month >> delimiter1 >> day >> delimiter2 >> year)) 
    {
        return false;
    }

    // Validate format
    if (delimiter1 != '-' || delimiter2 != '-') 
    {
        return false;
    }

    // Validate date values
    return isValidDate(year, month, day);
}

#include "TimeRange.h"
#include <sstream>
#include <iomanip>

namespace WEP
{
	Option<Time> Time::fromString(const String& str)
	{
		u32 h, m = 0;
		char sep = ' ';
		std::istringstream stream(str);
		if (stream >> h >> sep >> m && sep == ':' && stream.eof() &&
			h >= 0 && h < 24 && m >= 0 && m < 60) {
			Time time = Time(h, m);
			return { time };
		}
		return {};
	}

	bool Time::isEarlierThan(const Time& other) const
	{
		return hour < other.hour || (hour == other.hour && minute < other.minute);
	}

	bool Time::isLaterThan(const Time& other) const
	{
		return !isEarlierThan(other) && *this != other;
	}

	String Time::toString() const
	{
		std::ostringstream stream;
		stream << std::setw(2) << std::setfill('0') << hour << ":"
			<< std::setw(2) << std::setfill('0') << minute;
		return stream.str();
	}

	bool Time::operator==(const Time& other) const
	{
		return hour == other.hour && minute == other.minute;
	}

	bool Time::operator!=(const Time& other) const
	{
		return !(*this == other);
	}

	bool TimeRange::overlaps(const TimeRange& other) const
	{
		return !(this->end.isEarlierThan(other.start) || this->start.isLaterThan(other.end));
	}

	bool TimeRange::operator==(const TimeRange& other) const
	{
		return start == other.start && end == other.end;
	}

	bool TimeRange::operator!=(const TimeRange& other) const
	{
		return false;
	}

	String TimeRange::toString() const
	{
		return start.toString() + "-" + end.toString();
	}

	Option<TimeRange> TimeRange::fromString(const std::string& str)
	{
		size_t dashPos = str.find('-');
		if (dashPos == std::string::npos) {
			return {};
		}

		std::string startStr = str.substr(0, dashPos);
		std::string endStr = str.substr(dashPos + 1);

		auto start = Time::fromString(startStr);
		auto end = Time::fromString(endStr);

		if (!start.has_value() || !end.has_value()) return {};

		if (!start.value().isEarlierThan(end.value())) {
			return {};
		}

		return TimeRange(start.value(), end.value());
	}
}
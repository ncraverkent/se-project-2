#include "WeddingEventCenter.h"

namespace WEP
{
	void WeddingEventCenter::signOut()
	{
		this->signedInId = {};
	}

	bool WeddingEventCenter::signIn(const UUID& uuid)
	{
		if (businesses.find(uuid) != businesses.end())
		{
			this->signedInId = uuid;
			return true;
		}

		return false;
	}

	bool WeddingEventCenter::scheduleEvent(Arc<Event>& event)
	{
		size_t eventDayCount = 0;
		auto events = getEvents();
		for (const auto& e : events)
		{
			if (e->getDate() == event->getDate())
			{
				eventDayCount++;
			}
		}

		if (eventDayCount >= WeddingEventCenter::MAX_PARALLEL_EVENTS)
		{
			return false;
		}
		else
		{
			this->events.insert({ event->getId(), event });
		}
	}

	List<Arc<Event>> WeddingEventCenter::getEvents()
	{
		List<Arc<Event>> events = {};
		for (auto& event : this->events)
			events.push_back(event.second);

		return events;
	}

	Option<Arc<Event>> WeddingEventCenter::getEvent(const UUID& uuid)
	{
		auto it = this->events.find(uuid);
		if (it != this->events.end())
		{
			return { it->second };
		}
		else
		{
			return {};
		}
	}

	List<Arc<Business>> WeddingEventCenter::getBusinesses()
	{
		List<Arc<Business>> bs = {};
		for (auto& b : this->businesses)
			bs.push_back(b.second);

		return bs;
	}

	Option<Arc<Business>> WeddingEventCenter::getBusiness(const UUID& uuid)
	{
		auto it = this->businesses.find(uuid);
		if (it != this->businesses.end())
		{
			return { it->second };
		}
		else
		{
			return {};
		}
	}

	bool WeddingEventCenter::addBusiness(Business business)
	{
		const auto& name = business.getName();
		auto bs = getBusinesses();
		if (std::find_if(bs.begin(), bs.end(), [&name](const Arc<Business>& b) { return b->getName() == name; }) == bs.end())
		{
			Arc<Business> b = std::make_shared<Business>(business);
			UUID id = b->getId();
			businesses.insert({ id, b });
			return true;
		}

		return false;
	}
}

#pragma once
#include <string>
#include <vector>
#include "Events/Event.h"
#include "Utils/UUID.h"
#include "Business.h"
#include "Personel.h"

namespace WEP
{
	/**
	* The primary class for planning events
	*/
	class WeddingEventCenter
	{
	public:
		WeddingEventCenter() = default;

		/*
		* Tries to scheduel an event
		* @returns false if the event was failed to be scheduled
		* @param event The event to be scheduled
		*/
		bool scheduleEvent(Arc<Event>& event);
		/*
		* Returns the list of events that are currently scheduled
		*/
		List<Arc<Event>> getEvents();

		/**
		* @returns The event associated with its UUID
		*/
		Option<Arc<Event>> getEvent(const UUID& uuid);

		/**
		* @returns all registered businesses in this WeddingEventCenter
		*/
		List<Arc<Business>> getBusinesses();

		/**
		* @returns The business associated with its UUID
		*/
		Option<Arc<Business>> getBusiness(const UUID& uuid);

		/*
		* Adds a Business to the WeddingEventCenter
		* @returns True if the business was successfully added
		*/
		bool addBusiness(Business business);

		/*
		* Adds a Business to the WeddingEventCenter
		* @returns True if the Personnel was successfully added
		*/
		bool addPersonnel(Personnel personnel);

		/*
		* @returns The created Personnel with the given name
		*/
		Option<Arc<Personnel>> getPersonnel(const String& name);
		
		List<Arc<Personnel>> getAllPersonnel();

		/**
		* Signs out the current business
		* @todo this will change to be other things, like guests etc
		*/
		void signOut();

		/**
		* Signs in a current business
		* @returns If a business does not exist with the given UUID
		* @todo this will change to be other things, like guests etc
		*/
		bool signIn(const UUID& uuid);

		/**
		* @returns The currently signed in business, or invalid if there is no business signed in
		* @todo this will change to be other things, like guests etc
		*/
		const Option<UUID>& getSignIn() const { return this->signedInId; }
			
	private:
		std::string name;

		Option<UUID> signedInId;
		Map<UUID, Arc<Business>> businesses;
		Map<UUID, Arc<Event>> events;
		Map<String, Arc<Personnel>> personnel;

		static const int MAX_PARALLEL_EVENTS = 3;
	};
}

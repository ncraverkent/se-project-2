#pragma once
#include <string>
#include <vector>
#include "Utils/TimeRange.h"
#include "Rooms/Room.h"
#include "Equipment.h"
#include "Utils/UUID.h"

namespace WEP
{
	/**
	* @breif An activity for an event
	*/
	class Activity
	{
	public:
		/**
		* Constructs an activity
		* @param name The name of the activity
		* @param time the range of time that the activity covers
		* @param room The room that the activity is held in. It MUST live as long as this Activity
		* @param registrationCost the cost of registration for this activity
		* @param equipment All of the different equipment required for the activity
		*/
		Activity(std::string name, TimeRange time, Arc<Room> room, float registrationCost, std::vector<Equipment> equipment) :
			name(name), time(time), room(room), registrationCost(registrationCost), 
			equipment(equipment), id(generateUUID())
		{}

		/*
		* @returns The name of this activity
		*/
		const std::string& getName() const { return this->name; }
		/*
		* @returns the time range of this activity
		*/
		const TimeRange& getTime() const { return this->time; }
		/*
		* @returns the room of this activity
		*/
		const Room& getRoom() const { return *this->room; }

		const UUID& getId() const { return this->id; }

		/*
		* @returns the registration cost of this activity 
		*/
		float getRegistrationCost() const { return this->registrationCost; }

		/*
		* @returns The equipment for this activity
		*/
		const std::vector<Equipment>& getEquipment() const { return this->equipment; }

		/**
		* Prompts the user to create an activity
		*/
		static Option<Activity> promptCreateActivity();

		/**
		* Prompts the user to create a list of activities
		*/
		static List<Activity> promptCreateActivityList();

		static String formatActivityList(const List<Activity>& activites);

	private:
		std::string name;
		UUID id;
		TimeRange time;
		Arc<Room> room;
		float registrationCost;
		std::vector<Equipment> equipment;
	};
}
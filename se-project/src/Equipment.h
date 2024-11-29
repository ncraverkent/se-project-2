#pragma once
#include<string>
#include "Defs.h"

namespace WEP
{
	/**
	* A peice of equipment required for an activity
	*/
	class Equipment
	{
	public:

		/**
		* Constructor for the Equipment class
		*/
		Equipment(String name, String type, float cost) : name(name), type(type), rentalCost(cost) {}

		/**
		* @returns The name of this equipment
		*/
		const String& getName() const { return this->name; }
		/**
		* @returns The type of this equipment
		*/
		const String& getType() const { return this->type; }

		/**
		* @returns The cost of this equipment
		*/
		float getCost() const { return this->rentalCost; }

		/**
		* Prompts the user to create a peice of equipment that would be used for an activity
		*/
		static Option<Equipment> promptCreateEquipment();

		/**
		* Prompts the user to create a list of equipment
		*/
		static List<Equipment> promptEquipmentList();

		/**
		* Formats the data of the event
		* @returns The formatted string for the event
		*/
		String getDetails() const;

		/*
		* Formats the equipment list
		*/
		static String formatEquipmentList(const List<Equipment>& equipment, String tab = "\t");

	private:
		std::string name;
		std::string type;
		float rentalCost;
	};
}
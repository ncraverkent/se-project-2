#pragma once
#include<string>

namespace WEP
{
	/**
	* A peice of equipment required for an activity
	*/
	class Equipment
	{
	public:
		/**
		* Logs a request for equipment
		*/
		void requestEquipment();
		/**
		* @returns The name of this equipment
		*/
		const std::string& getName() const { return this->name; }
		/**
		* @returns The type of this equipment
		*/
		const std::string& getType() const { return this->type; 
		/**
		* @returns The cost of this equipment
		*/
		}
		float getCost() const { return this->rentalCost; }

	private:
		std::string name;
		std::string type;
		float rentalCost;
	};
}
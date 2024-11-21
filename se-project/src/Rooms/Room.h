#pragma once

namespace WEP
{
	/**
	* @breif The base class for all the differen types of rooms
	*/
	struct Room
	{
		/**
		* A virtual function for getting the room name
		*/
		virtual const char* getName() const = 0;
		/**
		* A virtual function for getting the room capacity
		*/
		virtual unsigned int getCapacity() const = 0;
		/**
		* A virtual function for getting the room cost
		* @note This is cost per hour
		*/
		virtual float getCost() const = 0;
	};

	struct ParisRoom : public Room
	{
		/**
		* @returns the name of the Paris Room
		* @todo implement
		*/
		const char* getName() const override;
		/**
		* @returns the capacity of the Paris Room
		* @todo implement
		*/
		unsigned int getCapacity() const override;
		/**
		* @returns the cost of the Paris room per hour
		* @todo implement
		*/
		float getCost() const override;
	};

	struct RomeRoom : public Room
	{
		/**
		* @returns the name of the Rome Room
		* @todo implement
		*/
		const char* getName() const override;
		/**
		* @returns the capacity of the Rome Room
		* @todo implement
		*/
		unsigned int getCapacity() const override;
		/**
		* @returns the cost of the Rome Room per hour
		* @todo implement
		*/
		float getCost() const override;
	};

	struct LasVegasRoom : public Room
	{
		/**
		* @returns the name of the Las Vegas Room
		* @todo implement
		*/
		const char* getName() const override;
		/**
		* @returns the capacity of the Las Vegas Room
		* @todo implement
		*/
		unsigned int getCapacity() const override;
		/**
		* @returns the cost of the Las Vegas Room per hour
		* @todo implement
		*/
		float getCost() const override;
	};
}


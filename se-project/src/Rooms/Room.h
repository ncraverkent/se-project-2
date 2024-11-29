#pragma once
#include <string>
#include <iostream>
#include "Defs.h"

namespace WEP
{
    /**
    * Base class for all rooms
    */
    class Room
    {
    private:
        std::string name; // room name
        float costPerHour; // room cost

    public:
        Room(std::string name, float costPerHour)
        {
            this->name = name;
            this->costPerHour = costPerHour;
        }

        /*
        * @returns the name of the room
        */
        std::string getName() const
        {
            return name;
        }

        float getCost() const { return costPerHour; }

        /**
        * @returns The capacity of the derived room
        */
        virtual size_t getCapacity() const = 0;
        /**
        * @returns If the derived room class has pool access
        */
        virtual bool hasPoolAccess() const = 0;

        static Arc<Room> promptSelectRoom();
    };

    class RomeRoom : public Room
    {
    public:
        RomeRoom() : Room("Rome Room", 300.0) {}
        bool hasPoolAccess() const override
        {
            return false;
        }

        size_t getCapacity() const override
        {
            return 100;
        }
    };

    /**
    * Paris room class
    */
    class ParisRoom : public Room
    {
    public:
        /**
        * initialize paris room with values
        */
        ParisRoom() : Room("Paris Room ", 400.0) {}


        bool hasPoolAccess() const override
        {
            return false;
        }

        size_t getCapacity() const override
        {
            return 200;
        }
    };

    /**
    * Las Vegas room class
    */
    class LasVegasRoom : public Room
    {
    public:
        /**
        * initialize Las Vegas Room with values
        */
        LasVegasRoom() : Room("Las Vegas Room ", 500.0) {}

        bool hasPoolAccess() const
        {
            return true;
        }

        size_t getCapacity() const override
        {
            return 400;
        }
    };
}

#pragma once
#include "Defs.h"

namespace WEP
{
	/**
	* A typedef for the UUID type, which is just a string in this case
	*/
	using UUID = String;

	/**
	* @breif Generates a Universily Unique IDentifier
	* @returns A universily unique identifier
	*/
	UUID generateUUID();
}
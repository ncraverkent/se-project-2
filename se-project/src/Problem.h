#pragma once
#include <string>
#include "Utils/Date.h"

namespace WEP
{
	/**
	* @enum ProblemStatus
	* The status of a given problem
	*/
	enum class ProblemStatus
	{
		Unknown,
		InProgress,
		Resolved,
	};

	/**
	* @breif A problem that has arizen during an activity of an event
	* These are typically Logged by personel who oversee an activity, and will be logged to the Problems section of the logs
	*/
	class Problem
	{
	public:
		/**
		* @param desc The description of the problem
		* @param name The name of personel who logged this problem
		* @param status The current status of the problem
		* @param timestamp The date that this problem took place
		*/
		Problem(std::string desc, std::string name, ProblemStatus status, Date timestamp) :
			description(desc), personelReportedName(name), status(status), timestamp(timestamp) {}
		/**
		* @returns The description of this problem
		*/
		const std::string& getDescription() const { return this->description; }
		/**
		* @returns The name of the personel who logged this problem
		*/
		const std::string& getPersonelName() const { return this->personelReportedName; }
		/**
		* @returns The status of this problem
		*/
		ProblemStatus getStatus() const { return this->status; }
		/**
		* @returns Updates the status of this problem
		*/
		void setStatus(ProblemStatus status) { this->status = status; }
		/**
		* @returns The date that this problem occured
		*/
		const Date& getTimestamp() const { return this->timestamp; }
	
	private:
		String description;
		String personelReportedName;
		ProblemStatus status;
		Date timestamp;
	};
}
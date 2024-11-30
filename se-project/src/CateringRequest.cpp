#include "CateringRequest.h"
#include "Utils/Prompts.h"
#include <sstream>

namespace WEP
{
	String CateringRequest::getDetails() const
	{
		return cateringCompany + " [$" + std::to_string(cateringCost) + "]";
	}

	Option<CateringRequest> CateringRequest::promptCreateCateringRequest()
	{
		if (!Console::promptConfirm("Do you wish to create a catering request?"))
			return {};

		String cateringCompany = Console::promptName("Please enter the catering company's name: ");
		u32 guestCount = Console::promptNumber("Please enter the expected number of guests: ");
		float cost = Console::promptFloat("Please enter the aproximate cost of catering in dollars: ");

		std::stringstream ss;
		ss << "Do you want to create a Catering Request with:\n"
			<< " - company name = " << cateringCompany << "\n"
			<< " - guest count = " << guestCount << "\n"
			<< " - cost = $" << cost << "\n";

		if (Console::promptConfirm(ss.str()))
		{
			return CateringRequest(cateringCompany, guestCount, cost);
		}
		else
		{
			return {};
		}
	}
}

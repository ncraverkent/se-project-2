#pragma once
#include "WeddingEventCenter.h"

namespace WEP
{
	/**
	* Manages the current display of the application, and is the main driver
	*/
	class DisplayMannager
	{
	public:
		const String QUIT_COMMAND = "quit";
		const String SIGN_IN_COMMAND = "signin";
		const String SIGN_OUT_COMMAND = "signout";

		const String CREATE_COMMAND = "create";
		const String CREATE_BUSINESS_ARG = "business";
		const String CREATE_EVENT_ARG = "event";
		const String CREATE_PERSONNEL_ARG = "personnel";

		const String PRINT_COMMAND = "print";
		const String PRINT_EVENTS_ARG = "events";
		const String PRINT_EVENT_ARG = "event";
		const String PRINT_BUSINESSES_ARG = "businesses";
		const String PRINT_SIGN_IN_ARG = "signin";
		const String PRINT_EVENTS_IDS_ARG_ARG = "ids";
		const String PRINT_PERSONNEL_ARG = "personnel";
		const String PRINT_ISSUES_ARG = "issues";
		const String PRINT_COST_ARG = "cost";

		const String ASSIGN_COMMAND = "assign";
		const String REPORT_COMMAND = "report";

		const String HELP_COMMAND = "help";
	public:
		DisplayMannager(WeddingEventCenter eventCenter) : eventCenter(eventCenter) {}
		void run();

	private:
		void runPrintCommand(const List<String>& commands);
		void runCreateCommand(const List<String>& commands);
		void runSignInCommand(const List<String>& commands);
		void runAssignPersonnelCommand();
		void reportIssueCommand(const List<String>& commands);
		void printError(const String& msg);
		void printHelpCommandList();

	private:
		WeddingEventCenter eventCenter;
	};
}
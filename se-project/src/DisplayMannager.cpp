#include "DisplayMannager.h"
#include "Utils/Prompts.h"

namespace WEP
{
	void DisplayMannager::run()
	{
		while (true)
		{

		}
	}

	bool DisplayMannager::runPrintCommand(const List<String>& commands)
	{
		return false;
	}

	bool DisplayMannager::runCreateCommand(const List<String>& commands)
	{
		return false;
	}

	bool DisplayMannager::runSignInCommand(const List<String>& commands)
	{
		return false;
	}
	 
	bool DisplayMannager::runSignOutCommand(const List<String>& commands)
	{
		return false;
	}

	void DisplayMannager::printError(const String& msg)
	{
	}

	void DisplayMannager::printHelpCommandList()
	{
	}
}
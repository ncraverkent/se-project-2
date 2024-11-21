#pragma once

namespace DisplayMannager
{
	/**
	* @enum AppState
	* The current state of the application
	*/
	enum AppState
	{
		Defualt
	};

	/**
	* Manages the current display of the application, and is the main driver
	*/
	class DisplayMannager
	{
	public:
		/**
		* Gets the input from the user
		*/
		void getUserInput();
		/*
		* Displays the output to visualize
		*/
		void displayOutput();

		/**
		* Requests what type of event the user wants to make
		*/
		void requestEventType();
		/**
		* Displays input for the Wedding event
		*/
		void createWeddingEvent();
		/**
		* Displays input for the Birthday event
		*/
		void createBirthdayEvent();
		/**
		* Displays input for the Funeral event
		*/
		void createFuneralEvent();

		/**
		* Displays input for creating an activity
		*/
		void createActivity();

		/**
		* Displays sign in for a personel
		*/
		void signInPersonel();
		/**
		* After a personel signs in shows input for displaying an issue
		*/
		void reportIssue();
	private:
		AppState state;
	};
}
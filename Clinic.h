#include "Queue.h"

class Clinic {
	private:
		Queue patients;
		//Stores the name of the clinic, used in printing.
		string name;
		//Stores the log of transactions for this clinic, which is emptied to the tranasction file at the end of the day.
		stringstream transactions;
	public:
		Clinic(string inName) : name(inName) {};
		/*
			PRE- Takes no arguments.
			POST- Prints the menu of the clinic.
		*/
		void printMenu();
		/*
			PRE- Controls when the menu is output and handles the user input.
			POST- Calls the appropraite functions based on user input.
		*/
		void getChoice();
		/*
			PRE- Takes in the critical status of the patient. Allows the user to enter patients info.
			POST- Creates a new patient and uses the insert function of Queue to place them in the queue.
		*/
		void addNewPatient(bool crit);
		/*
			PRE- Takes in a patient to be added to the queue.
			POST- Adds a patient to the end of the queue.
		*/
		void insertPatient(const Patient& newPat);
		/*
			PRE- Takes in no arguments, checks if the queue is empty.
			POST- Removes the patient at the front of the queue.
		*/
		void operate();
		/*
			PRE- Takes in no arguments, prompts the user for a SSN of a patient.
			POST- Removes the patient with the SSN, if found.
		*/
		void cancelPatient();
		/*
			PRE- Takes in the file storing the lefover patients, file containing the record of transactions, and the abbreviation of the clinic name.
			POST- Adds the remaing patients to the patient log and feeds the transaction stream to the transaction file.
		*/
		void endDay(ostream& patientFile, ostream& transFile, string abbrev);
		/*
			PRE- Takes in no arguments.
			POST- Ouputs the queue in order.
		*/
		void printQueue();
};

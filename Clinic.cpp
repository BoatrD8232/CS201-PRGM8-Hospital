#include "Clinic.h"

void Clinic::printMenu() {
	cout << "Welcome to the " << name << " Clinic" << endl;
	cout << "1: - Add Patient" << endl;
	cout << "2: - Add Critical Patient" << endl;
	cout << "3: - Take out Patient for Operation" << endl;
	cout << "4: - Cancel Patient" << endl;
	cout << "5: - List Patients in Queue" << endl;
	cout << "6: - Change Department or Exit" << endl;
	cout << "Enter your Choice ";
}

void Clinic::getChoice() {
	char choice = '1';
	while (choice != '6') {
		printMenu();
		cin >> choice;
		if (choice == '1') {
			//addNewPatient handles both regular and critical patients. Behavior is based on the bool passed to the function, true for critical patients.
			addNewPatient(false);
		}
		else if (choice == '2') {
			addNewPatient(true);
		}
		else if (choice == '3') {
			operate();
		}
		else if (choice == '4') {
			cancelPatient();
		}
		else if (choice == '5') {
			patients.print();
		}
		else if (choice != '6') {
			cout << "Invalid choice, choose again" << endl;
		}
	}
}

void Clinic::addNewPatient(bool crit) {
	//The data for the patient, output stores the formatted output which cleans up the ouput section as it is output twice.
	string fName, lName, inSSN, output = "";
	int SSN;
	//Stores if a valid SSN has been entered.
	bool isValidInput = false;
	cout << "Enter patient's first name: ";
	cin >> fName;
	cout << "\nEnter patient's last name: ";
	cin >> lName;
	cout << endl;
	//loops until the entered SSN is valid.
	while (!isValidInput) {
		cout << "Enter patient's social security number: ";
		cin >> inSSN;
		cout << endl;
		if (inSSN.length() == 0) { 
			cout << "Canceled" << endl;
			return; 
		}
		try {
			SSN = stoi(inSSN);
			Patient tempPat(fName, lName, SSN, crit);
			//Checks if the insertion was successful, if not output an error.
			if (patients.insert(tempPat)) {
				output += name + " Clinic Patient ";
				if (crit) {
					output += "(Critical): ";
				}
				else {
					output += "(Regular): ";
				}
				output += fName + " " + lName + " was added to the waiting room.";
				transactions << output << endl;
				cout << output << endl;
			}
			else {
				output = name + " Clinic waitlist is full, cannot add " + fName + " " + lName;
				cout << output << endl;
				transactions << output << endl;
			}
			isValidInput = true;
		}
		catch (invalid_argument) {
			cout << "SSN is not numeric, plese re-enter:" << endl;
		}
	}
}

void Clinic::insertPatient(const Patient& newPat) {
	// Output stores the formatted output.
	string output;
	if (patients.insert(newPat)) {
		output = name + " Clinic Paitent (Regular): " + newPat.fName + " " + newPat.lName + " was added to the waiting room.";
	}
	else {
		output = "Error- " + name + " Clinic is full, cannot add " + newPat.fName + " " + newPat.lName;
	}
	transactions << output << endl;
}

void Clinic::operate() {
	// output stores the formatted output which cleans up the ouput section as it is output twice.
	string output;
	//Checkes that there are patients in the queue.
	if (!patients.empty()) {
		output += name + " Clinic Patient: " + patients.front()->data.fName + " " + patients.front()->data.lName + " was taken to the operating room.";
		cout << output << endl;
		transactions << output << endl;
		patients.pop_front();
	}
	else {
		output = "Queue is empty, no patients to operate on.";
		cout << output << endl;
		transactions << output << endl;
	}
}

void Clinic::cancelPatient() {
	int SSN;
	//result stores the result of the removal. The first value is true if successful and the second stored the full name of the removed patient.
	pair<bool, string> result;
	cout << "Enter patient SSN: ";
	cin >> SSN;
	result = patients.remove(SSN);
	//Checks if the removal was successful.
	if (result.first == true) {
		cout << name << " Clinic Patient: " << result.second << " was removed from the waiting list." << endl;
		transactions << name << " Clinic Patient: " << result.second << " was removed from the waiting list." << endl;
	}
	else {
		cout << "ERROR " << name << " Clinic: Unable to find patient " << SSN << " In the waiting room" << endl;
		transactions << "ERROR " << name << " Clinic: Unable to find patient " << SSN << " In the waiting room" << endl;
	}
}

void Clinic::endDay(ostream& patientFile, ostream& transFile, string abbrev) {
	//Stores each line of the transaction stream.
	string line;
	transFile << '\n' << name << " clinic end of day report:" << endl;
	//Reads all the lines of the transaction stream and outputs them to the transaction file.
	while (getline(transactions, line)) {
		transFile << line << endl;
	}
	//Empties the queue and places the patients in the file to be read the next day.
	while (!patients.empty()) {
		patientFile << abbrev << ',' << patients.front()->data.fName << ',' << patients.front()->data.lName << ',' << patients.front()->data.SSN << endl;
		transFile << name << " Clinic Patient " << patients.front()->data.fName << ' ' << patients.front()->data.lName << " added to schedule for tomorrow" << endl;
		patients.pop_front();
	}
}

void Clinic::printQueue() {
	patients.print();
}
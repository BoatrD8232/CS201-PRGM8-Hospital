// CS201R-PGM8Hosptal 
// NAME:  David Boatright
// 12/5/2024

#include "Queue.h"
#include "Clinic.h"


//PRE- printMenu is called to print the main menu of the program.
//POST- The main menu is ouput.
void printMainMenu() {
    cout << "    KC Research Hospital" << endl;
    cout << "1: Heart Clinic" << endl;
    cout << "2: Pulmonary Clinic" << endl;
    cout << "3: Plastic Surgery" << endl;
    cout << "4: Quit" << endl;
    cout << "Choose the clinic: ";
}

int main()
{
    ifstream inFile;
    ofstream outFile, transFile;
    //Opens the list of patients.
    inFile.open("patient.csv");
    //Opens the file that any reamining patients will be output to at the end of the day.
    outFile.open("Overflow.csv");
    //Opens the transaction log.
    transFile.open("Transaction.txt");
    //Stores a line of the file, broken down into parts.
    vector<string> words;
    //Stores a line of the file and each word of the line.
    string word, line;
    //Stores the user's main menu choice.
    char choice = '1';
    //Creates a temporary patient and the variables that temporarily store the patient's data.
    Patient tempPat;
    int inSSN;
    bool validSSN;
    //Ceates 3 clinics and passes in the names for use in printing;.
    Clinic heart("Heart");
    Clinic pulmonary("Pulmonary");
    Clinic plastic("Plastic Surgery");
    //Reads in the data from the patient file, creates patients and fills the clinics.
    while (getline(inFile, line)) {
        words.clear();
        stringstream inss(line);
        while (getline(inss, word, ',')) {
            words.push_back(word);
        }
        try {
            inSSN = stoi(words.at(3));
            tempPat.fName = words.at(1);
            tempPat.lName = words.at(2);
            tempPat.SSN = inSSN;
            validSSN = true;
        }
        catch (invalid_argument& err) {
            transFile << "Invalid SSN in input file for " << words.at(1) << " " << words.at(2) << endl;
            validSSN = false;
        }
        if (validSSN) {
            if (words.at(0) == "HC") {
                heart.insertPatient(tempPat);
            }
            else if (words.at(0) == "PC") {
                pulmonary.insertPatient(tempPat);
            }
            else if (words.at(0) == "PSC") {
                plastic.insertPatient(tempPat);
            }
            else {
                transFile << "Invalid Clinic name in input file for " << words.at(1) << " " << words.at(2) << endl;;
            }
        }
    }
    //This loop runs the main menu.
    while (choice != '4') {
        printMainMenu();
        cin >> choice;
        if (choice == '1') {
            heart.getChoice();
        }
        else if (choice == '2') {
            pulmonary.getChoice();
        }
        else if (choice == '3') {
            plastic.getChoice();
        }
        else if (choice != '4') {
            cout << "Invalid choice, choose again" << endl;
        }
    }
    //Ends the day, finalizes ouput.
    heart.endDay(outFile, transFile, "HC");
    pulmonary.endDay(outFile, transFile, "PC");
    plastic.endDay(outFile, transFile, "PSC");
}
 

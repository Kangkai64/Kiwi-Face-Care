/*
Programme : BACS1013 Problem Solving and Programming
Tutorial group : RSW1S1G2
Team member : HO KANG KAI, LEE YONG KANG, POH QI XUAN, JANICE TEH LI QIAN
Application Name : Kiwi Face Care
*/

/*
Developer Notes :

This program is only compatible to Windows OS. It will not work properly in Linux or Mac OS.

Due to the security warning on time functions, #pragma warning (disable 4996) is added.
If this issue remains, you may try adding _CRT_SECURE_NO_WARNINGS to the preprocessor definitions as the steps below :

Project --> KiwiFaceCare Properties --> C / C++ -->
Preprocessor --> add '_CRT_SECURE_NO_WARNINGS' into the preprocessor definitions without the commas

*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream> // include file stream
#include <cstdlib> // c++ standard library functions
#include <limits> // for the cin.ignore() to ignore to 'infinity'
#include <sstream> // to convert string to int and vice versa
#include <ctime>
#include <chrono> // also for time
#include <conio.h> // password input mask, makes the program confined to Windows OS
#include <regex> // for email validation
#include <cstdio> // for remove functions
#define NOMINMAX // so it won't collide with the windows.h
#include <Windows.h>
#pragma warning (disable : 4996)

using namespace std;

enum DataField { NAME, CONTACT, EMAIL, USERNAME, PASSWORD, CONFIRM, AGE, USERID };
enum Time { TIMESTAMP, DATETIME, EXPIRY };

struct Booking {
	int slot = 0;
	string cust_Id = "";
	string bill_Id = "";
	string staff_Id = "";
	string serviceType = "";
	string appointmentDate;
	string appointmentTime;
	double amount;
};

struct UserCredentials {
	string userID;
	string username;
	string password;
	string timeCreated;
};

struct UserProfile {
	string name;
	string contact;
	string email;
	int age = 18;
	string gender;
};

void displayLogo(), getChoice(int&), displayMiniLogo(), validType(int&), displayService(string&, string&),
readAboutUs(), readExpert(), displayExit(), invalidChoice(),
loginField(), regField(char), generateId(char, char, string&), createUser(string&, string&, string&, string, string),
createProfile(string&, string&, string&, string&, string), validLogin(string&, string&), logout(), viewCustomerList(),
readUserId(string, int&, string[], char, string&, int), readUserList(string, int, string[], UserProfile[], int),
displayCustomerList(int, string[], UserProfile[], int), displayListData(int, int, UserProfile),
searchList(string, int, string[], UserProfile[], char, int&, string&, int&, string[]), searchOption(DataField&, int&), sortList(string, char, string[], UserProfile[], int),
SetColor(int), bubbleSort(string&, UserProfile&, string&, UserProfile&), getFilter(int, string[]),
filterResult(int, DataField, int, string[], int, string[], UserProfile[], string[], UserProfile[], bool&, int&), searchResult(string, string[], UserProfile[], int&, string[]),
sortOption(DataField&, int&), orderOption(bool&, int&), checkOrder(bool&, int, DataField, bool, string[], UserProfile[]), sortResult(int, string[], UserProfile[]);

// template, can be used to clear different types of array
template <typename T>
void clearArray(T arr[], int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = T();  // Assign the default value of type T
	}
}

bool validRegInput(string&, DataField, string), validUsername(string&, string), compareLexicographically(string, string);

string runClock(Time), getPassword();

void getCustData(string&, string&, string&, string), getStaffDetails(int, string&, string&),
handleBooking(string&, string, string, string, string, bool, int), dispSchedule(string&, string, string, bool&, int),
booking(string&, string, string, string, string, bool, int&), allSchedule(string&);

string getWeekChoice(string, Booking[]), promptForService(int, string, string, string, bool, int);

bool confirmBooking(Booking newBooking, string, string, string, string, bool, double), confirmPayment(int, string)
, checkSlotAvailability(int, int);

int paymentMethod(), calStartDay(string);

void displayWeeks(string&, Booking[]), saveBookingData(string&, Booking&);

int promptForSlot(Booking[], string, string, string, bool, int, int);

bool checkFullyBooked(int, Booking[]);

void dispBooking(string&), getIdByUsername(string&), processBooking(string&, string&, string**, bool&, string&, int&, int, int), dispSalesReport(),
readAllBooking(string&, string**, int&, int, int), dispBookingData(string**, int&), printBill(Booking newBooking, string&, string, string, string, string, bool, double)
, membership(string&), purOrRenewMembership(string&, string), checkMember(string&, string), dispUserBookingData(string**, int&), splitDate(string&, int&, int&, int&);

double calTotalAmount(string, bool, double);

bool confirmMember(int, string, int), isExpired(string&), userProfileExists(string&), isValidBookingId(string&);

void displayProfileMenu(string&, bool), readUserCredential(UserCredentials&, string&), readUserProfile(UserProfile&, string&),
writeUserCredential(string&, UserCredentials&), writeUserProfile(string&, UserProfile&),
displayUserCredentials(UserCredentials&), displayUserProfile(UserProfile&), changeUsername(UserCredentials&, string&), resetPassword(UserCredentials&, string&),
updateAgeAndGender(UserProfile&);

bool isDigitString(string&), checkLuhn(string&);
bool validateCard(), validateOnlinePayment(), validateEWallet();

int main() {


	displayLogo();
	system("pause");
	system("cls");
	int choice;
	char prefix = 'C';

	do
	{
		displayMiniLogo();
		cout << "Main Menu : " << endl;
		cout << "1. View expert" << endl;
		cout << "2. Login" << endl;
		cout << "3. Register" << endl;
		cout << "4. About Us" << endl;
		cout << "9. Exit" << endl;

		getChoice(choice);

		switch (choice) {
		case 1: readExpert(); break;
		case 2: loginField(); break;
		case 3: regField(prefix); break;
		case 4: readAboutUs(); break;
		case 9: SetColor(2); displayExit(); SetColor(7); break;
		default: invalidChoice();
		}

	} while (choice != 9);
	return 0;
}

void displayLogo() {

	string line;
	ifstream read;

	SetColor(3);
	read.open("Logo.txt");

	if (!read) {
		cerr << "Error opening file.\n" << endl;
	}
	else {
		while (getline(read, line)) {
			cout << line << endl;
		}
	}

	cout << endl;
	read.close();

	SetColor(7);
}

// to change text color
void SetColor(int textColor) {

	// Get handle to console for color change
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, textColor);
}

void displayMiniLogo() {

	SetColor(1);
	cout << "-------------------------\n";
	SetColor(11);
	cout << "||" << setw(4) << " " << "Kiwi Face Care" << right << setw(5) << "||" << endl;
	SetColor(1);
	cout << "-------------------------\n";
	SetColor(7);
	cout << "The time now is ";
	SetColor(6);
	cout << runClock(TIMESTAMP) << "\n\n";
	SetColor(7);
}

string runClock(Time timeChoice) {

	const time_t ONEDAY = 86400;
	auto now = chrono::system_clock::now();
	time_t legacyTime = chrono::system_clock::to_time_t(now);
	stringstream timeStream;

	switch (timeChoice)
	{
	case TIMESTAMP:
		timeStream << put_time(localtime(&legacyTime), "%I:%M:%S %p, %d/%m/%Y (%A)"); break;
	case DATETIME:
		timeStream << put_time(localtime(&legacyTime), "%d/%m/%Y"); break;
	case EXPIRY:
		legacyTime += 30 * ONEDAY; // add 30 days to get expiry date
		timeStream << put_time(localtime(&legacyTime), "%d/%m/%Y");
	}

	return timeStream.str();
}

void getChoice(int& choice) {

	cout << "\nEnter choice : ";
	cin >> choice;
	cout << endl;
	validType(choice);
}

void validType(int& choice) { // to handle wrong data type input

	if (cin.fail()) {

		cerr << "Invalid input. Please enter an integer. " << endl;
		cin.clear(); // Clears the failbit and ignore the remaining
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore everything until it encounters a new line
	}
}

void readExpert() {

	const string PROFILEPATH = "userData\\";
	string line, staffIntro = "", staffFile = "", staff_Id, staffName;
	char prefix = 'S';
	int staffChoice = 0;
	UserProfile userProfile;
	ifstream detailsRead;

	getStaffDetails(staffChoice, staff_Id, staffName);

	staffIntro = "Experts\\" + staffName + ".txt";
	staffFile = PROFILEPATH + staff_Id + ".dat";

	system("cls");
	readUserProfile(userProfile, staffFile);
	displayUserProfile(userProfile);
	cout << endl;

	detailsRead.open(staffIntro);

	while (getline(detailsRead, line))
	{
		cout << line << endl;
	}

	detailsRead.close();
	cout << endl;

	system("pause");
	system("cls");
}

void getStaffDetails(int staffChoice, string& staff_Id, string& staffName) {

	const string PROFILEPATH = "userData\\";
	ifstream read, profileRead;
	string staffId[11], lastId;
	UserProfile staffProfile[11];
	int recordCount = 0;

	readUserId(PROFILEPATH, recordCount, staffId, 'S', lastId, 10);
	readUserList(PROFILEPATH, recordCount, staffId, staffProfile, 10);

	do
	{
		system("cls");
		cout << "---------------------------------------\n";
		cout << "\tExperts of Kiwi Face Care\n";
		cout << "---------------------------------------\n\n";
		cout << "No.\t| Expert Name" << endl;
		cout << "====================================\n";
		for (int index = 0; index < recordCount; index++)
		{
			if (!staffId[index].empty()) {
				cout << index + 1 << "\t| " << staffProfile[index].name << endl;
			}
		}
		cout << endl;
		cout << "Choose your expert (number only) ";

		getChoice(staffChoice);

		if (staffChoice < 1 || staffChoice > recordCount)
		{
			invalidChoice();
		}

	} while (staffChoice < 1 || staffChoice > recordCount);

	staff_Id = staffId[staffChoice - 1];
	staffName = staffProfile[staffChoice - 1].name;
	cout << "Staff ID: " << staff_Id << "\nExpert Name: " << staffName << endl;
}

void readUserId(string PROFILEPATH, int& recordCount, string userId[], char prefix, string& lastId, int userIdSize) {

	ifstream read;
	string data, userType = "";

	// Clear the array before reading the next batch
	clearArray(userId, userIdSize);

	read.open(PROFILEPATH + "userId.txt");

	bool startReading = lastId.empty();  // Start reading immediately if lastId is empty

	if (!read)
	{
		cerr << "Error opening file." << endl;
	}
	else
	{
		while (read >> data)
		{
			// Skip until we find lastId if it is specified
			if (!startReading) {
				if (data == lastId) {
					startReading = true;  // Found lastId, start reading subsequent lines
				}
				continue;  // Skip until we find lastId
			}

			// If array has space and the data matches the prefix
			if (prefix != ' ')
			{
				if (recordCount < userIdSize)
				{
					if (data[0] == prefix)
					{
						userId[recordCount] = data; // don't know why it would skip the last element
						recordCount++;
					}
				}
				else
				{
					break;
				}
			}
			else
			{
				if (recordCount < userIdSize)
				{
					userId[recordCount] = data;
					recordCount++;
				}
				else
				{
					break;
				}
			}
		}
	}

	read.close();

	// Update lastId if we successfully read some records
	if (recordCount > 0) {
		lastId = userId[recordCount - 1];
	}
	else {
		lastId.clear();  // Clear lastId if no records are read
	}
}

void readUserProfile(UserProfile& userProfile, string& filePath) {
	ifstream inputFile(filePath);

	if (!inputFile) {
		cerr << "Error opening file: " << filePath << endl;
	}
	else
	{
		getline(inputFile, userProfile.name);    // First line is customer name
		getline(inputFile, userProfile.contact);  // Second line is contact number
		getline(inputFile, userProfile.email);  // Third line is email
		inputFile >> userProfile.age; // Fourth line is age (if exists)
		inputFile >> userProfile.gender; // Fifth line is gender (if exists)
	}

	inputFile.close();
}

void displayUserProfile(UserProfile& userProfile) {
	cout << "\n\tUser Profile" << endl;
	cout << "====================================" << endl;
	cout << "Full Name\t:" << userProfile.name << endl;
	cout << "Contact Number  :" << userProfile.contact << endl;
	cout << "Email\t\t:" << userProfile.email << endl;
	cout << "Age\t\t:" << userProfile.age << endl;
	cout << "Gender\t\t:" << userProfile.gender << endl;
	cout << endl;
}

void loginField() {

	string username, password;

	system("cls");
	displayMiniLogo();
	cout << "-----------\n";
	cout << "Login Field\n";
	cout << "-----------\n";
	cout << "Enter username : ";
	cin.ignore();
	getline(cin, username);
	cout << "Enter password : ";
	password = getPassword();
	cout << endl;

	validLogin(username, password);
}

void regField(char access) {

	const string CREDENTIALPATH = "userCredential\\", PROFILEPATH = "userData\\";
	string name, contact, email, usernameEnter, passwordEnter = "", confirmPass, newUserId;
	char prefix = access;
	bool valid;

	cin.get(); // to get the new line
	system("cls");
	do
	{
		displayMiniLogo();
		cout << "-------------------\n";
		cout << "Register Field\n";
		cout << "-------------------\n";
		cout << "Enter -999 to exit.\n";

		if (!name.empty())
		{
			cout << left << "Fields you have entered : \n\n";
			cout << "\n" << setw(15) << "Full Name" << ": " << name;
			if (!contact.empty())
			{
				cout << "\n" << setw(15) << "Contact Number" << ": " << contact;
			}
			if (!email.empty())
			{
				cout << "\n" << setw(15) << "Email" << ": " << email;
			}
			if (!usernameEnter.empty())
			{
				cout << "\n" << setw(15) << "Username" << ": " << usernameEnter;
			}
			if (!passwordEnter.empty())
			{
				cout << "\n" << setw(15) << "Password" << ": " << right << setfill('*') << setw(passwordEnter.length() + 1) << " " << setfill(' ');
			}
			cout << endl;
		}
		valid = true; // updated each time repeated

		if (valid && name.empty())
		{
			cout << "\nEnter your full name : ";
			getline(cin, name);

			valid = validRegInput(name, NAME, passwordEnter);
		}

		// Input contact number
		if (valid && contact.empty())
		{
			cout << "\nEnter your contact number (eg : 012-3456789) : ";
			cin >> contact;

			valid = validRegInput(contact, CONTACT, passwordEnter);
		}

		// Input email
		if (valid && email.empty())
		{
			cout << "\nEnter your email : ";
			cin >> email;

			valid = validRegInput(email, EMAIL, passwordEnter);
		}

		cin.ignore();

		// Input username
		if (valid && usernameEnter.empty())
		{
			cout << "\nEnter preferred username ( >= 3 characters ) : ";

			getline(cin, usernameEnter);

			valid = validRegInput(usernameEnter, USERNAME, passwordEnter);

			if (usernameEnter[0] == 'N')
			{
				return;
			}
		}

		// Input password
		if (valid && passwordEnter.empty())
		{
			cout << "\nYour password should have : " << endl;
			cout << "- 8 characters " << endl;
			cout << "- One uppercase and one lowercase " << endl;
			cout << "- One digit " << endl;
			cout << "- One special character [@$!%*?&]" << endl;

			cout << "\nEnter password   : ";
			passwordEnter = getPassword();

			valid = validRegInput(passwordEnter, PASSWORD, passwordEnter);
		}

		// Confirm password
		if (valid && confirmPass.empty())
		{
			cout << "\nConfirm password : ";
			confirmPass = getPassword();

			valid = validRegInput(confirmPass, CONFIRM, passwordEnter);
		}

		if (name == "-999" || contact == "-999" || email == "-999" || usernameEnter == "-999" || passwordEnter == "-999" || confirmPass == "-999")
		{
			system("cls");
			return;
		}

	} while (!valid);

	cout << endl;

	generateId(access, prefix, newUserId);
	createUser(usernameEnter, passwordEnter, newUserId, CREDENTIALPATH, PROFILEPATH);
	createProfile(name, contact, email, newUserId, PROFILEPATH);
	system("pause");
	system("cls");
}

void readAboutUs() {

	string line;
	ifstream read;

	system("cls");

	read.open("AboutUs.txt");

	if (!read) {
		cerr << "Error opening file.\n" << endl;
	}
	else {
		cout << "---------------------------------------\n";
		cout << "\tAbout Kiwi Face Care\n";
		cout << "---------------------------------------\n\n";

		while (getline(read, line))
		{
			cout << line << endl;
		}
	}

	read.close();
	cout << endl;
	system("pause");
	system("cls");
}

void displayExit() {

	system("cls");
	displayLogo();
	SetColor(2);
	cout << "Thank you for coming. Have a nice day." << endl;
	SetColor(7);
}

void invalidChoice() {

	cerr << "Invalid choice. Enter one number only." << endl;
	system("pause"); // Let the user read the error message before cls
	system("cls");
}

bool validRegInput(string& input, DataField data, string password) {

	const string CREDENTIALPATH = "userCredential\\";
	ifstream read;
	string dataField = "";

	// Define regular expression
	regex pattern;

	/*
		Explanation of the regex pattern:
	(\w+): Matches one or more word characters (letters, digits, and underscores).
	(\.|\+)?: Matches an optional period . or plus sign +.
	(\w*): Matches zero or more word characters (could be empty).
	@: Matches the @ symbol, which is mandatory in an email.
	(\w+): Matches the domain name (one or more word characters).
	(\.\w+)+: Matches the domain suffix (e.g., .com, .org). The + ensures at least one period followed by word characters is present.
	*/

	switch (data)
	{
	case NAME: pattern = regex(R"(^[A-Z][a-z]+(\s[A-Z]([a-z]))*(\s(bin|binti|a/l|a/p)?)*(\s[A-Z]([a-z])*){0,3}$)"); dataField = "Name"; break;
	case CONTACT: pattern = regex(R"(^01(1|2|3|4|6|7|8|9)-(\d){7,8}$)"); dataField = "Contact number"; break;
	case EMAIL: pattern = regex(R"(^(\w+)(\.|\+)?(\w*)(@)(\w+)(\.\w+)+$)"); dataField = "Email"; break;
	case USERNAME: pattern = regex(R"(^(\w){3,}$)"); dataField = "Username"; break;
	case PASSWORD: pattern = regex(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$)"); dataField = "Password";
	case CONFIRM: dataField = "Confirm Password";
	}

	// Try to match the data to the pattern
	if (!input.empty())
	{
		switch (data)
		{
		case NAME:
			if (!regex_match(input, pattern))
			{
				if (input != "-999")
				{
					cerr << "\nInvalid name. Your name should start with capital letters and does not have any numbers. Please try again.\n" << endl;
					input.clear();
				}
				cout << endl;
				system("pause");
				system("cls");
				return false;
			}
			else
			{
				cout << "Valid " << dataField << endl;
				return true;
			}
			break;
		case CONTACT:
			if (!regex_match(input, pattern))
			{
				if (input != "-999")
				{
					cerr << "\nContact number should be at least 10 numbers. Please enter a valid Malaysia contact number.\n" << endl;
					input.clear();
				}
				cout << endl;
				system("pause");
				system("cls");
				return false;
			}
			else
			{
				cout << "Valid " << dataField << endl;
				return true;
			}
			break;
		case EMAIL:
			if (!regex_match(input, pattern))
			{
				if (input != "-999")
				{
					cerr << "\nThe email format is incorrect. Please try again.\n" << endl;
					input.clear();
				}
				cout << endl;
				system("pause");
				system("cls");
				return false;
			}
			else
			{
				cout << "Valid " << dataField << endl;
				return true;
			}
			break;
		case USERNAME:
			if (!regex_match(input, pattern))
			{
				if (input != "-999")
				{
					cerr << "\nUsername should be at least 3 characters. Please try again.\n" << endl;
					input.clear();
				}
				cout << endl;
				system("pause");
				system("cls");
				return false;
			}
			else
			{
				read.open(CREDENTIALPATH + input + ".txt");
				if (!read)
				{
					read.close();
					cout << "Valid username and available" << endl;
					return true;
				}
				else
				{
					do
					{
						cerr << "\nUsername already occupied. Please choose another username.\n";
						cout << "Enter another username? [ Y / N ] ";
						cin >> input[0];
						cout << endl;

						input[0] = toupper(input[0]);
						cin.ignore();

						if (input[0] == 'Y')
						{
							input.clear();
							cout << "Enter preferred username ( >= 3 characters ) : ";

							getline(cin, input);
							system("cls");
							return (validRegInput(input, USERNAME, password));
						}
						else if (input[0] == 'N')
						{
							system("pause");
							system("cls");
							return false;
						}
						else {
							cin.clear(); // Clear the failbit
							cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
							cout << "Invalid input! Please enter again..\n";
							system("pause");
							system("cls");
						}
					} while (input[0] != 'N');
				}
			}
			break;
		case PASSWORD:
			if (!regex_match(input, pattern))
			{
				if (input != "-999")
				{
					cerr << "\nPassword is not in the correct pattern mentioned. Please try again.\n" << endl;
					input.clear();
				}
				cout << endl;
				system("pause");
				system("cls");
				return false;
			}
			else
			{
				cout << "Valid " << dataField << endl;
				password = input;
				return true;
			}
			break;
		case CONFIRM:
			if (input != password)
			{
				if (input != "-999")
				{
					cerr << "\nConfirm Password entered is not the same as Password. Please try again.\n" << endl;
					input.clear();
				}
				cout << endl;
				system("pause");
				system("cls");
				return false;
			}
			else
			{
				cout << "Valid " << dataField << endl;
				return true;
			}
		}
	}
	else
	{
		cerr << dataField << " cannot be empty. Please try again.\n\n" << endl;
		system("pause");
		system("cls");
		return false;
	}
}

string getPassword() {
	string password;
	char ch = ' ';

	while (ch != 13) {
		ch = _getch();  // Read a single character without echoing it

		// Check for Enter key (ASCII 13) to end input
		if (ch == 13) {
			cout << endl;
			break;
		}
		// Backspace handling
		else if (ch == 8 && !password.empty()) {
			cout << "\b \b";  // Erase the last '*' by moving back, printing a space, and moving back again
			password.pop_back();
		}
		// Regular character input
		else if (ch != 8) {
			cout << '*';  // Print asterisk
			password.push_back(ch);
		}
	}

	return password;
}

void generateId(char access, char prefix, string& newId) {

	const string PROFILEPATH = "userData\\";
	string latest_Id, num_string;
	stringstream buffer_stoi, buffer_itos;
	int num, choice;
	ifstream read;

	if (prefix != 'B') {
		read.open(PROFILEPATH + "userId.txt");

		if (!read) {
			cerr << "Error opening file.\n" << endl;
		}
		else {
			while (getline(read, latest_Id)) {
				if (!latest_Id.empty() && latest_Id[0] != ' ' && latest_Id[0] != '\n') {
					// Keep updating to the last valid ID in the file
					continue;
				}
			}
			read.close();
		}
	}
	else {
		read.open("booking\\bookingID.txt");

		if (!read) {
			cerr << "Error opening file for reading." << endl;
			// If the file doesn't exist or can't be opened, start with 'B001'
			newId = prefix + string("001");
			return;
		}
		else {
			while (getline(read, latest_Id)) {
				if (!latest_Id.empty() && latest_Id[0] != ' ' && latest_Id[0] != '\n') {
					// Keep updating to the last valid ID in the file
					continue;
				}
			}
			read.close();

			if (latest_Id.empty()) {
				// If no bill ID was found or the file is empty, start with the first ID
				newId = prefix + string("001");
				return;
			}
		}
	}

	// Extract the numerical part of the ID
	num_string = latest_Id.erase(0, 1); // Removes the prefix character
	buffer_stoi << num_string;
	buffer_stoi >> num;
	num += 1; // Increment by 1
	buffer_itos << num;
	buffer_itos >> num_string;

	if (access == 'A' && prefix != 'B') { // For Admin to register account for staff and admin
		do {
			cout << "--------------------\n";
			cout << "Admin Register Field\n";
			cout << "--------------------\n";
			cout << "Registering for : " << endl;
			cout << "1. Admin " << endl;
			cout << "2. Staff / Expert " << endl;
			cout << "3. Customer " << endl;

			getChoice(choice);

			switch (choice) {
			case 1: prefix = 'A'; break;
			case 2: prefix = 'S'; break;
			case 3: prefix = 'C'; break;
			default: invalidChoice();
			}
		} while (choice < 1 || choice > 3);
	}

	if (prefix == 'B') {
		// Format the new ID with leading zeros (3 digits)
		num_string = string(3 - num_string.length(), '0') + num_string;
	}

	newId = prefix + num_string;
}

void createUser(string& userEnter, string& passEnter, string& newUserId, string CREDENTIALPATH, string PROFILEPATH) {

	ofstream write;

	string lastUpdateDate = runClock(DATETIME);

	write.open(CREDENTIALPATH + userEnter + ".txt");
	write << newUserId << endl << userEnter << endl << passEnter << endl << lastUpdateDate;
	cout << "Your account is registered successfully." << endl;
	cout << "Your user ID is ";
	SetColor(2);
	cout << newUserId;
	SetColor(7);
	cout << "\nYour account is created on " << lastUpdateDate << endl;
	write.close();

	write.open(PROFILEPATH + "userId.txt", ios::app); // go to the end of the line
	write << endl << newUserId;
	write.close();
}

void createProfile(string& name, string& contact, string& email, string& newUserId, string PROFILEPATH) {

	ofstream write;

	write.open(PROFILEPATH + newUserId + ".dat");
	write << name << endl << contact << endl << email;
	write.close();
}

void validLogin(string& username, string& password) {

	const string CREDENTIALPATH = "userCredential\\";
	string usernameFile = "", passwordFile = "", userId;
	ifstream read(CREDENTIALPATH + username + ".txt");

	if (!read) {

		cerr << "Incorrect username or password. Please try again.\n\n";
		system("pause");
		system("cls");
	}
	else {
		getline(read, userId);
		getline(read, usernameFile);
		getline(read, passwordFile);

		if (username == usernameFile && password == passwordFile) {

			read.close();

			cout << "You are";
			SetColor(2);
			cout << " logged in.\n\n";
			SetColor(7);
			system("pause");
			system("cls");
			displayService(userId, username);
		}
		else {
			cerr << "Incorrect username or password. Please try again.\n\n";
			userId = ""; // to nullify the user Id
			system("pause");
			system("cls");
		}
	}
}

void displayService(string& userId, string& username) { // display service based on level of access

	int choice;
	char prefix = userId[0];

	do {
		displayMiniLogo();
		if (prefix == 'C') {
			cout << "Customer Service List : " << endl;
			cout << "1. View expert" << endl;
			cout << "2. View schedule" << endl;
			cout << "3. View profile" << endl;
			cout << "4. View booking" << endl;
			cout << "5. View membership" << endl;
			cout << "6. About us" << endl;
			cout << "9. Logout" << endl;
		}
		else if (prefix == 'S') {
			cout << "Staff Service List : " << endl;
			cout << "1. View customer list" << endl;
			cout << "2. View your schedule" << endl;
			cout << "3. View sales report" << endl;
			cout << "4. View profile" << endl;
			cout << "5. View booking" << endl;
			cout << "9. Logout" << endl;
		}
		else if (prefix == 'A') {
			cout << "Admin Service List : " << endl;
			cout << "1. View customer list" << endl;
			cout << "2. View schedule" << endl;
			cout << "3. View sales report" << endl;
			cout << "4. View profile" << endl;
			cout << "5. View booking" << endl;
			cout << "6. Register Account" << endl;
			cout << "9. Logout" << endl;
		}

		getChoice(choice);

		switch (prefix)
		{
		case 'C':
			switch (choice) {
			case 1: readExpert(); break;
			case 2: allSchedule(userId); break;
			case 3: displayProfileMenu(username, false); break;
			case 4: dispBooking(userId); break;
			case 5: membership(userId); break;
			case 6: readAboutUs(); break;
			case 9: logout(); break;
			default: invalidChoice();
			}break;
		case 'S':
			switch (choice) {
			case 1: viewCustomerList(); break;
			case 2: allSchedule(userId); break;
			case 3: dispSalesReport(); break;
			case 4: displayProfileMenu(username, false); break;
			case 5: dispBooking(userId); break;
			case 9: logout(); break;
			default: invalidChoice();
			}break;
		case 'A':
			switch (choice) {
			case 1: viewCustomerList(); break;
			case 2: allSchedule(userId); break;
			case 3: dispSalesReport(); break;
			case 4: displayProfileMenu(username, false); break;
			case 5: dispBooking(userId); break;
			case 6: regField(prefix); break;
			case 9: logout(); break;
			default: invalidChoice();
			}
		}

	} while (choice != 9);
}

void logout() {
	cout << "You are";
	SetColor(2);
	cout << " logged out." << endl;
	SetColor(7);
	system("pause");
	system("cls");
}

void allSchedule(string& userId) {
	system("cls");
	displayMiniLogo();
	const string PROFILEPATH = "userData\\";
	Booking bookingSlot[31]; // To handle slots for 5 days, assuming 6 slots per day (5 * 6 = 30, +1 for indexing from 1)
	int staffChoice = 1;
	char prefix = 'S';
	string staffFile, staff_Id, staffName;
	string profilePath = PROFILEPATH + userId + ".dat";

	if (userId[0] == 'C' || userId[0] == 'A') {
		getStaffDetails(staffChoice, staff_Id, staffName);
	}

	if (userId[0] == 'S') {
		ifstream read(profilePath);
		if (!read) {
			cout << "Error opening file." << endl;
			return;
		}
		getline(read, staffName);
	}

	staffFile = staffName + "\\";

	cout << staffName << " September Schedule: " << endl;
	cout << endl;

	displayWeeks(staffFile, bookingSlot);
	cout << endl;

	string weekChoice = getWeekChoice(staffFile, bookingSlot);
	bool status = true;
	int slot = 0;
	dispSchedule(userId, weekChoice, staffFile, status, slot);
	cout << endl;

	if (status && userId[0] == 'C')
	{
		handleBooking(userId, weekChoice, staffFile, staff_Id, staffName, status, slot);
	}

	if (userId[0] == 'A' || userId[0] == 'S')
	{
		char choice = 'Y';
		cout << "Do you want to view customer profile? [ Y / N ] :";
		cin >> choice;
		choice = toupper(choice);
		
		do
		{

			if (choice == 'Y')
			{
				const string PROFILEPATH = "userData\\";
				string userIdEnter;
				UserProfile userProfile;
				cout << "Enter customer ID : ";
				cin.ignore();
				getline(cin, userIdEnter);

				string profilePath = PROFILEPATH + userIdEnter + ".dat";
				ifstream check(profilePath);

				if (!check) {
					cout << "Customer ID does not exist..." << endl;
				}
				else {
					readUserProfile(userProfile, profilePath);
					displayUserProfile(userProfile);
				}

				cout << "Do you want to view another customer profile? [ Y / N ] :";
				cin >> choice;
				choice = toupper(choice);
			}
			if (choice != 'Y' && choice != 'N')
			{
				cin.clear(); // Clear the failbit
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
				cout << "Invalid input! Please enter again..\n";
			}

		} while (choice != 'N');

		system("pause");
	}
	system("cls");
}

void displayWeeks(string& staffFile, Booking bookingSlot[]) {
	int availableHours, weeks = 0;
	const int MAXHOURS = 30;
	const string WEEKFILES[5] = { "w1.txt", "w2.txt" , "w3.txt" , "w4.txt" ,"w5.txt" };

	for (int i = 0; i < 5; i++) {
		int bookedHours = 0;
		int startDay = 2 + (weeks * 7);
		string filePath = "booking\\" + staffFile + string(WEEKFILES[i]);
		ifstream read(filePath);
		if (!read) {
			cout << "Error opening file " << WEEKFILES[i] << "." << endl;
			continue;
		}

		int slotNumber;
		string slotLabel;
		while (read >> slotLabel >> slotNumber) {
			if (slotLabel == "Slot" && slotNumber >= 1 && slotNumber <= 30) {
				read >> bookingSlot[slotNumber].cust_Id;
				read >> bookingSlot[slotNumber].bill_Id;
				read >> bookingSlot[slotNumber].staff_Id;
				read >> bookingSlot[slotNumber].serviceType;
				read >> bookingSlot[slotNumber].appointmentDate;
				read >> bookingSlot[slotNumber].appointmentTime;
				read >> bookingSlot[slotNumber].amount;
				bookingSlot[slotNumber].slot = slotNumber;
				if (checkSlotAvailability(startDay, slotNumber)) {
					if (bookingSlot[slotNumber].serviceType != "C") {
						bookedHours += 2;
					}
					else {
						bookedHours++;
					}
				}
			}
		}
		read.close();

		availableHours = MAXHOURS - bookedHours;

		const char* numWeeks[5] = { "Week 1", "Week 2", "Week 3", "Week 4", "Week 5" };
		cout << numWeeks[weeks] << endl;
		cout << "-----------------------------------------------\n";
		cout << "| " << setw(8) << left << "Day" << "||  Mon |  Tue |  Wed |  Thu |  Fri |\n";
		cout << "-----------------------------------------------\n";
		cout << "| " << setw(8) << left << "Date" << "|| ";

		for (int day = 0; day < 5; day++) {
			if (startDay + day <= 30) {
				cout << setw(3) << right << startDay + day << "  | ";
				if (!checkSlotAvailability(startDay + day, day)) {
					availableHours -= 6;
				}
				else if (startDay + day == 30)
				{
					availableHours = 6 - bookedHours;
				}
			}
			else {
				cout << "     | ";
			}
		}
		cout << "\n-----------------------------------------------\n";
		cout << "Available Hours: " << availableHours << '\n' << endl;

		weeks++;
	}
}

bool checkSlotAvailability(int startDay, int slot) {

	int today = 0;
	stringstream buffer;
	int slotDay = (slot - 1) / 6 + startDay; // get the day of the slot
	buffer << runClock(DATETIME).substr(0, 2);
	buffer >> today;

	return slotDay - today > 0;
}

string getWeekChoice(string staffFile, Booking bookingSlot[]) {
	string weekChoice;
	do {
		cout << "Enter week choice to view detailed schedule (e.g., w1, w2): ";
		cin >> weekChoice;

		// Convert the input string to lowercase
		for (char& c : weekChoice) {
			c = tolower(c);
		}

		if (weekChoice != "w1" && weekChoice != "w2" && weekChoice != "w3" && weekChoice != "w4" && weekChoice != "w5") {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input! Please try again...\n\n";
			system("pause");
			system("cls");
			displayWeeks(staffFile, bookingSlot);
		}
	} while (weekChoice != "w1" && weekChoice != "w2" && weekChoice != "w3" && weekChoice != "w4" && weekChoice != "w5");
	return weekChoice;
}

void dispSchedule(string& userId, string weekChoice, string staffFile, bool& status, int slot) {
	system("cls");
	displayMiniLogo();

	Booking bookingSlot[31];
	int count = 0;
	string filePath = "booking\\" + staffFile + weekChoice + ".txt";

	ifstream read(filePath);
	if (!read) {
		cout << "Error opening file for reading." << endl;
		return;
	}

	string slotLabel;
	int slotNumber = 0;

	while (read >> slotLabel >> slotNumber) {
		if (slotLabel == "Slot" && slotNumber >= 1 && slotNumber <= 30) {
			read >> bookingSlot[slotNumber].cust_Id;
			read >> bookingSlot[slotNumber].bill_Id;
			read >> bookingSlot[slotNumber].staff_Id;
			read >> bookingSlot[slotNumber].serviceType;
			read >> bookingSlot[slotNumber].appointmentDate;
			read >> bookingSlot[slotNumber].appointmentTime;
			read >> bookingSlot[slotNumber].amount;
			bookingSlot[slotNumber].slot = slotNumber;
		}
	}
	read.close();

	// Display the schedule
	cout << "Booking schedule\n\n";
	cout << "========================================================================================================================\n";
	cout << setw(7) << "Day" << " (Date)\t||\t9:00 - 11:00\t11:00 - 13:00\t13:00 - 15:00\t15:00 - 17:00\t17:00 - 19:00\t19:00 - 21:00\n";
	cout << "========================================================================================================================\n";

	// Define days of the week and corresponding dates for September 2024
	string daysOfWeek[5] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };
	int startDay = calStartDay(weekChoice);

	// Loop through the week to display the schedule for each day
	for (int day = 0; day < 5; day++) {
		int currentDate = startDay + day;

		if (currentDate <= 30) {
			cout << setw(10) << left << daysOfWeek[day] << " (" << currentDate << ")\t||\t";

			// Calculate the start slot for the day
			int startSlotIndex = day * 6 + 1;

			// For admin or staff view, display the slot info even if fully booked or not available
			if (userId[0] == 'A' || userId[0] == 'S') {
				for (int i = 0; i < 6; i++) {
					int currentSlot = startSlotIndex + i;
					if (!bookingSlot[currentSlot].cust_Id.empty()) {
						SetColor(12); // Red Text
						cout << bookingSlot[currentSlot].cust_Id << "\t\t";
						SetColor(7);
					}
					else {
						SetColor(10);  // Green text
						cout << "Slot " << currentSlot << "\t\t";
						SetColor(7);
					}
				}
			}
			else {
				// For non-admin view, check if the day is available
				if (!checkSlotAvailability(currentDate, day)) {
					SetColor(12);
					cout << "\t\t\t\t\tNot Available";
					SetColor(7);
					count++;
				}
				else if (checkFullyBooked(startSlotIndex, bookingSlot)) {
					// Fully booked
					SetColor(12);
					cout << "\t\t\t\t\tFully Booked";
					SetColor(7);
					count++;
				}
				else {
					// Display available or booked slots for customer
					for (int i = 0; i < 6; i++) {
						int currentSlot = startSlotIndex + i;
						if (bookingSlot[currentSlot].cust_Id.empty()) {
							if (slot == currentSlot) {
								SetColor(14); // Yellow text
								cout << "Slot " << setw(2) << currentSlot << "\t\t";
								SetColor(7);
							}
							else {
								SetColor(10);  // Green text
								cout << "Slot " << setw(2) << currentSlot << "\t\t";
								SetColor(7);
							}
						}
						else {
							SetColor(12);
							cout << setw(10) << "Booked" << "\t";
							SetColor(7);
						}
					}
				}
			}
		}
		cout << endl;
	}
	cout << "========================================================================================================================\n\n";

	cout << "\nBooking Slot Legend:\n\n";

	SetColor(BACKGROUND_GREEN);  // Green background
	cout << "   ";
	SetColor(7);
	cout << "  : Available\t";
	SetColor(BACKGROUND_RED | BACKGROUND_GREEN);
	cout << "   ";
	SetColor(7);
	cout << "  : Choosen Slot\t";
	SetColor(BACKGROUND_RED);
	cout << "   ";
	SetColor(7);
	cout << "  : Not Available\n";

	if (count == 5) {
		status = false;
		cout << "\nNo available slot...\n" << endl;
		system("pause");
		system("cls");
	}
}

int calStartDay(string weekChoice) {

	int startDay = 2;
	if (weekChoice == "w2") {
		startDay = 9;
	}
	else if (weekChoice == "w3") {
		startDay = 16;
	}
	else if (weekChoice == "w4") {
		startDay = 23;
	}
	else if (weekChoice == "w5") {
		startDay = 30;
	}
	return startDay;
}

bool checkFullyBooked(int slot, Booking bookingSlot[]) {
	const int maxHours = 6;
	int dayIndex = (slot - 1) / 6;
	int hours = 0;

	for (int i = dayIndex * 6 + 1; i <= (dayIndex + 1) * 6; ++i) {
		if (!bookingSlot[i].cust_Id.empty()) {
			if (bookingSlot[i].serviceType != "C") {
				hours += 2;
			}
			else
			{
				hours += 1;
			}
		}
	}

	return hours >= maxHours;
}

void handleBooking(string& userId, string weekChoice, string staffFile, string staff_Id, string staffName, bool status, int slot) {

	char bookChoice;

	do {
		cout << "Do you want to make a booking? [ Y / N ]: ";
		cin >> bookChoice;

		bookChoice = toupper(bookChoice);

		if (bookChoice == 'Y') {
			system("cls");
			dispSchedule(userId, weekChoice, staffFile, status, slot);
			cout << '\n';
			booking(userId, weekChoice, staffFile, staff_Id, staffName, status, slot);
		}
		else if (bookChoice == 'N') {
			// follow the flow for natural break
		}
		else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nInvalid input! Expected input 'Y' or 'N' only!" << endl;
			system("pause");
			system("cls");
			dispSchedule(userId, weekChoice, staffFile, status, slot);
			cout << '\n';
		}
	} while (bookChoice != 'Y' && bookChoice != 'N');
}

void booking(string& userId, string weekChoice, string staffFile, string staff_Id, string staffName, bool status, int& slot) {
	string filePath = "booking\\" + staffFile + "\\" + weekChoice + ".txt";
	const string MEMBERSHIP_PATH = "membership/" + userId + ".txt";
	Booking bookingSlot[31]; // Initialize array for slots
	string memberType;
	double discountRate = 0.0;
	int startDay = calStartDay(weekChoice);

	ifstream read(filePath);
	if (!read) {
		cout << "Error opening file for reading." << endl;
		return;
	}

	string slotLabel;
	int slotNumber = 0;
	int hours = 0;

	while (read >> slotLabel >> slotNumber) {
		if (slotLabel == "Slot" && slotNumber >= 1 && slotNumber <= 30) {
			read >> bookingSlot[slotNumber].cust_Id;
			read >> bookingSlot[slotNumber].bill_Id;
			read >> bookingSlot[slotNumber].staff_Id;
			read >> bookingSlot[slotNumber].serviceType;
			read >> bookingSlot[slotNumber].appointmentDate;
			read >> bookingSlot[slotNumber].appointmentTime;
			read >> bookingSlot[slotNumber].amount;
			bookingSlot[slotNumber].slot = slotNumber;
		}
	}
	read.close();

	slot = promptForSlot(bookingSlot, weekChoice, userId, staffFile, status, slot, startDay);
	if (slot >= 1 && slot <= 30) {
		int start = ((slot - 1) / 6) * 6 + 1; // Calculate the starting index for the slot range
		int end = start + 5; // Calculate the ending index for the slot range

		for (int i = start; i <= end; i++) {
			if (bookingSlot[i].serviceType == "C") {
				hours += 1;
			}
			else if (bookingSlot[i].serviceType == "T1" || bookingSlot[i].serviceType == "T2" || bookingSlot[i].serviceType == "T3") {
				hours += 2;
			}
		}
	}

	int availableHours = 6 - hours;
	string serviceType = promptForService(availableHours, userId, weekChoice, staffFile, status, slot);
	cout << '\n';
	string timeSlots[6] = {
		"9:00-11:00", "11:00-13:00", "13:00-15:00",
		"15:00-17:00", "17:00-19:00", "19:00-21:00"
	};
	string daysOfWeek[5] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };
	int dayIndex = (slot - 1) / 6;
	int appointmentDate = startDay + dayIndex;
	int timeSlotIndex = (slot - 1) % 6;
	string dayOfWeek = daysOfWeek[dayIndex];
	string appointmentTime = timeSlots[timeSlotIndex];

	if (serviceType == "C") {
		// Display available time slots for consultation
		string startHour = appointmentTime.substr(0, appointmentTime.find('-'));
		int firstSlotHour = stoi(startHour.substr(0, startHour.find(':')));
		int secondSlotHour = firstSlotHour + 1;

		int timeChoice;
		do {
			cout << "The consultation time is " << appointmentTime << "\n" << endl;
			cout << "Please select a specific time for the service:" << endl;
			cout << "(1) " << firstSlotHour << ":00-" << secondSlotHour << ":00" << endl;
			cout << "(2) " << secondSlotHour << ":00-" << (secondSlotHour + 1) << ":00" << endl;
			cout << "Enter time slot (1 or 2): ";
			cin >> timeChoice;
			validType(timeChoice);
			if (timeChoice != 1 && timeChoice != 2) {
				cout << "\nInvalid input! Enter either 1 or 2.\n";
				system("pause");
			}
			system("cls");
			dispSchedule(userId, weekChoice, staffFile, status, slot);
			cout << '\n';
		} while (timeChoice != 1 && timeChoice != 2);

		// Adjust appointment time based on the selected choice
		if (timeChoice == 1) {
			appointmentTime = to_string(firstSlotHour) + ":00-" + to_string(secondSlotHour) + ":00";
		}
		else {
			appointmentTime = to_string(secondSlotHour) + ":00-" + to_string(secondSlotHour + 1) + ":00";
		}
	}

	ifstream readMember(MEMBERSHIP_PATH);
	/*bool memberExists = readMember.is_open();*/
	bool memberExists = false;

	if (readMember) {
		memberExists = true;
		getline(readMember, memberType);
		read.close();

		if (memberType == "Silver") {
			discountRate = 0.1;
		}
		else if (memberType == "Gold") {
			discountRate = 0.15;
		}
		else if (memberType == "Platinum") {
			discountRate = 0.20;
		}
	}

	double totalAmount = calTotalAmount(serviceType, memberExists, discountRate);

	Booking newBooking;
	newBooking.cust_Id = userId;
	newBooking.slot = slot;
	newBooking.staff_Id = staff_Id;
	newBooking.serviceType = serviceType;
	newBooking.appointmentDate = to_string(appointmentDate) + "/9/2024";
	newBooking.appointmentTime = appointmentTime;
	newBooking.amount = totalAmount;
	char prefix = 'B';

	generateId(userId[0], prefix, newBooking.bill_Id);
	cout << "Generated Bill ID: " << newBooking.bill_Id << endl;

	bool confirmed = confirmBooking(newBooking, weekChoice, staffName, dayOfWeek, memberType, memberExists, discountRate);

	if (confirmed) {
		saveBookingData(filePath, newBooking);
		system("pause");
		printBill(newBooking, userId, weekChoice, staffName, dayOfWeek, memberType, memberExists, discountRate);
	}
	else {
		cout << "Booking not saved.\n";
	}

	system("pause");
	system("cls");
}

int promptForSlot(Booking bookingSlot[], string weekChoice, string userId, string staffFile, bool status, int slot, int startDay) {
	int maxSlot = (weekChoice == "w5") ? 6 : 30; // Determine the maximum slot number based on the week choice

	do {
		cout << "Enter booking slot (number only): ";
		cin >> slot;
		validType(slot);

		if (slot < 1 || slot > maxSlot) {
			cout << "\nInvalid slot number. Please enter a number between 1 and " << maxSlot << "." << endl;
			system("pause");
		}
		else if (checkFullyBooked(slot, bookingSlot)) {
			cout << "\nThe selected day is fully booked. Please choose another slot." << endl;
			system("pause");
		}
		else if (!bookingSlot[slot].cust_Id.empty()) {
			cout << "\nSlot is already booked. Please choose another slot." << endl;
			system("pause");
		}
		else if (!checkSlotAvailability(startDay, slot)) {
			cout << "\nThe slot has already passed. Please choose another slot." << endl;
			system("pause");
		}
		system("cls");
		dispSchedule(userId, weekChoice, staffFile, status, slot);
		cout << '\n';
	} while (cin.fail() || slot < 1 || slot > maxSlot ||
		!bookingSlot[slot].cust_Id.empty() || checkFullyBooked(slot, bookingSlot) || !checkSlotAvailability(startDay, slot));

	return slot;
}

string promptForService(int availableHours, string userId, string weekChoice, string staffFile, bool status, int slot) {
	string serviceType;

	do {
		cout << "\nServices Provided: " << endl;

		if (availableHours == 1) {
			cout << "(C) Consultation\n" << endl;
		}
		else {
			cout << "(T1) Manicure & Pedicure" << endl;
			cout << "(T2) Facial Treatments" << endl;
			cout << "(T3) Haircuts" << endl;
			cout << "(C) Consultation\n" << endl;
		}
		cout << "Enter type of service (e.g., T1, T2, T3, C): ";
		cin >> serviceType;

		// Convert the input string to uppercase
		for (char& c : serviceType) {
			c = toupper(c);
		}

		if (availableHours == 1) {
			if (serviceType != "C") {
				cin.clear(); // Clear the failbit
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
				cout << "\nInvalid input! Only consultation is available...\n\n";
				system("pause");
				system("cls");
				dispSchedule(userId, weekChoice, staffFile, status, slot);
			}
		}
		else {
			if (serviceType != "T1" && serviceType != "T2" && serviceType != "T3" && serviceType != "C") {
				cin.clear(); // Clear the failbit
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
				cout << "\nInvalid input! Please enter a valid service type (T1, T2, T3, or C).\n\n";
				system("pause");
				system("cls");
				dispSchedule(userId, weekChoice, staffFile, status, slot);
			}
		}

	} while ((availableHours == 1 && serviceType != "C") ||
		(availableHours != 1 && serviceType != "T1" && serviceType != "T2" && serviceType != "T3" && serviceType != "C"));

	return serviceType;
}

double calTotalAmount(string serviceType, bool memberExists, double discountRate) {

	double totalAmount = 0;
	double discount = 1 - discountRate;

	if (memberExists) {

		if (serviceType == "T1") {
			totalAmount = 200 * discount;
		}
		else if (serviceType == "T2") {
			totalAmount = 150 * discount;
		}
		else if (serviceType == "T3") {
			totalAmount = 80 * discount;
		}
		else if (serviceType == "C") {
			totalAmount = 100 * discount;
		}
	}
	else {
		if (serviceType == "T1") {
			totalAmount = 200;
		}
		else if (serviceType == "T2") {
			totalAmount = 150;
		}
		else if (serviceType == "T3") {
			totalAmount = 80;
		}
		else if (serviceType == "C") {
			totalAmount = 100;
		}
	}
	return totalAmount;
}

bool confirmBooking(Booking newBooking, string weekChoice, string staffName, string dayOfWeek, string memberType, bool memberExists, double discountRate) {
	system("cls");
	char checkBook;
	string serviceName = "";

	if (newBooking.serviceType == "C")
	{
		serviceName = "Consultation";
	}
	else if (newBooking.serviceType == "T1")
	{
		serviceName = "Manicure & Pedicure";
	}
	else if (newBooking.serviceType == "T2")
	{
		serviceName = "Facial Treatment";
	}
	else if (newBooking.serviceType == "T3")
	{
		serviceName = "Haircut";
	}

	serviceName += " with " + staffName;

	do {
		displayMiniLogo();
		cout << "\nBooking Confirmation\n--------------------" << endl;
		cout << "Booking NO: " << newBooking.bill_Id << "\n" << endl;
		cout << "Details of service booking:\n" << endl;
		cout << "Service Name: " << serviceName << endl;
		cout << "Appointment Date: " << newBooking.appointmentDate << endl;
		cout << "Appointment Time: " << newBooking.appointmentTime << endl;
		cout << "Expert Name: " << staffName << endl;

		if (memberExists) {
			cout << "\nMembership type: " << memberType << endl;
			cout << "Member discount: " << fixed << setprecision(2) << (discountRate * 100) << "%" << endl;
		}
		cout << fixed << setprecision(2) << showpoint << "\nTotal Amount: RM " << newBooking.amount << endl;
		cout << "\nEnter 'Y' to confirm booking or 'N' to cancel: ";
		cin >> checkBook;

		checkBook = toupper(checkBook);

		if (checkBook == 'Y') {
			system("cls");
			displayMiniLogo();
			cout << "Booking No : " << newBooking.bill_Id << endl;
			int payMethod = paymentMethod();
			bool validPayment = false;
			switch (payMethod) {
			case 1:
				validPayment = validateCard();
				system("pause");
				break;
			case 2:
				validPayment = validateOnlinePayment();
				system("pause");
				break;
			case 3:
				validPayment = validateEWallet();
				system("pause");
				break;
			default:
				validPayment = false;
			}
			bool checkPay = confirmPayment(payMethod, newBooking.cust_Id);
			if (checkPay == true && validPayment == true) {
				cout << "\nBooking confirmed successfully!" << endl;
				return true;
			}
			else {
				cout << "\nBooking canceled." << endl;
				return false;
			}
			system("pause");
		}
		else if (checkBook == 'N') {
			cout << "\nBooking canceled." << endl;
			return false;
		}
		else {
			cin.clear(); // Clear the failbit
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
			cout << "\nInvalid input! Please enter again..\n";
			system("pause");
			system("cls");
		}
	} while (checkBook != 'Y' && checkBook != 'N');
	return false; // to ensure a value is returned
}

int paymentMethod() {
	int payMethod;
	cout << "Payment method:" << endl;
	cout << "(1) Credit/Debit Card\n(2) Online payment transfer\n(3) ewallet\n" << endl;
	cout << "Choose a payment method ";
	do {
		getChoice(payMethod);

		if (payMethod < 1 || payMethod > 3) {
			cout << "Invalid input! Enter one number only.\n";
		}
	} while (payMethod < 1 || payMethod > 3 || cin.fail());

	return payMethod;
}

bool confirmPayment(int payMethod, string userId) {
	system("cls");
	string custName, custTel, custEmail;
	char checkPay;

	do {
		displayMiniLogo();
		cout << "Selected payment process: \n" << endl;
		if (payMethod == 1) {
			cout << "Credit/Debit Card Payment Selected.\n" << endl;
		}
		else if (payMethod == 2) {
			cout << "Online Payment Transfer Selected.\n" << endl;
		}
		else if (payMethod == 3) {
			cout << "eWallet Payment Selected.\n" << endl;
		}

		getCustData(custName, custTel, custEmail, userId);
		cout << "Customer details: \n" << endl;
		cout << "Customer Name: " << custName << endl;
		cout << "Customer Telephone: " << custTel << endl;
		cout << "Customer Email: " << custEmail << endl;
		cout << "\nPlease ensure that all of the information above\nis correct before you proceed.\n";
		cout << "\nEnter 'Y' to confirm booking by paying 50% deposit or 'N' to cancel: ";
		cin >> checkPay;

		checkPay = toupper(checkPay); // Convert checkPay to uppercase

		if (checkPay != 'Y' && checkPay != 'N') {
			cin.clear(); // Clear the failbit
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
			cout << "\nInvalid input! Please enter again..\n";
			system("pause");
			system("cls");
		}
	} while (checkPay != 'Y' && checkPay != 'N');

	if (checkPay == 'Y') {
		return true;
	}
	return false;
}

bool isDigitString(string& str) {
	for (char c : str) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}

bool checkLuhn(string& cardNumber) {
	int sum = 0;
	bool alternate = false;

	// Traverse the card number from right to left
	for (int index = cardNumber.size() - 1; index >= 0; --index) {
		int num = cardNumber[index] - '0';

		if (alternate) {
			num *= 2;
			if (num > 9) {
				num -= 9;
			}
		}

		sum += num;
		alternate = !alternate;
	}

	return (sum % 10 == 0);
}

bool validateCard() {

	string cardNumber;
	bool valid = false;

	do
	{
		// Input the card number as a string
		cout << "Enter the card number: ";
		cin >> cardNumber;

		if (!isDigitString(cardNumber)) {
			cout << "Invalid input. The card number should contain only digits." << endl;
		}
		else if (cardNumber.length() != 13 && cardNumber.length() != 15 && cardNumber.length() != 16) {
			cout << "Invalid input. The card number should contain only 13, 15,or 16 digits." << endl;
		}
		else if (!checkLuhn(cardNumber)) {
			cout << "The card number is invalid." << endl;
		}
		else {
			valid = true;
			cout << "The card number is valid." << endl;
		}
		cin.clear(); // Clear the failbit
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input

	} while (valid == false);

	return valid;
}

bool validateOnlinePayment() {

	const string ONLINEPAYMENTLPATH = "onlinePaymentUsername\\";
	string onlinePaymentPasswordFile = "";

	bool isValid = false;
	string onlinePaymentUsername;
	string onlinePaymentPassword;

	do
	{
		cout << "\nEnter your online payment account username : ";
		cin >> onlinePaymentUsername;
		ifstream read(ONLINEPAYMENTLPATH + onlinePaymentUsername + ".txt");

		if (!read) {
			cout << "Payment account does not exist. Please try again.\n\n";
			cin.clear(); // Clear the failbit
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
		}
		else {
			do
			{
				cout << "Enter your password : ";
				cin >> onlinePaymentPassword;
				getline(read, onlinePaymentPasswordFile);
				if (onlinePaymentPassword == onlinePaymentPasswordFile) {
					cout << "Online payment account login successful!" << endl;
					isValid = true;
				}
				else {
					cout << "Incorrect online payment password. Please try again." << endl;
					cin.clear(); // Clear the failbit
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
				}
			} while (onlinePaymentPassword != onlinePaymentPasswordFile);
		}
	} while (isValid == false);

	return isValid;
}

bool validateEWallet() {
	const string EWALLETLPATH = "eWalletNumPin\\";
	string eWalletNumPinFile = "";

	bool isValid = false;
	string eWalletNum;
	string eWalletPin;


	// Define regular expression
	regex pattern = regex(R"(^01(1|2|3|4|6|8|9)(\d){7,8}$)");

	do
	{
		cout << "\nEnter your e-wallet number : ";
		cin >> eWalletNum;
		ifstream read(EWALLETLPATH + eWalletNum + ".txt");

		if (!regex_match(eWalletNum, pattern)) {
			cout << "E-Wallet number is invalid.\n";
		}
		else if (!read) {
			cout << "Incorrect E-Wallet Number. Please try again.\n\n";
		}
		else
		{
			do
			{
				cout << "Enter your 6-digit pin : ";
				cin >> eWalletPin;

				getline(read, eWalletNumPinFile);
				if (eWalletPin == eWalletNumPinFile) {
					cout << "E-Wallet verify successful!" << endl;
					isValid = true;
				}
				else {
					cout << "Incorrect E-Wallet pin. Please try again." << endl;
					cin.clear(); // Clear the failbit
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
				}
			} while (isValid == false);
		}
		cin.clear(); // Clear the failbit
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
	} while (isValid == false);
	return isValid;
}


void printBill(Booking newBooking, string& userId, string weekChoice, string staffName, string dayOfWeek, string memberType, bool memberExists, double discountRate) {

	const string PRINTPATH = "printBill/" + newBooking.bill_Id + ".txt";
	char checkPrint;
	string serviceName = "", custName, custTel, custEmail, readLine;

	if (newBooking.serviceType == "C")
	{
		serviceName = "Consultation";
	}
	else if (newBooking.serviceType == "T1")
	{
		serviceName = "Manicure & Pedicure";
	}
	else if (newBooking.serviceType == "T2")
	{
		serviceName = "Facial Treatment";
	}
	else if (newBooking.serviceType == "T3")
	{
		serviceName = "Haircut";
	}

	serviceName += " with " + staffName;

	getCustData(custName, custTel, custEmail, userId);

	ofstream writePrint(PRINTPATH);
	writePrint << "------------------------------------------------------" << endl;
	writePrint << setw(31) << "Receipt" << setw(23) << endl;
	writePrint << "------------------------------------------------------" << endl;
	writePrint << "Booking No: " << newBooking.bill_Id << endl;
	writePrint << "\nCustomer details: " << endl;
	writePrint << "\nCustomer Name: " << custName << endl;
	writePrint << "Customer Telephone: " << custTel << endl;
	writePrint << "Customer Email: " << custEmail << endl;
	writePrint << "\nDetails of service booking:\n" << endl;
	writePrint << "Service name: " << serviceName << endl;
	writePrint << "Appointment date: " << newBooking.appointmentDate << endl;
	writePrint << "Appointment time: " << newBooking.appointmentTime << endl;
	if (memberExists) {
		writePrint << "\nMembership type: " << memberType << endl;
		writePrint << "Member discount: " << fixed << setprecision(0) << (discountRate * 100) << "%" << endl;
	}
	writePrint << fixed << setprecision(2) << showpoint << "\nTotal Amount: RM " << newBooking.amount << endl;

	do {
		system("cls");
		displayMiniLogo();
		cout << "Do you want to print your bill?" << endl;
		cout << "\nEnter 'Y' to confirm or 'N' to cancel: ";
		cin >> checkPrint;
		cout << "\n";

		checkPrint = toupper(checkPrint);

		if (checkPrint == 'Y') {
			ifstream read(PRINTPATH);
			while (getline(read, readLine)) {
				cout << readLine << endl;
			}
			cout << "\nYour bill has been printed successfully." << endl;
			cout << "Thank you for using our service!\n" << endl;
		}
		else if (checkPrint == 'N') {
			cout << "\nThank you for using our service!\n" << endl;
		}
		else {
			cout << "\nInvalid input. Please try again." << endl;
		}

	} while (checkPrint != 'Y' && checkPrint != 'N');
}

void getCustData(string& custName, string& custTel, string& custEmail, string userId) {

	const string PROFILEPATH = "userData\\";
	ifstream read(PROFILEPATH + userId + ".dat");
	if (!read) {
		cout << "Error opening" << userId << "file." << endl;
		return;
	}

	// Read each line from the file into the respective variables
	getline(read, custName);
	getline(read, custTel);
	getline(read, custEmail);

	read.close();
}

void saveBookingData(string& filePath, Booking& newBooking) {
	ofstream write(filePath, ios::app);
	ofstream save("booking\\bookingID.txt", ios::app);
	if (!write && !save) {
		cout << "Error opening file for writing." << endl;
		return;
	}

	write << "Slot " << newBooking.slot << " " << newBooking.cust_Id << " " << newBooking.bill_Id << " " << newBooking.staff_Id << " " << newBooking.serviceType << " " << newBooking.appointmentDate << " " << newBooking.appointmentTime << " " << newBooking.amount << "\n";
	write.close();
	save << endl << newBooking.bill_Id;
	save.close();
	cout << "Booking slot added successfully." << endl;
}

void dispSalesReport() {

	const int STAFF_COUNT = 3;
	const int MAX_BOOKINGS = 100;
	const int BOOKING_FIELDS = 10;
	string bookingFolder = "booking";
	string staffFolders[STAFF_COUNT] = { "Emily Parker", "Olivia Brooks", "Jack Morgan" };
	string** bookingData = new string * [MAX_BOOKINGS];
	for (int index = 0; index < MAX_BOOKINGS; ++index) {
		bookingData[index] = new string[BOOKING_FIELDS];
	}

	int countBookings = 0; // number of bookings
	system("cls");
	displayMiniLogo();

	cout << right << " ____________________________________________________________________________________________________" << "\n"
		<< "|" << setw(100) << " " << "|\n"
		<< "|" << setw(66) << "Sales Report for September 2024" << setw(36) << "|\n"
		<< "|" << setw(100) << " " << "|\n"
		<< "|" << "====================================================================================================" << "|\n"
		<< "|" << setw(3) << "No." << "|" << setw(12) << "Customer ID" << "|" << setw(11) << "Booking ID"
		<< "|" << setw(9) << "Staff ID" << "|" << setw(13) << "Service Type" << "|" << setw(17) << "Appointment Date"
		<< "|" << setw(17) << "Appointment Time" << "|" << setw(11) << "Amount(RM)" << "|" << "\n"
		<< "|" << "====================================================================================================" << "|\n";

	for (int i = 0; i < STAFF_COUNT; ++i) {
		string staffFolder = bookingFolder + "/" + staffFolders[i];
		readAllBooking(staffFolder, bookingData, countBookings, MAX_BOOKINGS, BOOKING_FIELDS);
	}

	dispBookingData(bookingData, countBookings);

	// Clean up memory
	for (int i = 0; i < MAX_BOOKINGS; ++i) {
		delete[] bookingData[i];  // Delete each row
	}
	delete[] bookingData;  // Delete the array of pointers

	system("pause");
	system("cls");
}

void readAllBooking(string& staffFolder, string** bookingData, int& countBookings, int MAX_BOOKINGS, int BOOKING_FIELDS) {

	const int BOOKING_FILE = 5;
	const string WEEKFILES[BOOKING_FILE] = { "w1.txt", "w2.txt" , "w3.txt" , "w4.txt" ,"w5.txt" };
	string readLine;

	for (int i = 0; i < BOOKING_FILE; ++i) {
		string bookingDetailFiles = staffFolder + "/" + WEEKFILES[i];
		ifstream read(bookingDetailFiles);
		if (!read) {
			cout << "Error opening file: " << bookingDetailFiles << endl;
			continue;
		}
		else {
			while (getline(read, readLine) && countBookings < MAX_BOOKINGS) {
				istringstream readDetails(readLine);

				for (int col = BOOKING_FIELDS - 1; col >= 0; col--) {
					readDetails >> bookingData[countBookings][col];
				}

				countBookings++;
			}
		}
		read.close();
	}
}

void dispBookingData(string** bookingData, int& countBookings) {

	string stringAmount;
	double amount, totalAmount = 0.0;
	int countStaff1 = 0, countStaff2 = 0, countStaff3 = 0;

	for (int row = 0; row < countBookings; row++) {
		int col = 1;
		cout << fixed << setprecision(2) << showpoint << "|" << setw(3) << (row + 1)
			<< "|" << setw(12) << bookingData[row][col++]  // Customer ID 7
			<< "|" << setw(11) << bookingData[row][col++]  // Booking ID 6
			<< "|" << setw(9) << bookingData[row][col++] // Staff ID 5
			<< "|" << setw(13) << bookingData[row][col++]  // Service Type 4
			<< "|" << setw(17) << bookingData[row][col++]  // Appointment Date 3
			<< "|" << setw(17) << bookingData[row][col++]  // Appointment Time 2
			<< "|" << setw(11) << bookingData[row][col++] << "|" << endl; // Amount 1

		if (bookingData[row][5] == "S103") {
			countStaff1++;
		}
		else if (bookingData[row][5] == "S112") {
			countStaff2++;
		}
		else if (bookingData[row][5] == "S113") {
			countStaff3++;
		}

		amount = stod(bookingData[row][1]); // convert string to double
		totalAmount += amount;
	}

	cout << "|====================================================================================================|" << endl;

	int famousStaff = countStaff1;


	if (countStaff2 > famousStaff) {
		famousStaff = countStaff2;
	}
	if (countStaff3 > famousStaff) {
		famousStaff = countStaff3;
	}

	cout << "|" << setw(90) << "Total amount| " << setw(10) << totalAmount << "|" << endl;
	cout << "|====================================================================================================|" << endl;

	cout << "|The most famous expert:" << setw(78) << "|" << endl;
	if (countStaff1 == famousStaff) {
		cout << left << setw(15) << "|Emily Parker" << right << setw(87) << "|" << endl;
	}
	if (countStaff2 == famousStaff) {
		cout << left << setw(15) << "|Olivia Brooks" << right << setw(87) << "|" << endl;
	}
	if (countStaff3 == famousStaff) {
		cout << left << setw(15) << "|Jack Morgan" << right << setw(87) << "|" << endl;
	}
	cout << "|====================================================================================================|\n" << endl;

}

void dispBooking(string& userId) {

	system("cls");
	displayMiniLogo();

	const int STAFF_COUNT = 3, MAX_BOOKINGS = 100, BOOKING_COL = 10;
	const string CREDENTIALPATH = "userCredential\\", PROFILEPATH = "userData\\";
	string usernameFile, userIdFile, userIdGet;
	string bookingFolder = "booking", bookingId;
	string staffFolders[STAFF_COUNT] = { "Emily Parker", "Olivia Brooks", "Jack Morgan" };
	string** userBookingData = new string * [MAX_BOOKINGS];
	for (int index = 0; index < MAX_BOOKINGS; ++index) {
		userBookingData[index] = new string[BOOKING_COL];
	}
	int countBookings = 0;
	char cancelChoice, returnChoice;
	bool delBooking = false, userExist = false, continueProgram = true;

	while (continueProgram) {
		if (userId[0] == 'S' || userId[0] == 'A') {
			getIdByUsername(userIdGet);
		}
		else
		{
			userIdGet = userId;
		}

		usernameFile = PROFILEPATH + userIdGet + ".dat";

		if (userProfileExists(usernameFile)) {
			userExist = true;
			break;
		}
		else {

			userExist = false;

			do {
				system("cls");
				displayMiniLogo();
				cout << "\nDo you want to enter another username? [ENTER Y / N ONLY]: ";
				cin >> returnChoice;
				returnChoice = toupper(returnChoice);
				cout << "\n";

			} while (returnChoice != 'Y' && returnChoice != 'N');

			if (returnChoice == 'N') {
				break;
				return;
			}
		}
	}

	system("cls");

	if (userExist) {
		displayMiniLogo();

		UserProfile userProfile;

		readUserProfile(userProfile, usernameFile);
		displayUserProfile(userProfile);

		cout << "\nFinding user's booking in files." << endl;
		cout << "\n";

		cout << right << " _______________________________________________________________________________________" << "\n"
			<< "|" << setw(87) << " " << "|\n"
			<< "|" << setw(52) << "Booking Details" << setw(37) << "|\n"
			<< "|" << setw(87) << " " << "|\n"
			<< "|" << "=======================================================================================" << "|\n"
			<< "|" << setw(3) << "No." << "|" << setw(11) << "Booking ID"
			<< "|" << setw(9) << "Staff ID" << "|" << setw(13) << "Service Type" << "|" << setw(17) << "Appointment Date"
			<< "|" << setw(17) << "Appointment Time" << "|" << setw(11) << "Amount(RM)" << "|" << "\n"
			<< "|" << "=======================================================================================" << "|\n";

		for (int i = 0; i < STAFF_COUNT; ++i) {
			string staffFolder = bookingFolder + "/" + staffFolders[i];
			processBooking(staffFolder, userIdGet, userBookingData, delBooking, bookingId, countBookings, MAX_BOOKINGS, BOOKING_COL);
		}

		dispUserBookingData(userBookingData, countBookings);

		if (userId[0] == 'S' || userId[0] == 'A') {

			do {

				cout << "\nDo you want to cancel any booking? [ Y / N ]: ";
				cin >> cancelChoice;
				cancelChoice = toupper(cancelChoice);
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				if (cancelChoice != 'Y' && cancelChoice != 'N') {

					cout << "Enter Y or N only. Please try again.\n" << endl;
				}

			} while (cancelChoice != 'Y' && cancelChoice != 'N');

			if (cancelChoice == 'Y') {
				delBooking = true;
				do {

					cout << "\nEnter the booking ID to cancel (e.g., B001): ";
					cin >> bookingId;

					if (!isValidBookingId(bookingId)) {
						cout << "Invalid booking ID. Please try again." << endl;
					}

				} while (!isValidBookingId(bookingId));
			}

			if (delBooking) {
				for (int i = 0; i < STAFF_COUNT; ++i) {
					string staffFolder = bookingFolder + "/" + staffFolders[i];
					processBooking(staffFolder, userIdGet, userBookingData, delBooking, bookingId, countBookings, MAX_BOOKINGS, BOOKING_COL);
				}
			}
		}

		cout << endl;

		// Clean up memory
		for (int i = 0; i < MAX_BOOKINGS; ++i) {
			delete[] userBookingData[i];  // Delete each row
		}
		delete[] userBookingData;  // Delete the array of pointers

		system("pause");
		system("cls");

	}
}

void getIdByUsername(string& userIdGet) {

	string usernameInput, readLine, filepath = "";
	bool validInput = false;
	regex numbers(R"(^\d+$)"), symbols((R"([!@#$%^&*+-<>?])")), validUsername(R"(^(\w+){3,}$)");
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	do {
		cout << "Enter username: "; // Check user id by username
		getline(cin, usernameInput);

		if (usernameInput.empty()) {
			cout << "Username cannot be empty.\n" << endl;
		}
		else if (regex_match(usernameInput, numbers)) {
			cout << "Username cannot be only numbers.\n" << endl;
		}
		else if (regex_search(usernameInput, symbols)) {
			cout << "Username cannot contain symbols.\n" << endl;
		}
		else if (!regex_match(usernameInput, validUsername)) {
			cout << "Username should be at least three characters.\n" << endl;
		}
		else {
			validInput = true;
		}
	} while (!validInput);

	filepath = "userCredential\\" + usernameInput + ".txt";

	ifstream read(filepath);
	if (!read) {
		cout << "Username does not exist.\n" << endl;
		system("pause");
		return;
	}
	else {
		read >> userIdGet;
	}
	read.close();
}

bool userProfileExists(string& usernameFile) {

	ifstream read(usernameFile);
	return read.good();

}

void processBooking(string& staffFolder, string& userId, string** userBookingData, bool& delBooking, string& bookingId, int& countBookings, int MAX_BOOKINGS, int BOOKING_COL) {

	const int BOOKING_FILE = 5;
	const string WEEKFILES[BOOKING_FILE] = { "w1.txt", "w2.txt" , "w3.txt" , "w4.txt" ,"w5.txt" };
	string readLine;
	bool delStatus = false, foundBooking = false;

	for (int i = 0; i < BOOKING_FILE; ++i) {
		string bookingDetailFiles = staffFolder + "/" + WEEKFILES[i];
		ifstream read(bookingDetailFiles);
		if (!read) {
			cout << "Error opening file: " << bookingDetailFiles << endl;
			continue;
		}
		else {
			if (!delBooking) {
				while (getline(read, readLine)) {

					if (!userId.empty() && readLine.find(userId) != string::npos) { // check whether user id is exist in booking week file or not

						istringstream readBookData(readLine);

						for (int col = BOOKING_COL - 1; col >= 0; col--) {
							readBookData >> userBookingData[countBookings][col];
						}

						countBookings++;

					}
				}
				read.close();
			}
			else {

				string tempFile = staffFolder + "/temp.txt";
				ofstream write(tempFile);

				while (getline(read, readLine)) {
					if (readLine.find(bookingId) != string::npos) {
						foundBooking = true;
						continue;
					}
					write << readLine << endl;
				}
				write.close();
				read.close();

				if (foundBooking) {
					if (remove(bookingDetailFiles.c_str()) == 0) {
						if (rename(tempFile.c_str(), bookingDetailFiles.c_str()) == 0) {
							delStatus = true;
						}
						else {
							cout << "Failed to rename temporary file to " << bookingDetailFiles << endl;
						}
					}
					else {
						cout << "Failed to delete " << bookingDetailFiles << endl;
					}
				}
			}
		}
	}
	if (delBooking && delStatus) {
		cout << "Booking ID " << bookingId << " successfully cancelled." << endl;
	}
}

void dispUserBookingData(string** userBookingData, int& countBookings) {

	int countStaff1 = 0, countStaff2 = 0, countStaff3 = 0;

	for (int row = 0; row < countBookings; row++) {

		cout << fixed << setprecision(2) << showpoint << "|" << setw(3) << (row + 1)
			<< "|" << setw(11) << userBookingData[row][6]  // Booking ID 6
			<< "|" << setw(9) << userBookingData[row][5] // Staff ID 5
			<< "|" << setw(13) << userBookingData[row][4]  // Service Type 4
			<< "|" << setw(17) << userBookingData[row][3]  // Appointment Date 3
			<< "|" << setw(17) << userBookingData[row][2]  // Appointment Time 2
			<< "|" << setw(11) << fixed << setprecision(2) << userBookingData[row][1] << "|" << endl; // Amount 1
	}

	cout << "|=======================================================================================|" << endl;

}

bool isValidBookingId(string& bookingId) {

	if (bookingId.length() == 4 && bookingId[0] == 'B') {

		for (int i = 1; i < 4; ++i) {
			if (!isdigit(bookingId[i])) {
				return false;
			}
		}
		return true;
	}
	return false;
}

void membership(string& userId) {

	const string MEMBERSHIP_PATH = "membership/" + userId + ".txt";
	char choice;
	UserProfile userProfile;

	system("cls");

	displayMiniLogo();
	checkMember(userId, MEMBERSHIP_PATH);

	do {

		cout << "\nWould you want to purchase another membership or renew your membership? [ Y / N ]: ";
		cin >> choice;
		choice = toupper(choice);

		if (choice != 'Y' && choice != 'N') {
			cout << "Enter 'Y' OR 'N' only." << endl;
		}

	} while (choice != 'Y' && choice != 'N');

	if (choice == 'Y') {
		purOrRenewMembership(userId, MEMBERSHIP_PATH);
	}

	cout << "\n";

	system("pause");
	system("cls");
}

void checkMember(string& userId, string MEMBERSHIP_PATH) {

	ifstream read(MEMBERSHIP_PATH);
	string readLine, memberType, purchaseDate, expiryDate, discountRate;

	if (read) {

		cout << "\nMembership details: " << endl;

		getline(read, memberType);
		getline(read, discountRate);
		getline(read, purchaseDate);
		getline(read, expiryDate);

		cout << "\nMembership Type\t: " << memberType << endl;
		cout << "Purchase Date\t: " << purchaseDate << endl;
		cout << "Expiry Date\t: " << expiryDate << endl;

	}
	else {
		cout << "\nYou haven't purchased any memberships yet." << endl;
	}
}

void purOrRenewMembership(string& userId, string MEMBERSHIP_PATH) {

	int choice, memberPrice = 0;
	double discountRate = 0.0;
	char checkPur, memberChoice = ' ';
	string memberType, lastExpiryDate, readLine;
	string purchaseDate = runClock(DATETIME);
	string expiryDate = runClock(EXPIRY);
	bool validPayment = false;

	ifstream readMember(MEMBERSHIP_PATH);

	bool memberExists = false;

	if (readMember) {
		memberExists = true;
		for (int count = 0; count < 4; count++)
		{
			getline(readMember, readLine);
		}
		lastExpiryDate = readLine;

		readMember.close();

		if (!isExpired(lastExpiryDate)) {
			system("cls");
			displayMiniLogo();
			cout << "\nYour membership is still active and will expire on: " << lastExpiryDate << endl;
			cout << "\nYou cannot change or renew your membership until it expires." << endl;
			return;
		}
		else {
			system("cls");
			displayMiniLogo();
			cout << "\nYour membership expired on: " << lastExpiryDate << endl;

			do {
				cout << "\nDo you want to renew the same membership type or change to other type?" << endl;
				cout << "\nEnter your choice [ R = Renew, C = Change, N = Skip ]: ";
				cin >> memberChoice;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				memberChoice = toupper(memberChoice);

				if (memberChoice != 'R' && memberChoice != 'C' && memberChoice != 'N') {
					cout << "Invalid input. Try again." << endl;
				}

			} while (memberChoice != 'R' && memberChoice != 'C' && memberChoice != 'N');
		}
	}

	if (memberChoice == 'N') {
		cout << "\nNo membership has been changed or renewed." << endl;
	}
	else if (memberChoice == 'C' || !memberExists) {
		system("cls");
		displayMiniLogo();
		cout << "\nSelect membership type:" << endl;
		cout << "1. Silver membership" << endl;
		cout << "2. Gold membership" << endl;
		cout << "3. Platinum membership" << endl;
		cout << "\nEnter the number of the membership type [ 1 - 3 ]: ";
		getChoice(choice);

		switch (choice) {
		case 1: memberType = "Silver"; discountRate = 0.1; memberPrice = 50; break;
		case 2: memberType = "Gold"; discountRate = 0.15; memberPrice = 90; break;
		case 3: memberType = "Platinum"; discountRate = 0.20; memberPrice = 150;  break;
		default: cout << "Invalid number. Try again." << endl;
			return;
		}
	}
	else if (memberChoice == 'R') {

		ifstream read(MEMBERSHIP_PATH);
		getline(read, memberType);
		read.close();

		if (memberType == "Silver") {
			discountRate = 0.1;
			memberPrice = 50;
		}
		else if (memberType == "Gold") {
			discountRate = 0.15;
			memberPrice = 90;
		}
		else if (memberType == "Platinum") {
			discountRate = 0.20;
			memberPrice = 150;
		}
	}

	if (memberChoice != 'N')
	{
		cout << "\nMembership details: " << endl;
		cout << "\nMembership Type\t: " << memberType << endl;
		cout << "Purchase Date\t: " << purchaseDate << endl;
		cout << "Expiry Date\t: " << expiryDate << endl;
		cout << "Member Price\t: RM" << memberPrice << endl;

		do {
			cout << "\nEnter 'Y' to confirm purchase or 'N' to cancel: ";
			cin >> checkPur;

			checkPur = toupper(checkPur);

			if (checkPur == 'Y') {
				system("cls");
				displayMiniLogo();
				int payMethod = paymentMethod();
				switch (payMethod) {
				case 1:
					validPayment = validateCard();
					system("pause");
					break;
				case 2:
					validPayment = validateOnlinePayment();
					system("pause");
					break;
				case 3:
					validPayment = validateEWallet();
					system("pause");
					break;
				default:
					validPayment = false;
				}
				bool checkPay = confirmMember(payMethod, userId, memberPrice);

				if (checkPay == true && validPayment == true) {
					ofstream write(MEMBERSHIP_PATH);

					if (write) {
						write << memberType << endl;
						write << discountRate << endl;
						write << purchaseDate << endl;
						write << expiryDate << endl;
						write.close();
					}
					cout << "\nMembership confirmed successfully!" << endl;
				}
				else {
					cout << "\nMembership canceled." << endl;
				}
			}
			else if (checkPur == 'N') {
				cout << "\nMembership canceled." << endl;
			}
			else {
				cin.clear(); // Clear the failbit
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
				cout << "Invalid input! Please enter again..\n";
			}
		} while (checkPur != 'Y' && checkPur != 'N');
	}

}

bool isExpired(string& expiryDate) {

	int expiryDay, expiryMonth, expiryYear, currentDay, currentMonth, currentYear;
	string currentDate = runClock(DATETIME);

	splitDate(expiryDate, expiryDay, expiryMonth, expiryYear);
	splitDate(currentDate, currentDay, currentMonth, currentYear);

	if (currentYear < expiryYear) { // compare year 
		return false; // active
	}
	else if (currentYear > expiryYear) {
		return true; // expired
	}
	else if (currentMonth < expiryMonth) { // compare month if year is same
		return false; // active
	}
	else if (currentMonth > expiryMonth) {
		return true; // expired
	}
	else if (currentDay < expiryDay) { //compare day if month is same
		return false; // active
	}
	else if (currentDay > expiryDay) {
		return true; // expired
	}
	else {
		return true; // expired
	}

}

void splitDate(string& date, int& day, int& month, int& year) {

	char symbol;

	stringstream split(date);
	split >> day >> symbol >> month >> symbol >> year;

}

bool confirmMember(int payMethod, string userId, int memberPrice) {
	system("cls");
	displayMiniLogo();
	string custName, custTel, custEmail;
	char checkPay;

	cout << "Selected payment process: \n" << endl;
	if (payMethod == 1) {
		cout << "Credit/Debit Card Payment Selected.\n" << endl;
	}
	else if (payMethod == 2) {
		cout << "Online Payment Transfer Selected.\n" << endl;
	}
	else if (payMethod == 3) {
		cout << "eWallet Payment Selected.\n" << endl;
	}

	getCustData(custName, custTel, custEmail, userId);
	cout << "Customer details: \n" << endl;
	cout << "Customer Name: " << custName << endl;
	cout << "Customer Telephone: " << custTel << endl;
	cout << "Customer Email: " << custEmail << "\n" << endl;
	cout << "Member Price: RM" << memberPrice << endl;

	do {
		cout << "\nEnter 'Y' to confirm membership or 'N' to cancel: ";
		cin >> checkPay;

		checkPay = toupper(checkPay);

		if (checkPay != 'Y' && checkPay != 'N') {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input! Please enter again..\n";
		}
	} while (checkPay != 'Y' && checkPay != 'N');

	if (checkPay == 'Y') {
		return true;
	}
	return false;
}

void viewCustomerList() {

	const int MAXSIZE = 101;
	const string PROFILEPATH = "userData\\";
	int choice, recordCount = 0, page = 0, lowerbound, upperbound, searchChoice = 0, searchCall = 0;
	string userId[11], lastId = "", * sortedId = new string[MAXSIZE], filter[6];
	UserProfile userProfile[11], * sortedProfile = new UserProfile[MAXSIZE];
	char prefix = ' ';
	bool sortCall = false;

	do
	{
		system("cls");
		displayMiniLogo();
		cout << "Select a user type\n" << endl;
		cout << "User Type" << endl;
		cout << "=======================" << endl;
		cout << "[1] Customer\n[2] Staff\n[3] Admin\n[4] All type\n[9] Main Menu\n";

		getChoice(choice);

		switch (choice)
		{
		case 1: prefix = 'C'; break;
		case 2: prefix = 'S'; break;
		case 3: prefix = 'A'; break;
		case 4: prefix = ' '; break;
		case 9: delete[] sortedId; delete[] sortedProfile; system("cls"); return;
		default: invalidChoice();
		}
	} while ((choice < 1 || choice > 4) && choice != 9);

	int userIdSize = sizeof(userId) / sizeof(userId[0]) - 1;

	readUserId(PROFILEPATH, recordCount, userId, prefix, lastId, userIdSize);
	readUserList(PROFILEPATH, recordCount, userId, userProfile, userIdSize);

	do {
		system("cls");

		if (sortCall)
		{
			for (int index = 0; index < 10; index++)
			{
				userId[index] = sortedId[index + page * 10];
				userProfile[index] = sortedProfile[index + page * 10];
			}
		}

		if (userId[0].empty()) // If the next page is empty, stop displaying
		{
			lastId.clear();
		}

		displayCustomerList(recordCount, userId, userProfile, page);
		lowerbound = page * 10 + 1;
		upperbound = page * 10 + recordCount;

		if (lastId.empty())
		{
			cout << "\nYou have reached the end of list.\n\n" << endl;
			delete[] sortedId;
			delete[] sortedProfile;
			system("pause");
			system("cls");
			return;
		}

		if (searchCall > 0)
		{
			cout << "Filters applied : ";
			for (int index = 0; index < 6; index++)
			{
				cout << filter[index] << " ";
			}
			cout << "\n\n";
		}

		cout << "Options" << endl;
		cout << "=======================" << endl;
		cout << "[1] Next page\n[2] View Profile\n[3] Search\n[4] Sort\n[9] Main Menu" << endl;

		getChoice(choice);

		system("cls");

		switch (choice)
		{
		case 1: if (!lastId.empty()) // If there are IDs to read
		{
			if (!sortCall && searchCall == 0)
			{
				recordCount = 0;
				readUserId(PROFILEPATH, recordCount, userId, prefix, lastId, userIdSize);
				readUserList(PROFILEPATH, recordCount, userId, userProfile, userIdSize);
			}
			else if (searchCall > 0)
			{
				searchList(PROFILEPATH, userIdSize, userId, userProfile, prefix, recordCount, lastId, searchChoice, filter);
			}
			page++;
		}
			  break;
		case 2:
			do
			{
				displayCustomerList(recordCount, userId, userProfile, page);
				cout << "\nChoose the profile you want (number only)";
				getChoice(choice);

				if (choice < lowerbound || choice > upperbound) {
					cout << "Enter number within the range given on the list.\n\n";
					system("pause");
					system("cls");
				}
			} while (choice < lowerbound || choice > upperbound);

			system("cls");
			displayUserProfile(userProfile[choice - 1 - page * 10]);
			system("pause");
			system("cls");
			break;
		case 3:
			if (searchCall == 0)
			{
				page = 0;
				sortCall = false;
				searchCall++;
				lastId = "";
				searchList(PROFILEPATH, userIdSize, userId, userProfile, prefix, recordCount, lastId, searchChoice, filter);
			}
			else
			{
				searchResult(PROFILEPATH, userId, userProfile, recordCount, filter);
			}
			break;
		case 4:
			page = 0;
			if (searchCall == 0) // if search is not performed
			{
				sortCall = true;
				searchCall = 0;
				sortList(PROFILEPATH, prefix, sortedId, sortedProfile, MAXSIZE - 1);
			}
			else
			{
				sortCall = false;
				sortResult(recordCount, userId, userProfile);
			}
			break;
		case 9: break;
		default: displayCustomerList(recordCount, userId, userProfile, page); invalidChoice();
		}

	} while (choice != 9);
	delete[] sortedId;
	delete[] sortedProfile;
}

void readUserList(string PROFILEPATH, int recordCount, string userId[], UserProfile userProfile[], int userIdSize) {

	ifstream profileRead;
	string userFile = "";

	// Clear the array before reading the next batch
	clearArray(userProfile, userIdSize);

	for (int row = 0; row <= recordCount; row++)
	{
		if (!userId[row].empty())
		{
			userFile = PROFILEPATH + userId[row] + ".dat";
			profileRead.open(userFile);
			if (!profileRead)
			{
				cerr << "Error opening file." << endl;
			}
			else {
				readUserProfile(userProfile[row], userFile);
			}
			profileRead.close();
		}
	}
}

void displayCustomerList(int recordCount, string userId[], UserProfile userProfile[], int page) {

	displayMiniLogo();
	cout << "\nNo\t| " << left << setw(25) << "Name" << " | Contact Number\t\t| Email\t\t" << endl;
	cout << "============================================================================================\n";
	for (int row = 0; row <= recordCount; row++)
	{
		if (!userId[row].empty()) {
			displayListData(row, page, userProfile[row]);
		}
	}
	cout << endl;
}

void displayListData(int row, int page, UserProfile userProfile) {
	cout << left << row + 1 + page * 10 << "\t| " << setw(25) << userProfile.name << " | " << userProfile.contact << "\t\t| " << userProfile.email << endl;
}

void searchList(string PROFILEPATH, int userIdSize, string userId[], UserProfile userProfile[], char prefix, int& recordCount, string& lastId, int& choice, string filter[]) {

	const int PAGESIZE = 11;
	int count = 0;
	bool foundData = false;
	DataField data = NAME;
	string resultId[PAGESIZE], bufferId[PAGESIZE];
	UserProfile resultProfile[PAGESIZE], bufferProfile[PAGESIZE];
	ifstream read;

	for (int index = 0; index < userIdSize; index++)
	{
		bufferId[index] = userId[index]; // save the data before search
		bufferProfile[index] = userProfile[index];
	}

	if (choice == 0)
	{
		do
		{
			displayCustomerList(recordCount, userId, userProfile, 0);
			searchOption(data, choice);
		} while (choice < 1 || choice > 6);

		getFilter(choice, filter);
	}

	do
	{
		recordCount = 0;
		readUserId(PROFILEPATH, recordCount, userId, prefix, lastId, userIdSize);
		readUserList(PROFILEPATH, recordCount, userId, userProfile, userIdSize);

		filterResult(PAGESIZE, data, recordCount, filter, choice, userId, userProfile, resultId, resultProfile, foundData, count);

	} while (!lastId.empty() && count < 9); // Continue until no more IDs to read

	recordCount = count;

	if (!foundData)
	{
		cout << "\n\n\nNo data matches the filter applied." << endl;
		for (int index = 0; index < recordCount; index++)
		{
			userId[index] = bufferId[index]; // retrieve the data before search
			userProfile[index] = bufferProfile[index];
			filter[choice - 1].clear();
		}
	}
	else
	{
		for (int index = 0; index < recordCount; index++)
		{
			userId[index] = resultId[index];
			userProfile[index] = resultProfile[index];
		}
	}

	// don't know why the part in readUserId won't work properly
	if (recordCount > 0)
	{
		lastId = userId[recordCount - 1];
	}
	else
	{
		lastId.clear();
	}

	if (!foundData)
	{
		system("pause");
	}

	system("cls");
}

void searchOption(DataField& data, int& choice) {

	cout << "Search by: \n[1] User Id\n[2] Username\n[3] Name\n[4] Contact\n[5] Email\n[6] Age";

	getChoice(choice);

	if (choice < 1 || choice > 6)
	{
		invalidChoice();
	}

	switch (choice)
	{
	case 1: data = USERID; break;
	case 2: data = USERNAME; break;
	case 3: data = NAME; break;
	case 4: data = CONTACT;	break;
	case 5: data = EMAIL; break;
	case 6: data = AGE;
	}
}

void getFilter(int choice, string filter[]) {

	if (choice == 1)
	{
		cout << "Enter user ID: ";
		cin.ignore();
		getline(cin, filter[choice - 1]);
	}
	else if (choice == 2)
	{
		getIdByUsername(filter[choice - 1]);
	}
	else if (choice == 3)
	{
		cout << "Enter name: ";
		cin.ignore();
		getline(cin, filter[choice - 1]);
	}
	else if (choice == 4)
	{
		cout << "Enter contact number: ";
		cin.ignore();
		getline(cin, filter[choice - 1]);
	}
	else if (choice == 5)
	{
		cout << "Enter email: ";
		cin.ignore();
		getline(cin, filter[choice - 1]);
	}
	else if (choice == 6)
	{
		cout << "Enter age: ";
		cin.ignore();
		getline(cin, filter[choice - 1]);
	}
}

void filterResult(int PAGESIZE, DataField data, int recordCount, string filter[], int choice, string userId[], UserProfile userProfile[], string resultId[], UserProfile resultProfile[], bool& foundData, int& count) {

	switch (data)
	{
	case USERID: case USERNAME:

		for (int index = 0; index < recordCount; index++)
		{
			if (count < PAGESIZE - 1) {
				if (userId[index].find(filter[choice - 1]) != string::npos)
				{
					resultId[count] = userId[index];
					resultProfile[count] = userProfile[index];
					count++;
					foundData = true;
				}
			}
		}
		break;
	case NAME:
		for (int index = 0; index < recordCount; index++)
		{
			if (count < PAGESIZE - 1) {
				if (userProfile[index].name.find(filter[choice - 1]) != string::npos)
				{
					resultId[count] = userId[index];
					resultProfile[count] = userProfile[index];
					count++;
					foundData = true;
				}
			}
		}
		break;
	case CONTACT:
		for (int index = 0; index < recordCount; index++)
		{
			if (count < PAGESIZE - 1) {
				if (userProfile[index].contact.find(filter[choice - 1]) != string::npos)
				{
					resultId[count] = userId[index];
					resultProfile[count] = userProfile[index];
					count++;
					foundData = true;
				}
			}
		}
		break;
	case EMAIL:
		for (int index = 0; index < recordCount; index++)
		{
			if (count < PAGESIZE - 1) {
				if (userProfile[index].email.find(filter[choice - 1]) != string::npos)
				{
					resultId[count] = userId[index];
					resultProfile[count] = userProfile[index];
					count++;
					foundData = true;
				}
			}
		}
		break;
	case AGE:
		for (int index = 0; index < recordCount; index++)
		{
			if (count < PAGESIZE - 1) {
				if (to_string(userProfile[index].age).find(filter[choice - 1]) != string::npos)
				{
					resultId[count] = userId[index];
					resultProfile[count] = userProfile[index];
					count++;
					foundData = true;
				}
			}
		}
	}
}

void sortList(string PROFILEPATH, char prefix, string sortedId[], UserProfile sortedProfile[], int userIdSize) {

	int choice = 0, recordCount = 0;
	bool sorted = true, ascOrder = true;
	DataField data = NAME;
	string lastId = "";
	ifstream read;

	do
	{
		sortOption(data, choice);

	} while (choice < 1 || choice > 4);

	do
	{
		orderOption(ascOrder, choice);

	} while (choice < 1 || choice > 2);

	readUserId(PROFILEPATH, recordCount, sortedId, prefix, lastId, userIdSize);
	readUserList(PROFILEPATH, recordCount, sortedId, sortedProfile, userIdSize);

	do {
		checkOrder(sorted, recordCount, data, ascOrder, sortedId, sortedProfile);

	} while (!sorted);
}

void sortOption(DataField& data, int& choice) {

	cout << "\n\nSort by: \n[1] User Id\n[2] Name\n[3] Age";

	getChoice(choice);

	switch (choice)
	{
	case 1: data = USERID; break;
	case 2: data = NAME; break;
	case 3: data = AGE; break;
	default: invalidChoice();
	}
	system("cls");
}

void orderOption(bool& ascOrder, int& choice) {

	cout << "\n\nOrder by: \n[1] Ascending Order\n[2] Descending Order";

	getChoice(choice);

	switch (choice)
	{
	case 1: ascOrder = true; break;
	case 2: ascOrder = false; break;
	default: invalidChoice();
	}
	system("cls");
}

void checkOrder(bool& sorted, int recordCount, DataField data, bool ascOrder, string sortedId[], UserProfile sortedProfile[]) {

	sorted = true;
	for (int index = 0; index < recordCount - 1; index++) { // recordCount - 1 because it will access index + 1

		bool swapNeeded = false;
		switch (data)
		{
		case USERID:
			swapNeeded = ascOrder ?
				!compareLexicographically(sortedId[index], sortedId[index + 1]) :
				compareLexicographically(sortedId[index], sortedId[index + 1]);
			break;
		case NAME:
			swapNeeded = ascOrder ?
				!compareLexicographically(sortedProfile[index].name, sortedProfile[index + 1].name) :
				compareLexicographically(sortedProfile[index].name, sortedProfile[index + 1].name);
			break;
		case AGE:
			swapNeeded = ascOrder ?
				(sortedProfile[index].age > sortedProfile[index + 1].age) :
				(sortedProfile[index].age < sortedProfile[index + 1].age);
		}

		if (swapNeeded) {
			// Perform swapping
			bubbleSort(sortedId[index], sortedProfile[index], sortedId[index + 1], sortedProfile[index + 1]);
			sorted = false;
		}
	}
}

bool compareLexicographically(string currentElement, string nextElement) {

	size_t minLength = min(currentElement.length(), nextElement.length());

	// Compare each character
	for (size_t pos = 0; pos < minLength; ++pos) {
		if (currentElement[pos] < nextElement[pos]) {
			return true;  // currentElement is lexicographically smaller
		}
		else if (currentElement[pos] > nextElement[pos]) {
			return false; // nextElement is lexicographically smaller
		}
	}

	// If all characters up to minLength are the same, compare lengths
	return currentElement.length() < nextElement.length();
}

void bubbleSort(string& currentId, UserProfile& currentProfile, string& nextId, UserProfile& nextProfile) {

	string tempId;
	UserProfile tempProfile;

	tempId = currentId;
	currentId = nextId;
	nextId = tempId;

	tempProfile = currentProfile;
	currentProfile = nextProfile;
	nextProfile = tempProfile;
}

void searchResult(string PROFILEPATH, string userId[], UserProfile userProfile[], int& recordCount, string filter[]) {

	const int PAGESIZE = 11;
	int choice = 0, count = 0;
	DataField data = NAME;
	char changeFilter = 'Y';
	string resultId[PAGESIZE], bufferId[PAGESIZE];
	UserProfile resultProfile[PAGESIZE], bufferProfile[PAGESIZE];
	bool foundData = false;

	for (int index = 0; index < recordCount; index++)
	{
		bufferId[index] = userId[index]; // save the data before search
		bufferProfile[index] = userProfile[index];
	}

	do
	{
		displayCustomerList(recordCount, userId, userProfile, 0);
		searchOption(data, choice);
	} while (choice < 1 || choice > 6);

	if (!filter[choice - 1].empty())
	{
		do
		{
			cout << "\nYou have applied filter for this field." << endl;
			cout << "Do you want to change the filter? [ Y / N ]" << endl;
			cin >> changeFilter;
			changeFilter = toupper(changeFilter);

			if (changeFilter != 'Y' && changeFilter != 'N')
			{
				cout << "Enter 'Y' or 'N' only." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

		} while (changeFilter != 'Y' && changeFilter != 'N');

		cout << endl;
	}

	if (changeFilter == 'Y')
	{
		getFilter(choice, filter);
	}

	filterResult(PAGESIZE, data, recordCount, filter, choice, userId, userProfile, resultId, resultProfile, foundData, count);

	if (!foundData)
	{
		cout << "\nNo data matches the filter applied." << endl;
		for (int index = 0; index < recordCount; index++)
		{
			userId[index] = bufferId[index]; // retrieve the data before search
			userProfile[index] = bufferProfile[index];
		}
		filter[choice - 1].clear();
	}
	else
	{
		clearArray(userId, recordCount);
		for (int index = 0; index < count; index++)
		{
			userId[index] = resultId[index];
			userProfile[index] = resultProfile[index];
		}
		recordCount = count;
	}

	if (!foundData)
	{
		system("pause");
	}

	system("cls");
}

void sortResult(int recordCount, string sortedId[], UserProfile sortedProfile[]) {

	int choice = 0;
	bool sorted = true, ascOrder = true;
	DataField data = NAME;

	do
	{
		sortOption(data, choice);

	} while (choice < 1 || choice > 4);

	do
	{
		orderOption(ascOrder, choice);

	} while (choice < 1 || choice > 2);

	do {
		checkOrder(sorted, recordCount, data, ascOrder, sortedId, sortedProfile);

	} while (!sorted);
}

void displayProfileMenu(string& username, bool changes) {

	const string CREDENTIALPATH = "userCredential\\", PROFILEPATH = "userData\\";
	UserCredentials userCredential;
	UserProfile userProfile;

	string credentialPath = CREDENTIALPATH + username + ".txt";
	readUserCredential(userCredential, credentialPath);

	string profilePath = PROFILEPATH + userCredential.userID + ".dat";
	readUserProfile(userProfile, profilePath);

	// Option to update user data
	int choice;

	do {

		system("cls");
		displayMiniLogo();
		// Display current user profile and credentials
		displayUserProfile(userProfile);
		displayUserCredentials(userCredential);

		cout << "Options:" << endl;
		cout << "[1] Change username" << endl;
		cout << "[2] Reset password" << endl;
		cout << "[3] Update Age and Gender" << endl;
		cout << "[9] Main Menu" << endl;

		getChoice(choice);

		switch (choice) {
		case 1:
			changeUsername(userCredential, username);
			changes = true;
			break;
		case 2:
			resetPassword(userCredential, userCredential.password);
			changes = true;
			break;
		case 3:
			updateAgeAndGender(userProfile);
			changes = true;
			break;
		case 9:
			if (changes)
			{
				credentialPath = CREDENTIALPATH + userCredential.username + ".txt";
				writeUserCredential(credentialPath, userCredential);
				writeUserProfile(profilePath, userProfile);
			}
			break;
		default:
			invalidChoice();
		}
		system("cls");
	} while (choice != 9);
}

void readUserCredential(UserCredentials& userCredential, string& filePath) {
	ifstream inputFile(filePath);

	if (!inputFile) {
		cerr << "Error opening file: " << filePath << endl;
	}
	else
	{
		getline(inputFile, userCredential.userID);    // First line is userID
		getline(inputFile, userCredential.username);  // Second line is username
		getline(inputFile, userCredential.password);  // Third line is password
		getline(inputFile, userCredential.timeCreated); // Fourth line is date created
	}

	inputFile.close();
}

void displayUserCredentials(UserCredentials& userCredential) {
	cout << "\tUser Credentials" << endl;
	cout << "====================================" << endl;
	cout << "User ID\t\t:" << userCredential.userID << endl;
	cout << "Username\t:" << userCredential.username << endl;
	cout << "Password\t:" << setfill('*') << setw(userCredential.password.length() + 1) << " " << setfill(' ');
	cout << endl;
	cout << "Time Created\t:" << userCredential.timeCreated << endl;
	cout << endl;
}

void changeUsername(UserCredentials& userCredential, string& username) {

	const string CREDENTIALPATH = "userCredential\\", PROFILEPATH = "userData\\";
	string input;

	bool valid = false;

	cout << "\n\tNew Username" << endl;
	cout << "======================" << endl;
	cout << "Enter -999 to exit." << endl;

	cout << "Enter new username: ";
	cin.ignore();
	getline(cin, input);
	if (input.empty())
	{
		cerr << "Username cannot be empty. Please try again.\n\n" << endl;
	}
	else if (input == "-999")
	{
		return;
	}
	else
	{
		valid = validRegInput(input, USERNAME, "");

		if (input[0] == 'N')
		{
			return;
		}
	}

	if (valid)
	{
		if (rename((CREDENTIALPATH + username + ".txt").c_str(), (CREDENTIALPATH + input + ".txt").c_str()) == 0)
		{
			userCredential.username = username = input;
			cout << "Username updated successfully!" << endl;
			system("pause");
		}
		else
		{
			cerr << "Failed to rename the user credential file." << endl;
			system("pause");
		}
	}
}

void resetPassword(UserCredentials& userCredential, string& password) {

	regex pattern = regex(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$)");
	string oldPassword, newPassword, confirmPassword;
	bool valid = false;

	cout << "\n\tReset Password" << endl;
	cout << "======================" << endl;
	cout << "Enter -999 to exit." << endl;
	cout << "Enter old password\t:";
	oldPassword = getPassword();
	if (oldPassword != password)
	{
		cerr << "Error : Incorrect Password" << endl;
		system("pause");
		return;
	}

	cout << "\nYour password should have : " << endl;
	cout << "- 8 characters " << endl;
	cout << "- One uppercase and one lowercase " << endl;
	cout << "- One digit " << endl;
	cout << "- One special character [@$!%*?&]" << endl;

	do
	{
		cout << "\nEnter new password\t:";
		newPassword = getPassword();
		if (newPassword.empty())
		{
			cerr << "New Password cannot be empty. Please try again.\n\n" << endl;
		}
		else
		{
			valid = regex_match(newPassword, pattern);

			if (newPassword == "-999")
			{
				break;
			}

			if (!valid)
			{
				cerr << "New Password is not in the correct pattern mentioned. Please try again.\n\n" << endl;
			}
			else
			{
				cout << "Confirm new password\t:";
				confirmPassword = getPassword();
				if (confirmPassword.empty())
				{
					cerr << "Confirm Password cannot be empty. Please try again.\n\n" << endl;
				}
				else
				{
					valid = (confirmPassword == newPassword);

					if (confirmPassword == "-999")
					{
						break;
					}

					if (!valid)
					{
						cerr << "Confirm Password is different from New Password. Please try again.\n\n" << endl;
					}
					else
					{
						userCredential.password = password = newPassword;
						cout << "Password reset successfully!" << endl;
					}
				}
			}
		}

		system("pause");

	} while (!valid);
}

void updateAgeAndGender(UserProfile& userProfile) {
	char choice;
	int age;

	do
	{
		cout << "Enter your age: ";
		cin >> age;
		validType(age);
		if (age < 12 || age > 100)
		{
			cerr << "Error! You must be above 12 years old and below 100 years old." << endl;
		}
	} while (age < 12 || age > 100);

	userProfile.age = age;

	do
	{
		cout << "Enter your gender [ M / F ]: ";
		cin >> choice;
		choice = toupper(choice);

		if (choice == 'M')
		{
			userProfile.gender = "Male";
		}
		else if (choice == 'F')
		{
			userProfile.gender = "Female";
		}
		else
		{
			cerr << "Invalid Gender. Please try again." << endl;
		}
	} while (choice != 'M' && choice != 'F');

	cout << "Age and gender updated successfully!" << endl;
	system("pause");
}

void writeUserCredential(string& filePath, UserCredentials& userCredential) {
	ofstream outputFile(filePath);

	if (!outputFile) {
		cerr << "Error opening file for writing: " << filePath << endl;
		return;
	}

	outputFile << userCredential.userID << endl;
	outputFile << userCredential.username << endl;
	outputFile << userCredential.password << endl;
	outputFile << userCredential.timeCreated << endl;

	outputFile.close();
}

void writeUserProfile(string& filePath, UserProfile& userProfile) {
	ofstream outputFile(filePath);

	if (!outputFile) {
		cerr << "Error opening file for writing: " << filePath << endl;
		return;
	}

	outputFile << userProfile.name << endl;
	outputFile << userProfile.contact << endl;
	outputFile << userProfile.email << endl;
	outputFile << userProfile.age << endl;
	outputFile << userProfile.gender << endl;

	outputFile.close();
}
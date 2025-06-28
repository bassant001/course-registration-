#include "User.h"
#include "Student.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include<conio.h>
using namespace std;

// Static map to store users by their ID
unordered_map<int, User> User::usersById;

User::User() {
    semester = -2;
    id = 0;
    name = "";
    birthdate = "";
    phoneNumber = "";
    email = "";
    password = "";
    confirmPassword = "";
    gender = "";
    type = "";
}

User::User(int id)
{
    this->id = id;
}

User::User(int id, string name, string birthdate, string phoneNumber, string email,
    string password, string gender, string type, int semester)
    : id(id), name(name), birthdate(birthdate), phoneNumber(phoneNumber),
    email(email), password(password), gender(gender), type(type), semester(semester) {}

// Generate the next user ID by finding the max existing ID and adding 1
int User::getNextUserId() {
    ifstream file("users.csv");
    if (!file.is_open()) {
        return 1001;
    }

    string line;
    int maxId = 1000;

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr;
        getline(ss, idStr, ',');
        try {
            int currentId = stoi(idStr);
            if (currentId > maxId) {
                maxId = currentId;
            }
        }
        catch (...) {
            continue;
        }
    }

    file.close();
    return maxId + 1;
}


// Register a new user with input validation
User User::registerUser() {
    id = getNextUserId();

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your birthdate (YYYY-MM-DD): ";
    cin >> birthdate;

    // Validate phone number (max 11 digits)
    while (true) {
        cout << "Enter your phone number (max 11 digits): ";
        cin >> phoneNumber;
        if (phoneNumber.length() > 11) {
            cout << "Invalid phone number. Must not exceed 11 characters.\n";
        }
        else {
            break;
        }
    }
    // Validate email to contain @gmail.com and check if already exists
    while (true) {
        cout << "Enter your email (must be @gmail.com): ";
        cin >> email;

        if (email.find("@gmail.com") == string::npos) {
            cout << "Invalid email. It must contain '@gmail.com'.\n";
            continue;
        }

        bool emailExists = false;
        for (const auto& entry : User::usersById) {
            if (entry.second.getemail() == email) {
                emailExists = true;
                break;
            }
        }

        if (emailExists) {
            cout << "This email is already registered. Please enter another one.\n";
            continue;
        }

        break;
    }


    // Validate password length and confirmation
    while (true) {
        cout << "Enter your password (max 6 characters): ";
        cin >> password;

        if (password.length() > 6) {
            cout << "Password must be at most 6 characters long. Please try again.\n";
            continue;
        }

        cout << "Confirm your password: ";
        cin >> confirmPassword;

        if (password != confirmPassword) {
            cout << "Passwords do not match. Please try again.\n";
            continue;
        }

        break;
    }

    // Validate gender input
    while (true) {
        cout << "Enter your gender (m/f): ";
        cin >> gender;
        if (gender != "m" && gender != "f") {
            cout << "Invalid gender. Please enter 'Male' (m) or 'Female' (f).\n";
        }
        else {
            break;
        }
    }

    // Validate type input
    while (true) {
        cout << "Enter your user type 'student' (s) / 'administrator' (a): ";
        cin >> type;
        if (type != "s" && type != "a") {
            cout << "Invalid type. Must be 'student' (s) or 'administrator' (a).\n";
        }
        else {
            if (type == "s") {
                semester = 0;
            }
            else if (type == "a") {
                semester = -1;
            }
            break;
        }
    }
    cout << "Your assigned ID is: " << id << "\n";
    // Store in the in-memory map
    usersById[id] = *this;
    return *this;
}



// Log in an existing user using ID, name, and password
User* User::loginUser() {
    string idInput;
    int inputId;
    string inputName, inputPassword;

    cout << "Login\n";

    // Validate ID input as numeric only
    cout << "Enter your ID: ";
    getline(cin, idInput);
    while (idInput.empty() || !all_of(idInput.begin(), idInput.end(), ::isdigit)) {
        cout << "Invalid input. Please enter a numeric ID: ";
        getline(cin, idInput);
    }
    inputId = stoi(idInput);

    cout << "Enter your name: ";
    getline(cin, inputName);

    cout << "Enter your password: ";
    //cin >> inputPassword;
    char enteredPassword[100], ch;
    int i = 0;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b' && i > 0)
        {
            cout << "\b \b";
            i--;
        }
        else if (ch != '\b')
        {
            cout << '*';
            enteredPassword[i++] = ch;
        }
    }
    enteredPassword[i] = '\0';

    if (usersById.find(inputId) != usersById.end()) {
        User& user = usersById[inputId];
        if (user.getname() == inputName && user.getpassword() == enteredPassword) {
            cout << endl;
            return &user;
        }
    }
    cout << endl;
    cout << "No user found with that ID and name.\n";
    return nullptr;
}


string User::getname() const { return name; }
int User::getid() const { return id; }
string User::getbirthdate() const { return birthdate; }
string User::getphoneNumber() const { return phoneNumber; }
string User::getemail() const { return email; }
string User::getpassword()const { return password; }
string User::getgender() const { return gender; }
string User::gettype() const { return type; }
int User::getsemester() { return semester; }
void User::setSemester(int s) { this->semester = s; }
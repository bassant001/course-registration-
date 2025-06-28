
#pragma once
#include <string>
#include <unordered_map>

#pragma once
#include <string>
#include <unordered_map>
using namespace std;
class User {
protected:
    int id, semester = -2;
    string name, birthdate, phoneNumber, email;
    string password, confirmPassword, gender, type;
public:
    static unordered_map<int, User> usersById;
public:
    User();
    User(int id);
    User(int id, string name, string birthdate, string phoneNumber, string email, string password, string gender, string type, int semester);

    User registerUser();

    static User* loginUser();


    string getname() const;
    int getid() const;
    string getbirthdate() const;
    string getphoneNumber() const;
    string getemail() const;
    string getpassword() const;
    string getgender() const;
    string gettype() const;
    int getsemester();
    void setSemester(int s);
private:
    int getNextUserId();
};

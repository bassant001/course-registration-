#pragma once
#include <iostream>
#include <string>
using namespace std;
class User
{
protected:
    int id;
    string password;
    string confirm_pass;
    string email;
    string name;
    string birthdate;
    string gender;
    string phone;
    string type;

public:
    User();
    void Register();
    User login();

};
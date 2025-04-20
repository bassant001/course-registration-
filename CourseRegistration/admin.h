#pragma once
#include <string>
#include <iostream>
#include "course.h"
#include <unordered_map>
class admin
{
	int id;
	std::string fname, lname, password;
public:
	admin();
	unordered_map<string, Course> uploadCD(unordered_map<string, Course>courses);
	unordered_map<string, Course> setPre(unordered_map<string, Course>courses);
	void manageGrades();
	~admin();
};


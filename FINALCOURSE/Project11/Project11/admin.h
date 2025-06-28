#pragma once
#include <string>
#include <iostream>
#include "course.h"
#include <unordered_map>
#include "Student.h"
class admin
{
private:

	std::unordered_map<std::string, Course> courses;

	std::unordered_map<std::string, Student> students;
public:
	admin();

	bool checker();

	void menu(unordered_map<string, Course>& courses,
		unordered_map<int, unordered_set<string>>& all_registered_courses,
		unordered_map<int, unordered_map<string, grade>>& all_grades,
		unordered_map<int, Student>& all_students, string name,
		unordered_map <int, notification>& n);

	void upload_course_description(unordered_map<string, Course>& courses);

	void set_prerequisite(unordered_map<string, Course>& courses);

	~admin();

	void manageGrades(
		unordered_map<int, unordered_set<string>>& all_registered_courses,
		unordered_map<int, unordered_map<string, grade>>& all_grades,
		unordered_map<int, Student>& all_students);


	void notificaton(unordered_map <int, notification> n);

	void response(unordered_map <int, notification>& n, unordered_map<int, Student>& all_students, unordered_map<int, unordered_set<string>>& all_registered_courses);

};


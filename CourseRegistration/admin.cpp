#include "admin.h"
#include "Course.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
using namespace std;
admin::admin()
{
}


unordered_map<string, Course> admin::uploadCD(unordered_map<string, Course> courses)
{
	string code, title, syllabus, instructor, semester;
	int credit_hours;
	bool comp = true;
	cout << "Enter course code: ";
	cin >> code;
	cout << "Enter course title: ";
	cin >> title;
	cin.ignore(1000, '\n');
	do {
		try {
			cout << "Enter course credit hours (1:10): ";
			cin >> credit_hours;
			cin.ignore(1000, '\n');
		}
		catch (exception exp) {
			cout << "Invalid input.Try again\n";
			continue;
		}
		if (credit_hours < 0 && credit_hours>11) {
			cout << "Credit hours you entered are not allowed.\nTry again -> (y,Y)\nExit -> (type anything)\n";
			string ch;
			cin >> ch;
			if (ch == "y" || ch == "Y") {
				continue;
			}
			else {
				comp = false;
				break;
			}
		}
		else {
			break;
		}
	} while (true);
	cout << "Enter course syllabus: ";
	getline(cin, syllabus);
	cout << "Enter course instructor: ";
	getline(cin, instructor);
	cout << "Enter course semester: ";
	cin >> semester;

	if (comp) {
		Course c(code, title, credit_hours, syllabus, instructor, semester, "-");
		courses.insert({ code, c });
		return courses;
	}
	else {
		cout << "Failed to open the csv file\n";
	}
}

unordered_map<string, Course> admin::setPre(unordered_map<string, Course> all_courses)
{
	string course_id_pre, course_id;
	cout << "Enter Course ID: ";
	cin >> course_id;
	cout << "Enter Prerequisite Course ID: ";
	cin >> course_id_pre;
	if (all_courses.find(course_id_pre) != all_courses.end() && all_courses.find(course_id) != all_courses.end())
	{
		all_courses[course_id].setPrerequisites(course_id_pre);
	}
	else if (all_courses.find(course_id_pre) == all_courses.end()) {
		cout << "Prerequisit Course not found\n";
	}
	else {
		cout << "Course Not Found";
	}
	return all_courses;
}

void admin::manageGrades()
{
}

admin::~admin()
{
}

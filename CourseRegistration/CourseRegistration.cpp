#include <iostream>
#include "admin.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include "Course.h"

using namespace std;
unordered_map<string, Course> read_courses();
void save_courses(unordered_map<string, Course>);

int main() {
	unordered_map<string, Course> courses = read_courses();
	admin a;
	/*courses = a.uploadCD(courses);
	courses = a.setPre(courses);*/
	save_courses(courses);
}

unordered_map<string, Course> read_courses() {
	unordered_map<string, Course> courses;
	ifstream file("data.csv");
	string row;
	getline(file, row);
	while (getline(file, row)) {
		stringstream s(row);
		string code, title, syllabus, instructor, semester, prerequisites, crSTR;
		getline(s, code, ',');
		getline(s, title, ',');
		getline(s, crSTR, ',');
		getline(s, syllabus, ',');
		getline(s, instructor, ',');
		getline(s, semester, ',');
		getline(s, prerequisites, ',');
		if (prerequisites.empty())
			prerequisites = "-";
		int credit_hours = stoi(crSTR);
		Course c(code, title, credit_hours, syllabus, instructor, semester, prerequisites);
		courses.insert(make_pair(code, c));
	}
	file.close();
	return courses;
}
void save_courses(unordered_map<string, Course> courses) {
	ofstream file("data.csv");
	if (file.is_open()) {
		file << "code" << "," << "title" << "," <<
			"credit_hours" << "," << "syllabus" << ","
			<< "instructor" << "," << "semester" << "," << "prerequisites" << "\n";
		for (auto it = courses.begin(); it != courses.end(); it++) {
			file << it->second.getId() << "," << it->second.getTitle() << "," <<
				it->second.getHours() << "," << it->second.getSyllabus() << ","
				<< it->second.getInstructor() << "," << it->second.getSemester() << "," <<
				it->second.getPrerequisites() << "\n";
		}
		file.close();
	}
	else {
		cout << "Saving process is not completed successfully\n";
	}
}
void save_registered_courses(unordered_set<string>)
{

}

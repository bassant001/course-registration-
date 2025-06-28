//new version of the project
#include <iostream>
#include "admin.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include "Course.h"
#include "Student.h"
#include "User.h"
using namespace std;

bool checker();
void loadUsersFromFile();
void saveUsersToFile();

unordered_map<int, unordered_map<string, grade>> read_grades();
void save_grades(unordered_map<int, unordered_map<string, grade>>);

unordered_map<string, Course> read_courses();
void save_courses(unordered_map<string, Course>);

void save_registered_courses(unordered_map<int, unordered_set<string>> all_registered);//key std id and value unordered_set of reg. courses ids
unordered_map<int, unordered_set<string>> read_registered_courses(); //key std id and value unordered_set of reg. courses ids
void connect_student_to_registerd_courses(int stdID, unordered_map<int, unordered_set<string>>& all_registered_courses); //put the registered courses of a student in its object
void connect_students_to_grades_courses(int stdID,unordered_map<int, unordered_map<string, grade>>& all_completed_courses);

// global var
unordered_map<int, Student> all_students;
unordered_map<int, unordered_set<string>> all_registered_courses = read_registered_courses();
unordered_map<int, unordered_map<string, grade>> all_grades = read_grades();

int main() {
	/* ofstream tempFile("users.csv", ios::app); // creates the file if it doesn't exist
	tempFile.close();*/

	unordered_map <int, notification> n;  //this is a run time notification only

	unordered_map<string, Course> courses = read_courses();
	loadUsersFromFile();

	User u;
	Student s;
	admin a;
	string choice;
	do {
		cout << "Welcome to Course Registration system\n";
		cout << "=====================================================\n";
		cout << "1. Register\n2. Login\n3. Exit\nChoose: ";
		cin >> choice;
		cin.ignore();
		if (choice == "1")
		{
			if (checker()) {
				User newuser;
				newuser = u.registerUser();
				if (newuser.gettype() == "s")
				{
					all_students[newuser.getid()].setID(newuser.getid());
					all_students[newuser.getid()].setname(newuser.getname());
					all_students[newuser.getid()].setSemester(newuser.getsemester());
				}
			}

		}
		else if (choice == "2")
		{
			if (checker()) {
				User* loggedInUser = User::loginUser();
				if (loggedInUser != nullptr)
				{
					cout << "=====================================================\n";
					cout << " Logged in successfully " << endl;
					cout << "=====================================================\n";
					if (loggedInUser->gettype() == "a") {

						a.menu(courses, all_registered_courses, all_grades, all_students, loggedInUser->getname(), n);
					}
					else
					{
						all_students[loggedInUser->getid()].menu(courses, all_registered_courses, n);

					}
				}
				else
				{
					cout << "=====================================================\n";
					cout << "Login failed.\n";
					cout << "=====================================================\n";
				}
			}
		}
		else if (choice == "3") {
			if (checker()) {
				break;
			}
		}
		else
		{
			cout << "=====================================================\n";
			cout << "Invalid option.\n";
			cout << "=====================================================\n";
		}
	} while (true);

	cout << "Have a nice day.\n\n";
	cout << "=====================================================\n";
	saveUsersToFile();
	save_registered_courses(all_registered_courses);
	save_courses(courses);
	save_grades(all_grades);
}
unordered_map<string, Course> read_courses() {
	unordered_map<string, Course> courses;
	ifstream file("courses.csv");
	if (!file.is_open()) {
		cout << "Error: courses can not be read!\n" << endl;
		return courses;
	}

	string row;
	getline(file, row);
	while (getline(file, row)) {
		stringstream s(row);
		string code, title, syllabus, instructor, prerequisites, crSTR;
		getline(s, code, ',');
		getline(s, title, ',');
		getline(s, crSTR, ',');
		getline(s, syllabus, ',');
		getline(s, instructor, ',');

		getline(s, prerequisites, ',');

		if (prerequisites.empty())
			prerequisites = "-";

		int credit_hours = stoi(crSTR);
		Course c(code, title, credit_hours, syllabus, instructor, prerequisites);
		courses[code] = c;
	}
	file.close();
	return courses;
}

void save_courses(unordered_map<string, Course> courses) {
	ofstream file("courses.csv");
	if (!file.is_open()) {
		cout << "Error: saving courses data failed!\n" << endl;
		return;
	}

	file << "code" << "," << "title" << "," <<
		"credit_hours" << "," << "syllabus" << "," <<
		"instructor" << "," << "prerequisites" << "\n";

	for (auto& course : courses) {
		file << course.second.getId() << "," << course.second.getTitle() << "," <<
			course.second.getHours() << "," << course.second.getSyllabus() << "," <<
			course.second.getInstructor() << "," <<
			course.second.getPrerequisites() << "\n";
	}
	file.close();
}

unordered_map<int, unordered_set<string>> read_registered_courses()
{
	string filename = "RegisteredCourses.csv";
	unordered_map<int, unordered_set<string>> registered;
	ifstream file(filename);
	string row;
	getline(file, row); //to get header
	while (getline(file, row)) {
		stringstream s(row);
		string stdID, courseID;
		getline(s, stdID, ',');
		getline(s, courseID, ',');
		int studentID = stoi(stdID);
		registered[studentID].insert(courseID);
	}
	file.close();
	return registered;
}

void save_registered_courses(unordered_map<int, unordered_set<string>> registered)
{
	string filename = "RegisteredCourses.csv";
	ofstream file(filename);
	if (file.is_open()) {
		file << "student_id,course_id\n";
		for (auto& it : registered)
		{
			int studentID = it.first;
			for (auto myset = it.second.begin(); myset != it.second.end(); ++myset)
			{
				file << studentID << "," << *myset << "\n";
			}
		}
		file.close();

	}
	else
	{
		cout << "Failed to open file: " << filename << endl;
	}
}

void connect_student_to_registerd_courses(int stdID,unordered_map<int, unordered_set<string>>& all_registered_courses) //here i only work on one student 
{
	
		auto it = all_registered_courses.find(stdID); //make sure sid exsist in all registered coureses file
		if (it != all_registered_courses.end())
		{
			//loop on the set to get all the courses assigned to our student
			for (auto myset = it->second.begin(); myset != it->second.end(); ++myset)
			{
				all_students[stdID].getRegisteredCourses().insert(*myset);
			}

		}

}

void connect_students_to_grades_courses(int stdID, unordered_map<int, unordered_map<string, grade>>& all_completed_courses) // put grades in student object
{
	
		auto it1 = all_completed_courses.find(stdID); //make sure sid exsist in all completed coureses file
		if (it1 != all_completed_courses.end())
		{
			//loop on the map  which contains cid and grade 
			for (auto& it2 : it1->second)
			{

				all_students[stdID].getCompletedCourses().insert({ it2.first, it2.second }); //it2.second (is degree and semester)

			}
		}

}


void loadUsersFromFile() {
	ifstream file("users.csv");
	if (!file.is_open()) {
		cerr << "Error: Could not open file.\n";
		return;
	}

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string tidStr, tname, tbirthdate, tphone, temail, tpassword, tgender, ttype, tsemester;

		getline(ss, tidStr, ',');
		int tid = stoi(tidStr);

		getline(ss, tname, ',');
		getline(ss, tbirthdate, ',');
		getline(ss, tphone, ',');
		getline(ss, temail, ',');
		getline(ss, tpassword, ',');
		getline(ss, tgender, ',');
		getline(ss, ttype, ',');
		getline(ss, tsemester, ',');

		int semester = -2;
		if (!tsemester.empty()) {
			semester = stoi(tsemester);
		}
		// Reconstruct user and store in map
		User user(tid, tname, tbirthdate, tphone, temail, tpassword, tgender, ttype, semester);
		User::usersById[tid] = user;
		//new
		if (ttype == "s") //to load all stds
		{
			all_students[tid].setID(tid);
			all_students[tid].setname(tname);
			all_students[tid].setSemester(semester);
			connect_student_to_registerd_courses(tid,all_registered_courses);
			connect_students_to_grades_courses(tid, all_grades);

		}
	}

	file.close();
}


// Save all users from the map to the CSV file
void saveUsersToFile() {
	ofstream file("users.csv", ios::out);
	if (file.is_open()) {
		for (auto& entry : User::usersById) {

			if (entry.second.gettype() == "s")
			{
				int id = entry.second.getid();
				entry.second.setSemester(all_students[id].getsemester());
			}

			User& user = entry.second;
			file << user.getid() << "," << user.getname() << "," << user.getbirthdate() << ","
				<< user.getphoneNumber() << "," << user.getemail() << "," << user.getpassword() << ","
				<< user.getgender() << "," << user.gettype() << "," << user.getsemester() << "\n";
		}
		file.close();
		//cout << "Registration successful!\n";
	}
	else {
		cerr << "Error: Could not open file for writing.\n";
	}
}


unordered_map<int, unordered_map<string, grade>> read_grades() {
	unordered_map<int, unordered_map<string, grade>> all_grades;
	ifstream gradeFile("grades.csv");
	string line;

	getline(gradeFile, line); // Skip header line

	while (getline(gradeFile, line)) {
		stringstream ss(line);
		string studentID, courseID, degree, semester;

		getline(ss, studentID, ',');
		getline(ss, courseID, ',');
		getline(ss, degree, ',');
		getline(ss, semester, ',');

		int id = stoi(studentID);
		grade g = { degree, semester };
		all_grades[id][courseID] = g;
	}

	gradeFile.close(); // this should come before return
	return all_grades;
}

void save_grades(unordered_map<int, unordered_map<string, grade>> all_grades) {
	ofstream gradeFileOut("grades.csv");
	gradeFileOut << "student_id,course_id,degree,semester\n";

	for (const auto& student : all_grades) {
		for (const auto& course : student.second) {
			gradeFileOut << student.first << ","
				<< course.first << ","
				<< course.second.degree << ","
				<< course.second.semester << "\n";
		}
	}

	gradeFileOut.close();
}


bool checker()
{
	string ch;
	cout << "Do you want to do this process ? \n";
	cout << "To continue press (y/Y)\n";
	cin >> ch;
	cin.ignore();
	if (ch == "y" || ch == "Y") { return true; }
	else
		return false;
}
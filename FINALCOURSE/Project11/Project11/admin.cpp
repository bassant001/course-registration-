
#include "admin.h"
#include "Course.h"
#include "Student.h"


#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
using namespace std;
admin::admin()
{
}
bool admin::checker()
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
void admin::menu(unordered_map<string, Course>& courses,
    unordered_map<int, unordered_set<string>>& all_registered_courses,
    unordered_map<int, unordered_map<string, grade>>& all_grades,
    unordered_map<int, Student>& all_students, string name,
    unordered_map <int, notification>& n) {
    string choice;
    bool end;
    do {
        cout << "Welcome Admin : " << name << " \n";
        cout << "1- Upload Course Discribtion \n2- Set Prerequistie For Course\n3- Manage Grades\n4- notification\n5- response\n6- Logout\n";
        cout << "Enter Your Choise: ";
        cin >> choice;

        if (choice == "1") {
            if (checker()) { upload_course_description(courses); }
        }
        else if (choice == "2") {
            if (checker()) { set_prerequisite(courses); }
        }
        else if (choice == "3") {
            if (checker()) { manageGrades(all_registered_courses, all_grades, all_students); }
        }
        else if (choice == "4") {
            if (checker()) { notificaton(n); }
        }
        else if (choice == "5") {
            if (checker()) { response(n, all_students, all_registered_courses); }
        }
        else if (choice == "6") { // return to back menu
            if (checker()) {
                cout << "loging out...." << endl;
                cout << "=====================================================\n";
                break;
            }
        }
        else {
            cout << "Invalid input\n";
        }

    } while (true);
}

void admin::upload_course_description(unordered_map<string, Course>& courses)
{
    string choice;
    cout << "1- Upload course \n2-Update course \n";
    cout << "Enter Your Choise: ";
    cin >> choice;
    if (choice == "1") {
        string code, title, syllabus, instructor, hours;
        int credit_hours;
        bool comp = true;
        cout << "Enter course code: ";
        cin >> code;
        cin.ignore(1000, '\n');
        if (courses.find(code) != courses.end()) {
            cout << "This course is added already.\n";
            return;
        }
        cout << "Enter course title: ";


        getline(cin, title);

        do {

            cout << "Enter course credit hours (1:10): ";
            cin >> hours;
            cin.ignore(1000, '\n');


            try {
                credit_hours = stoi(hours);
                if (credit_hours < 0 || credit_hours>10) {
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
            }
            catch (exception e) {
                cout << "Invalid input.Try again\n";
                continue;
            }
        } while (true);

        if (comp) {
            cout << "Enter course syllabus: ";
            getline(cin, syllabus);
            cout << "Enter course instructor: ";
            getline(cin, instructor);
            Course c(code, title, credit_hours, syllabus, instructor, "-");
            courses.insert({ code, c });
            cout << "New course is added successfully\n";
            cout << "=====================================================\n";
        }
    }
    else if (choice == "2") {
        string code;
        cout << "Enter course code: ";
        cin >> code;
        cin.ignore(1000, '\n');
        if (courses.find(code) != courses.end()) {
            string ch;
            cout << "What do you want to update?\n";
            cout << "1- instructor \n2-credit hours\n";
            cout << "Enter Your Choise: ";
            cin >> ch;
            if (ch == "1") {
                string instructor;
                cout << "Enter new instructor: ";
                getline(cin, instructor);
                courses[code].setInstructor(instructor);
                cout << "New course is updated successfully\n";
                cout << "=====================================================\n";
            }
            else if (ch == "2") {
                string hours;
                int h;
                cout << "Enter course credit hours (1:10): ";
                cin >> hours;
                cin.ignore(1000, '\n');
                try {
                    h = stoi(hours);
                    if (h < 0 || h>10) {
                        cout << "Credit hours you entered are not allowed.\n";
                    }
                    else {
                        courses[code].setHours(h);
                        cout << "New course is updated successfully\n";
                        cout << "=====================================================\n";
                    }
                }
                catch (exception e) {
                    cout << "Invalid input.\n";
                }
            }
            else {
                cout << "Inalid input\n";
            }
        }
        else {
            cout << "No course is found with this course code\n";
        }
    }
    else {
        cout << "Inalid input\n";
    }
}

void admin::set_prerequisite(unordered_map<string, Course>& all_courses)
{
    string course_id_pre, course_id;
    cout << "Enter Course ID: ";
    cin >> course_id;
    cout << "\nIf You Want To DELETE Prerequisite Enter NULL \n";
    cout << "Enter Prerequisite Course ID: ";
    cin >> course_id_pre;
    if (course_id == course_id_pre)
    {
        cout << "Course And Prerequisite Must Be Diffrenet\n";
    }
    else if (course_id_pre == "NULL" && all_courses.find(course_id) != all_courses.end())
    {
        all_courses[course_id].setPrerequisites("-");
        cout << "Course Prerequisite Deleted Successfully\n";
        cout << "=====================================================\n";
    }
    else if (all_courses.find(course_id_pre) != all_courses.end() && all_courses.find(course_id) != all_courses.end())
    {
        all_courses[course_id].setPrerequisites(course_id_pre);
        cout << "Course Prerequisite Added Successfully\n";
        cout << "=====================================================\n";
    }
    else if (all_courses.find(course_id_pre) == all_courses.end()) {
        cout << "Prerequisit Course not found\n";
    }
    else {
        cout << "Course Not Found\n";
    }
}







void admin::manageGrades(
    unordered_map<int, unordered_set<string>>& all_registered_courses,
    unordered_map<int, unordered_map<string, grade>>& all_grades, unordered_map<int, Student>& all_students)
{
    string choice;
    cout << "1. Add Grade\n2. Update Grade\nEnter your choice: ";
    cin >> choice;

    if (choice == "1") {
        string student_id, course_id;
        string degree;
        string semester;

        cout << "Enter Student ID: ";
        cin >> student_id;
        cout << "Enter Course ID: ";
        cin >> course_id;
        int sID = -1;
        bool check = false;
        try {
            sID = stoi(student_id);
            auto it = all_registered_courses.find(sID);
            if (it != all_registered_courses.end()) {
                if (it->second.find(course_id) != it->second.end())
                    check = true;
            }
        }
        catch (exception& e) {}

        if (check) {
            do {
                cout << "Enter Degree [0-100]: ";
                cin >> degree;
                try {
                    float numeric = stof(degree);
                    if (numeric < 0 || numeric > 100) {
                        cout << "Degree should be in range [0,100]. Try again.\n";
                    }
                    else {
                        break;
                    }
                }
                catch (exception& e) {
                    cout << "Degree must be a numeric value between 0 and 100. Try again.\n";
                }
            } while (true);
            int sem;
            sem = all_students[sID].getsemester();

            semester = to_string(sem);
            int stdID = stoi(student_id);
            float deg;
            try {
                deg = stof(all_grades[stdID][course_id].degree);
            }
            catch (exception e) {
                deg = 0;
            }
            if (all_grades[stdID].find(course_id) != all_grades[stdID].end() && semester == all_grades[stdID][course_id].semester && deg > 60) {

                cout << "This grade is already entered for this student and course.\n";
            }
            else {
                grade g = { degree, semester };
                all_grades[stdID][course_id] = g;
                cout << "Grade added successfully!\n";
                cout << "=====================================================\n";
                all_students[stdID].add_completed_course(course_id, g);
                all_registered_courses[stdID].erase(course_id);

            }

        }
        else {
            cout << "Student ID or Course ID not found in the system.\n";
        }

    }
    else if (choice == "2") {
        string student_id, course_id;
        string degree;
        string semester;

        cout << "Enter Student ID: ";
        cin >> student_id;
        cout << "Enter Course ID: ";
        cin >> course_id;
        int stdID = -1;
        bool check = false;
        try {
            stdID = stoi(student_id);
            auto it = all_registered_courses.find(stdID);
            if (it != all_registered_courses.end()) {
                if (it->second.find(course_id) != it->second.end())
                    check = true;
            }
        }
        catch (exception& e) {}
        if (all_grades[stdID].find(course_id) != all_grades[stdID].end()) {
            grade current = all_grades[stdID][course_id];
            cout << "Current Degree: " << current.degree << "\n";
            cout << "Current Semester: " << current.semester << "\n";

            do {
                cout << "Enter New Degree [0-100]: ";
                cin >> degree;
                try {
                    float numeric = stof(degree);
                    if (numeric < 0 || numeric > 100) {
                        cout << "Degree should be in range [0,100]. Try again.\n";
                    }
                    else {
                        break;
                    }
                }
                catch (exception& e) {
                    cout << "Degree must be a numeric value between 0 and 100. Try again.\n";
                }
            } while (true);


            semester = current.semester;

            grade g = { degree, semester };
            all_grades[stdID][course_id] = g;
            cout << "Grade updated successfully!\n";
            cout << "=====================================================\n";
            all_students[stdID].updateGrade(course_id, g);

        }
        else {
            cout << "No grade found for this student in this course.\n";
        }

    }
    else {
        cout << "Invalid choice.\n";

    }
}


void admin::notificaton(unordered_map <int, notification> n)
{
    if (!n.empty())
    {
        for (auto it = n.begin();it != n.end();it++)
        {

            if (!it->second.registering.empty())
                for (auto myset = it->second.registering.begin(); myset != it->second.registering.end(); myset++)
                {
                    cout << "sid: " << it->first;
                    cout << " wants to add:";
                    cout << *myset << endl;
                }

            if (!it->second.deleting.empty())
                for (auto myset = it->second.deleting.begin(); myset != it->second.deleting.end(); myset++)
                {
                    cout << "sid: " << it->first;
                    cout << " wants to delete:";
                    cout << *myset << endl;

                }
        }
        cout << endl;
    }
    else
    {
        cout << "empty list! \n";
    }
    cout << "=====================================================\n";
}

bool response_checker()
{
    string ch;
    cout << "done! \n";
    cout << "Do you to continue to next request? \n";
    cout << "To continue press (y/Y)\n";
    cin >> ch;
    cin.ignore();
    if (ch == "y" || ch == "Y") { return true; }
    else
        return false;
}

void admin::response(unordered_map <int, notification>& n, unordered_map<int, Student>& all_students, unordered_map<int, unordered_set<string>>& all_registered_courses)
{
    if (!n.empty())
    {
        for (auto it = n.begin(); it != n.end(); it++)
        {
            auto& regSet = it->second.registering;
            for (auto myset = regSet.begin(); myset != regSet.end(); )
            {
                cout << "sid: " << it->first;
                cout << " wants to add:" << *myset << endl;
                string ans;
                cout << "add y/Y ";
                cin >> ans;
                if (ans == "y" || ans == "Y")
                {
                    all_students[it->first].getRegisteredCourses().insert(*myset);
                    all_registered_courses[it->first].insert(*myset);
                    n[it->first].notify_sudent.push_back("admin aproved to add course  " + *myset);
                }
                else
                {
                    n[it->first].notify_sudent.push_back("admin refused to add course  " + *myset);
                }

                regSet.erase(myset++);

                bool b = response_checker();
                if (!b)
                {
                    cout << " returning to main menu...\n";
                    return;
                }
            }

            auto& delSet = it->second.deleting;
            for (auto myset = delSet.begin(); myset != delSet.end(); )
            {
                cout << "sid: " << it->first;
                cout << " wants to delete:" << *myset << endl;
                string ans;
                cout << "delete y/Y ";
                cin >> ans;
                if (ans == "y" || ans == "Y")
                {
                    all_students[it->first].getRegisteredCourses().erase(*myset);
                    all_registered_courses[it->first].erase(*myset);
                    n[it->first].notify_sudent.push_back("admin aproved to delete course  " + *myset);
                }
                else
                {
                    n[it->first].notify_sudent.push_back("admin refused to delete course  " + *myset);
                }

                delSet.erase(myset++);

                bool b = response_checker();
                if (!b)
                {
                    cout << " returning to main menu...\n";
                    return;
                }
            }
        }
        //finshed all
        cout << "end no more requests!\n";
    }
    else
    {
        cout << "empty list! \n";
    }

    cout << "=====================================================\n";
}


admin::~admin() {}

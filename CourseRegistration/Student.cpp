#include "Student.h"

unordered_set<string> Student::getRegisteredCourses()
{
    return registeredCourses;
}

unordered_map<string, string> Student::getCompletedCourses()
{
    return completedCourses;
}

void Student::menu(unordered_map<string, Course> all_courses)
{
    int choice;
    while (true)
    {
        cout << "menu" << endl;
        cout << "press number" << endl;
        cout << "1- Course Registration:" << endl;
        cout << "2- Check Prerequisites:" << endl;
        cout << "3- View Grades:" << endl;
        cout << "4- make a report:" << endl;
        cout << "5- search:" << endl;
        cout << "6- logout:" << endl;
        cin >> choice;
        if (choice == 1)
        {
            
        }
        else if(choice == 2)
        {
            cout << "entre the course id";
            string CourseID;
            cin >> CourseID;
            check_prerequisites(all_courses, CourseID);
        }
        else if (choice == 3)
        {

        }
        else if (choice == 4)
        {

        }
        else if (choice == 5)
        {
           search_courses(all_courses);
        }
        else if (choice == 6)
        {

        }
        else
        {
            cout << "Invalid input";
        }
    }
}

void Student::search_courses(unordered_map<string, Course> all_courses)
{
    int searchChoice;
    cout << "Search by:" << endl;
    cout << "1- Course ID" << endl;
    cout << "2- Course Title" << endl; 
    cin >> searchChoice;
    cin.ignore(1000, '\n');
    if (searchChoice == 1)
    {
        string courseID;
        cout << "Enter course ID: ";
        getline(cin, courseID);
        auto it = all_courses.find(courseID);
        if (it != all_courses.end())
        {
            Course c = it->second;
            cout << "found" << endl;
            cout << "title: " << c.getTitle() << endl;
            cout << " id: " << c.getId() << endl;
            cout << " hours: " << c.getHours() << endl;
            cout << " instructor: " << c.getInstructor() << endl;
            cout << " prerequisites: " << c.getPrerequisites() << endl;
            cout << "syllabus: " << c.getSyllabus() << endl;
        }
        else
        {
            cout << "Course with ID: " << courseID << " not found " << endl;
        }
    }
    else if (searchChoice == 2)
    {
        bool found = false;
        string courseTitle;
        cout << "Enter course Title: ";
        cin >> courseTitle;
        for (auto it = all_courses.begin(); it != all_courses.end();it++)
        {
            Course c = it->second;
            if (c.getTitle() == courseTitle)
            {
                found = true;
                cout << "found" << endl;
                cout << "title: " << c.getTitle() << endl;
                cout << " id: " << c.getId() << endl;
                cout << " hours: " << c.getHours() << endl;
                cout << " instructor: " << c.getInstructor() << endl;
                cout << " prerequisites: " << c.getPrerequisites() << endl;
                cout << "syllabus: " << c.getSyllabus() << endl;
                break;
            }
        }
        if(!found)
        {
            cout << "Course with title: " << courseTitle << " not found " << endl;
        }
    }
    else
    {
        cout << "Invalid input";
    }
   
}

void Student::check_prerequisites(unordered_map<string, Course> all_courses, string courseID)
{
    auto it = all_courses.find(courseID);
    if (it != all_courses.end())
    {
        Course c = it->second;
        cout << "prerequisites for " << c.getTitle() << " is ";
        if (c.getPrerequisites() != "-")
        {
            cout << "Nothig" << endl;
        }
        else
        {
            cout << c.getPrerequisites() << endl;
        }
    }
    else
    {
        cout << "Course with ID: " << courseID << " not found " << endl;
    }
}

void Student::add_completed_course(string course_id, string grade) 
{
    completedCourses[course_id] = grade;
    registeredCourses.erase(course_id);
}

// try
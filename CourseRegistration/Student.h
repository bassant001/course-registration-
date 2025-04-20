#pragma once
#include "User.h"
#include "Course.h"
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;
class Student : public User
{
private:
    unordered_set<string> registeredCourses;              //key:courseID>>>>for courses that are not finished yet
    unordered_map<string, string> completedCourses;       //key:courseID, value:grade>>>>for courses that are finished and has it's grades

public:

    //Getter
    unordered_set<string> getRegisteredCourses();
    unordered_map<string, string> getCompletedCourses();

    //Methods
    void add_completed_course(string course_id, string grade); //dont forget to erase the completed course from registerd
    void menu(unordered_map<string, Course> all_courses);
    void search_courses(unordered_map<string, Course> all_courses);
    void check_prerequisites(unordered_map<string, Course> all_courses, string courseID);
};


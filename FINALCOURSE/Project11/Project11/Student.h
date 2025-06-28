#pragma once
#include "User.h"
#include "Course.h"
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
using namespace std;

struct notification
{
    //fields
    unordered_set<string> registering; //courses student want to register in the middle of smaster
    unordered_set<string> deleting;   //courses student want to delete from registed courses
    vector<string> notify_sudent; //massege of course aproved to delete or add 
    int counterR = 0;
    int counterD = 0;
    
};

struct grade 
{
    string degree;
    string semester;
};

class Student : public User
{
private:
    unordered_set<string> registeredCourses; //key:courseID>>>>for courses that are not finished yet
    unordered_map<string,grade> completedCourses; //key:courseID, value:(grade which is degree and semester)
    int total_hours = 0;

public:
    Student();
    Student(int id);
    Student(int id, unordered_set<string> rc, unordered_map<string, grade> cc);

    //Getter
    unordered_set<string>& getRegisteredCourses();
    unordered_map<string, grade>& getCompletedCourses();
    

    //Methods
    void setID(int id);
    void setname(string name);
    void add_completed_course(string course_id, grade g); //dont forget to erase the completed course from registerd
    void menu(unordered_map<string, Course> all_courses, unordered_map<int, unordered_set<string>>& all_registered_courses, unordered_map <int, notification>& n);
    Course  search_courses(unordered_map<string, Course> all_courses);
    void check_prerequisites(unordered_map<string, Course> all_courses, string courseID);
    void view_registered_courses();
    void register_course(unordered_map<string, Course> all_courses, unordered_map<int, unordered_set<string>>& all_registered_courses);
    Course search_courses(unordered_map<string, Course> all_courses, string id);
    void veiw_grades(unordered_map<string, Course> all_courses);
    float calc_GPA(unordered_map<string, Course> all_courses);
    void Report(unordered_map<string, Course> all_courses);
    void setSemester(int semester);
    int calctotalhours(unordered_map<string, Course> all_courses);
    void updateGrade(string course_id,grade g);
    bool checker();
    void veiw_notification(unordered_map <int, notification>& n);
    void settotalzero();
    // these methods to edit registred courses and need admin approve
    void exception_registration(unordered_map <int, notification>& n, unordered_map<string, Course> all_courses); //to register in the middle of the smaster
    void deleting_registred(unordered_map <int, notification>& n, unordered_map<string, Course> all_courses); //to delete a regesterd course
    int calccounterR(unordered_map<string, Course> all_courses, unordered_map <int, notification>& n);
    int calccounterD(unordered_map<string, Course> all_courses, unordered_map <int, notification>& n);
};



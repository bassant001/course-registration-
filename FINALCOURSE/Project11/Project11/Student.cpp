#include "Student.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

Student::Student() {}

Student::Student(int id) : User(id) {}

Student::Student(int id, unordered_set<string> rc, unordered_map<string, grade> cc) : User(id), registeredCourses(rc), completedCourses(cc) {}

// setters
void Student::setID(int id) { this->id = id; }

void Student::setname(string name) { this->name = name; }

void Student::setSemester(int semester) { this->semester = semester; }

unordered_set<string> &Student::getRegisteredCourses() { return registeredCourses; }

unordered_map<string, grade> &Student::getCompletedCourses() { return completedCourses; }

void Student::menu(unordered_map<string, Course> all_courses, unordered_map<int, unordered_set<string>> &all_registered_courses_for_all_students, unordered_map<int, notification> &n)
{
    calctotalhours(all_courses);
    string choice;
    while (true)
    {
        veiw_notification(n);

        cout << " welcome student: " << this->name << endl;
        cout << "1- Course Registration:" << endl;
        cout << "2- Check Prerequisites:" << endl;
        cout << "3- View Grades:" << endl;
        cout << "4- make a report:" << endl;
        cout << "5- search:" << endl;
        cout << "6- veiw registered courses:" << endl;
        cout << "7- edit registered courses:" << endl;
        cout << "8- logout:" << endl;
        cout << "press number" << endl;
        cin >> choice;
        if (choice == "1")
        {
            if (checker())
            {
                // note when registering a new course insert it in both all_registered_courses_for_all_students and in all_registered_courses_for_student_object
                register_course(all_courses, all_registered_courses_for_all_students);
            }
        }
        else if (choice == "2")
        {
            if (checker())
            {
                cout << "entre the course id: ";
                string CourseID;
                cin >> CourseID;
                check_prerequisites(all_courses, CourseID);
            }
        }
        else if (choice == "3")
        {
            if (checker())
            {
                veiw_grades(all_courses);
                cout << endl;
            }
        }
        else if (choice == "4")
        {
            if (checker())
            {
                Report(all_courses);
            }
        }
        else if (choice == "5")
        {
            if (checker())
            {
                search_courses(all_courses);
            }
        }
        else if (choice == "6")
        {
            if (checker())
            {
                view_registered_courses();
            }
        }
        else if (choice == "7")
        {
            if (checker())
            {
                cout << " note this process needs admin aprovall\n";
                cout << "1 delete course\n";
                cout << "2 add course\n";
                string c;
                cin >> c;
                if (c == "1")
                {
                    deleting_registred(n, all_courses);
                }
                else if (c == "2")
                {
                    exception_registration(n, all_courses);
                }
                else
                {
                    cout << " invalid input returning to menu..........\n\n";
                }
            }
        }

        else if (choice == "8")
        {
            if (checker())
            {
                this->total_hours = 0;
                n[this->id].counterR = 0;
                n[this->id].counterD = 0;
                cout << "loging out...." << endl;
                cout << "=====================================================\n";
                break;
            }
        }
        else
        {
            cout << "Invalid input" << endl;
        }
    }
    cout << endl;
}
Course Student::search_courses(unordered_map<string, Course> all_courses)
{
    string searchChoice;
    cout << "Search by:" << endl;
    cout << "1- Course ID" << endl;
    cout << "2- Course Title" << endl;
    cin >> searchChoice;
    cin.ignore(1000, '\n');
    if (searchChoice == "1")
    {
        string courseID;
        cout << "Enter course ID: ";
        getline(cin, courseID);
        auto it = all_courses.find(courseID);
        if (it != all_courses.end())
        {
            Course c = it->second;
            cout << " found" << endl;
            cout << " title: " << c.getTitle() << endl;
            cout << " id: " << c.getId() << endl;
            cout << " hours: " << c.getHours() << endl;
            cout << " instructor: " << c.getInstructor() << endl;
            cout << " prerequisites: " << c.getPrerequisites() << endl;
            cout << " syllabus: " << c.getSyllabus() << endl;
            return c;
        }
        else
        {
            cout << "Course with ID: " << courseID << " not found " << endl
                 << endl;
            return search_courses(all_courses);
        }
    }
    else if (searchChoice == "2")
    {
        bool found = false;
        string courseTitle;
        cout << "Enter course Title: ";
        getline(cin, courseTitle);
        for (auto it = all_courses.begin(); it != all_courses.end(); it++)
        {
            Course c = it->second;
            if (c.getTitle() == courseTitle)
            {
                found = true;
                cout << " found" << endl;
                cout << " title: " << c.getTitle() << endl;
                cout << " id: " << c.getId() << endl;
                cout << " hours: " << c.getHours() << endl;
                cout << " instructor: " << c.getInstructor() << endl;
                cout << " prerequisites: " << c.getPrerequisites() << endl;
                cout << " syllabus: " << c.getSyllabus() << endl;
                return c;
            }
        }
        if (!found)
        {
            cout << "Course with title: " << courseTitle << " not found " << endl;
        }
    }
    else
    {
        cout << "Invalid input\n";
    }
    cout << "=====================================================\n";
    return Course();
}

Course Student::search_courses(unordered_map<string, Course> all_courses, string courseID)
{
    auto it = all_courses.find(courseID);
    if (it != all_courses.end())
    {
        Course c = it->second;
        return c;
    }
    else
    {
        cout << "Course with ID: " << courseID << " not found " << endl;
    }

    return Course();
}

void Student::check_prerequisites(unordered_map<string, Course> all_courses, string courseID)
{
    auto it = all_courses.find(courseID);
    if (it != all_courses.end())
    {
        Course c = it->second;
        cout << "prerequisites for " << c.getId() << " is ";
        if (c.getPrerequisites() == "-")
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
    cout << "=====================================================\n";
}

void Student::add_completed_course(string course_id, grade g)
{
    completedCourses[course_id] = g;

    registeredCourses.erase(course_id);
}

void Student::view_registered_courses()
{
    int count = 0;
    for (auto it = registeredCourses.begin(); it != registeredCourses.end(); it++)
    {
        count++;
        cout << " course number: " << count << endl;
        cout << " course id: " << *it << endl
             << endl;
    }
    if (count == 0)
    {
        cout << " there is no registered courses\n"
             << endl;
    }
}

int Student::calctotalhours(unordered_map<string, Course> all_courses) // this will cont total hours our student have
{
    total_hours = 0;
    for (auto it = registeredCourses.begin(); it != registeredCourses.end(); it++)
    {
        Course c = search_courses(all_courses, *it);
        total_hours += c.getHours();
    }
    return total_hours;
}

void Student::updateGrade(string course_id, grade g)
{
    completedCourses[course_id] = g;
}

bool Student::checker()
{
    string ch;
    cout << "Do you want to do this process ? \n";
    cout << "To continue press (y/Y)\n";
    cin >> ch;
    cin.ignore();
    if (ch == "y" || ch == "Y")
    {
        return true;
    }
    else
        return false;
}

void Student::veiw_grades(unordered_map<string, Course> all_courses)
{
    cout << "=====================================================\n";
    cout << setw(20) << "Course Name"
         << setw(15) << "Semester"
         << setw(10) << "Grade" << endl;

    for (auto it = completedCourses.begin(); it != completedCourses.end(); it++)
    {
        Course c = search_courses(all_courses, it->first);
        float d = stof(it->second.degree); // fixed
        cout << setw(20) << c.getTitle()
             << setw(15) << it->second.semester << setw(7) << it->second.degree;

        if (d <= 100 && d >= 97)
            cout << " [A+]" << endl;
        else if (d < 97 && d >= 93)
            cout << " [A]" << endl;
        else if (d < 93 && d >= 89)
            cout << " [A-]" << endl;
        else if (d < 89 && d >= 84)
            cout << " [B+]" << endl;
        else if (d < 84 && d >= 80)
            cout << " [B]" << endl;
        else if (d < 80 && d >= 76)
            cout << " [B-]" << endl;
        else if (d < 76 && d >= 73)
            cout << " [C+]" << endl;
        else if (d < 73 && d >= 70)
            cout << " [C]" << endl;
        else if (d < 70 && d >= 67)
            cout << " [C-]" << endl;
        else if (d < 67 && d >= 64)
            cout << " [D+]" << endl;
        else if (d < 64 && d >= 60)
            cout << " [D]" << endl;
        else
            cout << " [F]" << endl;
    }
    cout << "=====================================================\n";
}

void Student::Report(unordered_map<string, Course> all_courses)
{
    ofstream file("Student_Report.txt");

    if (!file.is_open())
    {
        cout << "Error: Could not open the file!" << endl;
        return;
    }

    file << "===============================\n";
    file << left << setw(15) << "Student Name:" << name << "\n";
    file << left << setw(15) << "Student ID:" << id << "\n";
    file << "-------------------------------\n";

    file << "Completed Courses & Grades:\n";
    file << left << setw(20) << "Course Name"
         << setw(15) << "Semester"
         << setw(10) << "Grade" << "\n";
    file << string(45, '-') << "\n";

    for (auto it = completedCourses.begin(); it != completedCourses.end(); it++)
    {
        Course c = search_courses(all_courses, it->first);

        file << left << setw(20) << c.getTitle()
             // fix
             << setw(15) << it->second.semester
             << it->second.degree;
        float d = stof(it->second.degree);
        if (d <= 100 && d >= 97)
            file << " [A+]" << endl;
        else if (d < 97 && d >= 93)
            file << " [A]" << endl;
        else if (d < 93 && d >= 89)
            file << " [A-]" << endl;
        else if (d < 89 && d >= 84)
            file << " [B+]" << endl;
        else if (d < 84 && d >= 80)
            file << " [B]" << endl;
        else if (d < 80 && d >= 76)
            file << " [B-]" << endl;
        else if (d < 76 && d >= 73)
            file << " [C+]" << endl;
        else if (d < 73 && d >= 70)
            file << " [C]" << endl;
        else if (d < 70 && d >= 67)
            file << " [C-]" << endl;
        else if (d < 67 && d >= 64)
            file << " [D+]" << endl;
        else if (d < 64 && d >= 60)
            file << " [D]" << endl;
        else
            file << " [F]" << endl;
    }
    file << "-------------------------------\n";

    float GPA = calc_GPA(all_courses);
    file << left << setw(15) << "CGPA:" << fixed << setprecision(2) << GPA << "\n";
    file << "===============================\n";

    file.close();
    cout << "Report saved as 'Student_Report.txt'" << endl;
    cout << "=====================================================\n";
}

float Student::calc_GPA(unordered_map<string, Course> all_courses)
{
    float TotalPoints = 0;
    int TotalHours = 0;
    for (auto it = completedCourses.begin(); it != completedCourses.end(); it++)
    {
        Course c = search_courses(all_courses, it->first);
        if (stof(it->second.degree) >= 93)
            TotalPoints += 4.0 * c.getHours();
        else if (stof(it->second.degree) >= 89)
            TotalPoints += 3.7 * c.getHours();
        else if (stof(it->second.degree) >= 84)
            TotalPoints += 3.3 * c.getHours();
        else if (stof(it->second.degree) >= 80)
            TotalPoints += 3.0 * c.getHours();
        else if (stof(it->second.degree) >= 76)
            TotalPoints += 2.7 * c.getHours();
        else if (stof(it->second.degree) >= 73)
            TotalPoints += 2.3 * c.getHours();
        else if (stof(it->second.degree) >= 70)
            TotalPoints += 2.0 * c.getHours();
        else if (stof(it->second.degree) >= 67)
            TotalPoints += 1.7 * c.getHours();
        else if (stof(it->second.degree) >= 64)
            TotalPoints += 1.3 * c.getHours();
        else if (stof(it->second.degree) >= 60)
            TotalPoints += 1.0 * c.getHours();
        else
            TotalPoints += 0.0 * c.getHours();

        TotalHours += c.getHours();
    }

    return (TotalHours > 0) ? (TotalPoints / TotalHours) : 0.0;
}

void Student::register_course(unordered_map<string, Course> all_courses, unordered_map<int, unordered_set<string>> &all_registered_courses)
{
    // let number of hours for each smester = 10h (at most) and 1 (at least)
    // so obligatory he has to register for 1 hours to proceeed
    // every year when register smaster++
    // dont allow new registertion call befor making sure the resgiterd courses are empty  to make sure smester ened
    /*calctotalhours(all_courses);*/

    int least_hours = 5, most_hours = 10; // bulid condition on those
    string flag;
    bool succeed = false; // to inreaase if true

    if (!registeredCourses.empty())
    {
        cout << "you have to wait for the new semester and finish your registered Courses first!" << endl;
    }

    else
    {
        int comp = 0;

        if (completedCourses.empty())
            comp++;
        else
        {
            for (auto it = completedCourses.begin(); it != completedCourses.end(); it++)
            {

                if (stof(it->second.semester) == semester)
                {
                    if (stof(it->second.degree) >= 60)
                    {
                        comp++;
                    }
                }
            }
        }

        if (comp > 0)

        {
            cout << "you have to register at least 5h and at most for 10h " << endl;

            do
            {
                flag = "";
                cout << "your total hours now are: " << total_hours << endl
                     << endl;

                Course found;
                cout << "search for the course you want to register " << endl;
                found = search_courses(all_courses);

                if (found.getId() != "")
                {
                    string answer;
                    cout << "is this the course you want to register ? enter 'yes' or 'no' : ";
                    cin >> answer;
                    if (answer == "yes" || answer == "Yes")
                    {
                        bool compeleted = false;
                        if (registeredCourses.find(found.getId()) != registeredCourses.end())
                        {

                            cout << "this course is already registered. you can't register it again" << endl;
                            compeleted = true;
                        }
                        else if (completedCourses.find(found.getId()) != completedCourses.end())
                        {
                            if ((stof(completedCourses.find(found.getId())->second.degree) >= 60))
                            {
                                cout << "this course is already completed. you can't register it again" << endl;
                                compeleted = true;
                            }
                        }
                        if (!compeleted)
                        {

                            bool done;
                            // cout << " checking prerequisites for this course ";
                            if (found.getPrerequisites() != "-")
                            {
                                string preq = found.getPrerequisites();
                                if (completedCourses.find(preq) != completedCourses.end())
                                {
                                    if (stof(completedCourses.find(preq)->second.degree) >= 60)
                                    {
                                        cout << "the prerequisites for this course is completed. " << endl;
                                        done = true;
                                    }
                                    else
                                    {
                                        cout << "the prerequisites for this course is not completed . this course can't be registered " << endl;
                                        done = false;
                                    }
                                }
                                else
                                {
                                    cout << "the prerequisites for this course is not completed . this course can't be registered " << endl;
                                    done = false;
                                }
                            }
                            else
                            {
                                cout << "there is no prerequisites for this course. " << endl;
                                done = true;
                            }

                            if (done)
                            {
                                if (total_hours + found.getHours() <= 10)
                                {
                                    registeredCourses.insert(found.getId());
                                    all_registered_courses[this->id].insert(found.getId());
                                    total_hours += found.getHours();
                                    cout << " the course is registered successfully " << endl;
                                    succeed = true; // if at least one course is added he can begian a new smaster
                                }
                                else
                                {
                                    cout << "you cant register more than 10 h" << endl
                                         << endl;
                                    cout << "total hours for " << found.getTitle() << " is:" << found.getHours() << endl;
                                }
                            }
                        }
                        cout << endl;
                    }
                    else if (answer == "no" || answer == "No")
                    {
                        cout << "registration process for this course cancelled" << endl
                             << endl;
                    }
                    else
                    {
                        cout << " Invalid input" << endl
                             << endl;
                    }
                    // ask him if he want to do another regisrtration
                    cout << "total registered hours: " << total_hours << endl;
                }
                // ask if he want
                if (total_hours >= least_hours)
                {
                    flag = "";
                    while (flag != "y" && flag != "Y" && flag != "n" && flag != "N")
                    {
                        cout << " do you want to register for another course? " << endl;
                        cout << " note: if you press N/n you cant change your registered Courses list  " << endl;
                        cout << " answer y/n ";
                        cin >> flag;
                    }
                }

            } while (((flag == "y" || flag == "Y") && total_hours <= most_hours) || total_hours < least_hours);
        }
        else
        {
            cout << "you failed all your courses from last semester." << endl;
            cout << " resgistering all the courses from last semester to the current one." << endl;
            for (auto it = completedCourses.begin(); it != completedCourses.end(); it++)
            {
                if (stof(it->second.semester) == semester)
                {
                    Course c = all_courses.at(it->first);
                    registeredCourses.insert(c.getId());
                    all_registered_courses[this->id].insert(c.getId());
                    total_hours += c.getHours();
                    succeed = true;
                }
            }
            semester--;
        }
    }

    // at the end
    if (total_hours >= least_hours && succeed)
    {
        semester++;
        cout << "registration complete! Semester has started" << endl;
        cout << "new semester number : " << semester << endl
             << endl;
    }
    else if (registeredCourses.empty())
    {
        cout << "you must register at least 5 hours to start a new semester.\n";
        cout << "you can register later" << endl
             << endl;
    }
}

void Student::veiw_notification(unordered_map<int, notification> &n)
{
    auto it = n.find(this->id);
    if (it != n.end())
    {
        int i = 1;

        if (!it->second.notify_sudent.empty())
        {
            cout << "you have a new notification from admin:\n";
            for (auto myset = it->second.notify_sudent.begin(); myset != it->second.notify_sudent.end(); myset++)
            {
                cout << i++ << " " << *myset << endl;
            }
            n[this->id].notify_sudent.clear();
            cout << "=====================================================\n";
        }
    }
}

void Student::deleting_registred(unordered_map<int, notification> &n, unordered_map<string, Course> all_courses)
{
    calccounterD(all_courses, n);
    if (!registeredCourses.empty())
    {
        cout << "entre course id you want to delete : ";
        string cid;
        cin >> cid;
        if (n[this->id].deleting.find(cid) != n[this->id].deleting.end())
        {
            cout << "there is already a request for this course!\n";
            return;
        }
        Course c = search_courses(all_courses, cid);
        if (!c.getId().empty()) // if course exists
        {
            if (registeredCourses.find(cid) != registeredCourses.end())
            {
                if (total_hours - n[this->id].counterD - c.getHours() >= 5)
                {
                    n[this->id].deleting.insert(cid);
                    /* n[this->id].counterD += c.getHours();*/
                    cout << "waite for admin response\n";
                }
                else
                {
                    cout << "Cannot request deletion of this course. Doing so would drop you below the minimum allowed registered hours\n";
                }
            }
            else
            {
                cout << "you cant delete a course that you dont have!\n";
            }
        }
        else
        {
            cout << "this course doesnt exsist!\n";
        }
    }
    else
    {
        cout << "your registered courses is empty!\n";
    }
    cout << "=====================================================\n";
}

void Student::settotalzero()
{
    this->total_hours = 0;
}

void Student::exception_registration(unordered_map<int, notification> &n, unordered_map<string, Course> all_courses)
{
    calccounterR(all_courses, n);
    if (!registeredCourses.empty())
    {
        cout << "entre course id you want to regester for: ";
        string cid;
        cin >> cid;
        if (n[this->id].registering.find(cid) != n[this->id].registering.end())
        {
            cout << "there is already a request for this course!\n";
            return;
        }
        Course c = search_courses(all_courses, cid);
        if (!c.getId().empty()) // if course exists
        {
            if (registeredCourses.find(cid) == registeredCourses.end()) // if course is nt already  registered
            {
                auto it = completedCourses.find(cid);
                
                if (it != completedCourses.end())
                {
                    if (stof(it->second.degree) >=   60)
                    {
                        cout << "this course is already completed and you succed in it. you can't register for it again" << endl;
                        return;
                    }
                    else if (stof(it->second.degree) < 60)
                    {
                        cout << "you have to waite for new smaster to register for this course" << endl;
                        return;
                    }
                }

                // if course wasnt applied for befor  this is the scenrio
                if (c.getPrerequisites() != "-")
                {
                    string preq = c.getPrerequisites();
                    if (completedCourses.find(preq) != completedCourses.end())
                    {
                        if (stof(completedCourses.find(preq)->second.degree) >= 60) // make sure he succed
                        {
                            if (total_hours + n[this->id].counterR + c.getHours() <= 10) // make sure of time limit
                            {

                                cout << "the prerequisites for this course is completed." << endl;
                                cout << "wait for admin response\n";
                                n[this->id].registering.insert(cid);
                                /*  n[this->id].counterR += c.getHours(); */
                            }
                            else
                            {
                                cout << "your request is refused because it exceeds allowed hours\n";
                                cout << "total hours now (registered + requested): " << total_hours + n[this->id].counterR << endl;
                                cout << "course hours you are trying to register: " << c.getHours() << endl;
                            }
                            
                        }
                        
                    }
                    else
                    {
                        cout << "the prerequisites for this course is not completed.\n";
                        cout << "your request is refuesed!\n";
                    }
                }
                else
                {
                    if (total_hours + n[this->id].counterR + c.getHours() <= 10)
                    {
                        cout << "there is no prerequisites for this course.\n";
                        cout << "waite for admin response\n";
                        n[this->id].registering.insert(cid);
                        /*n[this->id].counterR += c.getHours();*/
                    }
                    else
                    {
                        cout << "your request is refused because it exceeds allowed hours\n";
                        cout << "total hours now (registered + requested): " << total_hours + n[this->id].counterR << endl;
                        cout << "course hours you are trying to register: " << c.getHours() << endl;
                    }
                }
            }
            else // course dosnt exsist
            {
                cout << "you already have this course!\n";
            }
        }
        else
        {
            cout << "this course doesnt exsist!\n";
            cout << "returning to menu........\n";
            cout << "=====================================================\n";
            return;
        }
    }
    else
    {
        cout << "your registered courses are empyty and your smaster has not begained yet!\n";
        cout << "please go register direct for courses you want you do not need admin approval\n";
        cout << "returning to menu........\n";
    }
    cout << "=====================================================\n";
}

int Student::calccounterR(unordered_map<string, Course> all_courses, unordered_map<int, notification> &n)
{
    n[this->id].counterR = 0;
    for (auto it = n[this->id].registering.begin(); it != n[this->id].registering.end(); it++)
    {
        Course c = search_courses(all_courses, *it);
        n[this->id].counterR += c.getHours();
    }
    return n[this->id].counterR;
}

int Student::calccounterD(unordered_map<string, Course> all_courses, unordered_map<int, notification> &n)
{
    n[this->id].counterD = 0;
    for (auto it = n[this->id].deleting.begin(); it != n[this->id].deleting.end(); it++)
    {
        Course c = search_courses(all_courses, *it);
        n[this->id].counterD += c.getHours();
    }
    return n[this->id].counterD;
}
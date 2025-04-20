#include "Course.h"
#include "iostream"
using namespace std;


Course::Course(string id, string title, int hours, string prereqs, string syl, string inst, string semester)
{
    this->id = id;
    this->title = title;
    this->hours = hours;
    this->prerequisites = prereqs;
    this->syllabus = syl;
    this->instructor = inst;
    this->semester = semester;
}
Course::Course()
{
}

Course::~Course()
{
}

void Course::setHours(int hours)
{
    this->hours = hours;
}

void Course::setId(string id)
{
    this->id = id;
}

void Course::setInstructor(string instructor)
{
    this->instructor = instructor;
}

void Course::setPrerequisites(string prerequisites)
{
    this->prerequisites = prerequisites;
}

void Course::setSyllabus(string syllabus)
{
    this->syllabus = syllabus;
}

void Course::setTitle(string title)
{
    this->title = title;
}

void Course::setSemester(string semester)
{
    this->semester = semester;
}

int Course::getHours()
{
    return hours;
}

string Course::getId()
{
    return id;
}

string Course::getInstructor()
{
    return instructor;
}

string Course::getPrerequisites()
{
    return prerequisites;
}

string Course::getSyllabus()
{
    return syllabus;
}

string Course::getTitle()
{
    return title;
}

string Course::getSemester()
{
    return semester;
}

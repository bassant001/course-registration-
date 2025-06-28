#include "Course.h"
#include "iostream"
using namespace std;


Course::Course(string id, string title, int hours, string syllabus, string instructor, string prerequisites)
{
    this->id = id;
    this->title = title;
    this->hours = hours;
    this->prerequisites = prerequisites;
    this->syllabus = syllabus;
    this->instructor = instructor;
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



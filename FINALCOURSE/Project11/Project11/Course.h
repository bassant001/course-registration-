#pragma once
#include "string"
using namespace std;

class Course
{
	string title;
	string id;
	string instructor;
	string prerequisites; //contain courseID 
	string syllabus;
	int hours;
	

public:
	Course(string id, string title, int hours, string prereqs, string syl, string inst);
	Course();
	~Course();

	void setTitle(string title);
	void setId(string id);
	void setInstructor(string instructor);
	void setPrerequisites(string prerequisites);
	void setSyllabus(string syllabus);
	void setHours(int hours);
	


	string getTitle();
	string getId();
	string getInstructor();
	string getPrerequisites();
	string getSyllabus();
	int getHours();

};


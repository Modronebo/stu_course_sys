#ifndef COURSE_H
#define COURSE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Course
{
public:
    string code;
    string name;
    string teacher;
    string location;
    int maxStudents;

    Course(const string &code, const string &name, const string &teacher, const string &location, int maxStudents)
        : code(code), name(name), teacher(teacher), location(location), maxStudents(maxStudents) {}
};

#endif
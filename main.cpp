#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "User.h"
#include "Admin.h"
#include "AdminSystem.h"
#include "Student.h"
#include "Course.h"
#include "StudentSystem.h"
#include "menu.h"

using namespace std;

int main()
{
    // 从文件中读取课程信息
    vector<Course> courses;
    ifstream courseFile("course.txt");
    if (courseFile.is_open())
    {
        string code, name, teacher, location;
        int maxStudents;
        while (courseFile >> code >> name >> teacher >> location >> maxStudents)
        {
            Course course(code, name, teacher, location, maxStudents);
            courses.push_back(course);
        }
        courseFile.close();
    }
    else
    {
        cout<<"文件未打开";
    }


    while (true)
    {
        Menu menu1;
        menu1.mainmenu();
    }
    return 0;
}

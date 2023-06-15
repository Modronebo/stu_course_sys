#ifndef ADMINSYSTEM_H
#define ADMINSYSTEM_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Course.h"
#include "Handle.h"
#include "System.h"

using namespace std;

// 管理员系统类
class AdminSystem : public System
{
private:
    vector<Course> courses;

public:
    void addCourse()
    {
        std::string code, name, teacher, location;
        int maxStudents;
        std::cout << "请输入添加课程内容\n";
        std::cout << "课程编号: \n";
        std::cin >> code;
        std::cout << "课程名称: \n";
        std::cin >> name;
        std::cout << "执教老师: \n";
        std::cin >> teacher;
        std::cout << "教学地点: \n";
        std::cin >> location;
        std::cout << "上限人数: \n";
        InputData(cin, "上限人数", maxStudents);

        Course newCourse(code, name, teacher, location, maxStudents);

        std::ofstream courseFile("course.txt", ios::app);
        if (courseFile.is_open())
        {
            courseFile << code << " " << name << " " << teacher << " " << location << " " << maxStudents << " "
                       << "0" << std::endl;
            courseFile.close();
        }

        std::cout << "添加成功！" << std::endl;
        courses.push_back(newCourse);
    }

    void removeCourse()
    {
        std::cout << "课程列表：" << std::endl;
        std::ifstream courseFile("course.txt");
        if (courseFile.is_open())
        {
            std::string line;
            while (getline(courseFile, line))
            {
                std::cout << line << std::endl;
            }
            courseFile.close();
        }
        else
        {
            std::cout << "无法打开课程文件！" << std::endl;
        }
        std::string code;
        std::cout << "请输入所删除课程的编号: ";
        std::cin >> code;

        for (auto it = courses.begin(); it != courses.end(); ++it)
        {
            if ((*it).code == code)
            {
                courses.erase(it);
                break;
            }
        }

        // 更新course.txt文件
        std::ifstream inputFile("course.txt");
        std::ofstream tempFile("temp.txt");
        if (inputFile.is_open() && tempFile.is_open())
        {
            std::string line;
            while (getline(inputFile, line))
            {
                if (line.find(code) == std::string::npos)
                {
                    tempFile << line << std::endl;
                }
            }
            inputFile.close();
            tempFile.close();

            remove("course.txt");
            rename("temp.txt", "course.txt");
            std::cout << "删除课程成功！" << std::endl;
        }
        else
        {
            std::cout << "无法删除课程！" << std::endl;
        }
    }

    void displayCourses()
    {
        for (const auto &course : courses)
        {
            cout << "课程编号: " << course.code << endl;
            cout << "课程名称: " << course.name << endl;
            cout << "执教老师: " << course.teacher << endl;
            cout << "教学地点: " << course.location << endl;
            cout << "上限人数: " << course.maxStudents << endl;
            cout << "-----------------------" << endl;
        }
    }

    void addStudent()
    {
        // 添加学生逻辑
        std::string name, level, college, username, password;
        std::cout << "请输入学生账号: ";
        std::cin >> username;
        std::cout << "请输入学生密码: ";
        std::cin >> password;
        std::cout << "请输入学生姓名: ";
        std::cin >> name;
        std::cout << "请输入学生级数: ";
        std::cin >> level;
        std::cout << "请输入学生学院: ";
        std::cin >> college;

        std::ofstream studentFile("stuacc.txt", ios::app);
        if (studentFile.is_open())
        {
            studentFile << username << " " << password << " " << name << " " << level << " " << college << std::endl;
            studentFile.close();
            std::cout << "添加学生成功！" << std::endl;
        }
        else
        {
            std::cout << "无法打开学生账号文件！" << std::endl;
        }
    }

    void removeStudent()
    {

        // 删除学生逻辑
        displayStudents();
        std::string username;
        std::cout << "请输入要删除的学生账号: ";
        std::cin >> username;

        std::ifstream studentFile("stuacc.txt");
        if (studentFile.is_open())
        {
            vector<std::string> lines;
            std::string line;
            while (getline(studentFile, line))
            {
                lines.push_back(line);
            }
            studentFile.close();

            std::ofstream outFile("stuacc.txt");
            if (outFile.is_open())
            {
                for (const std::string &line : lines)
                {
                    std::stringstream ss(line);
                    std::string usernameInFile;
                    ss >> usernameInFile;
                    if (usernameInFile != username)
                    {
                        outFile << line << std::endl;
                    }
                }
                outFile.close();
                std::cout << "删除学生成功！" << std::endl;
            }
            else
            {
                std::cout << "无法打开学生账号文件！" << std::endl;
            }
        }
        else
        {
            std::cout << "无法打开学生账号文件！" << std::endl;
        }
    }

    void displayStudents()
    {
        std::ifstream studentFile("stuacc.txt");
        if (studentFile.is_open())
        {
            std::string line;
            while (getline(studentFile, line))
            {
                std::cout << line << std::endl;
            }
            studentFile.close();
        }
        else
        {
            std::cout << "无法打开学生账号文件！" << std::endl;
        }
    }
    void changePassword() override
    {
        // 修改密码逻辑
        std::string adminUsername, oldPassword, newPassword;
        std::cout << "请输入管理员账号: ";
        std::cin >> adminUsername;
        std::cout << "请输入原密码: ";
        std::cin >> oldPassword;

        std::ifstream adminFile("adminacc.txt");
        if (adminFile.is_open())
        {
            vector<std::string> lines;
            std::string line;
            while (getline(adminFile, line))
            {
                lines.push_back(line);
            }
            adminFile.close();

            std::ofstream outFile("adminacc.txt");
            if (outFile.is_open())
            {
                bool passwordChanged = false;
                for (const std::string &line : lines)
                {
                    std::stringstream ss(line);
                    std::string username, password;
                    ss >> username >> password;
                    if (username == adminUsername && password == oldPassword)
                    {
                        std::cout << "请输入新密码: ";
                        std::cin >> newPassword;
                        outFile << username << " " << newPassword << std::endl;
                        passwordChanged = true;
                        std::cout << "修改密码成功！" << std::endl;
                    }
                    else
                    {
                        outFile << line << std::endl;
                    }
                }
                if (!passwordChanged)
                {
                    std::cout << "密码错误！" << std::endl;
                }
                outFile.close();
            }
            else
            {
                std::cout << "无法打开管理员账号文件！" << std::endl;
            }
        }
        else
        {
            std::cout << "无法打开管理员账号文件！" << std::endl;
        }
    }
    void changePassword(const string &name_s) {}
};

#endif
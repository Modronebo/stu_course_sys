#ifndef STUDENTSYSTEM_H
#define STUDENTSYSTEM_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "System.h"
using namespace std;

// 学生系统类
class StudentSystem : public System
{
private:
    string studentUsername;

public:
    StudentSystem() {}
    StudentSystem(const string &username) : studentUsername(username) {}

    void displayEnrolledCourses()
    {
        string filename = "choice.txt";
        ifstream file(filename);
        if (file.is_open())
        {
            string code, name, teacher, location;
            int maxStudents;
            int selStudents;
            while (file >> code >> name >> teacher >> location >> maxStudents >> selStudents)
            {
                cout << "课程编号: " << code << endl;
                cout << "课程名称: " << name << endl;
                cout << "执教老师: " << teacher << endl;
                cout << "教学地点: " << location << endl;
                cout << "上限人数: " << maxStudents << endl;
                cout << "已报人数: " << selStudents << endl;
                cout << "-----------------------" << endl;
            }
            file.close();
        }
    }

    void chooseCourse(const string &username)
    {
        ifstream studentCourseData(username + ".txt");
        std::map<string, string> StudentCourses;
        if (studentCourseData.is_open())
        {
            string line;
            while (getline(studentCourseData, line))
            {
                stringstream ss(line);
                string code;
                ss >> code;
                StudentCourses[code] = line;
            }
            studentCourseData.close();
        }

        // 选课逻辑
        string courseCode;
        cout << "请输入所选课程编号: ";
        cin >> courseCode;

        if (StudentCourses.find(courseCode) != StudentCourses.end())
        {
            cout << "重复选课" << endl;
            return;
        }
        
        ifstream courseFile("course.txt");
        if (courseFile.is_open())
        {
            std::map<string, string> courses;
            string line;
            while (getline(courseFile, line))
            {
                stringstream ss(line);
                string code;
                ss >> code;
                courses[code] = line;
            }
            courseFile.close();

            ofstream choiceFile("choice.txt", ios::app);
            if (choiceFile.is_open())
            {
                auto it = courses.find(courseCode);
                if (it != courses.end())
                {
                    string &courseInfo = it->second;
                    stringstream ss(courseInfo);
                    string code, courseName, teacher, location, capacity, enrolled;
                    ss >> code >> courseName >> teacher >> location >> capacity >> enrolled;
                    int capacityInt = stoi(capacity);
                    int enrolledInt = stoi(enrolled);
                    if (enrolledInt < capacityInt)
                    {
                        choiceFile << courseInfo << endl;
                        enrolledInt++;
                        stringstream updatedLine;
                        updatedLine << code << " " << courseName << " " << teacher << " " << location << " " << capacityInt << " " << enrolledInt;
                        courseInfo = updatedLine.str();

                        string studentFilename = username + ".txt";
                        ofstream outFile(studentFilename, ios::app);
                        if (outFile.is_open())
                        {
                            outFile << courseInfo << endl;
                            outFile.close();
                        }
                        else
                        {
                            cout << "无法打开学生文件！" << endl;
                        }

                        cout << "选课成功！" << endl;
                    }
                    else
                    {
                        cout << "此课程已满！" << endl;
                    }
                }
                else
                {
                    cout << "不存在此课程！" << endl;
                }
                choiceFile.close();

                // 更新 course.txt 中的课程信息
                ofstream outFile("course.txt");
                if (outFile.is_open())
                {
                    for (const auto &pair : courses)
                    {
                        outFile << pair.second << endl;
                    }
                    outFile.close();
                }
                else
                {
                    cout << "无法打开课程文件！" << endl;
                }
            }
            else
            {
                cout << "无法打开选课文件！" << endl;
            }
        }
        else
        {
            cout << "无法打开课程文件！" << endl;
        }
    }

    void displayChooseCourses(const string &username)
    {
        // 查看已选课程逻辑
        string studentFilename = username + ".txt";
        ifstream studentFile(studentFilename);
        if (studentFile.is_open())
        {
            cout << "已选课程：" << endl;
            cout<<"课程编码 课程名称 执教老师 上课地点 上限人数 选择排位"<<endl;
            string line;
            while (getline(studentFile, line))
            {
                cout << line << endl;
            }
            studentFile.close();
        }
        else
        {
            cout << "无已选课程！" << endl;
        }
    }

    void dropCourse(const string &username)
    {
        // 退课逻辑
        string courseCode;
        cout << "请输入所退课程编号: ";
        cin >> courseCode;

        string studentFilename = username + ".txt";
        ifstream studentFile(studentFilename);
        if (studentFile.is_open())
        {
            vector<string> lines;
            string line;
            while (getline(studentFile, line))
            {
                lines.push_back(line);
            }
            studentFile.close();

            ofstream outFile(studentFilename);
            if (outFile.is_open())
            {
                bool courseExists = false;
                for (const string &line : lines)
                {
                    stringstream ss(line);
                    string code;
                    ss >> code;
                    if (code != courseCode)
                    {
                        outFile << line << endl;
                    }
                    else
                    {
                        courseExists = true;
                    }
                }
                if (courseExists)
                {
                    // 更新 choice.txt 中的已报人数
                    ifstream courseFile("course.txt");
                    if (courseFile.is_open())
                    {
                        vector<string> courseLines;
                        string courseLine;
                        while (getline(courseFile, courseLine))
                        {
                            courseLines.push_back(courseLine);
                        }
                        courseFile.close();

                        ofstream outFile("course.txt");
                        if (outFile.is_open())
                        {
                            for (const string &line : courseLines)
                            {
                                stringstream ss(line);
                                string code;
                                ss >> code;
                                if (code == courseCode)
                                {
                                    string courseName, teacher, location, capacity, enrolled;
                                    ss >> courseName >> teacher >> location >> capacity >> enrolled;
                                    int enrolledInt = stoi(enrolled);
                                    enrolledInt--;
                                    stringstream updatedLine;
                                    updatedLine << code << " " << courseName << " " << teacher << " " << location << " " << capacity << " " << enrolledInt;
                                    outFile << updatedLine.str() << endl;
                                }
                                else
                                {
                                    outFile << line << endl;
                                }
                            }
                            outFile.close();
                            cout << "退课成功！" << endl;
                        }
                        else
                        {
                            cout << "无法打开选课文件！" << endl;
                        }
                    }
                    else
                    {
                        cout << "无法打开选课文件！" << endl;
                    }
                }
                else
                {
                    cout << "不存在此课程！" << endl;
                }
                outFile.close();
            }
            else
            {
                cout << "无法打开学生文件！" << endl;
            }
        }
        else
        {
            cout << "无已选课程！" << endl;
        }
    }

    void changePassword (const string &name_s) override
    {
        // 修改密码逻辑
        string currentPassword;
        cout << "请输入原密码：";
        cin >> currentPassword;

        // 验证密码是否正确
        ifstream studentFile("stuacc.txt");
        if (studentFile.is_open())
        {
            vector<string> lines;
            string line;
            while (getline(studentFile, line))
            {
                lines.push_back(line);
            }
            studentFile.close();

            bool passwordCorrect = false;
            for (string &line : lines)
            {
                stringstream ss(line);
                string name, grade, college, username, password;
                ss >> username >> password >> name >> grade >> college;
                if (username == name_s && password == currentPassword)
                {
                    passwordCorrect = true;
                    break;
                }
            }

            if (passwordCorrect)
            {
                string newPassword;
                cout << "请输入新密码：";
                cin >> newPassword;

                // 更新密码
                ofstream outFile("stuacc.txt");
                if (outFile.is_open())
                {
                    for (const string &line : lines)
                    {
                        stringstream ss(line);
                        string name, grade, college, username, password;
                        ss >> username >> password >> name >> grade >> college;

                        if (username == name_s)
                        {
                            outFile << username << " " << newPassword << " " << name << " " << grade << " " << college << endl;
                        }
                        else
                        {
                            outFile << line << endl;
                        }
                    }
                    outFile.close();
                    cout << "密码修改成功！" << endl;
                }
                else
                {
                    cout << "无法打开学生文件！" << endl;
                }
            }
            else
            {
                cout << "密码错误！" << endl;
            }
        }
        else
        {
            cout << "无法打开学生文件！" << endl;
        }
    }
    void changePassword() {}
};

#endif
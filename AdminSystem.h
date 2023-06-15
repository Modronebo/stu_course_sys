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

// ����Աϵͳ��
class AdminSystem : public System
{
private:
    vector<Course> courses;

public:
    void addCourse()
    {
        std::string code, name, teacher, location;
        int maxStudents;
        std::cout << "��������ӿγ�����\n";
        std::cout << "�γ̱��: \n";
        std::cin >> code;
        std::cout << "�γ�����: \n";
        std::cin >> name;
        std::cout << "ִ����ʦ: \n";
        std::cin >> teacher;
        std::cout << "��ѧ�ص�: \n";
        std::cin >> location;
        std::cout << "��������: \n";
        InputData(cin, "��������", maxStudents);

        Course newCourse(code, name, teacher, location, maxStudents);

        std::ofstream courseFile("course.txt", ios::app);
        if (courseFile.is_open())
        {
            courseFile << code << " " << name << " " << teacher << " " << location << " " << maxStudents << " "
                       << "0" << std::endl;
            courseFile.close();
        }

        std::cout << "��ӳɹ���" << std::endl;
        courses.push_back(newCourse);
    }

    void removeCourse()
    {
        std::cout << "�γ��б�" << std::endl;
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
            std::cout << "�޷��򿪿γ��ļ���" << std::endl;
        }
        std::string code;
        std::cout << "��������ɾ���γ̵ı��: ";
        std::cin >> code;

        for (auto it = courses.begin(); it != courses.end(); ++it)
        {
            if ((*it).code == code)
            {
                courses.erase(it);
                break;
            }
        }

        // ����course.txt�ļ�
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
            std::cout << "ɾ���γ̳ɹ���" << std::endl;
        }
        else
        {
            std::cout << "�޷�ɾ���γ̣�" << std::endl;
        }
    }

    void displayCourses()
    {
        for (const auto &course : courses)
        {
            cout << "�γ̱��: " << course.code << endl;
            cout << "�γ�����: " << course.name << endl;
            cout << "ִ����ʦ: " << course.teacher << endl;
            cout << "��ѧ�ص�: " << course.location << endl;
            cout << "��������: " << course.maxStudents << endl;
            cout << "-----------------------" << endl;
        }
    }

    void addStudent()
    {
        // ���ѧ���߼�
        std::string name, level, college, username, password;
        std::cout << "������ѧ���˺�: ";
        std::cin >> username;
        std::cout << "������ѧ������: ";
        std::cin >> password;
        std::cout << "������ѧ������: ";
        std::cin >> name;
        std::cout << "������ѧ������: ";
        std::cin >> level;
        std::cout << "������ѧ��ѧԺ: ";
        std::cin >> college;

        std::ofstream studentFile("stuacc.txt", ios::app);
        if (studentFile.is_open())
        {
            studentFile << username << " " << password << " " << name << " " << level << " " << college << std::endl;
            studentFile.close();
            std::cout << "���ѧ���ɹ���" << std::endl;
        }
        else
        {
            std::cout << "�޷���ѧ���˺��ļ���" << std::endl;
        }
    }

    void removeStudent()
    {

        // ɾ��ѧ���߼�
        displayStudents();
        std::string username;
        std::cout << "������Ҫɾ����ѧ���˺�: ";
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
                std::cout << "ɾ��ѧ���ɹ���" << std::endl;
            }
            else
            {
                std::cout << "�޷���ѧ���˺��ļ���" << std::endl;
            }
        }
        else
        {
            std::cout << "�޷���ѧ���˺��ļ���" << std::endl;
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
            std::cout << "�޷���ѧ���˺��ļ���" << std::endl;
        }
    }
    void changePassword() override
    {
        // �޸������߼�
        std::string adminUsername, oldPassword, newPassword;
        std::cout << "���������Ա�˺�: ";
        std::cin >> adminUsername;
        std::cout << "������ԭ����: ";
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
                        std::cout << "������������: ";
                        std::cin >> newPassword;
                        outFile << username << " " << newPassword << std::endl;
                        passwordChanged = true;
                        std::cout << "�޸�����ɹ���" << std::endl;
                    }
                    else
                    {
                        outFile << line << std::endl;
                    }
                }
                if (!passwordChanged)
                {
                    std::cout << "�������" << std::endl;
                }
                outFile.close();
            }
            else
            {
                std::cout << "�޷��򿪹���Ա�˺��ļ���" << std::endl;
            }
        }
        else
        {
            std::cout << "�޷��򿪹���Ա�˺��ļ���" << std::endl;
        }
    }
    void changePassword(const string &name_s) {}
};

#endif
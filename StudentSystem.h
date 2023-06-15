#ifndef STUDENTSYSTEM_H
#define STUDENTSYSTEM_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "System.h"
using namespace std;

// ѧ��ϵͳ��
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
                cout << "�γ̱��: " << code << endl;
                cout << "�γ�����: " << name << endl;
                cout << "ִ����ʦ: " << teacher << endl;
                cout << "��ѧ�ص�: " << location << endl;
                cout << "��������: " << maxStudents << endl;
                cout << "�ѱ�����: " << selStudents << endl;
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

        // ѡ���߼�
        string courseCode;
        cout << "��������ѡ�γ̱��: ";
        cin >> courseCode;

        if (StudentCourses.find(courseCode) != StudentCourses.end())
        {
            cout << "�ظ�ѡ��" << endl;
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
                            cout << "�޷���ѧ���ļ���" << endl;
                        }

                        cout << "ѡ�γɹ���" << endl;
                    }
                    else
                    {
                        cout << "�˿γ�������" << endl;
                    }
                }
                else
                {
                    cout << "�����ڴ˿γ̣�" << endl;
                }
                choiceFile.close();

                // ���� course.txt �еĿγ���Ϣ
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
                    cout << "�޷��򿪿γ��ļ���" << endl;
                }
            }
            else
            {
                cout << "�޷���ѡ���ļ���" << endl;
            }
        }
        else
        {
            cout << "�޷��򿪿γ��ļ���" << endl;
        }
    }

    void displayChooseCourses(const string &username)
    {
        // �鿴��ѡ�γ��߼�
        string studentFilename = username + ".txt";
        ifstream studentFile(studentFilename);
        if (studentFile.is_open())
        {
            cout << "��ѡ�γ̣�" << endl;
            cout<<"�γ̱��� �γ����� ִ����ʦ �Ͽεص� �������� ѡ����λ"<<endl;
            string line;
            while (getline(studentFile, line))
            {
                cout << line << endl;
            }
            studentFile.close();
        }
        else
        {
            cout << "����ѡ�γ̣�" << endl;
        }
    }

    void dropCourse(const string &username)
    {
        // �˿��߼�
        string courseCode;
        cout << "���������˿γ̱��: ";
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
                    // ���� choice.txt �е��ѱ�����
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
                            cout << "�˿γɹ���" << endl;
                        }
                        else
                        {
                            cout << "�޷���ѡ���ļ���" << endl;
                        }
                    }
                    else
                    {
                        cout << "�޷���ѡ���ļ���" << endl;
                    }
                }
                else
                {
                    cout << "�����ڴ˿γ̣�" << endl;
                }
                outFile.close();
            }
            else
            {
                cout << "�޷���ѧ���ļ���" << endl;
            }
        }
        else
        {
            cout << "����ѡ�γ̣�" << endl;
        }
    }

    void changePassword (const string &name_s) override
    {
        // �޸������߼�
        string currentPassword;
        cout << "������ԭ���룺";
        cin >> currentPassword;

        // ��֤�����Ƿ���ȷ
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
                cout << "�����������룺";
                cin >> newPassword;

                // ��������
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
                    cout << "�����޸ĳɹ���" << endl;
                }
                else
                {
                    cout << "�޷���ѧ���ļ���" << endl;
                }
            }
            else
            {
                cout << "�������" << endl;
            }
        }
        else
        {
            cout << "�޷���ѧ���ļ���" << endl;
        }
    }
    void changePassword() {}
};

#endif
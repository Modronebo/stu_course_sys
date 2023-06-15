#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <fstream>
#include <map>
#include "Handle.h"
#include "StudentSystem.h"
#include "AdminSystem.h"
class Menu
{
public:
    void mainmenu()
    {
        std::cout << "��ӭ����ѡ�ι���ϵͳ" << std::endl;
        std::cout << "1. ����Ա��¼" << std::endl;
        std::cout << "2. ѧ����¼" << std::endl;
        std::cout << "0. �˳�ϵͳ" << std::endl;
        std::cout << "����������ѡ��: ";
        int choice;
        do
        {
            InputData (cin, "ѡ��", choice, [](int choice){return choice >= 0 && choice <= 2;});
            if (choice == 1)
            {
                managermenu();
            }
            else if (choice == 2)
            {
                stumenu();
            }
            else if (choice == 0)
            {
                exit(0);
            }
            else
            {
                std::cout << "��Чѡ������������" << std::endl;
            }
        } while (choice != 1 && choice != 2 && choice != 0);
    }

    void managermenu()
    {
        std::string adminUsername, adminPassword;
        std::cout << "���������Ա�˺�: ";
        std::cin >> adminUsername;
        std::cout << "���������Ա����: ";
        std::cin >> adminPassword;

        std::ifstream adminFile("adminacc.txt");
        if (adminFile.is_open())
        {
            std::string username, password;
            bool loginSuccess = false;
            while (adminFile >> username >> password)
            {
                if (username == adminUsername && password == adminPassword)
                {
                    loginSuccess = true;
                    std::cout << "��¼�ɹ�����ӭ����Ա" << adminUsername << "����ϵͳ" << std::endl;
                    system("pause");
                    AdminSystem adminSystem;
                    Admin admin(username, password);
                    while (true)
                    {
                        Admin::printmenu();

                        int choice;
                        std::cin >> choice;

                        switch (choice)
                        {
                        case 1:
                            adminSystem.addCourse();
                            system("pause");
                            break;
                        case 2:
                            adminSystem.removeCourse();
                            system("pause");
                            break;
                        case 3:
                            adminSystem.addStudent();
                            system("pause");
                            break;
                        case 4:
                            adminSystem.removeStudent();
                            system("pause");
                            break;
                        case 5:
                            adminSystem.displayCourses();
                            system("pause");
                            break;
                        case 6:
                            adminSystem.changePassword();
                            system("pause");
                            break;
                        case 7:
                            admin.showuser();
                            system("pause");
                            break;
                        case 0:
                            break;
                        default:
                            std::cout << "��Чѡ������������" << std::endl;
                            break;
                        }

                        if (choice == 0)
                        {
                            system("cls");
                            break;
                        }
                    }
                }
            }
            if (!loginSuccess)
            {
                std::cout << "�˺Ż��������" << std::endl;
                system("pause");
                system("cls");
            }
            adminFile.close();
        }
        else
        {
            std::cout << "�޷��򿪹���Ա�˺��ļ���" << std::endl;
        }
    }

    void stumenu()
    {
        string studentUsername, studentPassword;
        cout << "������ѧ���˺�: ";
        cin >> studentUsername;
        cout << "������ѧ������: ";
        cin >> studentPassword;

        ifstream studentFile("stuacc.txt");
        if (studentFile.is_open())
        {
            string name, level, college, username, password;
            bool loginSuccess = false;
            while (studentFile >> username >> password >> name >> college >> level)
            {
                if (username == studentUsername && password == studentPassword)
                {
                    loginSuccess = true;
                    cout << "��¼�ɹ�����ӭѧ��" << name << "����ϵͳ" << endl;
                    system ("pause");
                    StudentSystem studentSystem(studentUsername);
                    Student student(username,password);
                    while (true)
                    {
                        Student::printmenu();
                        int choice;
                        cin >> choice;

                        if (choice == 1)
                        {
                            studentSystem.displayEnrolledCourses();
                            system ("pause");
                        }
                        else if (choice == 2)
                        {
                            studentSystem.chooseCourse(username);
                            system ("pause");
                        }

                        else if (choice == 3)
                        {
                            studentSystem.displayChooseCourses(username);
                            system ("pause");
                        }
                        else if (choice == 4)
                        {
                            studentSystem.dropCourse(username);
                            system ("pause");
                        }
                        else if (choice == 5)
                        {
                            studentSystem.changePassword(username);
                            system ("pause");
                        }
                        else if (choice==6)
                        {
                            student.showuser();
                            system ("pause");
                        }
                        else if (choice == 0)
                        {
                            system("cls");
                            break;
                        }
                        else
                        {
                            cout << "��Чѡ������������" << endl;
                        }
                    }

                    break;
                }
            }

            if (!loginSuccess)
            {
                std::cout << "�˺Ż��������" << std::endl;
                system("pause");
                system("cls");
            }
            studentFile.close();
        }
        else
        {
            cout << "�޷���ѧ���˺��ļ���" << endl;
        }
    }
};
#endif
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
        std::cout << "欢迎来到选课管理系统" << std::endl;
        std::cout << "1. 管理员登录" << std::endl;
        std::cout << "2. 学生登录" << std::endl;
        std::cout << "0. 退出系统" << std::endl;
        std::cout << "请输入您的选择: ";
        int choice;
        do
        {
            InputData (cin, "选择", choice, [](int choice){return choice >= 0 && choice <= 2;});
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
                std::cout << "无效选择！请重新输入" << std::endl;
            }
        } while (choice != 1 && choice != 2 && choice != 0);
    }

    void managermenu()
    {
        std::string adminUsername, adminPassword;
        std::cout << "请输入管理员账号: ";
        std::cin >> adminUsername;
        std::cout << "请输入管理员密码: ";
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
                    std::cout << "登录成功！欢迎管理员" << adminUsername << "进入系统" << std::endl;
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
                            std::cout << "无效选择！请重新输入" << std::endl;
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
                std::cout << "账号或密码错误" << std::endl;
                system("pause");
                system("cls");
            }
            adminFile.close();
        }
        else
        {
            std::cout << "无法打开管理员账号文件！" << std::endl;
        }
    }

    void stumenu()
    {
        string studentUsername, studentPassword;
        cout << "请输入学生账号: ";
        cin >> studentUsername;
        cout << "请输入学生密码: ";
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
                    cout << "登录成功！欢迎学生" << name << "进入系统" << endl;
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
                            cout << "无效选择！请重新输入" << endl;
                        }
                    }

                    break;
                }
            }

            if (!loginSuccess)
            {
                std::cout << "账号或密码错误" << std::endl;
                system("pause");
                system("cls");
            }
            studentFile.close();
        }
        else
        {
            cout << "无法打开学生账号文件！" << endl;
        }
    }
};
#endif
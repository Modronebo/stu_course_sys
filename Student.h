#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "User.h"
using namespace std;
// 派生类：学生
class Student : public User
{
public:
    Student() {}
    Student(const string &username, const string &password) : User(username, password) {}
    virtual void showuser() override;
    static void printmenu()
    {
        system ("cls");
        cout << "学生系统" << endl;
        cout << "1. 查看当前选课情况" << endl;
        cout << "2. 选课" << endl;
        cout << "3. 查看已选课程" << endl;
        cout << "4. 退课" << endl;
        cout << "5. 修改密码" << endl;
        cout << "6. 确认账号" << endl;
        cout << "0. 返回上级" << endl;
        cout << "请输入您的选择: ";
    }
};
void Student::showuser()
{
    std::cout << "此账号为" << username << endl;
}
#endif
#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "User.h"
#include "System.h"

using namespace std;

// 派生类：管理员
class Admin : public User
{
public:
    Admin() {}
    Admin(const string &username, const string &password) : User(username, password) {}
    virtual void showuser() override;
    static void printmenu()
    {
        system ("cls");
        std::cout << "管理员系统" << std::endl;
        std::cout << "1. 添加课程" << std::endl;
        std::cout << "2. 删除课程" << std::endl;
        std::cout << "3. 添加学生" << std::endl;
        std::cout << "4. 删除学生" << std::endl;
        std::cout << "5. 查看当前选课情况" << std::endl;
        std::cout << "6. 修改密码" << std::endl;
        std::cout << "7. 确认账号" << endl;
        std::cout << "0. 返回上级" << std::endl;
        std::cout << "请输入您的选择: ";
    }
    
};
void Admin::showuser()
{
    std::cout << "此账号为" << username << endl;
}

#endif
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

// �����ࣺ����Ա
class Admin : public User
{
public:
    Admin() {}
    Admin(const string &username, const string &password) : User(username, password) {}
    virtual void showuser() override;
    static void printmenu()
    {
        system ("cls");
        std::cout << "����Աϵͳ" << std::endl;
        std::cout << "1. ��ӿγ�" << std::endl;
        std::cout << "2. ɾ���γ�" << std::endl;
        std::cout << "3. ���ѧ��" << std::endl;
        std::cout << "4. ɾ��ѧ��" << std::endl;
        std::cout << "5. �鿴��ǰѡ�����" << std::endl;
        std::cout << "6. �޸�����" << std::endl;
        std::cout << "7. ȷ���˺�" << endl;
        std::cout << "0. �����ϼ�" << std::endl;
        std::cout << "����������ѡ��: ";
    }
    
};
void Admin::showuser()
{
    std::cout << "���˺�Ϊ" << username << endl;
}

#endif
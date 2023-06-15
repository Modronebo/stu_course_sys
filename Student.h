#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "User.h"
using namespace std;
// �����ࣺѧ��
class Student : public User
{
public:
    Student() {}
    Student(const string &username, const string &password) : User(username, password) {}
    virtual void showuser() override;
    static void printmenu()
    {
        system ("cls");
        cout << "ѧ��ϵͳ" << endl;
        cout << "1. �鿴��ǰѡ�����" << endl;
        cout << "2. ѡ��" << endl;
        cout << "3. �鿴��ѡ�γ�" << endl;
        cout << "4. �˿�" << endl;
        cout << "5. �޸�����" << endl;
        cout << "6. ȷ���˺�" << endl;
        cout << "0. �����ϼ�" << endl;
        cout << "����������ѡ��: ";
    }
};
void Student::showuser()
{
    std::cout << "���˺�Ϊ" << username << endl;
}
#endif
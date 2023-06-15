#ifndef USER_H
#define USER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// ���ࣺ�û�
class User
{
protected:
    string username;
    string password;

public:
    User() {}
    User(const string &username, const string &password) : username(username), password(password) {}

    bool verifyCredentials(const string &enteredUsername, const string &enteredPassword)
    {
        return (username == enteredUsername && password == enteredPassword);
    }
    virtual void showuser() = 0;
};

#endif
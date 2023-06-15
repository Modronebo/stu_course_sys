#ifndef SYSTEM_H
#define SYSTEM_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Course.h"
#include "Handle.h"
using namespace std;

// ����Աϵͳ��
class System
{
public:
    virtual ~System() {}
    virtual void changePassword() = 0;
    virtual void changePassword(const string &name_s) = 0;
};

#endif
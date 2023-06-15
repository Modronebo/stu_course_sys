#ifndef HANDLE_H
#define HANDLE_H
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <functional>
#include <iomanip>
#include <sstream>

template<typename T>
void InputData(std::istream &is, const char * str , T &data)//无检查函数
{
    while(true){
        is >> data;
        if ( is.fail() ){
            is.clear();
            while (is.get() != '\n' && is.good())
                continue;
            std::cerr << "输入错误!\n";
            system ("pause");
            std::cout << "请再次输入"+ std::string(str)+": ";
            continue;
        }   

        break;
    }

    while (is.get() != '\n' && is.good())
        continue;
}

//检查输入是否正常，第二个参数是提示信息（只要变量名），最后一个参数是检查函数，返回值为bool，参数为输入的值
template<typename T, typename Func>
void InputData(std::istream &is, const char * str , T &data, Func check)
{
    while(true){
        is >> data;
        if ( is.fail() ){
            is.clear();
            while (is.get() != '\n' && is.good())
                continue;
            std::cerr << "输入错误!\n";
            system ("pause");
            std::cout << "请再次输入"+ std::string(str)+": ";
            continue;
        }   

        if ( !check(data) ){
            std::cerr << "输入错误!\n";
            while (is.get() != '\n' && is.good())
                continue;
            system ("pause");
            std::cout << "请再次输入"+ std::string(str)+": ";
            continue;
        }

        break;
    }

    while (is.get() != '\n' && is.good())
        continue;
}
//模版函数不建议分离编译，所以放在头文件里
#endif
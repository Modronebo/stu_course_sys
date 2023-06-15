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
void InputData(std::istream &is, const char * str , T &data)//�޼�麯��
{
    while(true){
        is >> data;
        if ( is.fail() ){
            is.clear();
            while (is.get() != '\n' && is.good())
                continue;
            std::cerr << "�������!\n";
            system ("pause");
            std::cout << "���ٴ�����"+ std::string(str)+": ";
            continue;
        }   

        break;
    }

    while (is.get() != '\n' && is.good())
        continue;
}

//��������Ƿ��������ڶ�����������ʾ��Ϣ��ֻҪ�������������һ�������Ǽ�麯��������ֵΪbool������Ϊ�����ֵ
template<typename T, typename Func>
void InputData(std::istream &is, const char * str , T &data, Func check)
{
    while(true){
        is >> data;
        if ( is.fail() ){
            is.clear();
            while (is.get() != '\n' && is.good())
                continue;
            std::cerr << "�������!\n";
            system ("pause");
            std::cout << "���ٴ�����"+ std::string(str)+": ";
            continue;
        }   

        if ( !check(data) ){
            std::cerr << "�������!\n";
            while (is.get() != '\n' && is.good())
                continue;
            system ("pause");
            std::cout << "���ٴ�����"+ std::string(str)+": ";
            continue;
        }

        break;
    }

    while (is.get() != '\n' && is.good())
        continue;
}
//ģ�溯�������������룬���Է���ͷ�ļ���
#endif
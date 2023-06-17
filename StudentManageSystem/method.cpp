#include "method.h"

string method::readFile(const std::string& fileName)
{
    string str = "";
    fstream read(fileName, ios::in);
    if (!read.is_open())
    {
        cerr << fileName << "�ļ���ʧ��" << endl;
        return "";
    }
    char buf[1024];
    while (read.getline(buf, sizeof(buf)))
    {
        str += buf;
        str += "\n";
    }
    read.close();
    return str;
}

void method::writeFile(const std::string& fileName, string str)
{
    fstream write(fileName, ios::out);
    if (!write.is_open())
    {
        cerr << fileName << "�ļ�д��ʧ��" << endl;
        return;
    }
    write << str;
    write.close();
}
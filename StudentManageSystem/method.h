#ifndef METHOD_H
#define METHOD_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class method
{
public:
    method();
    static string readFile(const std::string& fileName);
    static void writeFile(const std::string& fileName, string str);
};

#endif
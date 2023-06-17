#pragma once
#include "Student.h"
#include "Course.h"
#include "Grade.h"
#include <vector>
#include <regex>

using namespace std;

class Management
{
   

public:
    void readstu();
    void readcou();
    void readgra();
    int Choice;
    long long check;
    string pattern;
};

class oprStudent : public Management
{
private:
    vector<Student *> stu_vec;
    vector<Student *> stu_result;

public:
    void readstu();
    void addStudent();
    void removeStudent();
    void modifyStudent();
    void findStudent();
    // oprStudent();/*构造函数用于初始化对象的成员变量。当创建一个类的对象时，会自动调用的构造函数，构造函数可以执行一些的初始化操作，比如分配内存、打开文件等等。*/
};

class oprCourse : public Management
{
private:
    vector<Course *> cou_vec;
    vector<Course *> cou_result;

public:
    void readcou();
    void addCourse();
    void removeCourse();
    void modifyCourse();
    void findCourse();
};
class oprGrade : public Management
{
private:
    vector<Grade*> gra_vec;
    vector<Grade*> gra_result;

public:
    void readgra();
    void addGrade();
    void removeGrade();
    void modifyGrade();
    void findGrade();
    string  sid, cid, score, rank;
    regex reg_sid(string sid);
    regex reg_cid(string cid);
    regex reg_score(string score);
    regex reg_rank(string rank);
};




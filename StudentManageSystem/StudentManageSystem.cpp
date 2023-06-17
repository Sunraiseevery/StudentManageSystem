// StudentManageSystem.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
// #include <string>
#include "Management.h"
#include "Grade.h"

using namespace std;
oprStudent a;
oprCourse b;
oprGrade c;


#include <iostream>

void clear_screen()
{
    std::cout << "\033[2J\033[1;1H";//ANSI 转义序列方式清空屏幕
}
inline void MainMeau()
{
    cout << "---<<STUDENT-MANAGE-SYSTEM>>---" << endl;
    cout << "1.学生信息" << endl;
    cout << "2.课程信息" << endl;
    cout << "3.成绩信息" << endl;
    cout << "4.EXIT" << endl;
};

inline void StudentMeau()
{
    cout << "---学生信息---" << endl;
    cout << "1.增加学生" << endl;
    cout << "2.删除学生" << endl;
    cout << "3.查询学生信息" << endl;
    cout << "4.修改学生信息" << endl;
    cout << "5.返回上一级" << endl;
}

inline void CourseMeau()
{
    cout << "---课程信息---" << endl;
    cout << "1.添加课程" << endl;
    cout << "2.删除课程" << endl;
    cout << "3.查询课程信息" << endl;
    cout << "4.更改课程信息" << endl;
    cout << "5.返回上一级" << endl;
}

inline void MarkMeau()
{
    cout << "---成绩信息---" << endl;
    cout << "1.录入成绩" << endl;
    cout << "2.删除成绩" << endl;
    cout << "3.查询成绩信息" << endl;
    cout << "4.更改成绩信息" << endl;
    cout << "5.返回上一级" << endl;
}

void meau0()
{
    MainMeau();
}
void meau1()
{
start1:
    StudentMeau();
    cin.sync(); // 清空缓冲区
    switch (getchar())
    {
    case '1':
        clear_screen();
        a.readstu();
        a.addStudent();
        clear_screen();
        goto start1;

    case '2':
        clear_screen();
        a.readstu();
        a.removeStudent();
        clear_screen();
        goto start1;

    case '3':
        clear_screen();
        a.readstu();
        a.findStudent();
        system("pause");
        clear_screen();
        // break;
        goto start1;

    case '4':
        clear_screen();
        a.readstu();
        a.modifyStudent();
        clear_screen();
        goto start1;

    case '5':
        clear_screen();
        break;

    default:
        clear_screen();
        cout << "输入错误" << endl
             << endl;

        goto start1;
    }
}
void meau2()
{
start2:
    CourseMeau();
    cin.ignore(100, '\n'); // 清空缓冲区
    switch (getchar())
    {
    case '1':
        clear_screen();
        b.readcou();
        b.addCourse();
        clear_screen();
        goto start2;

    case '2':
        clear_screen();
        b.readcou();
        b.removeCourse();
        clear_screen();
        goto start2;

    case '3':
        clear_screen();
        b.readcou();
        b.findCourse();
        system("pause");
        clear_screen();
        goto start2;

    case '4':
        clear_screen();
        b.readcou();
        b.modifyCourse();
        clear_screen();
        goto start2;
    case '5':
        clear_screen();
        break;

    default:
        clear_screen();
        cout << "输入错353误" << endl
             << endl;
        goto start2;
    }
}
void meau3()
{


start3:
    MarkMeau();
    cin.ignore(100, '\n'); // 清空缓冲区
    switch (getchar())
    {
    case '1':
        clear_screen();
        c.readgra();
        c.addGrade();
 
      
        break;

    case '2':
        clear_screen();
        break;

    case '3':
        clear_screen();
        c.readgra();
        c.findGrade();

 
        break;

    case '4':
        clear_screen();
        break;

    case '5':
        clear_screen();
        break;

    default:
        clear_screen();
        cout << "输入错454误" << endl
             << endl;

        goto start3;
    }
}

int main()
{
    while (true)
    {
        meau0();
        switch (getchar())
        {
        case '1':
            clear_screen();
            meau1();
            break;

        case '2':
            clear_screen();
            meau2();
            break;

        case '3':
            clear_screen();
            meau3();
            break;

        case '4':
            clear_screen();
            goto out;
            break;

        default: // 回车回车会显示错误
            clear_screen();
            cout << "输入错误" << endl
                 << endl;
        }
        cin.ignore(100, '\n'); // 清空缓冲区
    }
out:
    cout << "感谢使用本系统" << endl;

    return 0;
}

// 入门使用技巧:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

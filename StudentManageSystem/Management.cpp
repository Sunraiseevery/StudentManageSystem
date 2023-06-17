// #include "Student.h"
#include "method.h"
#include "Management.h"
#include <sstream>
#include <iomanip>

//regex sid_reg(sid_empty ? ".*" : sid);     // sid 可能为空，需要使用三目运算符进行判断
//regex cid_reg(cid_empty ? ".*" : Grade::cid);     // cid 可能为空，需要使用三目运算符进行判断
//regex score_reg(score_empty ? ".*" : score);   // score 可能为空，需要使用三目运算符进行判断
//regex rank_reg(rank_empty ? ".*" : rank);   // rank 可能为空，需要使用三目运算符进行判断

bool match(const string& text, const regex& reg) {
    regex regex(text);
    return regex_match("", reg);
}
Grade* checkInput(string input_char,string cid,string sid) {
    string rank; string  score; int input_num;
    // 检查输入字符是否为字母或数字
    if (!isdigit(input_char[0])) {
       
        switch (toupper(input_char[0])) {
        case 'A':score= "95";
        case 'B': score= "85";
        case 'C': score= "75";
        case 'D': score= "95";
        case 'E': score= "0";
            cout << "输入的是等级 " << input_char << endl;
            break;
        default:
            cout << "输入无效等级，应该输入“A B C D E ”中一种" << endl;
            break; return nullptr;
        }
        rank = toupper(input_char[0]);
        Grade* grade = new Grade;
        grade->sid = sid;
        grade->cid = cid;
        grade->score = score;
        grade->grade = rank;
        return grade;

    }
    // 检查输入是否是 0-100 以内的数字
    else if (isdigit(input_char[0])) {
        input_num = stoi(input_char); //将输入字符转换为整数
        if (input_num >= 0 && input_num <= 100) {

            score = input_char;
            
            
            if (input_num < 60) {
                rank = "E";
            }
            else if (input_num < 70) {
                rank = "D";
            }
            else if (input_num < 80) {
                rank = "C";
            }
            else if (input_num < 90) {
                rank = "B";
            }
            else if (input_num < 100) {
                rank = "A";
            }
            else {
                rank = "S";
            }

            cout << "输入成绩为： " << input_num <<"\t等级为"<<rank << endl;
            Grade* grade = new Grade;
            grade->sid = sid;
            grade->cid = cid;
            grade->score = score;
            grade->grade = rank;
            return grade;
            
        }
        else {
            cout << "输入超出范围" << endl; return nullptr;
        }
    }
    else {
        cout << "输入无效" << endl; return nullptr;
    }
}
void oprStudent::readstu()
{
    string str = method::readFile("stuinfo.txt");
    stringstream ss(str);
    string line;
    stu_vec.clear();
    while (getline(ss, line))
    {
        Student *stu = new Student;
        istringstream iss(line);

        iss >> stu->id >> stu->name >> stu->classes >> stu->sex;
        stu_vec.push_back(stu);
    }
}

void PrintStudentTableHeader() {
    constexpr int kWidthId = 8;
    constexpr int kMaxNameLength = 20;
    constexpr int kWidthClass = 12;
    cout << setw(kWidthId) << left << "学号" << " "
        << setw(kMaxNameLength) << left << "姓名"
        << setw(kWidthClass) << left << "班级"
        << setw(4) << left << "性别" << endl;
}

void PrintStudentTableData(const vector<Student*>& students) {
    constexpr int kWidthId = 8;
    constexpr int kMaxNameLength = 20;
    constexpr int kWidthClass = 12;
    for (auto&& s : students) {
        cout << setw(kWidthId) << left << s->id << " "
            << setw(kMaxNameLength) << left << s->name
            << setw(kWidthClass) << left << s->classes
            << setw(4) << left << s->sex << endl;
    }
}

void PrintStudentTableFooter(const vector<Student*>& students) {
    cout << "总共有" << students.size() << " 条学生信息" << endl;
}

void oprStudent::findStudent() {
    int choice;
    while (true) {
        cout << "请选择查询方式" << endl;
        cout << "1. 全部查询" << endl;
        cout << "2. 模糊筛选查询" << endl;
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1: {
            constexpr int kWidthId = 8;
            constexpr int kWidthClass = 12;
            constexpr int kMaxNameLength = 20;
            // 输出表头
            PrintStudentTableHeader();
            // 输出表格
            PrintStudentTableData(stu_vec);
            // 输出总数据条数
            PrintStudentTableFooter(stu_vec);
            return;
        }
        case 2: {
            // 模糊搜索关键字
            cout << "请输入查询条件(学号/学生名/班级): ";
            cin.ignore(100, '\n');
            string keyword;
            cin >> keyword;
            regex reg(keyword);
            vector<Student*> found_students;
            for (auto&& elem : stu_vec) {
                if (regex_search(to_string(elem->id), reg) || regex_search(elem->name, reg) || regex_search(elem->classes, reg)) {
                    found_students.push_back(elem);
                }
            }
            // 输出表头
            PrintStudentTableHeader();
            // 输出表格
            PrintStudentTableData(found_students);
            // 输出总数据条数
            PrintStudentTableFooter(found_students);
            return;
        }
        default:
            cout << "输入错误，请重新输入" << endl;
        }
    }
}

void oprStudent::addStudent()
{
    cout << "请输入学号" << endl;
    cin >> check;
    if (!(check >= 100000000000 && check < 1000000000000))
    {
        cout << "不合规范的输入！！！" << endl;
        cin.ignore(100, '\n'); // 清空缓冲区
        cin.clear();
        system("pause");
        return;
    }
    for (auto &elem : stu_vec)
    {
        if (elem->id == check)
        {
            cout << "该学号已存在" << endl;
            cin.ignore(100, '\n'); // 清空缓冲区
            cin.clear();
            system("pause");
            return;
        }
    }
    Student *stu = new Student;
    stu->id = check;
    cout << "请输入姓名" << endl;
    cin >> stu->name;
    cout << "请输入班级" << endl;
    cin >> stu->classes;
    cout << "请输入性别" << endl;
    cin >> stu->sex;
    stu_vec.push_back(stu);

    stringstream writestream;
    for (auto &elem : stu_vec)
    {
        writestream << elem->id << "\t" << elem->name << "\t" << elem->classes << "\t" << elem->sex << endl;
    }
    method::writeFile("stuinfo.txt", writestream.str());
    cout << "添加成功" << endl;
    system("pause");
}

void oprStudent::removeStudent()
{
    cout << "请输入要删除学生的学号:";
    cin.ignore(100, '\n'); // 清空缓冲区
    cin >> pattern;
    for (int i = 0; i < stu_vec.size(); i++)
    {
        if ((to_string(stu_vec[i]->id) == pattern))
        {
            stu_vec.erase(stu_vec.begin() + i);
            stringstream writestream;
            for (auto &elem : stu_vec)
            {
                writestream << elem->id << "\t" << elem->name << "\t" << elem->classes << "\t" << elem->sex << endl;
            }
            method::writeFile("stuinfo.txt", writestream.str());
            cout << "删除成功" << endl;
            system("pause");
            return;
        }
    }
    cout << "该学生不存在" << endl;
    system("pause");
    return;
}

void oprStudent::modifyStudent()
{
    cout << "请输入要更改学生的学号:";
    cin.ignore(100, '\n'); // 清空缓冲区
    cin >> pattern;
    for (int i = 0; i < stu_vec.size(); i++)
    {
        if ((to_string(stu_vec[i]->id) == pattern))
        {
            cout << "请输入新的姓名" << endl;
            cin >> stu_vec[i]->name;
            cout << "请输入新的班级" << endl;
            cin >> stu_vec[i]->classes;
            cout << "请输入新的性别" << endl;
            cin >> stu_vec[i]->sex;
            stringstream writestream;
            for (auto &elem : stu_vec)
            {
                writestream << elem->id << "\t" << elem->name << "\t" << elem->classes << "\t" << elem->sex << endl;
            }
            method::writeFile("stuinfo.txt", writestream.str());
            cout << "更改成功" << endl;
            system("pause");
            return;
        }
    }
    cout << "该学生不存在" << endl;
    system("pause");
    return;
}
// // 操作学生数据

void oprCourse::readcou()
{
    string str = method::readFile("courseinfo.txt");
    stringstream ss(str);
    string line;
    cou_vec.clear();
    while (getline(ss, line))
    {
        Course *cou = new Course;
        istringstream iss(line);

        iss >> cou->cid >> cou->cname >> cou->credit >> cou->chour;
        cou_vec.push_back(cou);
    }
}

void oprCourse::findCourse()
{
    cout << "请选择查询方式" << endl;
    cout << "1.全部查询" << endl;
    cout << "2.模糊筛选查询" << endl;
    cin >> Choice;
    cout << "\033[2J\033[1;1H";
    switch (Choice)
    {
    case 1:
        cout << "课程号*****"
             << "\t"
             << "课程名"
             << "\t"
             << "学分"
             << "\t"
             << "学时" << endl;
        for (auto &elem : cou_vec)
        {
            cout << elem->cid << "\t" << elem->cname << "\t" << elem->credit << "\t" << elem->chour << endl;
        }
        cout << "总共有" << cou_vec.size() << "条课程信息" << endl;
        break;
    case 2:
        cout << "请输入查询条件(课程号/课程名):";
        cin.ignore(100, '\n'); // 清空缓冲区
        cin >> pattern;
        regex reg(pattern);
        for (auto &elem : cou_vec)
        {
            if (regex_search(to_string(elem->cid), reg) || regex_search(elem->cname, reg))
            {
                cout << elem->cid << "\t" << elem->cname << "\t" << elem->credit << "\t" << elem->chour << endl;
            }
        }
        break;
    }
}

void oprCourse::addCourse()
{
    cout << "请输入课程号" << endl;
    cin >> check;
    if (!(check >= 10000000 && check < 100000000))
    {
        cout << "不合规范的输入！！！" << endl;
        cin.ignore(100, '\n'); // 清空缓冲区
        cin.clear();
        system("pause");
        return;
    }
    for (auto &elem : cou_vec)
    {
        if (elem->cid == check)
        {
            cout << "该课程已存在" << endl;
            cin.ignore(100, '\n'); // 清空缓冲区
            cin.clear();
            system("pause");
            return;
        }
    }
    Course *cou = new Course;
    cou->cid = check;
    cout << "请输入课程名字" << endl;
    cin >> cou->cname;
    cout << "请输入学分" << endl;
    cin >> cou->credit;
    if (cin.fail())
    {
        cout << "输入有误" << endl;
        cin.ignore(100, '\n'); // 清空缓冲区
        cin.clear();
        system("pause");
        return;
    }
    cou->chour = (cou->credit * 16.0);
    cou_vec.push_back(cou);

    stringstream writestream;
    for (auto &elem : cou_vec)
    {
        writestream << elem->cid << "\t" << elem->cname << "\t" << elem->credit << "\t" << elem->chour << endl;
    }
    method::writeFile("courseinfo.txt", writestream.str());
    cout << "添加成功" << endl;
    system("pause");
}

void oprCourse::removeCourse()
{
    cout << "请输入要删除的课程号:";
    cin.ignore(100, '\n'); // 清空缓冲区
    cin >> pattern;
    for (int i = 0; i < cou_vec.size(); i++)
    {
        if ((to_string(cou_vec[i]->cid) == pattern))
        {
            cou_vec.erase(cou_vec.begin() + i);
            stringstream writestream;
            for (auto &elem : cou_vec)
            {
                writestream << elem->cid << "\t" << elem->cname << "\t" << elem->credit << "\t" << elem->chour << endl;
            }
            method::writeFile("courseinfo.txt", writestream.str());
            cout << "删除成功" << endl;
            system("pause");
            return;
        }
    }
    cout << "该课程不存在" << endl;
    system("pause");
    return;
}

void oprCourse::modifyCourse()
{
    cout << "请输入要修改的课程号:";
    cin.ignore(100, '\n'); // 清空缓冲区
    cin >> pattern;
    for (int i = 0; i < cou_vec.size(); i++)
    {
        if ((to_string(cou_vec[i]->cid) == pattern))
        {
            cout << "请输入新的课程名" << endl;
            cin >> cou_vec[i]->cname;
            cout << "请输入新的学分" << endl;
            cin >> cou_vec[i]->credit;
            cou_vec[i]->chour = (cou_vec[i]->credit * 16.0);
            stringstream writestream;
            for (auto &elem : cou_vec)
            {
                writestream << elem->cid << "\t" << elem->cname << "\t" << elem->credit << "\t" << elem->chour << endl;
            }
            method::writeFile("courseinfo.txt", writestream.str());
            cout << "更改成功" << endl;
            system("pause");
            return;
        }
    }
    cout << "该课程不存在" << endl;
    system("pause");
    return;
}

void oprGrade:: readgra(){
    string str = method::readFile("grade.txt");
    stringstream ss(str);
    string line;
    gra_vec.clear();
    while (getline(ss, line))
    {
        Grade* gra = new Grade;
        istringstream iss(line);
        iss >> gra->sid >> gra->cid >> gra->score >> gra->grade;
        gra_vec.push_back(gra);
    }
};

void oprGrade::addGrade() {
    cout << "请选择" << endl;
    cout << "1.单次录入" << endl;
    cout << "2.多次录入" << endl;
    string sid;
    cin.sync();
    cin.ignore(100, '\n');
    int a;
    cin >> a;
    switch (a) {
    case 1: // 改为数字
        cin.clear();
        cout << "学号" << endl;
        cin >> sid;
        if (sid.length() != 12 || !all_of(sid.begin(), sid.end(), [](char c) -> bool { return isdigit(c); })) {
            cout << "不合规范的输入！！！" << endl;
            cin.sync();
            cin.clear();
            cin.ignore(INT_MAX);
            return; // 直接结束函数
        }
        else {
            string coureid;
            cout << "课程号" << endl;
            cin >> coureid;
            if (coureid.length() != 8 /*|| !all_of(coureid.begin(), sid.end(), [](char c) -> bool { return isdigit(c); })*/) {
                cout << "不合规范的输入！！！" << endl;
                cin.sync();
                cin.clear();
              
                break;// 直接结束函数
            }
            else {
                cout << "输入百分制成绩或者等级" << endl;
                string inputGra;
                cin >> inputGra;
                Grade* pGrade = checkInput(inputGra, coureid, sid);
                if (pGrade == nullptr) {
                    cout << "输入不合法！" << endl;
                    return; // 直接结束函数
                }
                else {
                   
                    cout << pGrade << endl;
                    cout <<pGrade << endl;
                    gra_vec.push_back(pGrade);
                    // do something with the grade vector
                    stringstream writestream;
                    for (auto& elem : gra_vec) {
                        writestream << elem->sid << "\t" << elem->cid << "\t" << elem->score << "\t" << elem->grade << endl;
                    }
                    method::writeFile("grade.txt", writestream.str());
                    cout << "添加成功" << endl;
                    system("pause");
                    delete pGrade;
                }
            }
        }
        break; // case 1 后要有 break

    case 2:
        while (true) {
            cin.clear();
            cout << "学号" << endl;
            cin >> sid;
            if (sid.length() != 12 || !all_of(sid.begin(), sid.end(), [](char c) -> bool { return isdigit(c); })) {
                cout << "不合规范的输入！！！" << endl;
                cin.sync();
                cin.clear();
                cin.ignore(INT_MAX);
                return; // 直接结束函数
            }
            else {
                string coureid;
                cout << "课程号" << endl;
                cin >> coureid;
                if (coureid.length() != 8 /*|| !all_of(coureid.begin(), sid.end(), [](char c) -> bool { return isdigit(c); })*/) {
                    cout << "不合规范的输入！！！" << endl;
                    cin.sync();
                    cin.clear();

                    break;// 直接结束函数
                }
                else {
                    cout << "输入百分制成绩或者等级" << endl;
                    string inputGra;
                    cin >> inputGra;
                    Grade* pGrade = checkInput(inputGra, coureid, sid);
                    if (pGrade == nullptr) {
                        cout << "输入不合法！" << endl;
                        return; // 直接结束函数
                    }
                    else {

                        cout << pGrade << endl;
                        cout << pGrade << endl;
                        gra_vec.push_back(pGrade);
                        // do something with the grade vector
                        stringstream writestream;
                        for (auto& elem : gra_vec) {
                            writestream << elem->sid << "\t" << elem->cid << "\t" << elem->score << "\t" << elem->grade << endl;
                        }
                        method::writeFile("grade.txt", writestream.str());
                        cout << "添加成功" << endl;
                        system("pause");
                        delete pGrade;
                    }
                }
            }
            break;
        }

    default:
        cout << "输入不规范\n返回" << endl;
        return; // 直接结束函数
    }
}

void oprGrade::removeGrade() {
    cin.clear();
    cout << "学号" << endl;
    string sid;
    cin >> sid;
    if (sid.length() != 12 || !all_of(sid.begin(), sid.end(), [](char c) -> bool { return isdigit(c); })) {
        cout << "不合规范的输入！！！" << endl;
        cin.sync();
        cin.clear();
        cin.ignore(INT_MAX);
        return; // 直接结束函数
    }
    else {
        string coureid;
        cout << "课程号" << endl;
        cin >> coureid; \
            if (coureid.length() != 8 /*|| !all_of(coureid.begin(), sid.end(), [](char c) -> bool { return isdigit(c); })*/) {
                cout << "不合规范的输入！！！" << endl;
                cin.sync();
                cin.clear();

                return;// 直接结束函数
            }
            else {
                gra_result.clear();
                stringstream writestream;
              
                for (auto&&gra : gra_vec) {
                    regex sid_reg(sid);
                    regex cid_reg(coureid);
                    if ((regex_search(gra->sid, sid_reg)) && (regex_search(gra->cid, cid_reg) )) {
                       gra_result.push_back(gra);


                    }
                   
                }
                for (auto gra : gra_result) {
                    // 在 gra_vec 中查找 gra 对象的迭代器
                    auto it = std::find(gra_vec.begin(), gra_vec.end(), gra);
                    // 如果找到了，就从 gra_vec 中删除它
                    if (it != gra_vec.end()) {
                        gra_vec.erase(it);
                    }
                }
                method::writeFile("grade.txt", writestream.str());
                cout << "删除成功" << endl;
                
            }
    }
}

void oprGrade::modifyGrade(){
    cout << "1，修改个人信息\t2，修改课程信息及成绩\t" << endl;
    cin.clear(); int ctr;
        cin >> ctr;
        switch (ctr)
        {
        case 1:
            cout << "输入学号" << endl;
            getline(cin, sid);
            cout << "输入课程课程号" << endl;
            getline(cin, cid);
            for (auto gra : gra_vec) {


                if ((regex_search(gra->sid, reg_sid(sid)) || sid.empty()) && (regex_search(gra->cid, reg_cid(cid)) || cid.empty()) && (regex_search(gra->score, reg_score(score)) || score.empty()) && (regex_search(gra->grade, reg_rank(rank)) || rank.empty())
                    )
                {
                    gra_result.push_back(gra);
                    cout << "学号：" << gra->sid << " 课程号：" << gra->cid << " 得分：" << gra->score << " 等级：" << gra->grade << endl;

                }

            }
        case 2:
        default:
            break;
        }


};

void oprGrade::findGrade() {
    cout << "请选择查询方式" << endl;
    cout << "1.全部查询" << endl;
    cout << "2.模糊筛选查询" << endl;
    cin.clear();
    cin >> Choice;
    cout << "\033[2J\033[1;1H";
    vector<Grade*>result;

    switch (Choice)
    {
    case 1: cout << "学号*****"
        << "\t"
        << "课程号"
        << "\t"
        << "得分"
        << "\t"
        << "等级" << endl;
        for (auto& elem : gra_vec)
        {
            cout << elem->sid << "\t" << elem->cid << "\t" << elem->score << "\t" << elem->grade << endl;
        }
        cout << "总共有" << gra_vec.size() << "条课程信息" << endl; break;
  

    case 2:
        cin.clear();
       
        cout << "依次输入成绩的 学号、课程号、得分和等级\n未知信息可回车跳过，默认为空" << endl;
        cin.ignore(100, '\n');
        cout << "请输入成绩学号：";
        getline(cin,sid );
        cout << "输入学号为" << sid << endl;
        cout << "请输入成绩课程号：";
        getline(cin, cid);
        cout << "请输入成绩得分：";
        getline(cin, score);
        cout << "请输入成绩等级：";
        getline(cin, rank);
        for (auto gra : gra_vec) {

        
            if ((regex_search(gra->sid,reg_sid(sid))||sid.empty())&&(regex_search(gra->cid,reg_cid(cid))||cid.empty())&&(regex_search(gra->score,reg_score(score))||score.empty())&&(regex_search(gra->grade,reg_rank(rank))||rank.empty())
                )
            {
                result.push_back(gra);
                cout << "学号：" << gra->sid << " 课程号：" << gra->cid << " 得分：" << gra->score << " 等级：" << gra->grade << endl;

            }
          
        } 
       
        break;

    default: {  
        cout << "da" << endl;
        break; }
    }

}


//for (auto gra : gra_result) {
//    // 在 gra_vec 中查找 gra 对象的迭代器
//    auto it = std::find(gra_vec.begin(), gra_vec.end(), gra);
//    // 如果找到了，就从 gra_vec 中删除它
//    if (it != gra_vec.end()) {
//        gra_vec.erase(it);
//    }
//}
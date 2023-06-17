// #include "Student.h"
#include "method.h"
#include "Management.h"
#include <sstream>
#include <iomanip>

//regex sid_reg(sid_empty ? ".*" : sid);     // sid ����Ϊ�գ���Ҫʹ����Ŀ����������ж�
//regex cid_reg(cid_empty ? ".*" : Grade::cid);     // cid ����Ϊ�գ���Ҫʹ����Ŀ����������ж�
//regex score_reg(score_empty ? ".*" : score);   // score ����Ϊ�գ���Ҫʹ����Ŀ����������ж�
//regex rank_reg(rank_empty ? ".*" : rank);   // rank ����Ϊ�գ���Ҫʹ����Ŀ����������ж�

bool match(const string& text, const regex& reg) {
    regex regex(text);
    return regex_match("", reg);
}
Grade* checkInput(string input_char,string cid,string sid) {
    string rank; string  score; int input_num;
    // ��������ַ��Ƿ�Ϊ��ĸ������
    if (!isdigit(input_char[0])) {
       
        switch (toupper(input_char[0])) {
        case 'A':score= "95";
        case 'B': score= "85";
        case 'C': score= "75";
        case 'D': score= "95";
        case 'E': score= "0";
            cout << "������ǵȼ� " << input_char << endl;
            break;
        default:
            cout << "������Ч�ȼ���Ӧ�����롰A B C D E ����һ��" << endl;
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
    // ��������Ƿ��� 0-100 ���ڵ�����
    else if (isdigit(input_char[0])) {
        input_num = stoi(input_char); //�������ַ�ת��Ϊ����
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

            cout << "����ɼ�Ϊ�� " << input_num <<"\t�ȼ�Ϊ"<<rank << endl;
            Grade* grade = new Grade;
            grade->sid = sid;
            grade->cid = cid;
            grade->score = score;
            grade->grade = rank;
            return grade;
            
        }
        else {
            cout << "���볬����Χ" << endl; return nullptr;
        }
    }
    else {
        cout << "������Ч" << endl; return nullptr;
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
    cout << setw(kWidthId) << left << "ѧ��" << " "
        << setw(kMaxNameLength) << left << "����"
        << setw(kWidthClass) << left << "�༶"
        << setw(4) << left << "�Ա�" << endl;
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
    cout << "�ܹ���" << students.size() << " ��ѧ����Ϣ" << endl;
}

void oprStudent::findStudent() {
    int choice;
    while (true) {
        cout << "��ѡ���ѯ��ʽ" << endl;
        cout << "1. ȫ����ѯ" << endl;
        cout << "2. ģ��ɸѡ��ѯ" << endl;
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1: {
            constexpr int kWidthId = 8;
            constexpr int kWidthClass = 12;
            constexpr int kMaxNameLength = 20;
            // �����ͷ
            PrintStudentTableHeader();
            // ������
            PrintStudentTableData(stu_vec);
            // �������������
            PrintStudentTableFooter(stu_vec);
            return;
        }
        case 2: {
            // ģ�������ؼ���
            cout << "�������ѯ����(ѧ��/ѧ����/�༶): ";
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
            // �����ͷ
            PrintStudentTableHeader();
            // ������
            PrintStudentTableData(found_students);
            // �������������
            PrintStudentTableFooter(found_students);
            return;
        }
        default:
            cout << "�����������������" << endl;
        }
    }
}

void oprStudent::addStudent()
{
    cout << "������ѧ��" << endl;
    cin >> check;
    if (!(check >= 100000000000 && check < 1000000000000))
    {
        cout << "���Ϲ淶�����룡����" << endl;
        cin.ignore(100, '\n'); // ��ջ�����
        cin.clear();
        system("pause");
        return;
    }
    for (auto &elem : stu_vec)
    {
        if (elem->id == check)
        {
            cout << "��ѧ���Ѵ���" << endl;
            cin.ignore(100, '\n'); // ��ջ�����
            cin.clear();
            system("pause");
            return;
        }
    }
    Student *stu = new Student;
    stu->id = check;
    cout << "����������" << endl;
    cin >> stu->name;
    cout << "������༶" << endl;
    cin >> stu->classes;
    cout << "�������Ա�" << endl;
    cin >> stu->sex;
    stu_vec.push_back(stu);

    stringstream writestream;
    for (auto &elem : stu_vec)
    {
        writestream << elem->id << "\t" << elem->name << "\t" << elem->classes << "\t" << elem->sex << endl;
    }
    method::writeFile("stuinfo.txt", writestream.str());
    cout << "��ӳɹ�" << endl;
    system("pause");
}

void oprStudent::removeStudent()
{
    cout << "������Ҫɾ��ѧ����ѧ��:";
    cin.ignore(100, '\n'); // ��ջ�����
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
            cout << "ɾ���ɹ�" << endl;
            system("pause");
            return;
        }
    }
    cout << "��ѧ��������" << endl;
    system("pause");
    return;
}

void oprStudent::modifyStudent()
{
    cout << "������Ҫ����ѧ����ѧ��:";
    cin.ignore(100, '\n'); // ��ջ�����
    cin >> pattern;
    for (int i = 0; i < stu_vec.size(); i++)
    {
        if ((to_string(stu_vec[i]->id) == pattern))
        {
            cout << "�������µ�����" << endl;
            cin >> stu_vec[i]->name;
            cout << "�������µİ༶" << endl;
            cin >> stu_vec[i]->classes;
            cout << "�������µ��Ա�" << endl;
            cin >> stu_vec[i]->sex;
            stringstream writestream;
            for (auto &elem : stu_vec)
            {
                writestream << elem->id << "\t" << elem->name << "\t" << elem->classes << "\t" << elem->sex << endl;
            }
            method::writeFile("stuinfo.txt", writestream.str());
            cout << "���ĳɹ�" << endl;
            system("pause");
            return;
        }
    }
    cout << "��ѧ��������" << endl;
    system("pause");
    return;
}
// // ����ѧ������

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
    cout << "��ѡ���ѯ��ʽ" << endl;
    cout << "1.ȫ����ѯ" << endl;
    cout << "2.ģ��ɸѡ��ѯ" << endl;
    cin >> Choice;
    cout << "\033[2J\033[1;1H";
    switch (Choice)
    {
    case 1:
        cout << "�γ̺�*****"
             << "\t"
             << "�γ���"
             << "\t"
             << "ѧ��"
             << "\t"
             << "ѧʱ" << endl;
        for (auto &elem : cou_vec)
        {
            cout << elem->cid << "\t" << elem->cname << "\t" << elem->credit << "\t" << elem->chour << endl;
        }
        cout << "�ܹ���" << cou_vec.size() << "���γ���Ϣ" << endl;
        break;
    case 2:
        cout << "�������ѯ����(�γ̺�/�γ���):";
        cin.ignore(100, '\n'); // ��ջ�����
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
    cout << "������γ̺�" << endl;
    cin >> check;
    if (!(check >= 10000000 && check < 100000000))
    {
        cout << "���Ϲ淶�����룡����" << endl;
        cin.ignore(100, '\n'); // ��ջ�����
        cin.clear();
        system("pause");
        return;
    }
    for (auto &elem : cou_vec)
    {
        if (elem->cid == check)
        {
            cout << "�ÿγ��Ѵ���" << endl;
            cin.ignore(100, '\n'); // ��ջ�����
            cin.clear();
            system("pause");
            return;
        }
    }
    Course *cou = new Course;
    cou->cid = check;
    cout << "������γ�����" << endl;
    cin >> cou->cname;
    cout << "������ѧ��" << endl;
    cin >> cou->credit;
    if (cin.fail())
    {
        cout << "��������" << endl;
        cin.ignore(100, '\n'); // ��ջ�����
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
    cout << "��ӳɹ�" << endl;
    system("pause");
}

void oprCourse::removeCourse()
{
    cout << "������Ҫɾ���Ŀγ̺�:";
    cin.ignore(100, '\n'); // ��ջ�����
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
            cout << "ɾ���ɹ�" << endl;
            system("pause");
            return;
        }
    }
    cout << "�ÿγ̲�����" << endl;
    system("pause");
    return;
}

void oprCourse::modifyCourse()
{
    cout << "������Ҫ�޸ĵĿγ̺�:";
    cin.ignore(100, '\n'); // ��ջ�����
    cin >> pattern;
    for (int i = 0; i < cou_vec.size(); i++)
    {
        if ((to_string(cou_vec[i]->cid) == pattern))
        {
            cout << "�������µĿγ���" << endl;
            cin >> cou_vec[i]->cname;
            cout << "�������µ�ѧ��" << endl;
            cin >> cou_vec[i]->credit;
            cou_vec[i]->chour = (cou_vec[i]->credit * 16.0);
            stringstream writestream;
            for (auto &elem : cou_vec)
            {
                writestream << elem->cid << "\t" << elem->cname << "\t" << elem->credit << "\t" << elem->chour << endl;
            }
            method::writeFile("courseinfo.txt", writestream.str());
            cout << "���ĳɹ�" << endl;
            system("pause");
            return;
        }
    }
    cout << "�ÿγ̲�����" << endl;
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
    cout << "��ѡ��" << endl;
    cout << "1.����¼��" << endl;
    cout << "2.���¼��" << endl;
    string sid;
    cin.sync();
    cin.ignore(100, '\n');
    int a;
    cin >> a;
    switch (a) {
    case 1: // ��Ϊ����
        cin.clear();
        cout << "ѧ��" << endl;
        cin >> sid;
        if (sid.length() != 12 || !all_of(sid.begin(), sid.end(), [](char c) -> bool { return isdigit(c); })) {
            cout << "���Ϲ淶�����룡����" << endl;
            cin.sync();
            cin.clear();
            cin.ignore(INT_MAX);
            return; // ֱ�ӽ�������
        }
        else {
            string coureid;
            cout << "�γ̺�" << endl;
            cin >> coureid;
            if (coureid.length() != 8 /*|| !all_of(coureid.begin(), sid.end(), [](char c) -> bool { return isdigit(c); })*/) {
                cout << "���Ϲ淶�����룡����" << endl;
                cin.sync();
                cin.clear();
              
                break;// ֱ�ӽ�������
            }
            else {
                cout << "����ٷ��Ƴɼ����ߵȼ�" << endl;
                string inputGra;
                cin >> inputGra;
                Grade* pGrade = checkInput(inputGra, coureid, sid);
                if (pGrade == nullptr) {
                    cout << "���벻�Ϸ���" << endl;
                    return; // ֱ�ӽ�������
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
                    cout << "��ӳɹ�" << endl;
                    system("pause");
                    delete pGrade;
                }
            }
        }
        break; // case 1 ��Ҫ�� break

    case 2:
        while (true) {
            cin.clear();
            cout << "ѧ��" << endl;
            cin >> sid;
            if (sid.length() != 12 || !all_of(sid.begin(), sid.end(), [](char c) -> bool { return isdigit(c); })) {
                cout << "���Ϲ淶�����룡����" << endl;
                cin.sync();
                cin.clear();
                cin.ignore(INT_MAX);
                return; // ֱ�ӽ�������
            }
            else {
                string coureid;
                cout << "�γ̺�" << endl;
                cin >> coureid;
                if (coureid.length() != 8 /*|| !all_of(coureid.begin(), sid.end(), [](char c) -> bool { return isdigit(c); })*/) {
                    cout << "���Ϲ淶�����룡����" << endl;
                    cin.sync();
                    cin.clear();

                    break;// ֱ�ӽ�������
                }
                else {
                    cout << "����ٷ��Ƴɼ����ߵȼ�" << endl;
                    string inputGra;
                    cin >> inputGra;
                    Grade* pGrade = checkInput(inputGra, coureid, sid);
                    if (pGrade == nullptr) {
                        cout << "���벻�Ϸ���" << endl;
                        return; // ֱ�ӽ�������
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
                        cout << "��ӳɹ�" << endl;
                        system("pause");
                        delete pGrade;
                    }
                }
            }
            break;
        }

    default:
        cout << "���벻�淶\n����" << endl;
        return; // ֱ�ӽ�������
    }
}

void oprGrade::removeGrade() {
    cin.clear();
    cout << "ѧ��" << endl;
    string sid;
    cin >> sid;
    if (sid.length() != 12 || !all_of(sid.begin(), sid.end(), [](char c) -> bool { return isdigit(c); })) {
        cout << "���Ϲ淶�����룡����" << endl;
        cin.sync();
        cin.clear();
        cin.ignore(INT_MAX);
        return; // ֱ�ӽ�������
    }
    else {
        string coureid;
        cout << "�γ̺�" << endl;
        cin >> coureid; \
            if (coureid.length() != 8 /*|| !all_of(coureid.begin(), sid.end(), [](char c) -> bool { return isdigit(c); })*/) {
                cout << "���Ϲ淶�����룡����" << endl;
                cin.sync();
                cin.clear();

                return;// ֱ�ӽ�������
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
                    // �� gra_vec �в��� gra ����ĵ�����
                    auto it = std::find(gra_vec.begin(), gra_vec.end(), gra);
                    // ����ҵ��ˣ��ʹ� gra_vec ��ɾ����
                    if (it != gra_vec.end()) {
                        gra_vec.erase(it);
                    }
                }
                method::writeFile("grade.txt", writestream.str());
                cout << "ɾ���ɹ�" << endl;
                
            }
    }
}

void oprGrade::modifyGrade(){
    cout << "1���޸ĸ�����Ϣ\t2���޸Ŀγ���Ϣ���ɼ�\t" << endl;
    cin.clear(); int ctr;
        cin >> ctr;
        switch (ctr)
        {
        case 1:
            cout << "����ѧ��" << endl;
            getline(cin, sid);
            cout << "����γ̿γ̺�" << endl;
            getline(cin, cid);
            for (auto gra : gra_vec) {


                if ((regex_search(gra->sid, reg_sid(sid)) || sid.empty()) && (regex_search(gra->cid, reg_cid(cid)) || cid.empty()) && (regex_search(gra->score, reg_score(score)) || score.empty()) && (regex_search(gra->grade, reg_rank(rank)) || rank.empty())
                    )
                {
                    gra_result.push_back(gra);
                    cout << "ѧ�ţ�" << gra->sid << " �γ̺ţ�" << gra->cid << " �÷֣�" << gra->score << " �ȼ���" << gra->grade << endl;

                }

            }
        case 2:
        default:
            break;
        }


};

void oprGrade::findGrade() {
    cout << "��ѡ���ѯ��ʽ" << endl;
    cout << "1.ȫ����ѯ" << endl;
    cout << "2.ģ��ɸѡ��ѯ" << endl;
    cin.clear();
    cin >> Choice;
    cout << "\033[2J\033[1;1H";
    vector<Grade*>result;

    switch (Choice)
    {
    case 1: cout << "ѧ��*****"
        << "\t"
        << "�γ̺�"
        << "\t"
        << "�÷�"
        << "\t"
        << "�ȼ�" << endl;
        for (auto& elem : gra_vec)
        {
            cout << elem->sid << "\t" << elem->cid << "\t" << elem->score << "\t" << elem->grade << endl;
        }
        cout << "�ܹ���" << gra_vec.size() << "���γ���Ϣ" << endl; break;
  

    case 2:
        cin.clear();
       
        cout << "��������ɼ��� ѧ�š��γ̺š��÷ֺ͵ȼ�\nδ֪��Ϣ�ɻس�������Ĭ��Ϊ��" << endl;
        cin.ignore(100, '\n');
        cout << "������ɼ�ѧ�ţ�";
        getline(cin,sid );
        cout << "����ѧ��Ϊ" << sid << endl;
        cout << "������ɼ��γ̺ţ�";
        getline(cin, cid);
        cout << "������ɼ��÷֣�";
        getline(cin, score);
        cout << "������ɼ��ȼ���";
        getline(cin, rank);
        for (auto gra : gra_vec) {

        
            if ((regex_search(gra->sid,reg_sid(sid))||sid.empty())&&(regex_search(gra->cid,reg_cid(cid))||cid.empty())&&(regex_search(gra->score,reg_score(score))||score.empty())&&(regex_search(gra->grade,reg_rank(rank))||rank.empty())
                )
            {
                result.push_back(gra);
                cout << "ѧ�ţ�" << gra->sid << " �γ̺ţ�" << gra->cid << " �÷֣�" << gra->score << " �ȼ���" << gra->grade << endl;

            }
          
        } 
       
        break;

    default: {  
        cout << "da" << endl;
        break; }
    }

}


//for (auto gra : gra_result) {
//    // �� gra_vec �в��� gra ����ĵ�����
//    auto it = std::find(gra_vec.begin(), gra_vec.end(), gra);
//    // ����ҵ��ˣ��ʹ� gra_vec ��ɾ����
//    if (it != gra_vec.end()) {
//        gra_vec.erase(it);
//    }
//}
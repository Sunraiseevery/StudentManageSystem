//#include "method.h"
//#include "Grade.h"
//#include <sstream>
//
//using namespace std;
//
//Grade::Grade()
//{
//    string str_gra = method::readFile("grade.txt");
//    stringstream ss(str_gra);
//    string line;
//    gra_vec.clear();
//    while (getline(ss, line))
//    {
//        Grade *gra = new Grade;
//        istringstream iss(line);
//
//        iss >> gra->sid >> gra->cid>>gra->score >> gra->grade;
//        gra_vec.push_back(gra);
//    }
//}
//
////Grade::~Grade()
////{
////    for (auto ptr : gra_vec)
////    {
////        delete ptr;
////    }
////}
////
////void Grade::addGrade(){}
////
////void Grade::delGrade()
////{
////}
////
////void Grade::showGrade()
////{
////  
////}
//
//void Grade::modifyGrade()
//{
//}
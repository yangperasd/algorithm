/*************************************************************************
	> File Name: ./src/main.cpp
	> Author: yang 
	> Mail: yangperasd@163.com 
	> Created Time: 2015年09月12日 星期六 10时53分49秒
 ************************************************************************/

#include<iostream>
#include "List.h"
#include <functional>
using namespace std;
class Date
{
    public:
        Date()=default;
        Date& operator=(const Date& lhs)=default;
        Date(const Date& lhs)=default;
        ~Date() {cout<<"~Date"<<endl;}
};
bool operator == (const Date& lhs,const Date& rhs)
{
    return true;
}
int main()
{
    List<Date> L;
    Date a;
    L.InsertNext(NULL,a);
    Date b;
    L.DelNext(NULL,b);
}

/*************************************************************************
	> File Name: ./src/main.cpp
	> Author: yang 
	> Mail: yangperasd@163.com 
	> Created Time: 2015年09月15日 星期二 14时59分15秒
 ************************************************************************/

#include<iostream>
#include <functional>
#include "Set.h"
using namespace std;
int main()
{
    
}

int test()
{
    Set<int> aSet1,aSet2;
    for(int i=0;i<10;++i)
    {
        aSet1.insert(static_cast<int>(random()%10));
    }
    for(auto elem:aSet1)
    cout<<elem<<" ";
    cout<<endl;

    for(int i=0;i<2;++i)
    {
        aSet2.insert(static_cast<int>(random()%10));
    }
    for(auto elem:aSet2)
    cout<<elem<<" ";
    cout<<endl;

    Set<int> aSet3;
    SetUnion(aSet1.begin(),aSet1.end(),aSet2.begin(),aSet2.end(),back_inserter(aSet3),less<int> ());
    
    cout<<"--------------"<<endl;
    for(auto elem:aSet3)
    {
        cout<<elem<<" ";
    }
    cout<<endl;
    
    return 1;
}

/*************************************************************************
	> File Name: ./include/List.h
	> Author: yang 
	> Mail: yangperasd@163.com 
	> Created Time: 2015年09月10日 星期四 21时04分50秒
 ************************************************************************/

#ifndef _LIST_H
#define _LIST_H
template<typename T> 
struct ListElem
{
    T data;
    struct ListElem *next;
};
#endif

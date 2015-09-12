/*************************************************************************
> File Name: ./include/Iterator.h
> Author: yang 
> Mail: yangperasd@163.com 
> Created Time: 2015年09月12日 星期六 16时25分03秒
************************************************************************/

#ifndef _ITERATOR_H
#define _ITERATOR_H
template<typename N,typename D>
//N for Node type, D for Date type
class Iterator
{
    public:
        Iterator(const N& val=nullptr):ptr_(val) {}
        D& operator*();
        D* operator->();
    private:
        N* ptr_;
};
#endif

/*************************************************************************
  > File Name: ./include/List.h
  > Author: yang 
  > Mail: yangperasd@163.com 
  > Created Time: 2015年09月10日 星期四 21时04分50秒
 ************************************************************************/

#ifndef _LIST_H
#define _LIST_H
#include <iostream>
#include <functional>
using std::function;using std::equal_to;

template <typename T > 
class List
{/*{{{*/
    public:
        class LNode
        {/*{{{*/
            public:
                explicit LNode(const T& val):data_(val),pnext_(nullptr) {}
                LNode(T&& val):data_(std::move(val)),pnext_(nullptr) {}
                LNode(const LNode& anode):data_(anode.data_),pnext_(nullptr) {}
                LNode& operator =(const LNode& anode)
                {/*{{{*/
                    if(this!=&anode)
                    {
                        data_=anode.data_;
                        pnext_=nullptr; //we shouldn't let "pnext=anode.pnext_"
                    }
                    return *this;
                }/*}}}*/
                LNode& operator=(LNode&& anode)
                {/*{{{*/
                    if(this!=&anode)
                    {
                        data_=std::move(anode.data_);
                        pnext_=std::move(anode.pnext_);//maybe this is wrong
                    }
                    return *this;
                }/*}}}*/
                ~LNode() {pnext_=nullptr;}

                T data_;
                LNode *pnext_;
        };/*}}}*/
        explicit List(function<bool(const T& lhs,const T& rhs)> ElmMatch=equal_to<T> ()):ElmMatch_(ElmMatch),size_(0),ptail_(nullptr),phead_(nullptr) {}
        ~List();

        bool InsertNext(LNode *ppos,const T& val);
        bool DelNext(LNode *ppos,T& val);
        inline size_t size() const {return size_;}
        inline LNode* begin() const {return phead_;}
        inline LNode* end() const {return ptail_;}
        inline bool isHead(LNode* ptr) const {return ptr==phead_;}
        inline bool isTail(LNode* ptr) const {return ptr==ptail_;}
        inline bool empty() const {return size_==0;}
    private:
        function<bool(const T& lhs,const T& rhs)> ElmMatch_;
        LNode* phead_;
        LNode* ptail_;
        size_t size_;
};/*}}}*/

template<typename T>
bool List<T>::InsertNext(LNode* ppos,const T& val)
{/*{{{*/
    LNode* pnew=new LNode(val);
    if(!pnew) return false;

    if(ppos==nullptr)
    {//insert at the head of the list 
        empty()&&(ptail_=pnew);
        pnew->pnext_=phead_;
        phead_=pnew;
    }
    else 
    {
        pnew->pnext_=ppos->pnext_;
        ppos->pnext_=pnew;
        (!pnew->pnext_)&&(ptail_=pnew);
    }
    ++size_;
    return true;
}/*}}}*/

template<typename T>
bool List<T>::DelNext(LNode* ppos,T& val)
{/*{{{*/
    if(empty()) return false;
    LNode* oldElm;
    if(ppos)
    {
        if(!ppos->pnext_) return false;
        oldElm=ppos->pnext_;
        ppos->pnext_=oldElm->pnext_;
        (!oldElm->pnext_)&&(ptail_=ppos);
    }
    else 
    {
        oldElm=phead_;
        phead_=oldElm->pnext_;
        (!phead_)&&(ptail_=phead_);
    }
    --size_;
    delete oldElm;
    return true;
}/*}}}*/

template<typename T>
List<T>::~List()
{
    while(!empty())
    {
        T val;
        DelNext(NULL,val);
    }
}

#endif

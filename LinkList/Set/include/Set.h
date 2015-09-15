/*************************************************************************
> File Name: ./include/Set.h
> Author: yang 
> Mail: yangperasd@163.com 
> Created Time: 2015年09月15日 星期二 09时12分35秒
************************************************************************/

#ifndef _SET_H
#define _SET_H
#include <list>
#include <utility>
#include <algorithm>
#include <iostream>
using std::list;using std::pair;using std::copy;
template<typename T>
class Set 
{
    public:
    //rename for some type /*{{{*/
    using iterator=typename list<T>::iterator;
    using size_type= typename list<T>::size_type;
    using value_type=typename list<T>::value_type;
    using const_iterator=typename list<T>::const_iterator;/*}}}*/
    public:
    //related to initialization /*{{{*/
    Set()=default;
    Set(const Set&)=default;
    Set(Set&&)=default;
    Set& operator=(const Set&)=default;
    Set& operator=(Set&&)=default;/*}}}*/

    //Iterators/*{{{*/
    iterator begin() {return data_.begin();}
    iterator end() {return data_.end();}/*}}}*/

    //Capacity /*{{{*/
    size_type size() const {return data_.size();}
    bool empty() const {return data_.empty();}/*}}}*/

    //Modifiers
    pair<iterator,bool> insert(const value_type& value) ;
    pair<iterator,bool> insert(value_type&& value) ;
    size_type erase(const value_type& key);
    iterator erase(iterator pos);
    void push_back(const value_type& key) {return data_.push_back(key);}
    void push_back(value_type&& key) {return data_.push_back(std::move(key));}

    //Lookup
    iterator find(const value_type& key);


    //Non-member function 
    friend bool operator==(const Set& lhs,const Set& rhs);

    //data member /*{{{*/
    private:
    list<T> data_;/*}}}*/
};
//Set operations /*{{{*/
template<typename InputIt1,typename InputIt2>
bool SetIncludes(InputIt1 first1,InputIt1 last1,
              InputIt2 first2,InputIt2 last2)
{
    for(;first2!=last2;++first1)
    {
        if(first1==last1||*first2<*first1)
        return false;
        if(!(*first1<*first2))
        ++first2;
    }
        return true;
}
template<typename InputIt1,typename InputIt2,
typename OutputIt,typename Compare>
OutputIt SetDifference(InputIt1 first1,InputIt1 last1,
                        InputIt2 first2,InputIt2 last2,
                        OutputIt d_first,Compare comp)
{
    while(first1!=last1)
    {
        if(first2==last2) return copy(first1,last1,d_first);
        if(comp(*first1,*first2))
            *d_first++=*first1++;
        else 
        {
            if(!(comp(*first2,*first1)))
                ++first1;
            ++first2;
        }
    }
        return d_first;
}
template<typename InputIt1,typename InputIt2,
typename OutputIt,typename Compare>
OutputIt SetIntersection(InputIt1 first1,InputIt1 last1,
                          InputIt2 first2,InputIt2 last2,
                          OutputIt d_first,Compare comp)
{
    while(first1!=last1&&first2!=last2)
    {
        if(comp(*first1,*first2))
        {
            ++first1;
        }
        else 
        {
            if(!comp(*first2,*first1))
                *d_first++=*first1++;
            ++first2;
        }
    }
        return d_first;
}
template<typename InputIt1,typename InputIt2,
typename OutputIt,typename Compare>
OutputIt SetUnion(InputIt1 first1,InputIt1 last1,
                   InputIt2 first2,InputIt2 last2,
                   OutputIt d_first,Compare comp)
{
    for(;first1!=last1;++d_first)
    {
        if(first2==last2) return copy(first1,last1,d_first);
        if(comp(*first1,*first2)) *d_first=*first1++;
        else 
        {
            *d_first=*first2;
            if(!comp(*first2,*first1))
                ++first1;
            ++first2;
        }
    }
        return copy(first2,last2,d_first);
}/*}}}*/
template<typename T>
pair<typename Set<T>::iterator,bool> Set<T>::insert(const value_type& value) 
{/*{{{*/
 iterator pos=data_.begin(),iter;
 bool insSucess=false;
 for(iter=data_.begin();iter!=data_.end();++iter)
 {
     if(*iter==value) break;
    if (*iter<value) ++pos;
 }
 if(iter==data_.end()) 
 {
     insSucess=true;
     iter= data_.insert(pos,value);
 }   
 return make_pair(iter,insSucess);
}/*}}}*/
template<typename T>
pair<typename Set<T>::iterator,bool> Set<T>::insert(value_type&& value) 
{/*{{{*/
 iterator pos=data_.begin(),iter;
 bool insSucess=false;
 for(iter=data_.begin();iter!=data_.end();++iter)
 {
     if(*iter==value) break;
     if(*iter<value) ++pos;
 }
 if(iter==data_.end()) 
 {
     insSucess=true;
     iter= data_.insert(pos,std::move(value));
 }   
 return make_pair(iter,insSucess);

}/*}}}*/
template<typename T>
typename Set<T>::size_type Set<T>::erase(const value_type& key)
{/*{{{*/
 size_type cnt=0;
 for(iterator iter=data_.begin;iter!=data_.end;++iter)
 {
     if(*iter==key) 
     {
         iter=data_erase(iter);
         ++cnt;
     }  
 }
 return cnt;
}/*}}}*/
template<typename T>
typename Set<T>::iterator Set<T>::erase(iterator pos)
{
    return data_.erase(pos);
}
template<typename T>
bool operator==(const Set<T>& lhs,const Set<T>& rhs)
{/*{{{*/
    if(lhs.size()!=rhs.size())
    return false;
    if(includes(lhs.begin(),lhs.end(),
                rhs.begin(),rhs.end()))
    return true;
    else return false;
}/*}}}*/

#endif

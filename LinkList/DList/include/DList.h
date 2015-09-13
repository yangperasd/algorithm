/*************************************************************************
> File Name: include/DList.h
> Author: yang 
> Mail: yangperasd@163.com 
> Created Time: 2015年09月13日 星期日 15时12分45秒
************************************************************************/

#ifndef _DLIST_H
#define _DLIST_H
#include <memory>
#include <initializer_list>
#include <iterator>
using std::allocator;using std::initializer_list;
template <typename T,typename A=allocator<T> >
class DList
{
    public:
    //rename some type for DList /*{{{*/
    using allocator_type=A;
    using value_type=typename A::value_type;
    using reference=typename A::reference;
    using const_reference=typename A::const_reference;
    using size_type=typename A::size_type;/*}}}*/

    private:
    class DNode
    {/*{{{*/
        public:
        DNode(const value_type& val):data_(val),prior_(nullptr),pnext_(nullptr) {}
        DNode()=default;
        DNode(const DNode& lhs)=delete;
        DNode(DNode&& lhs):data_(std::move(lhs.data_)),prior_(lhs.prior_),pnext_(lhs.pnext_) {}
        DNode& operator=(const DNode& lhs)=delete;
        ~DNode() {}
        public:
        value_type data_;
        DNode* prior_;
        DNode* pnext_;
    };/*}}}*/

    public:
    //define iterator type 
    class iterator
    {/*{{{*/
     public:
     //rename some type for this class/*{{{*/
     using difference_type =typename A::difference_type;
     using value_type=typename A::value_type;
     using reference=typename A::reference;
     using pointer=typename A::pointer;
     using size_type=typename A::size_type;/*}}}*/

     //member funcion 

     //rated to initialization /*{{{*/
     explicit iterator();
     iterator(const iterator& lhs);
     ~iterator();
     iterator& operator=(const iterator& lhs);/*}}}*/

     //increase or decrease iterator /*{{{*/
     iterator& operator++();
     iterator operator++(int);
     iterator& operator--();
     iterator operator--(int);
     iterator& operator+=(size_type) ;
     iterator& operator-=(size_type);/*}}}*/

     //dereference iterator /*{{{*/
     reference operator*() const;
     pointer operator->() const;/*}}}*/

     //Non-member function/*{{{*/
     friend bool operator==(const iterator& lhs,const iterator& rhs) ;
     friend bool operator!=(const iterator& lhs,const iterator& rhs) ;
     friend iterator operator+(size_type value_type,const iterator& iter) ;
     friend difference_type operator -(const iterator& value_type,const iterator&  iter) ;/*}}}*/
    };/*}}}*/

    //define const iterator type 
    class const_iterator
    {/*{{{*/
     public:
     //rename some type for this class/*{{{*/
     using difference_type=typename A::difference_type;
     using value_type=typename A::value_type;
     using const_reference=typename A::const_reference;
     using const_pointer=typename A::const_pointer;/*}}}*/

     //member funcion 

     //rated to initialization/*{{{*/
     explicit const_iterator();
     const_iterator(const iterator& lhs);
     const_iterator(const const_iterator& lhs);
     ~const_iterator();
     const_iterator& operator=(const const_iterator&);/*}}}*/

     //increase or decrease iterator /*{{{*/
     const_iterator& operator++();
     const_iterator operator++(int);
     const_iterator& operator--();
     const_iterator operator--(int);
     const_iterator& operator+=(size_type) ;
     const_iterator& operator-=(size_type);/*}}}*/

     //dereference iterator /*{{{*/
     const_reference operator*() const;
     const_pointer operator->() const;/*}}}*/

     //Non-member function/*{{{*/
     friend  bool operator==(const const_iterator& lhs,const const_iterator& rhs);
     friend  bool operator!=(const const_iterator& lhs,const const_iterator& rhs);
     friend const_iterator operator+(size_type value_type,const const_iterator& iter) ;
     friend difference_type operator -(const const_iterator&,const const_iterator& iter) ;/*}}}*/

    };/*}}}*/

    //get reverse iterator type by using std::reverse_iterator
    using reverse_iterator=std::reverse_iterator<iterator>;
    using const_reverse_iterator=std::reverse_iterator<const_iterator>;

    //member function 

        //rated to initialization/*{{{*/
        explicit DList();
        DList(const DList&);
        DList& operator=(const DList&);
        ~DList();
        allocator_type get_allocator();/*}}}*/

    //for creating iterator 
    iterator begin();/*{{{*/
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;/*}}}*/

    //for element access
    reference front();/*{{{*/
    const_reference front() const;
    reference back();
    const_reference back() const;/*}}}*/

    //for modifier
    void push_front(const value_type&);/*{{{*/
    void push_front(value_type&&);
    void push_back(const value_type&);
    void push_back(value_type&&);
    void pop_front();
    void pop_back();

    template<typename ...Args>
    void emplace_back(Args...);
    template<typename ...Args>
    iterator emplace(const_iterator,Args...);
    iterator insert(const_iterator,const value_type&);
    iterator insert(const_iterator,value_type&&);
    iterator insert(const_iterator,size_type,const value_type&);
    template<typename iter>
    iterator insert(const_iterator,iter,iter);
    iterator insert(const_iterator,initializer_list<value_type>);

    iterator erase(const_iterator);
    iterator erase(const_iterator,const_iterator);

    void clear();
    template<typename iter>
    void assign(iter,iter);
    void assign(initializer_list<value_type>);
    void assign(size_type,const value_type&);
    void swap(const DList&);/*}}}*/

   //for capacity 
   bool empty() const;/*{{{*/
   size_type size() const ;
   size_type max_size() const;/*}}}*/

    //Non-member function 
    friend  bool operator==(const DList&,const DList&) ;
    friend  bool operator!=(const DList&,const DList&) ;

    private:
        iterator first_;
        iterator last_;
        size_type size_;

};

template<typename T,class A=allocator<T> >
void swap(DList<T,A>&,DList<T,A>&);

template<typename T,class A>
DList<T,A>::DList()
{
    
}
#endif

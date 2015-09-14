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
#include <limits>
using std::allocator;using std::initializer_list;using std::numeric_limits;
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
               explicit  DNode(const value_type& val):data_(val),prior_(nullptr),pnext_(nullptr) {}
                DNode()=default;
                DNode(const DNode& lhs):data_(lhs.data_),prior_(nullptr),pnext_(nullptr) {}
                DNode(DNode&& lhs):data_(std::move(lhs.data_)),prior_(lhs.prior_),pnext_(lhs.pnext_) {}
                DNode& operator=(const DNode& lhs)=delete;
                ~DNode() {}
            //data member 
            public:
                value_type data_;
                DNode* prior_;
                DNode* pnext_;
        };/*}}}*/

    public:
        //define iterator type 
        class const_iterator;
        class iterator
        {/*{{{*/
            public:
                //rename some type for this class/*{{{*/
                using difference_type =typename A::difference_type;
                using value_type=typename A::value_type;
                using reference=typename A::reference;
                using pointer=typename A::pointer;
                using size_type=typename A::size_type;/*}}}*/
            friend const_iterator;
                //member funcion 

                //rated to initialization /*{{{*/
                explicit iterator():pnode_(nullptr) {};
                explicit iterator(DNode* pnode):pnode_(pnode) {}
                iterator(const iterator& lhs)=default;
                ~iterator()=default;
                iterator& operator=(const iterator& lhs)=default;/*}}}*/

                //increase or decrease iterator /*{{{*/
                iterator& operator++()
                {
                    pnode_=pnode_->pnext_;
                    return *this;
                }
                iterator operator++(int)
                {
                    DNode* pTmp=pnode_;
                    pnode_=pnode_->pnext_;
                    return iterator(pTmp);
                }
                iterator& operator--()
                {
                    pnode_=pnode_->prior_;
                    return *this;
                }
                iterator operator--(int)
                {
                    DNode* pTmp=pnode_;
                    pnode_=pnode_->prior_;
                    return *this;
                }
                iterator& operator+=(size_type time) 
                {
                    while(time--)
                    {
                       ++ *this;
                    }
                    return *this;
                }
                iterator& operator-=(size_type time)
                {
                    while(time--)
                    {
                        -- *this;
                    }
                    return *this;
                }/*}}}*/

                //dereference iterator /*{{{*/
                reference operator*() const
                {
                    return pnode_->data_;
                }
                pointer operator->() const
                {
                    return &pnode_->data_;
                }/*}}}*/
                
                //set to end-pointer
                void setEnd()
                {
                    pnode_=numeric_limits<int>::max();
                }

                //Non-member function/*{{{*/
                friend bool operator==(const iterator& lhs,const iterator& rhs) 
                {
                    return lhs.pnode_==rhs.pnode_;
                }
                friend bool operator!=(const iterator& lhs,const iterator& rhs) 
                {
                    return !(lhs==rhs);
                }
                friend iterator operator+(size_type time,iterator iter) 
                {
                   iter+=time;
                   return iter;
                }
                friend difference_type operator -(iterator lhs,iterator  rhs) 
                {/*{{{*/
                    size_type cnt=0;
                    iterator lhsTmp(lhs),rhsTmp(rhs);
                    while(lhsTmp&&rhsTmp)
                    {
                        if(lhsTmp==rhs) break;
                        if(rhsTmp==lhs) break;
                        ++lhsTmp;
                        ++rhsTmp;
                        ++cnt;
                    }
                    if(lhsTmp==rhs)
                        return cnt;
                    if(rhsTmp==lhs)
                        return -cnt;
                    if(!lhsTmp)
                    {
                        while(rhsTmp&&rhsTmp!=lhs)
                        {++rhsTmp;++cnt;}
                        if(!rhsTmp) return PTRDIFF_MAX;
                        else return -cnt;
                    }
                    if(!rhsTmp)
                    {
                        while(lhsTmp&&lhsTmp!=rhs)
                        {++lhsTmp;++cnt;}
                        if(!lhsTmp) return PTRDIFF_MAX;
                        else return cnt;
                    }

                }/*}}}*//*}}}*/
            //data member 
            private:
                DNode* pnode_;
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
                explicit const_iterator()=default;
                explicit const_iterator(DNode* pnode):pnode_(pnode) {}
                const_iterator(const iterator& lhs):pnode_(lhs.pnode_) {}
                const_iterator(const const_iterator& lhs)=default;
                ~const_iterator()=default;
                const_iterator& operator=(const const_iterator&)=default;/*}}}*/

                //increase or decrease iterator /*{{{*/
                const_iterator& operator++()
                {
                    pnode_=pnode_->pnext_;
                    return *this;
                }
                const_iterator operator++(int)
                {
                    DNode* const pTmp=pnode_;
                    ++*this;
                    return const_iterator (pTmp);
                }
                const_iterator& operator--()
                {
                    pnode_=pnode_->prior_;
                    return *this;
                }
                const_iterator operator--(int)
                {
                    DNode* const pTmp=pnode_;
                    --*this;
                    return const_iterator(pTmp);
                }
                const_iterator& operator+=(size_type time) 
                {
                    while(time--)
                    {
                        ++*this;
                    }
                    return *this;
                }
                const_iterator& operator-=(size_type time)
                {
                    while(time--)
                    {
                        --*this;
                    }
                    return *this;
                }/*}}}*/

                //dereference iterator /*{{{*/
                const_reference operator*() const 
                {
                    return pnode_->data_;
                }
                const_pointer operator->() const
                {
                    return & pnode_->data_;
                }/*}}}*/

                //set to end-pointer
                void setEnd()
                {
                    pnode_=numeric_limits<int>::max();
                }
                //Non-member function/*{{{*/
                friend  bool operator==(const const_iterator& lhs,const const_iterator& rhs)
                {
                    return lhs.pnode_==rhs.pnode_;
                }
                friend  bool operator!=(const const_iterator& lhs,const const_iterator& rhs)
                {
                    return !(rhs==lhs);
                }
                friend const_iterator operator+(size_type time,const_iterator iter) 
                {
                    iter+=time;
                    return iter;
                }
                friend difference_type operator -(const const_iterator&,const const_iterator& iter) 
                {
                    //no complete 
                    return 1;
                }/*}}}*/

                //data member 
                DNode* const pnode_;
        };/*}}}*/

        //get reverse iterator type by using std::reverse_iterator
        using reverse_iterator=std::reverse_iterator<iterator>;
        using const_reverse_iterator=std::reverse_iterator<const_iterator>;

        //member function 

        //rated to initialization/*{{{*/
        explicit DList()
        {
            DNode nodeTmp;
            first_=iterator(&nodeTmp);
            last_=first_;
        }
        DList(const DList&)=delete;
        DList& operator=(const DList&)=delete;
        ~DList()=default;
        allocator_type get_allocator()
        {
            return A ();
        };/*}}}*/

        //for creating iterator 
        iterator begin()/*{{{*/ 
        {
            return first_+1;    
        }
        const_iterator begin() const
        {
            return first_+1;
        }
        const_iterator cbegin() const 
        {
            return first_+1;
        }
        iterator end()
        {
            iterator tmp;
            tmp.setEnd();
            return tmp;
        }
        const_iterator end() const 
        {
            iterator tmp;
            tmp.setEnd();
            return tmp;
        }
        const_iterator cend() const 
        {
            iterator tmp;
            tmp.setEnd();
            return tmp;
        }
        reverse_iterator rbegin()=delete;
        const_reverse_iterator rbegin() const=delete;
        const_reverse_iterator crbegin() const=delete;
        reverse_iterator rend()=delete;
        const_reverse_iterator rend() const=delete;
        const_reverse_iterator crend() const=delete;/*}}}*/

        //for element access
        reference front()/*{{{*/
        {
        
        }
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

#endif

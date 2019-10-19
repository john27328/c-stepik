#include <iostream>
#include <vector>
#include <list>

template<class T>
class VectorList
{
private:
    using VectT  = std::vector<T>;
    using ListT = std::list<VectT>;

public:
    using value_type = T;

    VectorList() = default;
    VectorList(VectorList const &) = default;
    VectorList(VectorList &&) = default;

    VectorList & operator=(VectorList &&)     = default;
    VectorList & operator=(VectorList const &) = default;

    // метод, который будет использоваться для заполнения VectorList
    // гарантирует, что в списке не будет пустых массивов
    template<class It>
    void append(It p, It q) // определена снаружи
  {
        if (p != q)
            data_.push_back(VectT(p,q));
    }


    bool empty() const { return size() == 0; }

    // определите метод size
    size_t size() const
    {
        size_t s = 0;
        for(auto &i: data_){
            for(auto &j: i){
            s++;
            }
        }
        return s;
    }

    // определите const_iterator
    struct const_iterator : std::iterator<std::bidirectional_iterator_tag, const T> {
        const_iterator(){}

        const_iterator(const ListT *p,
                       const decltype((*p).begin()) itList,
                       const decltype((*((*p).begin())).begin()) itVector)
            : p_(p), itList_(itList), itVector_(itVector){
        }


        const T& operator*() const{
            return *itVector_;
        }


        const T* operator->() const{
            return &(*itVector_);
        }

        const_iterator &operator++ (){
            itVector_++;
            if (itVector_ == itList_->end()){
                itList_++;
                if(itList_ != p_->end())
                {
                    itVector_ = itList_->begin();
                }
                else
                    itList_--;
            }
            return *this;
        }

        const_iterator operator++(int){
            auto tmp(*this);
                ++*this;
            return tmp;
        }

        const_iterator &operator-- (){
            if(itVector_ == itList_->begin()){
                --itList_;
                itVector_ = itList_->end();
            }
            --itVector_;
            return *this;
        }

        const_iterator operator--(int){
            auto tmp(*this);
                --*this;
            return tmp;
        }

        bool operator== (const const_iterator  it) const{
            if(itList_ == it.itList_ && itVector_ == it.itVector_)
                return 1;
            else
                return 0;
        }

        bool operator!= (const const_iterator  it) const{
            return !(*this == it);
        }

    private:
        const ListT *p_;
        decltype((*p_).begin()) itList_;
        decltype((*((*p_).begin())).begin()) itVector_;
    };

    // определите методы begin / end
    const_iterator begin() const {
         return const_iterator(&data_, data_.begin(), data_.begin()->begin());
    }
    const_iterator end()   const {
        if (data_.empty())
            return const_iterator(&data_, data_.begin(), data_.begin()->begin());
        else
            return const_iterator(&data_, --data_.end(), (--data_.end())->end());
    }

    // определите const_reverse_iterator
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // определите методы rbegin / rend
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end()) ;
    }
    const_reverse_iterator rend()   const {
        return const_reverse_iterator(begin());
    }

private:
    ListT data_;
};

int main()
{
  VectorList<char> vlist;
  std::cout << "empty size is " << vlist.size() << " " << vlist.empty() << std::endl;
  auto q1 = vlist.begin();
  auto q2 = vlist.end();

  std::cout << "empty vlist.begin() == vlist.end() " << (q1 == q2) << std::endl;

  std::cout << "std::distance(begin,end)﻿ " << (std::distance(vlist.begin(), vlist.end())) << std::endl;
  typename VectorList<char>::const_iterator it1 = vlist.begin();
  typename VectorList<char>::const_reverse_iterator rit(it1);
  typename VectorList<char>::const_iterator it2 = rit.base();
  if (it1 == it2)
      std::cout << "base() works fine" << std::endl;
  else
      std::cout << "base() doesn't work as expected" << std::endl;

  std::vector<char> v1;
  v1.push_back('A');
  v1.push_back('B');
  v1.push_back('C');

  std::vector<char> v2;
  v2.push_back('D');
  v2.push_back('E');
  v2.push_back('F');
  v2.push_back('G');
  vlist.append(v1.begin(), v1.end());
  vlist.append(v2.begin(), v2.end());

  auto i = vlist.begin();

  std::cout << "Size is " << vlist.size() << " " << vlist.empty() << std::endl;
  std::cout << "begin is " << *i << std::endl;
  std::cout << "std::distance(begin,end)﻿ " << (std::distance(vlist.begin(), vlist.end())) << std::endl;
  std::cout << "*(++begin) == 'B'? " << (*++vlist.begin() == 'B') << std::endl;
  std::cout << "*(++begin) == 'A'? " << (*++vlist.begin() == 'A') << std::endl;
  std::cout << std::endl;


  std::cout << "Test ++i" << std::endl;
  for (i = vlist.begin(); i != vlist.end(); ++i)
    std::cout << *i << " ";
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "Test i++" << std::endl;
  for (i = vlist.begin(); i != vlist.end(); i++)
    std::cout << *i << " ";
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "Test --i" << std::endl;
  for (i = vlist.end(); i != vlist.begin();)
    std::cout << *--i << " ";
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "Test i--" << std::endl;
  for (i = vlist.end(); i != vlist.begin();) {
    i--;
    std::cout << *i << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;


  std::cout << std::endl;
  auto j = vlist.rbegin(); j++;
  std::cout << "rbegin is " << *j << std::endl;
  j = --vlist.rend();
  std::cout << "--rend is " << *--j << std::endl;

  std::cout << "Test reverse_const_iterator ++" << std::endl;
  for (j = vlist.rbegin(); j != vlist.rend(); ++j)
    std::cout << *j << " ";
  std::cout << std::endl;

  //system("pause");
  return 0;
}

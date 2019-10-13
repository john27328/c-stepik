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
            s +=  i.size();
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
            if(itVector_ == (*itList_).end()){
                itList_++;
                if(itList_ != (*p_).end())
                {
                    itVector_ = (*itList_).begin();
                }
            }
            return *this;
        }

        const_iterator operator++(int){
            auto tmp = *this;
                ++*this;
            return tmp;
        }

        const_iterator &operator-- (){
            if(itList_ == (*p_).end())
                --itList_;
            if(itVector_ == (*itList_).begin()){
                --itList_;
                itVector_ = --((*itList_).end());
            } else {
                --itVector_;
            }
            return *this;
        }

        const_iterator operator--(int){
            auto tmp = *this;
                --*this;
            return tmp;
        }

        bool operator== (const const_iterator  it){
            if(itList_ == it.itList_ && itVector_ == it.itVector_)
                return 1;
            else
                return 0;
        }

        bool operator!= (const const_iterator  it){
            if(itList_ != it.itList_ || itVector_ != it.itVector_)
                return 1;
            else
                return 0;
        }

    private:
        const ListT *p_;
        decltype((*p_).begin()) itList_;
        decltype((*((*p_).begin())).begin()) itVector_;
    };

    // определите методы begin / end
    const_iterator begin() const {
         return const_iterator(&data_, data_.begin(), (*(data_.begin())).begin());
    }
    const_iterator end()   const {
        return const_iterator(&data_, data_.end(), (*(--(data_.end()))).end()); }

    // определите const_reverse_iterator
    using const_reverse_iterator = const std::reverse_iterator<const_iterator>;

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
    VectorList<char> v;
    auto *p = &v;
    int q = 0;
    for(int i = 0; i < 10; i++){
        std::vector<char> vec;
        for (int j = 0; j < 10; j++){
            vec.push_back(q++);
            std::cout << q - 1 <<" ";
        }
        v.append(vec.begin(), vec.end());
        std::cout << std::endl;
    }

    //list<vector<double>>::iterator it;
    std::cout << v.size() << std::endl;
    auto it = v.begin();
    std::cout << *++it << std::endl;
    std::cout << *it-- << std::endl;
    std::cout << *it << std::endl;
    std::cout << *--(v.end()) << std::endl;

    for(auto i: v){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    auto __tmp = it;
    std::cout << *++__tmp << std::endl;

    auto rit = v.rbegin();
    auto rend = v.rend();
    std::cout << *--rend<< std::endl;
    for(; rit != v.rend(); ++rit){
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    VectorList<std::vector<double>> v2;
    for(int i = 0; i < 10; i++){
        std::vector<std::vector<double>> vec;
        std::vector<double> tmp;
        for (int j = 0; j < 10; j++){
            tmp.push_back(10+i+j);
            tmp.push_back(10+j-i);
            vec.push_back(tmp);
        }
        v2.append(vec.begin(), vec.end());
        //std::cout << std::endl;
    }
    auto it2 = v2.begin();
    std::cout << (++++++++++it2)->at(1)<< std::endl;

    return 0;
}

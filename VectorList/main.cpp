#include <iostream>

using namespace std;

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
    //    template<class ItL, class ItV>
    struct const_iterator : std::iterator<bidirectional_iterator_tag, T> {
        const_iterator(){}
        const_iterator(const ListT *p, decltype((*p).begin()) itList, decltype((*((*p).begin())).begin()) itVector)
            : p_(p), itList_(itList), itVector_(itVector){
        }
        T operator*(){
            return   *itVector_;
        }

        const_iterator operator++ (){
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
        const_iterator operator-- (){
            if(itList_ == (*p_).end())
                --itList_;
            if(itVector_ == (*itList_).begin()){
                itList_--;
                itVector_ = --((*itList_).end());
            } else {
                itVector_--;
            }
            return *this;
        }

        bool operator== (const_iterator  it){
            if(itList_ == it.itList_ && itVector_ == itVector_)
                return 1;
            else
                return 0;
        }

        bool operator!= (const_iterator  it){
            if(itList_ != it.itList_ || itVector_ != itVector_)
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
    //... const_reverse_iterator ...

    // определите методы rbegin / rend
    //const_reverse_iterator rbegin() const { return ... ;   }
    //const_reverse_iterator rend()   const { return ... ; }

private:
    ListT data_;
};

int main()
{
    VectorList<double> v;
    int q = 0;
    for(int i = 0; i < 10; i++){
        std::vector<double> vec;
        for (int j = 0; j < 10; j++){
            vec.push_back(q++);
            cout << q - 1 <<" ";
        }
        v.append(vec.begin(), vec.end());
        cout << endl;
    }

    //list<vector<double>>::iterator it;
    cout << v.size() << endl;
    auto it = v.begin();
    cout << *(++it) << endl;
    cout << *(--it) << endl;
    cout << *(--(v.end())) << endl;

    for(auto i: v){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}

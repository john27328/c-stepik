#include <iostream>
#include <list>

// так как в задании не указан тип элементов,
// которые хранятся в списке, то давайте сделаем
// эту функцию шаблонной
// Параметр It — это тип итератора
template<class It>
size_t max_increasing_len(It p, It q)
{
    size_t n = 1;
    size_t n_max = 1;
    auto tmp = p;
    p++;
    for(;p != q; ++p){
        if (*p > *tmp) {
            n++;
        }
        else {

            n=1;
        }
        if (n > n_max) n_max = n;
        tmp++;
    }
    return n_max;
}

int main()
{
    std::list<int> const l1 = {7,8,9,4,5,6,1,2,3,4};
    size_t len1 = max_increasing_len(l1.begin(), l1.end()); // 4, соответствует подотрезку 1,2,3,4

    std::list<int> const l2 = {-3,-2,-1,0,0,1,2,3,4,5};
    size_t len2 = max_increasing_len(l2.begin(), l2.end()); // 6, соответствует подотрезку 0,1,2,3,4,5
    std::cout << len1 << " " << len2 << std::endl;
    return 0;
}

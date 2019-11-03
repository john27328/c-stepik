#include <iostream>
#include <future>
#include <list>

// заголовок <future> уже подключён.
// заново подключать не нужно

// реализация функции mapreduce
//... map_reduce(... p, ... q, ... f1, ... f2,  size_t threads)
//{

//}

#include <vector>
template <typename IT, typename F1, typename F2>
auto map_reduce(IT p, IT q, F1 f1, F2 f2, size_t threads)
{
    auto n = std::distance(p, q);
    auto dn = n / (threads);

    auto map_reduce_tread = [](IT pt, IT qt, F1 f1, F2 f2){
        auto res = f1(*pt);
        while(++pt != qt)
            res = f2(res, f1(*pt));
        return res;
    };

    IT qt = p;
    using Future = std::future<decltype(f1(*qt))>;
    std::vector<Future> vec;
    for (size_t i = 0; i < threads - 1; i++){
        IT pt = qt;
        for (size_t j = 0; j < dn; j++){
            qt++;
        }
        vec.push_back(std::async(map_reduce_tread, pt, qt, f1, f2));
    }
    vec.push_back(std::async(map_reduce_tread, qt, q, f1, f2));

    auto res = vec[0].get();
    for (size_t i = 1; i < threads; i++){
        res += vec[i].get();
    }
    return res;
}

using namespace std;

int main()
{
    std::list<int> l = {1,2,3,4,5,6,7,8,9,10};
//     параллельное суммирование в 3 потока
    auto sum = map_reduce(l.begin(), l.end(),
                 [](int i){return i;},
                          std::plus<int>(), 3);
    cout << sum<< endl;
    return 0;
}

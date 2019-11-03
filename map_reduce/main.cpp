#include <iostream>
#include <future>
#include <list>
#include <string>
#include <assert.h>
#include <vector>

// заголовок <future> уже подключён.
// заново подключать не нужно

// реализация функции mapreduce
//... map_reduce(... p, ... q, ... f1, ... f2,  size_t threads)
//{

//}

template <typename IT, typename F1, typename F2>
auto map_reduce(IT p, IT q, F1 f1, F2 f2, const size_t threads) -> decltype (f1(*p))
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
    Future vec[threads];
    for (size_t i = 0; i < threads - 1; i++){
        IT pt = qt;
        for (size_t j = 0; j < dn; j++){
            qt++;
        }
        vec[i] = std::async(std::launch::async, map_reduce_tread, pt, qt, f1, f2);
    }
    vec[threads-1] = std::async(std::launch::async, map_reduce_tread, qt, q, f1, f2);

    auto res = vec[0].get();
    for (size_t i = 1; i < threads; i++){
        res = f2(res, vec[i].get());
    }
    return res;
}

using namespace std;

int main()
{
    std::list<int> l1 = {1,2,3,4,5,6,7,8,9,10};
//     параллельное суммирование в 3 потока
    auto sum1 = map_reduce(l1.begin(), l1.end(),
                 [](int i){return i;},
                          std::plus<int>(), 10);
    cout << sum1<< endl;

    const std::vector<std::string> l = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
    for (int i = 1; i <= l.size(); ++i) {
       auto sum = map_reduce(l.begin(), l.end(), [](std::string i){return i;}, std::plus<std::string>(), i);
       assert(sum == "1234567891011");
    }

    return 0;
}

#include <iostream>
#include <tuple>

//using namespace std;

template<int i, int j, typename  T>
auto to_pair(T t) -> decltype(std::make_pair(std::get<i>(t), std::get<j>(t))){
   return  std::make_pair(std::get<i>(t), std::get<j>(t));
}

int main()
{
    auto t = std::make_tuple(0, 3.5, "Hello");
    std::pair<double, char const *> p = to_pair<1,2>(t);
    // p содержит 3.5 и "Hello"
    return 0;
}

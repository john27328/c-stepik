#include <iostream>

using namespace std;

struct Dummy { };
typedef int type;

template<class T1, class T2>
struct SameType
{
    static const bool value = 0;
};

template<class T1>
struct SameType <T1,T1>
{
    static const bool value = 1;
};

int main()
{
    std::cout << SameType<int, int>::value << std::endl; // выведет 1, т. е. true
    std::cout << SameType<int, type>::value << std::endl; // 1, type == int
    std::cout << SameType<int, int&>::value << std::endl; // 0, int и ссылка на int - различные типы
    std::cout << SameType<Dummy, Dummy>::value << std::endl; // 1
    std::cout << SameType<int, const int>::value << std::endl; // 0, const - часть типа
    return 0;
}

#include <iostream>

template <int ... Ints>
struct IntList;

template <int I, int ... Ints>
struct IntList<I, Ints...>{
    static int const Head = I;
    using Tail = IntList<Ints...>;
};

template <>
struct IntList<>{};

template <typename IL>
struct Length{
    static int const value = 1 + Length<typename IL::Tail>::value;
};

template <>
struct Length<IntList<>>{
    static int const value = 0;
};

int main()
{
    using primes = IntList<2,3,5,7,11,13>;
    constexpr int head = primes::Head;
    using odd_primes = primes::Tail;

    constexpr size_t len = Length<primes>::value; // 6
    std::cout << len << std::endl;
    return 0;
}

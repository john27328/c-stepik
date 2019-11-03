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

int main()
{
    using primes = IntList<2,3,5,7,11,13>;
    constexpr int head = primes::Head;
    using odd_primes = primes::Tail;
    return 0;
}

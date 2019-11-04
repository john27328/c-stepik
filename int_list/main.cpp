#include <iostream>
#include <tuple>

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


template <int I, typename IL>
struct IntCons;

template <int I, int ... Ints>
struct IntCons<I, IntList<Ints...>>{
    using type = IntList<I, Ints...>;
};

template <int I, int L = 0>
struct Generate{
    using type = typename IntCons<L, typename Generate<I-1, L+1>::type>::type;
};

template <int L>
struct Generate<0, L>{
    using type = IntList<>;
};

template<typename T>
void check()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}


int main()
{
    using primes = IntList<2,3,5,7,11,13>;
    constexpr int head = primes::Head;
    using odd_primes = primes::Tail;
    check<primes>();

    constexpr size_t len = Length<primes>::value; // 6
    std::cout << len << std::endl;

    using L1 = IntList<2,3,4>;


    using L2 = IntCons<1, L1>::type;   // IntList<1,2,3,4>
    constexpr size_t len2 = Length<L2>::value; // 4
    std::cout << len2 << std::endl;

    using L3 = Generate<5>::type;      // IntList<0,1,2,3,4>
    constexpr size_t len3 = Length<L3>::value; // 5
    check<L3>();

    std::cout << len3 << std::endl;

    return 0;
}

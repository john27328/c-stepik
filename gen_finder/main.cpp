#include <iostream>
#include <functional>
template<class F>
int * find_if(int * p, int * q, F f)
{
    for ( ; p != q; ++p )
        if (f(*p))
            return p;
    return q;
}
//using namespace std;

int main()
{
    // определение переменной

    auto gen_finder = [](int *p, int *q) ->
            std::function<bool (int)> {
        return [p, q](int m) ->
                bool {
            for (int *i = p; i !=q; ++i) {
                if (m == *i) return 1;
            }
            return 0;
        };
    };

    int primes[5] = {2,3,5,7,11};

    int m[10] = {0,0,1,1,4,6,7,8,9,10};

    // first_prime будет указывать на число 7
    int * first_prime = find_if(m, m + 10, gen_finder(primes, primes + 5));

    return 0;
}

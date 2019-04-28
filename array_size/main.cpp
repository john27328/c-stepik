#include <iostream>
#include <cstddef> // size_t

using namespace std;

template <class T, size_t N>
size_t array_size(T (&x)[N])
{
    return N;
}

int main()
{
    int ints[] = {1, 2, 3, 4};
    int *iptr = ints;
    double doubles[] = {3.14};
    cout << array_size(ints) << endl; // вернет 4
    cout << array_size(doubles) <<endl; // вернет 1
    //array_size(iptr); // тут должна произойти ошибка компиляции
    return 0;
}

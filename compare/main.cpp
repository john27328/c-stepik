#include <iostream>

template<typename T, typename I>
bool compare(const T &a, const T &b, I T::*mptr)
{
    if ((a.*mptr)() < (b.*mptr)())
        return 1;
    else {
         return 0;
    }
}

int main()
{
    std::string s1("Elf");
    std::string s2("Archer");

    // сравнение строк по длине
    bool r1 = compare(s1, s2, &std::string::size); // true
    bool r2 = compare(s1, s1, &std::string::size); // false
    return 0;
}

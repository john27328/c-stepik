#include <iostream>

using namespace std;

#include <ostream>
#include <typeinfo>

// принимает произвольное число аргументов
void print_values(std::ostream & os)
{

}

template<typename T, typename... Args>
void print_values(std::ostream & os, T value, Args... args)
{
    os << typeid(value).name() << ": " << value <<std::endl;
    print_values(os, args...);
}

// принимает произвольное число аргументов
void printf(std::ostream & os, char const *s)
{
    while (*s){
        if(*s == '%' && *(++s) != '%')
            std::cout << "error" << std::endl;
        os << *s++;
    }
}

template<typename T, typename... Args>
void printf(std::ostream & os, char const *s, T value, Args... args)
{
    os << typeid(value).name() << ": " << value <<std::endl;
    while (*s){
        if(*s == '%' && *(++s) != '%') {
            os << value;
            printf(os, args...);
            return;
        }
        os << *s++;
    }
    std::cout << "error" << std::endl;
}


int main()
{
    print_values(std::cout, 0, 3.5, "Hello");
    return 0;
}

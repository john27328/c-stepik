#include <iostream>
#include <string>
#include <sstream>
#include <exception>

// описание класса исключения bad_from_string
//...

// функция from_string
template<class T>
T from_string(std::string const& s)
{
    // реализация
    std::string tmp(s);
    std::istringstream str(tmp);
    T out;
    str >> out;
    return out;
}


using namespace std;

int main()
{

    string s1("123");
    int    a1 = from_string<int>   (s1); // a1 = 123
    double b1 = from_string<double>(s1); // b1 = 123.0
    string c1 = from_string<string>(s1); // c1 = "123"
    cout << a1 << " " << b1 << " " << c1 << endl;

    string s2("12.3");
    int    a2 = from_string<int>   (s2); // исключение
    double b2 = from_string<double>(s2); // b2 = 12.3
    string c2 = from_string<string>(s2); // c2 = "12.3"
    cout << a2 << " " << b2 << " " << c2 << endl;

    string s3("abc");
    int    a3 = from_string<int>   (s3); // исключение
    double b3 = from_string<double>(s3); // исключение
    string c3 = from_string<string>(s3); // c3 = "abc"
    cout << a3 << " " << b3 << " " << c3 << endl;

    cout << "Hello World!" << endl;
    return 0;
}

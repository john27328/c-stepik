#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <memory>

// описание класса исключения bad_from_string
class bad_from_string: public std::exception{
public:
    bad_from_string(const std::string c): c_(c){}
    ~bad_from_string() noexcept override{}
    const char* what() const noexcept override {
        return c_.c_str();
    }
private:
    const std::string c_;
};

// функция from_string
template<class T>
T from_string(std::string const& s)
{
    // реализация
    std::string tmp(s);
    std::istringstream temp_str(tmp);
    char tmpOut;
    T out;
    temp_str >> std::noskipws >> tmpOut;
    if (tmpOut == ' '){
        throw bad_from_string("пробел в начале строки \"" + s + "\"");
        std::cout << "пробел в начале" << std::endl;
    }
    std::istringstream str(s);
    str >> std::noskipws >> out >> tmpOut;
    if (tmpOut == ' '){
        throw bad_from_string("пробел в конце строки \"" + s + "\"");
        std::cout << "пробел в конце" << std::endl;
    }
    return out;
}


using namespace std;

int main()
{

    string s1("123  ");
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

    char ch1, ch2, ch3;
        std::istringstream("a b c") >> ch1 >> ch2 >> ch3;
        std::cout << "Default  behavior: c1 = " << ch1 << " c2 = " << ch2 << " c3 = " << ch3 << '\n';
        std::istringstream("a b c") >> std::noskipws >> ch1 >> ch2 >> ch3;
        std::cout << "noskipws behavior: c1 = " << ch1 << " c2 = " << ch2 << " c3 = " << ch3 << '\n';
    return 0;
}

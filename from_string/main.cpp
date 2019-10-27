#include <iostream>
#include <string>
#include <sstream>
#include <exception>
//#include <cassert>
#include <vector>


// описание класса исключения bad_from_string
class bad_from_string: public std::exception{
public:
    bad_from_string(const std::string c): c_(c){}
    //~bad_from_string() noexcept override{}
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
    std::string tempOutD;
    std::string tempOutDNS;
    char tempOutC;
    T out;
    std::istringstream str(s);
    std::istringstream strt(s);

//    strt >> tempOutD;
//    if (tempOutD != s){
//        throw bad_from_string("неверный формат строки \"" + s + "\"");
//    }

    str.exceptions(std::istringstream::failbit | std::istringstream::badbit);
    try {
        str >> std::noskipws >> out;
    } catch (std::istringstream::failure &e) {
        throw bad_from_string("неверный формат строки \"" + s + "\"");
    }

    bool key = 1;
    try {
        str >> std::noskipws  >> tempOutC;
    } catch (std::istringstream::failure &e) {
        key = 0;
    }
    if (key) throw bad_from_string("неверный формат строки \"" + s + "\"");
    return out;
}


using namespace std;
// Safe from_string() call
#define _SFROM_STRING(type1)                        \
    try {                                           \
        cout << endl << "<" #type1 ">: \'";           \
        cout << from_string<type1>(str) << "\'";            \
    }                                               \
    catch (exception const& e) {                    \
        cout<<"catch std::exception: "<< e.what();  \
    }                                               \
    catch (...) {                                   \
        cout<<"catch unknown";                      \
    }
using namespace std;
void from_string_test()
{
    vector<string> strings{ "123", "12.3", "", " ", "abc", " 123", "123 ", "12 3", "-1", "a", "a ", " a", "a b", "A" };
    //               string  123    12.3   e    e   "abc"   e       e       e      "-1"  "a"   e     e     e     "A"
    //               double  123    12.3   e    e    e      e       e       e       -1    e    e     e     e      e
    //                  int  123    e      e    e    e      e       e       e       -1    e    e     e     e      e
    //                 char  e      e      e   ' '   e      e       e       e       e    'a'   e     e     e     'A'
    for (auto& str : strings) {
        cout << endl << "from_string(\'" << str << "\'):";
        _SFROM_STRING(string);
        _SFROM_STRING(double);
        _SFROM_STRING(int);
        _SFROM_STRING(char);
        cout << endl;
    }
}

void oldTest(){
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
}

int main()
{
    from_string_test();
    return 0;
}

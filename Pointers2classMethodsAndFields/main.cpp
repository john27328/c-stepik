#include <iostream>
#include <string>

using namespace std;

struct Unit{
    Unit(const string& arg1, size_t arg2, double arg3)
        : name(arg1), health_points(arg2), karma(arg3) {}

    const string& GetName() const {return name;}
    size_t GetHealth() const {return health_points;}
    double GetKarma() const {return karma;}

    string name;
    size_t health_points;
    double karma;
};

template<typename T, typename S>
bool compare(T a, T b, S (T::*mptr)() const)
{
    if ((a.*mptr)() < (b.*mptr)()) return true;
    else return false;
}

//bool compare(std::string a, std::string b, std::size_t (std::string ::*mptr)() const)
//{
//    std::size_t sa = (a.*mptr)();
//    std::size_t  sb = (b.*mptr)();
//    if (sa < sb) return true;
//    else return false;
//}

int main(){
    Unit orc("orc", 25, 0.3);
    Unit elf("elf", 20, 1.5);
    std::cout << compare(orc, elf, &Unit::GetName) << "\n";
    std::cout << compare(orc, elf, &Unit::GetHealth) << "\n";
    std::cout << compare(orc, elf, &Unit::GetKarma) << "\n";
    std::cout << compare<string, size_t>("abd","vgfa", &string::size) << "\n";
    std::cout << compare<string, size_t>("abdgh","vgfa", &string::size) << "\n";
}

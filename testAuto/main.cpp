#include <iostream>

using namespace std;

int main()
{
    std::string s = "Compiler";

    auto sz = s.size();

    auto c1 = s[0];

    decltype(s[0]) c2 = s[7];

    decltype(s[0] + s[7]) c3 = s[1];

    decltype(s)   sa = s;

    decltype((s)) sb = s;

    c1 = 'K';
    c2 = '!';
    cout << "Hello World!" << endl;
    return 0;
}

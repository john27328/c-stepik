#include <iostream>
using namespace std;

int main()
{
    char tmpC = '\0';
    char c = '\0';
    while (cin.get(c)) {
        if (!(tmpC == ' ' && c == tmpC))
            cout << c;
        tmpC = c;
    }

    return 0;
}

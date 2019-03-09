#include <iostream>

unsigned gcd(unsigned a, unsigned b);

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    unsigned a = 6, b = 9;
    cout << gcd(a, b) <<endl;
    return 0;
}

unsigned gcd(unsigned a, unsigned b)
{
    if (a > b){
        unsigned tmp = a;
        a = b;
        b = tmp;
    }
    if (a == 0) {
        return b;
    }
    else {
        gcd(a, b % a);
    }
}


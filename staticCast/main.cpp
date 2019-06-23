#include <iostream>

using namespace std;


struct Number {};

struct BigInt : Number
{
    BigInt(int x);
};


struct String
{
    explicit String(char const * s);
};


int main()
{
    int a = 3.5;
    double b = 7;
    BigInt c = 100500;
    String d = static_cast<String>("str");
    Number *e = &c;
    BigInt *f = static_cast<BigInt*>(e);
    void *g = f;
    BigInt *h = static_cast<BigInt*>(g);

    cout << "Hello World!" << endl;
    return 0;
}

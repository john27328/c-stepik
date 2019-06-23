#include <iostream>

using namespace std;

struct Base {
int a;
};

struct D1 : Base {
    int b;
};

struct D2 : Base {
    int c;
};

struct D3 : D1, D2 {
    int d;
};

// base указывает на экземпляр Base, соответствующий D1
// нужно вернуть указатель на экземпляр Base, соответствующий D2
Base const * D1BaseToD2Base( Base const * base )
{
    const D1 & d1 = (const D1&)*base;
    const D3 & d3 = (const D3&) d1;
    const D2 &d2 = (const D2&)d3;
    return (const Base*)&d2;
}

int main()
{
    D3 d3;
    D2 &d1 = d3;
    Base *base = &(d1);
    D1BaseToD2Base(base);
    return 0;
}

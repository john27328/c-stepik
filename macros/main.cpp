#include <iostream>
#define MAX(x, y, r) {int xt = (x); int yt = (y); r = xt > yt ? xt : yt;}

using namespace std;

int main()
{
    int a = 10;
    int b = 20;
    int c = 0;
    MAX(a, b, c); // теперь c равно 20
    cout << c << endl;
    MAX(a += b, b, c); // теперь a = с = 30
    cout << c << endl;
    return 0;
}

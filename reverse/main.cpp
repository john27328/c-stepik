#include <iostream>

using namespace std;

void rev();

int main()
{
    rev();
    return 0;
}

void rev()
{
    int a;
    cin >> a;
    if (a!=0)
    {
        rev();
        cout << a <<' ';
    }
}

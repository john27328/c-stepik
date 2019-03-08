#include <iostream>
using namespace std;

int log2(int a)
{
    int temp = 1;
    int p = 0;
    while (temp <=  a)
    {
        p++;
        temp*=2;
    }
    return p-1;
}



int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int a;
        cin >> a;
        cout << log2(a) << endl;
    }
    return 0;
}

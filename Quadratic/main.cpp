#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    int d = b * b - 4 * a * c;
    if (d < 0)
        cout << "No real roots" << endl;
    else {
        cout << (- b + sqrt(d)) / (2 * a) << " " << (- b - sqrt(d)) / (2 * a) << endl;
    }
    return 0;
}

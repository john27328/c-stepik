#include <iostream>

using namespace std;

template <typename U, typename T>
void copy_n(T* t, U* u, int n){
    for (int i = 0; i < n; i++) {
        t[i] = (T)u[i];
    }
}

int main()
{
    int ints[] = {1, 2, 3, 4};
    double doubles[4] = {};
    copy_n(doubles, ints, 4); // теперь в массиве doubles содержатся элементы 1.0, 2.0, 3.0 и 4.0
    cout << "Hello World!" << endl;
    return 0;
}

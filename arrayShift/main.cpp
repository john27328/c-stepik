#include <iostream>

using namespace std;

void rotate(int a[], unsigned size, int shift)
{
    int b[size];
    for (int i = 0; i < size; i++)
    {
        int j  = (size + i - shift % size)%size;
        b[j] = a[i];
    }
    for (int i = 0; i < size; i++)
    {
        a[i] = b[i];
    }
}



int main()
{
    int mas[] = {1, 2, 3, 4, 5, 6};
    unsigned size = sizeof(mas)/sizeof(int);
    rotate(mas, size, 2);
    for (int i = 0; i < size; i++)
    {
       cout << mas[i]<<' ';
    }
    return 0;
}

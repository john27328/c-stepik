#include <iostream>

using namespace std;

int ** transpose(const int * const * m, unsigned rows, unsigned cols)
{
    int **nm = new int*[cols];
    for (int j = 0; j < cols; j++)
    {
        nm[j] = new int[rows];
        for (int i = 0; i < rows; i++)
            nm[j][i] = m[i][j];
    }
    return nm;
}


int main()
{
    const unsigned N = 3, M = 5;
    int **m;
    m = new int *[N];
    for (int i = 0; i < N; i++)
    {
        m[i] = new int[M];
        for (int j = 0; j < M; j++)
           m[i][j] = M * i + j;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            cout << m[i][j] << " ";
        cout << endl;
    }

    int ** nm = transpose(m, N, M);

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            cout <<nm[i][j] << " ";
        cout << endl;
    }

    return 0;
}

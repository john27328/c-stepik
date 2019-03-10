#include <iostream>

using namespace std;

void swap_min(int *m[], unsigned rows, unsigned cols)
{
    int min_a =m[0][0];
    int *min_row = m[0];
    int min_i = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            if(m[i][j] < min_a)
            {
                min_a = m[i][j];
                min_row = m[i];
                min_i = i;
            }
    }
    m[min_i] = m[0];
    m[0] = min_row;
}



int main()
{
    const unsigned N = 6, M = 6;
    int **m;
    m = new int *[N];
    for (int i = 0; i < N; i++)
    {
        m[i] = new int[M];
        for (int j = 0; j < M; j++)
           m[i][j] = M * (i - N / 2)*(i - N / 2) + j*j;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            cout << m[i][j] << " ";
        cout << endl;
    }

    swap_min(m,N,M);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            cout << m[i][j] << " ";
        cout << endl;
    }


    return 0;

}

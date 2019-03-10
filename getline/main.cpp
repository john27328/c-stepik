#include <iostream>

using namespace std;

char *resize(const char *str, unsigned size, unsigned new_size)
{
    char * strTemp = new char[new_size];
    for(unsigned i = 0; i<size && i < new_size; i++)
    {
        strTemp[i] = str[i];
    }
    delete[] str;
    return strTemp;
}


char *getline()
{
    unsigned len = 10;
    unsigned size = 0;
    char c = '\0';
    char *str = new char[len];
    while (cin.get(c)) {
        if (c== '\n') break;
        str[size] = c;
        size++;
        if (size > len)
        {
//            cout << len << ' ' << size <<endl;
            str = resize(str, len, len+=10);
        }
    }
    str[size] = '\0';
    return str;
}

void printChar(const char *str)
{
    char *p = (char *)str;
    while( *p != '\0')
    {
        cout << *p;
        p++;
    }
}

int main()
{
    char *str = getline();
    printChar(str);
    delete [] str;
    return 0;
}

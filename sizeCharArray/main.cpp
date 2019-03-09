#include <iostream>

using namespace std;

unsigned strlen(const char *str)
{
    char *p = (char *)str;
    while( *p != '\0')
    {
        p++;
    }
    return p - str;
}


int main()
{
    char str[] = "C-style";
    cout << strlen(str);
    return 0;
}


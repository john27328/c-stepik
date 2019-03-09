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

void strcat(char *to, const char *from)
{
    char *pt = (char *)to + strlen(to);
    char *pf = (char *)from;
    while( *pf != '\0')
    {
        *pt = *pf;
        pf++;
        pt++;
    }
    *pt = '\0';

}

void printChar(const char *str)
{
    char *p = (char *)str;
    while( *p != '\0')
    {
        cout << *p;
        p++;
    }

    cout << '!' <<endl;
}

int main()
{
    char to[20] = "C-style";
    char from[] = "add";
    strcat(to, from);
    printChar(to);
    return 0;
}


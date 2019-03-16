#include <iostream>

using namespace std;

#include <cstddef> // size_t
#include <cstring> // strlen, strcpy

struct String {

    /* Реализуйте этот конструктор */
    String(const char *str = "");
    String(size_t n, char c);
    ~String();

    size_t size;
    char *str;

    size_t strlen(const char *str);
    char *strcoppy(const char *str, size_t size);
    void append(String &other);

};

String::String(const char *str)
{
    this->size = strlen(str);
    this->str = strcoppy(str,this->size);
}

String::String(size_t n, char c)
{
    this->str = new char[n+1];
    this->size = n;
    for(size_t i = 0; i<size; i++)
    {
        this->str[i] = c;
    }
    this->str[size] = '\0';
}

String::~String()
{
    delete[] this->str;
}

size_t String::strlen(const char *str)
{
    char *p = (char *)str;
    while( *p != '\0')
    {
        p++;
    }
    return p - str;
}

char *String::strcoppy(const char *str, size_t size)
{
    char *newstr = new char[size+1];
    for(size_t i = 0; i<size; i++)
    {
        newstr[i] = str[i];
    }
    newstr[size] = '\0';
    return newstr;
}

void String::append(String &other)
{
    size_t newseze = this->size + other.size;
    char *newstr = new char [newseze + 1];
    for (size_t i = 0;i < this->size; i++) {
        newstr[i] = this->str[i];
    }
    for (size_t i = 0; i < other.size; i++) {
        newstr[this->size + i] = other.str[i];
    }
    newstr[newseze] = '\0';
    delete [] this->str;
    this->str = newstr;
    this->size = newseze;
}


int main()
{
    cout << "Hello World!" << endl;
    String s1("Hello,");
    String s2(" world!");
    s1.append(s2);
    return 0;
}

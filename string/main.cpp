#include <iostream>

using namespace std;

#include <cstddef> // size_t
#include <cstring> // strlen, strcpy

struct String {

    /* Реализуйте этот конструктор */
    String(const char *str = "");
    String(size_t n, char c);
    String(const String &other);
    String &operator=(const String &other)
    {
        if(this != &other)
        {
            delete [] this->str;
            this->size = other.size;
            this->str = new char[other.size + 1];

            for (int i = 0; i < other.size + 1; ++i) {
                this->str[i] = other.str[i];
            }

        }
        return *this;
    }
    void print();
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

String::String(const String &other): size(other.size), str(new char[other.size + 1])
{
    for (size_t i = 0; i < other.size+1; i++) {
        this->str[i]=other.str[i];
    }
    //str[other.size] = '\0';
}

void String::print()
{
    for (int i = 0; i < this->size; ++i) {
        cout << this->str[i];
    }
    cout << endl;
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
    String s1(",");
    String s2(" world!");
    s1 = s1;
    s1.print();
    return 0;
}

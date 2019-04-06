#include <iostream>

using namespace std;

#include <cstddef> // size_t
#include <cstring> // strlen, strcpy

struct String {

    /* Реализуйте этот конструктор */
    String(const char *str = "");
    String(size_t n, char c);
    String(const String &other);
    String &operator=(const String &other);
    void print() const;
    ~String();

    size_t size;
    char *str;

    size_t strlen(const char *str);
    char *strcoppy(const char *str, size_t size) const;
    void append(String &other);


    struct TmpString{
        TmpString(const size_t i=0, const char *str = 0):i(i),str(str) {}
        const size_t i;
        const char * str;
        char * newstr;
        String operator[] (const size_t j){
            const size_t newsize = j-i;
            newstr = new char[newsize + 1];
            for (size_t k = 0; k<newsize; k++){
                newstr[k] = str[k+i];
            }
            newstr[newsize] = '\0';
            String tmp(newstr);
            delete [] newstr;
            return tmp;
        }
    };

public:
    TmpString operator[] (const size_t i) const
    {
        return TmpString(i,this->str);
    }
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

String &String::operator=(const String &other)
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

void String::print() const
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

char *String::strcoppy(const char *str, size_t size) const
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
String str;
    String const hello("hello");
    String const hell = hello[0][4]; // теперь в hell хранится подстрока "hell"
    hell.print();
    String const ell  = hello[1][4]; // теперь в ell хранится подстрока "ell"
    ell.print();
    return 0;
}

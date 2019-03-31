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


private:
    struct TmpString{
        TmpString(size_t i, String *str):i(i),str(str) {}
        ~TmpString(){
            delete str;
            delete[] newstr;
        }
        size_t i;
        String *str;
        char *newstr;
        String operator[] (size_t j){
            size_t newsize = j-i;
            newstr = new char[newsize + 1];
            for (size_t k = 0; k<newsize; k++){
                newstr[k] = str->str[k+i];
            }
            newstr[newsize] = '\0';
            return String(newstr);
        }
    };
public:
    TmpString operator[] (size_t i) const
    {
        auto tmp = new String(*this);
        return TmpString(i,tmp);
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

    String const hello("hello");
    String const hell = hello[0][4]; // теперь в hell хранится подстрока "hell"
    hell.print();
    String const ell  = hello[1][4]; // теперь в ell хранится подстрока "ell"
    ell.print();
    return 0;
}

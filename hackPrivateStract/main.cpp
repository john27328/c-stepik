#include <iostream>

using namespace std;


// Класс Cls определен точно таким образом:

struct Cls {
    Cls(char c, double d, int i): c(c),d(d), i(i)
    {

    }
    void print()
    {
        cout << c << " "<<d << " " << i << endl;
//        cout << (void *)(&c) << " "<< &d << " " << &i << endl;
//        cout <<  ((char *) &d - (char *)&c ) << endl;
    }
private:
    char c;
    double d;
    int i;
};



// Эта функция должна предоставить доступ к полю c объекта cls.
// Обратите внимание, что возвращается ссылка на char, т. е.
// доступ предоставляется на чтение и запись.
char &get_c(Cls &cls) {
    return (char &)(cls);
}

// Эта функция должна предоставить доступ к полю d объекта cls.
// Обратите внимание, что возвращается ссылка на double, т. е.
// доступ предоставляется на чтение и запись.
double &get_d(Cls &cls) {
    char *p = (char *)&cls;
    p += sizeof(char) + 7;
    double *dp = (double *)p;
    double *&cp = dp;
    return (*cp);
}

// Эта функция должна предоставить доступ к полю i объекта cls.
// Обратите внимание, что возвращается ссылка на int, т. е.
// доступ предоставляется на чтение и запись.
int &get_i(Cls &cls) {
    char *p = (char *)&cls;
//    cout << sizeof(char) + sizeof(double) + 7 <<endl;
    p += sizeof(char) + sizeof(double) + 7;
    int *ip =(int *)p;
    int *&cp = ip;
    return (*cp);
}

int main()
{
    Cls cls('h', 3.14, 4);
    cls.print();
    char &c = get_c(cls);
    c = 'u';
    double &d = get_d(cls);
    d = 4;
    int &i = get_i(cls);
    i = 42;
//    cout << "((char *) &d - (char *)&c ) " <<((char *) &d - (char *)&c ) << endl;
    cls.print();
    return 0;
}

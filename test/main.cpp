#include <iostream>

using namespace std;

class A
{
public:
    virtual void a(){
        cout << "public A"<<endl;
    }
    virtual ~A(){}

private:
    virtual void b(){
        cout << "private A"<<endl;
    }
protected:
    virtual void c(){
        cout << "protected A"<<endl;
    }
};

class B: private A
{
    void b(){
        cout << "private B"<<endl;
        A::a();

    }
    void a(){
        cout << "public B"<<endl;
    }
    void c(){
        cout << "protected B"<<endl;
    }
};

class C: public B
{
public:
    void b(){
        cout << "private C"<<endl;
        B::c();
    }
private:
    void a(){
        cout << "public C"<<endl;
    }
};

int main ()
{
    A a;
    B b;
    C c;
    a.a();
    c.b();
    return 0;
}

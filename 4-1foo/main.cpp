#include <iostream>

using namespace std;

#include <iostream>

struct Foo {
    void say() const { std::cout << "Foo says: " << msg << "\n"; }
protected:
    Foo(const char *msg) : msg(msg) { }
private:
    const char *msg;
};

void foo_says(const Foo &foo) { foo.say(); }



// Вам нужно определить функцию get_foo, как описано в задании,
// чтобы компилировался и работал как ожидается следующий код:
//
// foo_says(get_foo("Hello!"));

class FooCild : public Foo
{
public:
    FooCild(const char *msg): Foo(msg) { }
};

Foo get_foo(const char *msg) {
    FooCild fooc(msg);
    return (Foo)fooc;
}

int main(int argc, char *argv[])
{
    foo_says(get_foo("Hello!"));
    return 0;
}

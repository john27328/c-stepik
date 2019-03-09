#include <iostream>
using namespace std;

int foo() {
  int * m[1];
  cout << "Hello" << endl;
  return 2;
}

int bar() {
  int * m[1];
  m[3] = (int *) &foo;
  return 1;
}

int main()
{
  bar();
  cout << "world" <<endl;
  return 0;
}

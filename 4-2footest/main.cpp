#include <iostream>

using namespace std;

void foo(char) { std::cout << "char" << std::endl; }
void foo(signed char) { std::cout << "signed char" << std::endl; }
void foo(unsigned char) { std::cout << "unsigned char" << std::endl; }

float  square(float value) { return value * value; }
//double square(float value) { return (double)value * value; }

void promotion(char &) { std::cout << "char" << std::endl; }
void promotion(int  &) { std::cout << "int"  << std::endl; }
void promotion(long &) { std::cout << "long" << std::endl; }

int main()
{
    //foo(97);
    short sh = 10;
    promotion(sh);
    //double sq = square(2.0);
    return 0;
}

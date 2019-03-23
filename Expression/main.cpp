#include <iostream>

using namespace std;

struct Expression
{
public:
    virtual double evaluate() const = 0;
    virtual ~Expression(){}
};

struct Number: public Expression
{
public:
    Number(double value)
        : value(value)
    {}
    ~Number(){}

    double evaluate() const
    {
        return value;
    }
private:
    double value;
};

struct BinaryOperation: public Expression
{
public:
    /*
      Здесь op это один из 4 символов: '+', '-', '*' или '/', соответствующих операциям,
      которые вам нужно реализовать.
     */
    BinaryOperation(Expression const * left, char op, Expression const * right)
        : left(left), op(op), right(right)
    { }
    ~BinaryOperation(){
        delete left;
        delete right;
    }

    double evaluate() const
    {
        switch (op) {
        case '+':
            return left->evaluate() + right->evaluate();
        case '-':
            return left->evaluate() - right->evaluate();
        case '*':
            return left->evaluate() * right->evaluate();
        case '/':
            return left->evaluate() / right->evaluate();
        default:
            break;
        }
    }

private:
    Expression const * left;
    Expression const * right;
    char op;
};

bool check_equals(Expression const *left, Expression const *right)
{
    char const* l = &(((char const*)left)[0]);
    char const* r = &(((char const*)right)[0]);
    cout << " l = " << l << " r = " << r << endl;
    return *l == *r;
}


int main()
{
    // сначала создаём объекты для подвыражения 4.5 * 5
    Expression * sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
    // потом используем его в выражении для +
    Expression * expr = new BinaryOperation(new Number(3), '+', sube);

    // вычисляем и выводим результат: 25.5
    std::cout << expr->evaluate() << std::endl;

    // тут освобождаются *все* выделенные объекты
    // (например, sube будет правым операндом expr, поэтому его удалять не нужно)
    cout << check_equals(new Number(4.5), new Number(3)) <<endl;
    cout << check_equals(new Number(4.5), expr) <<endl;
    delete expr;
    return 0;
}

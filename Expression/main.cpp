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

struct ScopedPtr
{
    // реализуйте следующие методы:
    //
    explicit ScopedPtr(Expression *ptr = 0): ptr_(ptr) {}
    ~ScopedPtr(){
        delete ptr_;
    }
    Expression* get() const{
        return ptr_;
    }
    Expression* release()
    {
        Expression* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }
    void reset(Expression *ptr = 0){
        delete ptr_;
        ptr_=ptr;
    }
    Expression& operator*() const{
        Expression &tmp = *ptr_;
        return tmp;
    }
    Expression* operator->() const{
        return ptr_;
    }

private:
    // запрещаем копирование ScopedPtr
    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator=(const ScopedPtr&);

    Expression *ptr_;
};

struct counter
{
    int i = 0;
};

struct SharedPtr
{
    // реализуйте следующие методы
    //
    explicit SharedPtr(Expression *ptr = 0):ptr_(ptr) {
        c_ = new counter;
        c_->i++;
    }
    ~SharedPtr(){
        c_->i--;
        if (c_->i == 0){
            //cout << "del " << ptr_<<endl;
            delete c_;
            delete ptr_;
        }
    }
    SharedPtr(const SharedPtr & sPtr){
        ptr_ = sPtr.ptr_;
        c_ = sPtr.c_;
        c_->i++;
    }
    SharedPtr& operator=(const SharedPtr &sPtr){
        c_->i--;
        if (c_->i == 0){
            delete c_;
            delete ptr_;
        }
        ptr_ = sPtr.ptr_;
        c_ = sPtr.c_;
        c_->i++;
        return *this;
    }
    Expression* get() const{
        return ptr_;
    }
    void reset(Expression *ptr = 0){
        c_->i--;
        if (c_->i == 0){
            delete ptr_;
            delete c_;
        }
        ptr_=ptr;
        c_ = new counter;
        c_->i++;
    }
    Expression& operator*() const{
        Expression &tmp = *ptr_;
        return tmp;
    }
    Expression* operator->() const{
        return ptr_;
    }

private:
    counter *c_;
    Expression *ptr_;
};

int main()
{
//    // сначала создаём объекты для подвыражения 4.5 * 5
//    Expression * sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
//    // потом используем его в выражении для +
//    Expression * expr = new BinaryOperation(new Number(3), '+', sube);

//    // вычисляем и выводим результат: 25.5
//    std::cout << expr->evaluate() << std::endl;

//    // тут освобождаются *все* выделенные объекты
//    // (например, sube будет правым операндом expr, поэтому его удалять не нужно)
//    cout << check_equals(new Number(4.5), new Number(3)) <<endl;
//    cout << check_equals(new Number(4.5), expr) <<endl;
//    delete expr;

    SharedPtr ptr1(new BinaryOperation(new Number(4.5), '*', new Number(5)));
    SharedPtr ptr2 = ptr1;
    SharedPtr ptr3(new Number(4.5));
    SharedPtr ptr4 = ptr3;
    ptr3 = ptr1;
    Expression *ptr = ptr1.get();
    return 0;
}

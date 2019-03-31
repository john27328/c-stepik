#include <iostream>

struct Rational {
    Rational(int numerator = 0, int denominator = 1) : numerator_(numerator), denominator_(denominator) {}

    void add(Rational rational) {
        numerator_ = numerator_ * rational.denominator_ + rational.numerator_ * denominator_;
        denominator_ *= rational.denominator_;
    }

    void sub(Rational rational) {
        numerator_ = numerator_ * rational.denominator_ - rational.numerator_ * denominator_;
        denominator_ *= rational.denominator_;
    }

    void mul(Rational rational) {
        numerator_ *= rational.numerator_;
        denominator_ *= rational.denominator_;
    }

    void div(Rational rational) {
        numerator_ /= rational.denominator_;
        denominator_ /= rational.numerator_;
    }

    void neg() {
        numerator_ = -numerator_;
    }

    void inv() {}

    double to_double() const {
        return numerator_ / (double) denominator_;
    }

    Rational &operator += (Rational r){
        this->add(r);
        return *this;
    }
    Rational &operator *= (Rational r){
        this->mul(r);
        return *this;
    }
    Rational &operator -= (Rational r){
        this->sub(r);
        return *this;
    }
    Rational &operator /= (Rational r){
        this->div(r);
        return *this;
    }

    Rational operator -() const{
        Rational r = *this;
        r.neg();
        return  r;
    }

    Rational operator +() const{
        Rational r = *this;
        return  r;
    }

    bool negative(){
        return (this->numerator_* this->denominator_) < 0;
    }

    operator double() const
    {
        return this->to_double();
    }

private:
    int numerator_;
    int denominator_;
};



Rational operator+ (Rational r1, Rational const &r2)
{
    return r1+=r2;
}

Rational operator- (Rational r1, Rational const &r2)
{
    return r1-=r2;
}

Rational operator* (Rational r1, Rational const &r2)
{
    return r1*=r2;
}

Rational operator/ (Rational r1, Rational const &r2)
{
    return r1/=r2;
}

bool operator < (Rational const &a, Rational const &b)
{
    Rational r = a - b;
    return r.negative();
}

bool operator == (Rational const &a, Rational const &b)
{
    return !(a < b) && !(b < a);
}

bool operator != (Rational const &a, Rational const &b)
{
    return !(a == b);
}
bool operator > (Rational const &a, Rational const &b)
{
    return (b < a);
}

bool operator <= (Rational const &a, Rational const &b)
{
    return !(b < a);
}

bool operator >= (Rational const &a, Rational const &b)
{
    return !(a < b);
}


int main() {
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational r3(5);
    Rational r4 = r1;
    int i = 3;

    r1.add(r2);
    r4+=r2;
    std::cout << r1.to_double() << " " << r4.to_double()<<std::endl;
    r1.sub(r2);
    r4-=r2;
    std::cout << r1.to_double() << " " << r4.to_double()<< std::endl;
    r1.neg();
    std::cout << r1.to_double() << " " << r4.to_double()<< std::endl;
    r3.mul(r1);
    (r4*=5)*=7;
    std::cout << r3.to_double() << " " << r4.to_double()<< std::endl;
    r3.div(r2);
    r3 = +i;
    r4 = +(-r3);
    std::cout << r3.to_double() << " " << r4.to_double()<< std::endl;
}

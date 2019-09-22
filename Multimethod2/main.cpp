#include <iostream>

#include <typeinfo>
#include <typeindex>
#include <map>
#include <tuple>


// базовый класс фигуры (полиморфный)
struct Shape {
    Shape(){}
    virtual ~Shape(){}
};

// прямоугольник
struct Rectangle : Shape {
    Rectangle(){}
    int x1=0, y1=0, x2=0, y2=0;
    ~Rectangle(){}
};

// треугольник
struct Triangle : Shape {
    Triangle() {}
    int x1=0, y1=0, x2=0, y2=0, x3=0, y3=0;
    ~Triangle(){}
};

// функция для проверки пересечения двух прямоугольников
bool is_intersect_r_r(Shape * a, Shape * b){
    std::type_index tA = typeid (*a);
    std::type_index tB = typeid (*b);
    std::cout << "is_intersect_r_r " << tA.name() << " " << tB.name() << std::endl;
    return true;
}

// функция для проверки пересечения прямоугольника и треугольника
bool is_intersect_r_t(Shape * a, Shape * b){
    std::type_index tA = typeid (*a);
    std::type_index tB = typeid (*b);
    std::cout << "is_intersect_r_t  " << tA.name() << " " << tB.name() << std::endl;
    return true;
}


// Base - базовый класс иерархии
// Result - тип возвращаемого значения мультиметода
// Commutative - флаг, который показывает, что
// мультиметод коммутативный (т.е. f(x,y) = f(y,x)).


template<class Base, class Result, bool Commutative>
struct Multimethod2
{
    using type = const std::type_index;
    using doubleType = std::tuple<type, type>;
    using pF = Result (*)(Shape*, Shape*);
private:
    std::map<doubleType, pF> _map;
public:
    // устанавливает реализацию мультиметода
    // для типов t1 и t2 заданных через typeid
    // f - это функция или функциональный объект
    // принимающий два указателя на Base
    // и возвращающий значение типа Result
    // добавляет реализацию мультиметода для двух типов, которые заданы через std::type_info.
    void addImpl(type a, type b, pF f)
    {
//        std::cout << "addImpl " << a.name() << " " << b.name() << std::endl;
        _map.emplace(std::make_tuple(a, b), f);
    }

    // проверяет, есть ли реализация мультиметода
    // для типов объектов a и b
    // принимает два указателя и проверяет, есть ли реализация мультиметода для соответствующих типов.
    bool hasImpl(Base * a, Base * b) const
    {
        std::type_index tA = typeid (*a);
        std::type_index tB = typeid (*b);
//        std::cout << "hasImpl " << tA.name() << " " << tB.name() << std::endl;
        auto it = _map.find(std::make_tuple(tA, tB));
        if (it  != _map.end()){
//            std::cout << "hasImpl true" << std::endl;
            return true;
        }
        if (Commutative){
            it = _map.find(std::make_tuple(tB, tA));
            if (it  != _map.end()){
    //            std::cout << "hasImpl true" << std::endl;
                return true;
            }
        }
//        std::cout << "hasImpl false" << std::endl;
        return false;
    }

    // Применяет мультиметод к объектам
    // по указателям a и b
    //принимает два указателя и вызывает для них соответствующую реализацию.
    Result call(Base * a, Base * b) const
    {
        std::type_index tA = typeid (*a);
        std::type_index tB = typeid (*b);
        auto it = _map.find(std::make_tuple(tA, tB));
        if (it != _map.end()){
            //pF f = it->second;
            //Result tmp = (f)(a,b);
            return (it->second)(a,b);
        }
        if (Commutative){
            it = _map.find(std::make_tuple(tB, tA));
            if (it  != _map.end()){
    //            std::cout << "hasImpl true" << std::endl;
                return (it->second)(b,a);
            }
        }
        return 0;
    }

};

int main()
{
    // мультиметод для наследников Shape
    // возращающий bool и являющийся коммутативным
    Multimethod2<Shape, bool, true> is_intersect;

    // добавляем реализацию мультиметода для двух прямоугольников
    is_intersect.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_r_r);

    // добавляем реализацию мультиметода для прямоугольника и треугольника
    is_intersect.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);

    // создаём две фигуры
    Shape * s1 = new Triangle();
    Shape * s2 = new Rectangle();

    // проверяем, что реализация для s1 и s2 есть
    if (is_intersect.hasImpl(s1, s2))
    {
         // вызывается функция is_intersect_r_t(s2, s1)
         bool res = is_intersect.call(s1, s2);

         // Замечание: is_intersect_r_t ожидает,
         // что первым аргументом будет прямоугольник
         // а вторым треугольник, а здесь аргументы
         // передаются в обратном порядке.
         // ваша реализация должна самостоятельно
         // об этом позаботиться
    }
    return 0;
}

#include <iostream>
#include <cstddef>
using namespace std;

template <typename T>
class Array
{
    // explicit Array(size_t size = 0, const T& value = T())
    //   конструктор класса, который создает
    //   Array размера size, заполненный значениями
    //   value типа T. Считайте что у типа T есть
    //   конструктор, который можно вызвать без
    //   без параметров, либо он ему не нужен.
public:
    explicit Array(size_t size = 0, const T& value = T()):s(size){
        array = new T[size];
        for (size_t i = 0; i < size; i++)
        {
            array[i] = value;
        }
    }

    // Array(const Array &)
    //   конструктор копирования, который создает
    //   копию параметра. Считайте, что для типа
    //   T определен оператор присваивания.
    Array(const Array  &arr){
        this->s = arr.s;
        array = new T[s];
        for (size_t i = 0; i < s; i++)
        {
            this->array[i] = arr.array[i];
        }
    }

    // ~Array()
    //   деструктор, если он вам необходим.

    ~Array(){
        delete array;
    }

    // Array& operator=(...)
    //   оператор присваивания.


    // size_t size() const
    //   возвращает размер массива (количество
    //                              элементов).
    size_t size() const{
        return s;
    }
    // T& operator[](size_t)
    // const T& operator[](size_t) const
    //   две версии оператора доступа по индексу.

    void print()
    {
        for (size_t i = 0; i < s; i++)
        {
            cout << array[i] <<endl;
        }
    }
private:
    T *array;
    size_t s;
};

int main()
{
    auto arr = new Array<int>(3, 43);
    auto arr2 = arr;
    arr->print();
    arr2->print();
    cout << "Hello World!" << endl;
    return 0;
}

#include <iostream>

//using namespace std;

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
    explicit Array(size_t size = 0, const T& value = T()):size_(size){
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
        this->size_ = arr.size_;
        array = new T[size_];
        for (size_t i = 0; i < size_; i++)
        {
            this->array[i] = arr.array[i];
        }
    }

    // ~Array()
    //   деструктор, если он вам необходим.

    ~Array(){
        delete[] array;
    }

    // Array& operator=(...)
    //   оператор присваивания.
    Array& operator=(const Array  &arr)
    {
        if (arr.array != this->array)
        {
            delete[] this->array;
            this->size_ = arr.size_;
            this->array = new T[size_];
            for (size_t i = 0; i < size_; i++)
            {
                this->array[i] = arr.array[i];
            }
        }
        return *this;
    }

    // size_t size() const
    //   возвращает размер массива (количество
    //                              элементов).
    size_t size() const{
        return size_;
    }
    // T& operator[](size_t)
    // const T& operator[](size_t) const
    //   две версии оператора доступа по индексу.

    T& operator[](size_t i){
        //std::cout << "test " <<   array[i];
        return (array[i]);
    }

    const T& operator[](size_t i)const{
        return array[i];
    }
    void print()
    {
        for (size_t i = 0; i < size_; i++)
        {
            std::cout << array[i] <<std::endl;
        }
    }

        void prnt()
        {
            for (size_t i = 0; i < size_; ++i)
                std::cout << *(array+i);
            std::cout << std::endl;
        }

private:
    T *array;
    size_t size_;
};

template <class T, class Less>
T minimum(Array<T> arr, Less less){
    T min = arr[0];
    for (size_t i=0; i < arr.size(); i++){
        if (less(arr[i],min)) { min = arr[i];}
    }
    return min;
}

bool less(int a, int b) { return a < b; }
struct Greater { bool operator()(int a, int b) const { return b < a; } };


int main()
{
    Array<int> ints(3);
    ints[0] = 10;
    ints[1] = 2;
    ints[2] = 15;
    int min = minimum(ints, less); // в min должно попасть число 2
    int max = minimum(ints, Greater()); // в max должно попасть число 15
    return 0;
}

#include <iostream>

using namespace std;
template <typename T>
class Array
{
public:
    explicit Array(size_t size = 0, const T& value = T()):size_(size){
        array = new T[size];
        for (size_t i = 0; i < size; i++)
        {
            array[i] = value;
        }
    }

    Array(const Array  &arr){
        this->size_ = arr.size_;
        array = new T[size_];
        for (size_t i = 0; i < size_; i++)
        {
            this->array[i] = arr.array[i];
        }
    }

    ~Array(){
        delete[] array;
    }

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

    size_t size() const{
        return size_;
    }

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

template <typename T>
void flatten(const Array<T>& array, std::ostream& out)
{

    for(int i = 0; i < array.size(); i++){
        flatten(array[i], out);
    }
}

void flatten(const Array<int>& array, std::ostream& out)
{
    for(int i = 0; i < array.size(); i++){
        out << array[i] << " ";
    }
}

void flatten(const Array<double>& array, std::ostream& out)
{
    for(int i = 0; i < array.size(); i++){
        out << array[i] << " ";
    }
}



int main()
{
    Array<int> ints(2, 0);
    ints[0] = 10;
    ints[1] = 20;
    flatten(ints, std::cout); // выводит на экран строку "10 20"
    cout << endl;
    Array< Array<int> > array_of_ints(2, ints);
    flatten(array_of_ints, std::cout); // выводит на экран строку "10 20 10 20"
    cout << endl;
    Array<double> doubles(10, 3.14);
    flatten(doubles, std::cout); // работать должно не только для типа int
    return 0;
}

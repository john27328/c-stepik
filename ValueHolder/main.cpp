#include <iostream>

using namespace std;
struct ICloneable
{
    virtual ICloneable* clone() const = 0;
    virtual ~ICloneable() { }
};

template <typename T>
struct ValueHolder: ICloneable{
    explicit ValueHolder (const T &data):data_(data){}
    ValueHolder* clone() const{
        return (new ValueHolder(*this));
    }
    ~ValueHolder(){}
    T data_;
};

class Any
{
public:
    Any():data_(nullptr){
    }

    template<class T>
    Any(T data){
        data_ = new ValueHolder<T>(data);
    }

    ~Any(){
        delete data_;
    }

    Any (const Any &any):data_(nullptr){
        if (any.data_ != nullptr)
            data_ = any.data_->clone();
    }

    Any& operator=(const Any &any)
    {
        if (any.data_ != nullptr)
        {
            if (data_ != any.data_)
            {
                delete data_;
                data_ = any.data_->clone();
            }
        }
        else{
            delete data_;
            data_ = nullptr;
        }
        return *this;
    }

    template<class T>
    T* cast(){
        ValueHolder<T>* tmp = dynamic_cast<ValueHolder<T> *>(data_);

        if (tmp != nullptr) return &(tmp->data_);
        else
            return nullptr;
    }


private:
    ICloneable *data_;
};

//int main()
//{
//    Any empty;
//    Any i(10); // i хранит значение 10
//    Any copy(i); // copy хранит 10, как и i
//    empty = copy; // empty хранит 10, как и copy
//    empty = 0; // а теперь empty хранит 0
//    int *iptr = i.cast<int>(); // *iptr == 10
//    char *cptr = i.cast<char>(); // cptr == 0,
//    // потому что i хранит int, а не char
//    Any empty2;
//    empty = empty2;
//    int *p = empty2.cast<int>(); // p == 0
//    return 0;
//}

void test0();
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();

int main()
{
    test0();
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    cout << "WIN!"<<endl;
    return 0;
}

void test0()
{
    struct X
    {
        ICloneable *p;
    };
    cout << endl << "***** Empty ***" << " (" << __FUNCTION__ << ")" << endl;
    Any aEmpty(NULL);
    //auto test = *aEmpty.cast<long long>();
    //cout << *aEmpty.cast<int>() << endl;
    Any bEmpty;
    if (((X*)&bEmpty)->p == NULL) {
        cout << "Empty: OK";
    }
    else
    {
        cout << "Empty: Failed" << endl;
    }
    cout << endl;
    if (bEmpty.cast<string>()) { cout << *bEmpty.cast<string>() << endl; }
    Any  cEmpty;
    bEmpty = cEmpty;
    cout << "Address: " << &bEmpty << " Pointer value: " << (((X*)&bEmpty)->p) << endl;
}
void test1()
{
    cout << endl << "***** INT (Self = Self ) ***" << " (" << __FUNCTION__ << ")" << endl;
    int INT = 1;
    Any aINT(INT);
    cout << *aINT.cast<int>() << " == " << INT << endl;
    aINT = aINT;
    cout << *aINT.cast<int>() << " == " << INT << endl;
}
void test2()
{
    cout << endl << "***** INT (Copy ) ***" << " (" << __FUNCTION__ << ")" << endl;
    int INT = 2;
    Any aINT(INT);
    cout << *aINT.cast<int>() << " == " << INT << endl;;
    Any nEmpy(aINT);
    cout << *nEmpy.cast<int>() << " == " << INT << endl;


}

void test3()
{
    cout << endl << "***** INT (Empty, =, copy, cast) ***" << " (" << __FUNCTION__ << ")" << endl;
    int INT = 10;
    {
        Any aINT(INT);
        cout << *aINT.cast<int>() << " == " << INT ;
    }
    cout << endl;
    {
        Any aINT(INT);
        Any aEmpty;
        aEmpty = aINT;
        int tmp = *aEmpty.cast<int>();
        cout << tmp << " == " << INT ;
    }
    cout << endl;
    {
        Any aINT(INT);
        Any aEmpty;
        aEmpty = aINT;
        aEmpty = aEmpty;
        cout << *aEmpty.cast<int>() << " == " << INT ;
    }
    cout << endl;
    {
        Any aEmpty;
        aEmpty = 0;
        cout << *aEmpty.cast<int>() << " == " << 0 ;
    }
    cout << endl;
    {
        struct X
        {
            ICloneable *p;
        };
        Any aEmpty;
        Any bEmpty(aEmpty);
        if (((X*)&bEmpty)->p == NULL) {
            cout << "Empty: OK";
        }
        else
        {
            cout << "Empty: Failed" << endl;
        }
    }
    cout << endl;
    return;
}

void test4()

{
    string  STR("Hello!");
    cout << endl << "***** STRING (empty, =, copy, cast) ***" << " (" << __FUNCTION__ << ")" << endl;
    {

        Any aINT(STR);
        cout << *aINT.cast<string>() << " == " << STR ;
    }
    cout << endl;
    {
        Any aINT(STR);
        Any aEmpty;
        aEmpty = aINT;
        cout << *aEmpty.cast<string>() << " == " << STR << endl;
    }
    cout << endl;
    {
        string sEmpty("");
        Any aEmpty(sEmpty);
        aEmpty = aEmpty;
        cout << *aEmpty.cast<string>() << " == " << STR << endl;
        aEmpty = aEmpty;
        cout << *aEmpty.cast<string>() << " == " << STR << endl;
        Any nEmpty(aEmpty);
        cout << *nEmpty.cast<string>() << " == " << STR << endl;
    }
    cout << endl;
    {
        int i = 10;
        ValueHolder<int>* intHolder = new ValueHolder<int>(i);
        ValueHolder<char>* charHolder = dynamic_cast<ValueHolder<char>*>(intHolder->clone());
        ValueHolder<int>* int2Holder = dynamic_cast<ValueHolder<int>*>(intHolder->clone());
        cout << "Char* 4 Int* " << (charHolder ? "Cast: OK" : "Cast: Failed") << endl;
        cout << "Int* 4 Int*" << (int2Holder ? "Cast: OK" : "Cast: Failed") ;
        delete intHolder;
        delete charHolder;
        delete int2Holder;
    }
    cout << endl;
}
void test5()
{
    cout << endl << "*** INT, DOUBLE, STRING ***" << " (" << __FUNCTION__ << ")" << endl;
    string Hello = "Hello World People";
    ValueHolder<int> Int(10);
    ValueHolder<string> Str(Hello);
    double Dbl = 10.112233;

    Any aHello(Hello);
    Any aInt(Int);
    Any aStr(Str);
    Any aDbl(Dbl);

    cout << aHello.cast<string>()->data() << " == " << Hello.data() << endl;
    cout << aInt.cast<ValueHolder<int> >()->data_ << " == " << Int.data_ << endl;
    cout << aStr.cast<ValueHolder<string> >()->data_.data() << " == " << Hello.data() << endl;
    cout << *aDbl.cast<double>() << " == " << Dbl << endl;

    aHello = (char*)"Any other simple text";
    aInt = 10241;
    aDbl = 234.5675;

    cout << *aHello.cast<char *>() << " == " << "Any other simple text" << endl;
    cout << *aInt.cast<int>() << " == " << 10241 << endl;
    cout << *aDbl.cast<double>() << " == " << 234.5675 << endl;
}
void test6()
{
    // Memory leak!!!
    cout << endl << "*** Array (= new Any(i))***" << " (" << __FUNCTION__ << ")" << endl;
    int n = 5;
    {
        Any *pAny = new Any[n];
        for (int i = 0; i < n; i++)
            pAny[i] = new Any(i*i + 1);

        for (int i = 0; i < n; i++)
            cout << "\tpAny[" << i << "] = " << *(*pAny[i].cast<Any*>())->cast<int>() << " == " << i*i + 1 << endl;
        delete[] pAny;
    }
    cout << endl;
}

void test7()
{
    cout << endl << "*** Array (= Any(i))***" << " (" << __FUNCTION__ << ")" << endl;
    const int n = 30;
    Any pAny2[n];

    for (int i = 0; i < n; i++)
        pAny2[i] = Any(i + 1);

    for (int i = 0; i < n; i++)
        cout << "\tpAny2[" << i << "] = " << *pAny2[i].cast<int>() << " == " << i + 1 << endl;
}

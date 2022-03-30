#include <iostream>

using namespace std;

class A {
    int m;
    void test1(){}
};

class B {
    virtual void test2(){}
    void test3(){}
};

template <typename T>
std::true_type check(
    decltype(dynamic_cast<const volatile void*>(static_cast<T*>(nullptr)))
);

template <typename T>
std::false_type check(...);

template <typename T>
struct has_virtual_function : decltype(check<T>(nullptr))
{

};

template<typename T>
void foo(T& c)
{
  if (has_virtual_function<T>::value)
    cout << " T has virtual function"<<endl;
  else
    cout << " T has not virtual function"<<endl;

}

int main()
{
  A a;
  B b;

  foo(a);
  foo(b);
}

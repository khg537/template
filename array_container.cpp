#include <iostream>
#include <type_traits>
#include <vector>

using namespace std;

template<int N> struct int2type
{
  enum{ value = N};
};

template<typename T> struct xis_array
{
  static constexpr bool value = false;
  static constexpr size_t  size = -1;
};

template<typename T, size_t N> struct xis_array<T[N]>
{
  static constexpr bool value = true;
  static constexpr size_t size = N;
};

template<typename T>
double average_imp(T& a, int2type<1>)
{
    int sum = 0;

    for (int i = 0 ; i < xis_array<T>::size ; i++)
    {
      sum += a[i];
    }

    return (double) sum / xis_array<T>::size;
}

template<typename T>
double average_imp(T& a, int2type<0>)
{
    int sum = 0;

    for (typename T::iterator it = a.begin(); it != a.end() ; it++)
    {
      sum += *it;
    }

    return (double) sum / a.size();
}

template<typename T>
double average(T& a)
{

  return average_imp(a,int2type<is_array<T>::value>());

}

int main()
{
  int x[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9 ,10};
  vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  cout << average(x) << endl;
  cout << average(v) << endl;
  return 0;
}

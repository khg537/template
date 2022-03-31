#include <iostream>
#include <cstring>

using namespace std;

int print(int a)
{
  cout<<a ;
  return 0;
}

template<typename...Types>
void cpp_print(char* arg, Types ... args)
{
  int num = 0;

  size_t nSize = sizeof...(args);

  char* ptr = strstr(arg, "%d" );

  while(ptr != nullptr && ++num)
  {
    ptr = strstr(ptr +1, "%d" );
  }

  if (nSize != num) throw std::invalid_argument( "Invalid argument" );

  int x[] = {print(args)...};

}

int main()
{
  // printf("%d\n", 1, 2,3);
  // printf("%d%d\n", 1);


  try
  {
     cpp_print("%d\n", 1 , 2, 3);
    // cpp_print("%d%d%d\n",1);
    cpp_print("%d%d\n",13, 5);
  }
  catch(...)
  {
    cout << " Exception" <<endl;
  }
}

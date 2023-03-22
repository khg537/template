#include <iostream>
#include <new>

using namespace std;

class Point
{
  int x;
  int y;
public:
  Point(int a, int b): x(a), y(b) { }

  friend ostream& operator<<(ostream& os, const Point& p)
  {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
  }

};

template<typename T> class Vector
{
  T* buff;
  int sz;
  int capa;
public:
  Vector(int size,  const T& val) : sz(size), capa(size)
  {
    buff = static_cast<T*>(operator new(sizeof(T)*size));
    for (int i = 0 ; i < size ; i++)
    {
      new(&buff[i]) T(val);
    }
  }

  void resize(int new_sz)
  {
    if (new_sz <= sz) 
    {   
      for (int i = new_sz ; i < sz; i++)
      {   
        buff[i].~T();
      }   
      sz = new_sz;
    }   
    else
         else
    {
      T* p1 = static_cast<T*>(operator new(sizeof(T)*new_sz));

      for (int i = 0 ; i < sz ; i++)
      {
        new(&p1[i]) T(move_if_noexcept(buff[i]));
      }

      for (int i = sz ; i < new_sz ; i++)
      {
        new(&p1[i]) T(0,0);
      }

      sz = new_sz;
      capa = new_sz;
      buff= p1;
    }

    
  }

  void resize(int new_sz, const T& val)
  {
    if (new_sz <= sz)
    {
      for (int i = new_sz ; i < sz; i++)
      {
        buff[i].~T();
      }
      sz = new_sz;
    }
    else
    {
      T* p1 = static_cast<T*>(operator new(sizeof(T)*new_sz));

      for (int i = 0 ; i < sz ; i++)
      {
        new(&p1[i]) T(move_if_noexcept(buff[i]));
      }

      for (int i = sz ; i < new_sz ; i++)
      {
        buff[i].~T();
      }
      sz = new_sz;
      capa = new_sz;
      buff = p1;
    }
  }

  int size()
  {
    return sz;
  }
  
  int capacity()
  {
    return capa;
  }

  friend ostream& operator<<(ostream& os, const Vector<T>& v)
  {
    os << "[";
    for (int i = 0 ; i < v.sz ; i++)
      os << v.buff[i] <<"\n" ;
    os<<"]";
      return os;
  }

  Vector(const std::initializer_list<T>& i_list) : sz(i_list.size()), capa(i_list.size())
  {
    buff = static_cast<T*>(operator new(sizeof(T)*sz));
    int i = 0;
    for (auto& e : i_list)
    {
      new(&buff[i++]) T(e);
    }

  }

  T* begin() const {return buff;}
  T* end() const{return buff + sz;};

};

int main()
{
  Vector<Point> v(10, Point(1,1));

//  cout <<v <<endl;
  v.resize(20, Point(0,0));

//  cout <<v <<endl;
  v.resize(10);

//  cout <<v <<endl;

//  cout <<v.size() << endl;
//  cout <<v.capacity() << endl;

  Vector<int> v2{1,2,3, 4,5,6,7,8, 9, 11,22,33,44};

  for (auto n : v2)
    cout << n <<endl;
}

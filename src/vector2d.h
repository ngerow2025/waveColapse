//
// Created by ngero on 3/22/21.
//

#ifndef MYPROJECT_VECTOR2D_H
#define MYPROJECT_VECTOR2D_H
#include <boost/stacktrace.hpp>
#include <iostream>
#include <map>

template <typename T>
class Matrix2dv2
{
private:
  T _defVal;
public:
  Matrix2dv2(T defVal): _defVal(defVal){}
  T &getVal(int a, int b)
  {
    if (m.find(a) == m.end())
    {
      return _defVal;
    }
    else
    {
      if (m[a].find(b) == m[a].end())
      {
        return _defVal;
      }
      else
      {
        return m[a][b];
      }
    }
  }
  std::map<int, T> &operator[](int a)
  {
    return m[a];
  }
  std::map<int, std::map<int, T>> m;

};

template <typename T>
using Matrix2d = std::map<int, std::map<int, T>>;

#endif//MYPROJECT_VECTOR2D_H

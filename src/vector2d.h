//
// Created by ngero on 3/22/21.
//

#ifndef MYPROJECT_VECTOR2D_H
#define MYPROJECT_VECTOR2D_H
#include <iostream>
#include <map>


#ifdef _MSC_VER
#pragma warning(disable: 4826 4619)
#endif
#include <boost/stacktrace.hpp>
#ifdef _MSC_VER
#pragma warning(default: 4619 4619)
#endif

template<typename T>
class Matrix2dv2
{
private:
  T _defVal;
  std::map<int, std::map<int, T>> m;
public:
  explicit Matrix2dv2(T defVal) : _defVal(defVal) {}
  T &getVal(int a, int b)
  {
    if (m.find(a) == m.end()) {
      return _defVal;
    }

    if (m[a].find(b) == m[a].end()) {
      return _defVal;
    }

    return m[a][b];
  }
  std::map<int, T> &operator[](int a)
  {
    return m[a];
  }
};

template<typename T>
using Matrix2d = std::map<int, std::map<int, T>>;

#endif//MYPROJECT_VECTOR2D_H

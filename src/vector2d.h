//
// Created by ngero on 3/22/21.
//

#ifndef MYPROJECT_VECTOR2D_H
#define MYPROJECT_VECTOR2D_H
#include <iostream>
#include <map>



//return def val at unknown location
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

//put def val at unassinged location
template<typename T>
class Matrix2dv3{
private:
  T _defVal;
  std::map<int, std::map<int, T>> m;
public:
  explicit Matrix2dv3(T defVal) : _defVal(defVal){}
  T &getVal(int x, int y){
    if(m.find(x) == m.end()){
      m[x][y] = this->_defVal;
      return(m[x][y]);
    }
    if(m[x].find(y) == m[x].end()){
      m[x][y] = this->_defVal;
      return(m[x][y]);
    }
    return(m[x][y]);

  }
};


//has a at_loc that returns wheather a sirtin place exists
template<typename T>
class Matrix2dv4{
private:
  std::map<int, std::map<int, T>> m;
public:
  T &getVal(int x, int y) {
    if(m.find(x) == m.end() || m[x].find(y) == m[x].end()){
      std::cout << "chickity check yourself before you rickity reck youself" << std::endl;
      exit(EXIT_FAILURE);
    }
    return(m[x][y]);

  }
  [[nodiscard]] bool at_loc(int x, int y) {
    return(!(m.find(x) == m.end() || m[x].find(y) == m[x].end()));
  }
  void set(int x, int y, T val){
    m[x][y] = val;
  }
  std::map<int, std::map<int, T>> getData() const {

    return(m);
  }
};




#endif//MYPROJECT_VECTOR2D_H

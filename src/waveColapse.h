//
// Created by ngero on 3/22/21.
//

#ifndef MYPROJECT_WAVECOLAPSE_H
#define MYPROJECT_WAVECOLAPSE_H

#include <functional>
#include <vector>
#include "vector2d.h"
#include <list>


#ifdef _MSC_VER
#pragma warning(disable: 4826 4619)
#endif
#include <boost/dynamic_bitset.hpp>
#ifdef _MSC_VER
#pragma warning(default: 4619 4619)
#endif

struct output{
  int** data;
  int x;
  int y;
};


int* serialise(output data);

enum class dims{
  x,
  y,
  z
};
struct rule{
  boost::dynamic_bitset<> top;
  boost::dynamic_bitset<> bottom;
  boost::dynamic_bitset<> left;
  boost::dynamic_bitset<> right;
};

std::function<output(int x, int y)> gen_new(int dimentions, int width, int height, float* weights, int weights_len, rule* rules, int rules_len);

struct tile
{
  int width;
  int height;
  char charactor;
};
inline bool operator==(tile lhs, tile rhs ){
  return(lhs.width == rhs.width && lhs.height == rhs.height && lhs.charactor == rhs.charactor);
}

inline bool operator!=(tile lhs, tile rhs ){
  return(!(lhs.width == rhs.width && lhs.height == rhs.height && lhs.charactor == rhs.charactor));
}




using domain = boost::dynamic_bitset<>;
using tiles_probs = Matrix2d<domain>;
using tiles = Matrix2dv2<std::pair<tile *, int>>;




void print_map(const Matrix2d<domain> &thang);

float random(float min, float max);

class WCF{
private:
  void update_prob(int x, int y, int depth);
  tiles world_;
  std::vector<float> weights_;
  std::vector<tile> tileSet_;
  std::map<int, rule> rules_;
public:
  WCF(int width, int height, std::vector<float> weights, std::vector<tile> tileSet, std::map<int, rule> rules);
//  void gen_more(int xmin, int xmax, int ymin, int ymax);
  tiles_probs world_probility;
};



#endif//MYPROJECT_WAVECOLAPSE_H

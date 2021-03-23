//
// Created by ngero on 3/22/21.
//

#ifndef MYPROJECT_WAVECOLAPSE_H
#define MYPROJECT_WAVECOLAPSE_H

#include <functional>
#include <vector>
#include "vector2d.h"
#include <list>


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
//int = static_cast<int>(dims::x)
struct rule{
  dims dim;
  int first;//positive direction
  int second;//negitive direction
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




typedef std::list<int> domain;
typedef Matrix2d<domain> tiles_probs;
typedef Matrix2dv2<tile*> tiles;






float random(float min, float max);

class WCF{
private:
  void update_prob(int x, int y, int depth);
public:
  tiles_probs world_probility;
  tiles world;
  std::vector<float> weights;
  std::vector<tile> tileSet;
  std::vector<rule> rules;
  WCF(int width, int height, std::vector<float> weights, std::vector<tile> tileSet, std::vector<rule> rules);
  void gen_more(int xmin, int xmax, int ymin, int ymax);
};




int argmax(int* inputs, float size);
float argmax(float* inputs, float size);

#endif//MYPROJECT_WAVECOLAPSE_H

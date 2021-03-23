//
// Created by ngero on 3/22/21.
//


#include <utility>
#include <vector>
#include "waveColapse.h"
#include <numeric>
#include <iostream>
#include <boost/stacktrace.hpp>
#include <boost/random.hpp>
#include "vector2d.h"
#include <map>
#include <boost/dynamic_bitset.hpp>
#define MAX_PROPIGATION 5

void print_map(const Matrix2d<domain>& thang) {
  for (auto it = thang.cbegin(); it != thang.cend(); ++it) {
    int x = it->first;
    for (auto it2 = it->second.cbegin(); it2 != it->second.cend(); ++it2) {
      std::cout << "pos: " << x << " " << it2->first << std::endl << "val: " << std::endl;
      for (auto thing : it2->second) {
        std::cout << "  " << thing << std::endl;
      }

    }
  }
}

boost::random::mt19937 gen;
int main(){



  gen.seed(static_cast<const unsigned int>(time(nullptr)));
  std::vector<float> weights{1, 1, 1};
  std::vector<tile> tileSet{
    tile{3, 3, 'a'},
    tile{3, 3, 'b'},
    tile{3, 3, 'c'}
  };
  std::vector<rule> rules{
    {dims::x, 0, 1},
    {dims::x, 0, 2},
    {dims::x, 1, 0},
    {dims::x, 1, 2},
    {dims::x, 2, 0},
    {dims::x, 2, 1},


    {dims::y, 0, 1},
    {dims::y, 0, 2},
    {dims::y, 1, 0},
    {dims::y, 1, 2},
    {dims::y, 2, 0},
    {dims::y, 2, 1},
  };
  const int width = 5, height = 5;
  WCF wtf(width, height, weights, tileSet, rules);
  print_map(wtf.world_probility);
  std::cout << "done" << std::endl;
  return(0);
}

float random(float min, float max){
  boost::random::uniform_real_distribution<> dist(static_cast<double>(min), static_cast<double>(max));
  return(static_cast<float>(dist(gen)));
}


WCF::WCF(int width, int height, std::vector<float> weights, std::vector<tile> tileSet, std::vector<rule> rules) :
  world(*new Matrix2dv2<tile*>(nullptr)),
  weights(std::move(weights)),
  tileSet(std::move(tileSet)),
  rules(std::move(rules))
{
  //set the center start tile to a weighted random tile from tileSet
  float random_num = random(0, std::accumulate(this->weights.begin(), this->weights.end(), 0.0F));
  for(unsigned int i = 0 ; i < this->weights.size(); i++){

    if(random_num < this->weights[i]){
      this->world[0][0] = new tile(this->tileSet[i]);
      break;
    }
    random_num -= this->weights[i];
  }
  this->update_prob(0, 0, 0);



  this->gen_more(-width/2, width/2, -height/2, height/2);
};



void WCF::update_prob(int x, int y, int depth) {
  if (this->world.getVal(x, y) != nullptr) {
    //the tile is already determined
    //this->wold_probability
    //assume that the surrounding guesses are accurate and up to date
    if(this->tileSet.size() > 64){
      std::cout << "to many tiles" << std::endl << boost::stacktrace::stacktrace() << std::endl;
      exit(EXIT_FAILURE);
    }
    unsigned long up = 0;
    for(unsigned int i = 0; i < this->tileSet.size(); i++){
      up |= 1UL >> i;
    }


  }
  if(depth < MAX_PROPIGATION){
    this->update_prob(x+1, y+1, depth+1);
    this->update_prob(x+1, y-1, depth+1);
    this->update_prob(x-1, y+1, depth+1);
    this->update_prob(x-1, y-1, depth+1);
  }
}



void WCF::gen_more(int minx, int maxx, int miny, int maxy){

};
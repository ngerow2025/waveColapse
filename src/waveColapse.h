//
// Created by ngero on 3/22/21.
//

#ifndef MYPROJECT_WAVECOLAPSE_H
#define MYPROJECT_WAVECOLAPSE_H

#include <functional>
#include <vector>
#include "vector2d.h"
#include <list>
#include <numeric>
#include <emscripten.h>


#ifdef _MSC_VER
#pragma warning(disable: 4826 4619)
#endif
#include <boost/dynamic_bitset.hpp>
#ifdef _MSC_VER
#pragma warning(default: 4619 4619)
#endif

constexpr int MAX_PROPIGATION = 5;



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
  boost::dynamic_bitset<uint8_t> top;
  boost::dynamic_bitset<uint8_t> bottom;
  boost::dynamic_bitset<uint8_t> left;
  boost::dynamic_bitset<uint8_t> right;
};

std::function<output(int x, int y)> gen_new(int dimentions, int width, int height, float* weights, int weights_len, rule* rules, int rules_len);


using tile = int;









using domain = boost::dynamic_bitset<uint8_t>;
using tiles_probs = Matrix2dv4<domain>;
using tiles = Matrix2dv2<int>;





  float random_(float min, float max);









template<long unsigned int size>
class WCF{
private:
  tiles world_;
  std::array<float, size> weights_;
  std::array<tile, size> tileSet_;
  std::array<rule, size> rules_;
  tiles_probs world_probility;
  void update_prob(int x, int y, int depth)
  {
    if (this->world_.getVal(x, y) == -1) {

      std::cout << "updating: " << x << ", " << y << std::endl;
      bool new_ = false;
      if(!this->world_probility.at_loc(x, y)){
        this->world_probility.set(x, y, *new boost::dynamic_bitset<uint8_t>());
        new_ = true;
      }



      boost::dynamic_bitset<uint8_t> possibiltys(size);

      for (unsigned int i = 0; i < size; i++) {
        possibiltys[i] = false;
      }


      //offset: (0, 1)
      if (this->world_.getVal(x, y + 1) != -1) {
        auto rule = this->rules_[static_cast<long unsigned int>(this->world_.getVal(x, y + 1))];
        possibiltys |= rule.bottom;
      } else {
        if(this->world_probility.at_loc(x, y + 1)){
          for (unsigned int i = 0; i < size; i++) {
            if (this->world_probility.getVal(x, y + 1)[i]) {
              possibiltys |= this->rules_[static_cast<long unsigned int>(i)].bottom;
            }
          }
        }
      }

      //offset: (0, -1)
      if (this->world_.getVal(x, y - 1) != -1) {
        auto rule = this->rules_[static_cast<long unsigned int>(this->world_.getVal(x, y - 1))];
        possibiltys |= rule.top;
      } else {
        if(this->world_probility.at_loc(x, y - 1)){
          for (unsigned int i = 0; i < size; i++) {
            if (this->world_probility.getVal(x, y - 1)[i]) {
              possibiltys |= this->rules_[static_cast<long unsigned int>(i)].top;
            }
          }
        }
      }

      //offset: (1, 0)
      if (this->world_.getVal(x + 1, y) != -1) {
        auto rule = this->rules_[static_cast<long unsigned int>(this->world_.getVal(x + 1, y))];
        possibiltys |= rule.left;
      } else {
        if(this->world_probility.at_loc(x + 1, y)){
          for (unsigned int i = 0; i < size; i++) {
            if (this->world_probility.getVal(x + 1, y)[i]) {
              possibiltys |= this->rules_[static_cast<long unsigned int>(i)].left;
            }
          }
        }
      }

      //offset: (-1, 0)
      if (this->world_.getVal(x - 1, y) != -1) {
        auto rule = this->rules_[static_cast<long unsigned int>(this->world_.getVal(x - 1, y))];
        possibiltys |= rule.right;
      } else {
        if(this->world_probility.at_loc(x - 1, y)){
          for (unsigned int i = 0; i < size; i++) {
            if (this->world_probility.getVal(x - 1, y)[i]) {
              possibiltys |= this->rules_[static_cast<long unsigned int>(i)].right;
            }
          }
        }
      }
      if (this->world_probility.getVal(x, y) != possibiltys || new_) {
        this->world_probility.getVal(x, y) = possibiltys;

        std::cout << "updated to new probibility: ";
        for(unsigned int i = 0; i < this->world_probility.getVal(x, y).size(); i++){
          std::cout << this->world_probility.getVal(x, y).test(i);
        }
        std::cout << std::endl;
        if (depth < MAX_PROPIGATION) {
          this->update_prob(x + 1, y, depth + 1);
          this->update_prob(x - 1, y, depth + 1);
          this->update_prob(x, y + 1, depth + 1);
          this->update_prob(x, y - 1, depth + 1);
        }
      } else {
        std::cout << "same" << std::endl;
      }
    } else if (depth < MAX_PROPIGATION) {
      this->update_prob(x + 1, y, depth + 1);
      this->update_prob(x - 1, y, depth + 1);
      this->update_prob(x, y + 1, depth + 1);
      this->update_prob(x, y - 1, depth + 1);
    }
  }
public:
  WCF(int width, int height, std::array<float, size>  weights, std::array<tile, size>  tileSet, std::array<rule, size>  rules) : world_(*new Matrix2dv2<int>(-1)),
                                                                                                                            weights_(std::move(weights)),
                                                                                                                            tileSet_(std::move(tileSet)),
                                                                                                                            rules_(std::move(rules)),
                                                                                                                            world_probility(*new Matrix2dv4<boost::dynamic_bitset<uint8_t>>())
  {
    //set the center start tile to a weighted random tile from tileSet
    float random_num = random_(0, std::accumulate(this->weights_.begin(), this->weights_.end(), 0.0F));
    for (unsigned int i = 0; i < size; i++) {

      if (random_num < this->weights_[i]) {
        this->world_[0][0] = static_cast<int>(i);
        auto tmp = *new boost::dynamic_bitset<uint8_t>(size);
        tmp[i] = true;
        this->world_probility.set(0, 0, tmp);
        break;
      }
      random_num -= this->weights_[i];
    }
    this->update_prob(0, 0, 0);

    std::cout << "expanding to: " << width << ", " << height << std::endl;
    this->gen_more(-width / 2, width / 2, -height / 2, height / 2);
  }
  void print_world() const {
    for(auto const& [key, val] : this->world_probility.getData()){
      for(auto const& [key2, val2] : val){
        std::cout << key << ", " << key2 << ":" << std::endl;
        for(unsigned int i = 0; i < val2.size(); i++){
          std::cout << val2[i];
        }
        std::cout << std::endl;
      }
    }
  }
  int gen_one(int x, int y){
    this->update_prob(x, y, 0);
    auto last = this->world_probility.getVal(x, y);
    this->update_prob(x, y, 0);
    while(last != this->world_probility.getVal(x, y)){
      last = this->world_probility.getVal(x, y);
      this->update_prob(x, y, 0);
    }
    if(last.count() == 1){
      long unsigned int index = last.find_first();
      this->world_[x][y] = static_cast<int>(index);
      auto tmp = *new boost::dynamic_bitset<uint8_t>(size);
      tmp[index] = true;
      this->world_probility.set(x, y, tmp);
    }else{
      float sum = 0.0F;
      for(long unsigned int i = 0; i < last.size(); i++){
        if(last.test(i)){
          sum += this->weights_[i];
        }
      }
      float rand_num = random_(0.0F, sum);
      for(long unsigned int i = 0;; i++){
        if(last.test(i)){
          rand_num -= this->weights_[i];
        }
        if(rand_num < 0.0F){
          this->world_[x][y] = static_cast<int>(i);
          auto tmp = *new boost::dynamic_bitset<uint8_t>(size);
          tmp[i] = true;
          this->world_probility.set(x, y, tmp);
          break;
        }
      }
    }
    return(this->world_[x][y]);
  }
  void gen_more(int xmin, int xmax, int ymin, int ymax){
    for(int x = xmin; x < xmax + 1; x++){
      for(int y = ymin; y < ymax + 1; y++){
        this->gen_one(x, y);
      }
    }
  };
};



#endif//MYPROJECT_WAVECOLAPSE_H

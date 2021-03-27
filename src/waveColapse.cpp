//
// Created by ngero on 3/22/21.
//

//find out how to enable clang tidy/format for clion


#include <utility>
#include <vector>
#include "waveColapse.h"
#include <numeric>
#include <iostream>
#include <map>


#ifdef _MSC_VER
#pragma warning(disable: 4619)
#pragma warning(disable: 4826)
#endif
#include <boost/random.hpp>
#ifdef _MSC_VER
#pragma warning(default: 4619)
#pragma warning(default: 4826)
#endif





constexpr int MAX_PROPIGATION = 5;





float random(float min, float max)
{
  boost::random::uniform_real_distribution<> dist(static_cast<double>(min), static_cast<double>(max));
  boost::random::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(nullptr)));
  return (static_cast<float>(dist(gen)));
}


WCF::WCF(int width, int height, std::vector<float> weights, std::vector<tile> tileSet, std::map<int, rule> rules) : world_probility(*new Matrix2dv2<boost::dynamic_bitset<>>(boost::dynamic_bitset<>(tileSet.size(), 1))),
                                                                                                                    world_(*new Matrix2dv2<std::pair<tile *, int>>(std::make_pair(nullptr, -1))),
                                                                                                                    weights_(std::move(weights)),
                                                                                                                    tileSet_(std::move(tileSet)),
                                                                                                                    rules_(std::move(rules))
{
  //set the center start tile to a weighted random tile from tileSet
  float random_num = random(0, std::accumulate(this->weights_.begin(), this->weights_.end(), 0.0F));
  for (unsigned int i = 0; i < this->weights_.size(); i++) {

    if (random_num < this->weights_[i]) {
      this->world_[0][0] = std::make_pair(new tile(this->tileSet_[i]), i);
      break;
    }
    random_num -= this->weights_[i];
  }
  this->update_prob(0, 0, 0);

  std::cout << "expanding to: " << width << ", " << height << std::endl;
//  this->gen_more(-width / 2, width / 2, -height / 2, height / 2);
}


void WCF::update_prob(int x, int y, int depth)
{
  if (this->world_.getVal(x, y).first == nullptr) {
    std::cout << "updating: " << x << ", " << y << std::endl;
    //the tile is already determined
    //this->wold_probability
    //assume that the surrounding guesses are accurate and up to date

    boost::dynamic_bitset possibiltys(this->tileSet_.size());

    for (unsigned int i = 0; i < this->tileSet_.size(); i++) {
      possibiltys[i] = false;
    }


    //offset: (0, 1)             move boost into the project for github CI
    if (this->world_.getVal(x, y + 1).first != nullptr) {
      auto rule = this->rules_[this->world_.getVal(x, y + 1).second];
      possibiltys |= rule.bottom;
    } else {
      for (unsigned int i = 0; i < this->tileSet_.size(); i++) {
        if (this->world_probility.getVal(x, y + 1)[i]) {
          possibiltys |= this->rules_[static_cast<int>(i)].bottom;
        }
      }
    }

    //offset: (0, -1)
    if (this->world_.getVal(x, y - 1).first != nullptr) {
      auto rule = this->rules_[this->world_.getVal(x, y - 1).second];
      possibiltys |= rule.top;
    } else {
      for (unsigned int i = 0; i < this->tileSet_.size(); i++) {
        if (this->world_probility.getVal(x, y - 1)[i]) {
          possibiltys |= this->rules_[static_cast<int>(i)].top;
        }
      }
    }

    //offset: (1, 0)
    if (this->world_.getVal(x + 1, y).first != nullptr) {
      auto rule = this->rules_[this->world_.getVal(x + 1, y).second];
      possibiltys |= rule.left;
    } else {
      for (unsigned int i = 0; i < this->tileSet_.size(); i++) {
        if (this->world_probility.getVal(x + 1, y)[i]) {
          possibiltys |= this->rules_[static_cast<int>(i)].left;
        }
      }
    }

    //offset: (-1, 0)
    if (this->world_.getVal(x - 1, y).first != nullptr) {
      auto rule = this->rules_[this->world_.getVal(x - 1, y).second];
      possibiltys |= rule.right;
    } else {
      for (unsigned int i = 0; i < this->tileSet_.size(); i++) {
        if (this->world_probility.getVal(x - 1, y)[i]) {
          possibiltys |= this->rules_[static_cast<int>(i)].right;
        }
      }
    }
    if(this->world_probility.getVal(x, y) != possibiltys){
      std::cout << "updated to new probibility" << std::endl;
      this->world_probility.getVal(x, y) = possibiltys;
      if (depth < MAX_PROPIGATION) {
        this->update_prob(x + 1, y + 1, depth + 1);
        this->update_prob(x + 1, y - 1, depth + 1);
        this->update_prob(x - 1, y + 1, depth + 1);
        this->update_prob(x - 1, y - 1, depth + 1);
      }
    }else{
      std::cout << "calculated same probibility";
    }
  }else if(depth < MAX_PROPIGATION){
    this->update_prob(x + 1, y, depth + 1);
    this->update_prob(x - 1, y, depth + 1);
    this->update_prob(x, y + 1, depth + 1);
    this->update_prob(x, y - 1, depth + 1);
  }
}


//void WCF::gen_more(int minx, int maxx, int miny, int maxy){
//
//};
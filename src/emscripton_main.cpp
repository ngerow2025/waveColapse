//
// Created by ngero on 4/3/21.
//

#include "emscripton_main.h"
#include "vector2d.h"
#include "waveColapse.h"
#include <emscripten.h>

extern "C"{

  EMSCRIPTEN_KEEPALIVE
  WCF<size>* make_WCF(){
    const std::array<float, size> weights = {3.0F, 2.0F, 1.0F};
    const std::array<int, size> tiles_ = {0, 1, 2};
    const std::array<rule, size> rules = ([](){
      std::array<rule, size> rules_;

      for(long unsigned int i = 0; i < size; i++){
        rules_[i].bottom = *new boost::dynamic_bitset<uint8_t>(size);
        rules_[i].bottom.set();
        rules_[i].top = *new boost::dynamic_bitset<uint8_t>(size);
        rules_[i].top.set();
        rules_[i].left = *new boost::dynamic_bitset<uint8_t>(size);
        rules_[i].left.set();
        rules_[i].right = *new boost::dynamic_bitset<uint8_t>(size);
        rules_[i].right.set();
      }
      return(rules_);
    })();



    return(new WCF<size>(10, 10, weights, tiles_, rules));
  }
  EMSCRIPTEN_KEEPALIVE
  int getTile(WCF<size>* thing, int x, int y){
    return(thing->gen_one(x, y));
  }



}
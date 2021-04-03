#include <functional>
#include <iostream>

//#include <spdlog/spdlog.h>
//#include <docopt/docopt.h>
#include "waveColapse.h"


int main()
{


  std::array<float, 4> weights{ 1, 1, 1 };
  std::array<tile, 4> tileSet{1, 2, 3, 4};

  // 0 1
  // 3 2
  std::array<rule, 4> rules = ([]() {
    std::array<rule, 4> rules_;
    rules_[0].bottom = *new boost::dynamic_bitset<uint8_t>(4);
    rules_[0].left = *new boost::dynamic_bitset<uint8_t>(4);
    rules_[0].top = *new boost::dynamic_bitset<uint8_t>(4);
    rules_[0].right = *new boost::dynamic_bitset<uint8_t>(4);

    rules_[0].bottom[3] = true;
    rules_[0].left[1] = true;
    rules_[0].right[1] = true;
    rules_[0].top[3] = true;


//    rules_[0].bottom.set();
//    rules_[0].left.set();
//    rules_[0].right.set();
//    rules_[0].top.set();


    rules_[1].bottom = *new boost::dynamic_bitset<uint8_t>(4);
    rules_[1].left = *new boost::dynamic_bitset<uint8_t>(4);
    rules_[1].top = *new boost::dynamic_bitset<uint8_t>(4);
    rules_[1].right = *new boost::dynamic_bitset<uint8_t>(4);

    rules_[1].top[2] = true;
    rules_[1].left[0] = true;
    rules_[1].bottom[2] = true;
    rules_[1].right[0] = true;


//    rules_[1].bottom.set();
//    rules_[1].left.set();
//    rules_[1].right.set();
//    rules_[1].top.set();


    rules_[2].bottom = *new boost::dynamic_bitset<uint8_t>(4);
    rules_[2].left = *new boost::dynamic_bitset<uint8_t>(4);
    rules_[2].top = *new boost::dynamic_bitset<uint8_t>(4);
    rules_[2].right = *new boost::dynamic_bitset<uint8_t>(4);


    rules_[2].bottom[1] = true;
    rules_[2].left[3] = true;
    rules_[2].right[3] = true;
    rules_[2].top[1] = true;


//    rules_[2].bottom.set();
//    rules_[2].left.set();
//    rules_[2].right.set();
//    rules_[2].top.set();


    rules_[3].bottom = *new boost::dynamic_bitset<uint8_t>(4);
    rules_[3].left = *new boost::dynamic_bitset<uint8_t>(4);
    rules_[3].top = *new boost::dynamic_bitset<uint8_t>(4);
    rules_[3].right = *new boost::dynamic_bitset<uint8_t>(4);


    rules_[3].top[0] = true;
    rules_[3].left[2] = true;
    rules_[3].bottom[0] = true;
    rules_[3].right[2] = true;


//    rules_[3].bottom.set();
//    rules_[3].left.set();
//    rules_[3].right.set();
//    rules_[3].top.set();


    return (rules_);
  })();


  //  std::map<int, rule> rules;
  //  for (int i = 0; i < 3; i++) {
  //    rule tmpr;
  //    for (int j = 0; j < 4; j++) {
  //      boost::dynamic_bitset<uint8_t> tmpb(3);
  //      for (unsigned long k = 0; k < 3; k++) {
  //        tmpb[k] = true;
  //      }
  //      switch (j) {
  //      case 1:
  //        tmpr.left = tmpb;
  //        break;
  //      case 0:
  //        tmpr.right = tmpb;
  //        break;
  //      case 2:
  //        tmpr.bottom = tmpb;
  //        break;
  //      case 3:
  //        tmpr.top = tmpb;
  //        break;
  //      default:
  //        std::cerr << "waaaaaa?" << std::endl
  //                  << boost::stacktrace::stacktrace() << std::endl;
  //        exit(EXIT_FAILURE);
  //      }
  //    }
  //    rules[i] = tmpr;
  //  }
  constexpr int width = 5;
  constexpr int height = 5;
  WCF<4UL> wtf(width, height, weights, tileSet, rules);
  wtf.print_world();
  std::cout << "done" << std::endl;
  return (0);
}
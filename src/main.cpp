#include <functional>
#include <iostream>

#include <spdlog/spdlog.h>
#include <docopt/docopt.h>
#include "waveColapse.h"


#ifdef _MSC_VER
#pragma warning(disable: 4826 4619)
#endif
#include <boost/stacktrace.hpp>
#ifdef _MSC_VER
#pragma warning(default: 4619 4619)
#endif


int main()
{


  std::vector<float> weights{ 1, 1, 1 };
  std::vector<tile> tileSet{
    tile{ 3, 3, 'a' },
    tile{ 3, 3, 'b' },
    tile{ 3, 3, 'c' }
  };
  std::map<int, rule> rules;
  for (int i = 0; i < 3; i++) {
    rule tmpr;
    for (int j = 0; j < 4; j++) {
      boost::dynamic_bitset<> tmpb(3);
      for (unsigned long k = 0; k < 3; k++) {
        tmpb[k] = true;
      }
      switch (j) {
      case 1:
        tmpr.left = tmpb;
        break;
      case 0:
        tmpr.right = tmpb;
        break;
      case 2:
        tmpr.bottom = tmpb;
        break;
      case 3:
        tmpr.top = tmpb;
        break;
      default:
        std::cerr << "waaaaaa?" << std::endl
                  << boost::stacktrace::stacktrace() << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    rules[i] = tmpr;
  }
  const int width = 5;
  const int height = 5;
  WCF wtf(width, height, weights, tileSet, rules);
  print_map(wtf.world_probility);
  std::cout << "done" << std::endl;
  return (0);
}
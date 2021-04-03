//
// Created by ngero on 3/22/21.
//



#include "waveColapse.h"
#include <map>
#include <emscripten.h>

#ifdef _MSC_VER
#pragma warning(disable : 4619)
#pragma warning(disable : 4826)
#endif
#include <boost/random.hpp>
#ifdef _MSC_VER
#pragma warning(default : 4619)
#pragma warning(default : 4826)
#endif




  float random_(float min, float max)
  {
    boost::random::uniform_real_distribution<> dist(min, max);
    boost::random::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(nullptr)));
    return (static_cast<float>(dist(gen)));
  }

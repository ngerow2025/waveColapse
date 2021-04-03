//
// Created by ngero on 4/3/21.
//

#ifndef MYPROJECT_EMSCRIPTON_MAIN_H
#define MYPROJECT_EMSCRIPTON_MAIN_H

#include "waveColapse.h"
#include "vector2d.h"

constexpr int size = 3;

extern "C"{

  WCF<size>* make_WCF();
  int getTile(WCF<size>* wcf, int x, int y);

}


#endif//MYPROJECT_EMSCRIPTON_MAIN_H

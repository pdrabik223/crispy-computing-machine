//
// Created by piotr on 26/10/2021.
//

#ifndef THELOCKSCREENQUESTION__ENGINE_H_
#define THELOCKSCREENQUESTION__ENGINE_H_

#include "plane.h"

class Engine {

public:
  Engine(Plane plane);
  void Step();



private:
  Cell::State ComputeState(const pm::Coord& position);
  const double k_g_ = 10;
  const double k_attraction_ = 20;

protected:
  Plane plane_;


};

#endif // THELOCKSCREENQUESTION__ENGINE_H_

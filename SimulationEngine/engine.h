//
// Created by piotr on 26/10/2021.
//

#ifndef THELOCKSCREENQUESTION__ENGINE_H_
#define THELOCKSCREENQUESTION__ENGINE_H_

#include "plane.h"


class Engine {



public:
  Engine(const Plane& plane);
  void Step();

  const Plane &GetPlane() const;
  std::vector<unsigned> CountCells();
private:
  Cell::State ComputeStateAir(const pm::Coord& position);
  Cell::State ComputeStateFluid(const pm::Coord& position);
  const double k_g_ = 10;
  const double k_attraction_ = 20;
  bool IsFluid(const pm::Coord& position);
  bool IsAir(const pm::Coord& position);
  bool IsBarier(const pm::Coord& position);



protected:
  Plane plane_;

  unsigned frame_ = 0;

};

#endif // THELOCKSCREENQUESTION__ENGINE_H_

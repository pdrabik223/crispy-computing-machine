//
// Created by piotr on 26/10/2021.
//

#include "engine.h"

#include <utility>

Engine::Engine(const Plane &plane) : plane_(plane) {}

Cell::State Engine::ComputeStateAir(const pm::Coord &position) {

  if (IsFluid({position.x, position.y - 1}))
    return Cell::State::FLUID;

  if (IsFluid({position.x - 1, position.y - 1}) and
      IsFluid({position.x - 1, position.y}))
    return Cell::State::FLUID;
  if (IsFluid({position.x + 1, position.y - 1}) and
      IsFluid({position.x + 1, position.y}))
    return Cell::State::FLUID;

  return Cell::State::AIR;
}
Cell::State Engine::ComputeStateFluid(const pm::Coord &position) {

  if (IsAir({position.x, position.y + 1}))
    return Cell::State::AIR;



  return Cell::State::FLUID;
}
void Engine::Step() {

  Plane buffer(plane_.GetWidth(), plane_.GetHeight());

  for (int x = 0; x < plane_.GetWidth(); ++x)
    for (int y = 0; y < plane_.GetHeight(); ++y) {
      switch (plane_.GetCell({x, y}).state) {
      case Cell::State::AIR:
        buffer.GetCell({x, y}).state = ComputeStateAir({x, y});
        break;
      case Cell::State::FLUID:
        buffer.GetCell({x, y}).state = ComputeStateFluid({x, y});
        break;
      case Cell::State::BARRIER:
        buffer.GetCell({x, y}).state = Cell::State::BARRIER;
        break;
      }
    }

  plane_ = buffer;
}

const Plane &Engine::GetPlane() const { return plane_; }

bool Engine::IsFluid(const pm::Coord &position) {
  return plane_.GetCell(position).state ==
         Cell::State::FLUID;
}
bool Engine::IsAir(const pm::Coord &position) {
  return plane_.GetCell(position).state == Cell::State::AIR;
}
bool Engine::IsBarier(const pm::Coord &position) {
  return plane_.GetCell(position).state ==
         Cell::State::BARRIER;
}

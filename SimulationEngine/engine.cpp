//
// Created by piotr on 26/10/2021.
//

#include "engine.h"

#include <utility>

Engine::Engine(Plane plane) : plane_(std::move(plane)) {}

Cell::State Engine::ComputeStateAir(const pm::Coord &position) {

  if (plane_.GetCell({position.x, position.y - 1}).state == Cell::State::FLUID)
    return Cell::State::FLUID;

  if (plane_.GetCell({position.x - 1, position.y - 1}).state ==
          Cell::State::FLUID and
      plane_.GetCell({position.x - 1, position.y}).state == Cell::State::FLUID)
    return Cell::State::FLUID;

  if (plane_.GetCell({position.x + 1, position.y - 1}).state ==
          Cell::State::FLUID and
      plane_.GetCell({position.x + 1, position.y}).state == Cell::State::FLUID)
    return Cell::State::FLUID;

  return Cell::State::AIR;
}
void Engine::Step() {

  Plane buffer(plane_.GetWidth(), plane_.GetHeight());

  for (int x = 0; x < plane_.GetWidth(); ++x) {
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
  }

  plane_ = buffer;
}
Cell::State Engine::ComputeStateFluid(const pm::Coord &position) {
  if(plane_.GetCell({position.x, position.y - 1}).state == Cell::State::AIR)
    return Cell::State::AIR;


   return Cell::State::FLUID;

}
const Plane &Engine::GetPlane() const { return plane_; }

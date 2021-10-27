//
// Created by piotr on 26/10/2021.
//

#include "engine.h"

#include <utility>

Engine::Engine(const Plane &plane) : plane_(plane) {}

Cell::State Engine::ComputeStateAir(const pm::Coord &position) {

  // gravity strait down
  if (IsFluid({position.x, position.y - 1}))
    return Cell::State::FLUID;

  // gravity down and left
  if (IsFluid({position.x - 1, position.y - 1}) and
      IsFluid({position.x - 1, position.y}))
    return Cell::State::FLUID;

  // gravity down and right
  if (IsFluid({position.x + 1, position.y - 1}) and
      IsFluid({position.x + 1, position.y}))
    return Cell::State::FLUID;

  // gravity down and left
  if (IsFluid({position.x - 2, position.y - 1}) and
      IsFluid({position.x - 1, position.y}) and
      IsFluid({position.x - 2, position.y}))
    return Cell::State::FLUID;

  // gravity down and left
  if (IsFluid({position.x + 2, position.y - 1}) and
      IsFluid({position.x + 1, position.y}) and
      IsFluid({position.x + 2, position.y}))
    return Cell::State::FLUID;

  return Cell::State::AIR;
}
Cell::State Engine::ComputeStateFluid(const pm::Coord &position) {

  // gravity strait down
  if (IsAir({position.x, position.y + 1}))
    return Cell::State::AIR;

  // gravity down and left
  if (IsFluid({position.x, position.y + 1}) and
      IsAir({position.x - 1, position.y}) and
      IsAir({position.x - 1, position.y + 1}))
    return Cell::State::AIR;

  // gravity down and right
  if (IsFluid({position.x, position.y + 1}) and

      IsAir({position.x + 1, position.y}) and

      IsAir({position.x + 1, position.y + 1}))
    return Cell::State::AIR;

  // gravity down and left
  if (IsFluid({position.x, position.y + 1}) and
      IsFluid({position.x - 1, position.y}) and
      IsFluid({position.x - 1, position.y + 1}) and

      IsAir({position.x - 2, position.y + 1}) and

      IsAir({position.x - 1, position.y}) and
      IsAir({position.x - 2, position.y}))
    return Cell::State::AIR;

  // gravity down and left
  if (IsFluid({position.x, position.y + 1}) and
      IsFluid({position.x + 1, position.y}) and
      IsFluid({position.x + 1, position.y + 1}) and

      IsAir({position.x + 2, position.y + 1}) and

      IsAir({position.x + 1, position.y}) and
      IsAir({position.x + 2, position.y}))
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

  printf("frame: %d\tno water particles: %d\tno air particles: %d\n", frame_,
         CountCells()[(int)Cell::State::FLUID],
         CountCells()[(int)Cell::State::AIR]);
  frame_++;
}

const Plane &Engine::GetPlane() const { return plane_; }

bool Engine::IsFluid(const pm::Coord &position) {
  if (position.x < 0 or position.y < 0 or position.x >= plane_.GetWidth() or
      position.y >= plane_.GetHeight())
    return false;
  return plane_.GetCell(position).state == Cell::State::FLUID;
}
bool Engine::IsAir(const pm::Coord &position) {
  if (position.x < 0 or position.y < 0 or position.x >= plane_.GetWidth() or
      position.y >= plane_.GetHeight())
    return false;
  return plane_.GetCell(position).state == Cell::State::AIR;
}
bool Engine::IsBarier(const pm::Coord &position) {
  if (position.x < 0 or position.y < 0 or position.x >= plane_.GetWidth() or
      position.y >= plane_.GetHeight())
    return true;
  return plane_.GetCell(position).state == Cell::State::BARRIER;
}
std::vector<unsigned> Engine::CountCells() {

  std::vector<unsigned> numbers;
  numbers.reserve(3);
  for (int i = 0; i < 3; i++)
    numbers.push_back(0);

  for (int i = 0; i < plane_.Size(); ++i) {
    numbers[(int)plane_[i].state]++;
  }
  return numbers;
}

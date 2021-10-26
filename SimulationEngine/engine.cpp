//
// Created by piotr on 26/10/2021.
//

#include "engine.h"

#include <utility>
Engine::Engine(Plane plane) : plane_(std::move(plane)) {}

Cell::State Engine::ComputeState(const pm::Coord& position) {




  return Cell::State::AIR;
}

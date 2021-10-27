//
// Created by piotr on 26/10/2021.
//

#include "plane.h"
Plane::Plane(unsigned int width, unsigned int height)
    : width_(width), height_(height) {
  data_.reserve(Size());

  for (int i = 0; i < Size(); ++i) {
    data_.emplace_back(Cell::State::AIR);
  }
  AddBorder();
}
void Plane::AddBorder() {

  for (int x = 0; x < GetWidth(); x++)
    GetCell({x, 0}).state = Cell::State::BARRIER;

  // vertical bottom
  for (int x = 0; x < GetWidth(); x++)
    GetCell({x, (int)GetHeight() - 1}).state = Cell::State::BARRIER;

  // left edge
  for (int y = 0; y < GetHeight(); y++)
    GetCell({0, y}).state = Cell::State::BARRIER;

  // right ege
  for (int y = 0; y < GetHeight(); y++)
    GetCell({(int)GetWidth() - 1, y}).state = Cell::State::BARRIER;
}
unsigned int Plane::GetWidth() const { return width_; }
unsigned int Plane::GetHeight() const { return height_; }
void Plane::AddSquare(const pm::Coord& start, unsigned int width,
                      unsigned int height) {

  for (int x = 0; x < width; ++x) {
    for (int y = 0; y < height; ++y) {
      GetCell({x+start.x, y+ start.y}).state = Cell::State::FLUID;

    }
  }
}

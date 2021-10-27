//
// Created by piotr on 26/10/2021.
//

#ifndef THELOCKSCREENQUESTION_SIMULATIONENGINE_PLANE_H_
#define THELOCKSCREENQUESTION_SIMULATIONENGINE_PLANE_H_

#include "cell.h"
#include <coord/coord.h>
#include <vector>

/// used to store one
class Plane {

public:
  Plane() : width_(0), height_(0) {}
  Plane(unsigned int width, unsigned int height);
  Plane(const Plane &other) = default;
  Plane &operator=(const Plane &other) = default;
  unsigned Size() const { return width_ * height_; };

  Cell &operator[](unsigned position) { return data_[position]; }
  Cell &GetCell(const pm::Coord &position) { return data_[Int(position)]; }

  void AddBorder();
  unsigned int GetWidth() const;
  unsigned int GetHeight() const;

  void AddSquare(const pm::Coord& start, unsigned width, unsigned height);

private:
  unsigned Int(const pm::Coord &position) const {
    return position.ToInt(width_);
  }

protected:
  unsigned width_;
  unsigned height_;
  std::vector<Cell> data_;
};

#endif // THELOCKSCREENQUESTION_SIMULATIONENGINE_PLANE_H_

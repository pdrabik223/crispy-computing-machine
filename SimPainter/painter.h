//
// Created by piotr on 27/10/2021.
//

#ifndef THELOCKSCREENQUESTION_SIMPAINTER_PAINTER_H_
#define THELOCKSCREENQUESTION_SIMPAINTER_PAINTER_H_

#include "../SFML/include/SFML/Graphics/RenderWindow.hpp"
#include "../SFML/include/SFML/Window/Event.hpp"
#include "../CellularSimulationEngine/plane.h"
class Painter {
public:
  Painter() = delete;
  Painter(int screen_width, int screen_height, int plane_width, int plane_height);

  /// main window loop
  void MainLoop();
  void DrawPlane(sf::RenderWindow &window);
  const Plane &GetPlane() const;

private:
  bool PopulateMousePosition(const sf::RenderWindow &window, pm::Coord &mouse_position);
  std::vector<pm::Coord> GetHighlightedPositions(const sf::RenderWindow &window);
  void CheckBoundariesAndPush(const pm::Coord &position, std::vector<pm::Coord> &push_target);

  void DrawCircle(const pm::Coord &center, std::vector<pm::Coord> &target, int radius);
  void DrawFilledInCircle(const pm::Coord &center, std::vector<pm::Coord> &target);

protected:
  int screen_width_;
  int screen_height_;

  float cell_size_;

  Cell::State current_brush_state_ = Cell::State::FLUID;
  int brush_size_ = 1;

  sf::Event event_;
  Plane plane_;
};

#endif // THELOCKSCREENQUESTION_SIMPAINTER_PAINTER_H_

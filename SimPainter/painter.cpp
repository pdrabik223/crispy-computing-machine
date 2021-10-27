//
// Created by piotr on 27/10/2021.
//

#include "painter.h"
#include "../SFML/include/SFML/Window/ContextSettings.hpp"
#include "../sfml_window/view.h"
Painter::Painter(int screen_width, int screen_height, int plane_width,
                 int plane_height):screen_width_(screen_width),screen_height_(screen_height),plane_(plane_width,plane_height) {

  float cell_width = screen_width / plane_width;
  float cell_height = screen_height / plane_height;

  cell_size_ = cell_height < cell_width ? cell_height : cell_width;
  MainLoop();
}
void Painter::MainLoop() {
  sf::ContextSettings settings;
  //  settings.antialiasingLevel = 10;

  sf::RenderWindow window(sf::VideoMode(screen_width_, screen_height_), "CoA",
                          sf::Style::Default, settings);

  window.setPosition(sf::Vector2i(0, 0));
  pm::Coord mouse_position;

  DrawPlane(window);
  window.display();

  while (window.isOpen()) {
    // check all the window's events that were triggered since the last
    // iteration of the loop
    while (window.waitEvent(event_)) {
      if (event_.type == sf::Event::Closed)
        window.close();
      else if (event_.type == sf::Event::KeyPressed) {
        if (event_.key.code == sf::Keyboard::B) {
          current_brush_state_ = Cell::State::BARRIER;
          DrawPlane(window);
        } else if (event_.key.code == sf::Keyboard::F) {
          current_brush_state_ = Cell::State::FLUID;
          DrawPlane(window);
        } else if (event_.key.code == sf::Keyboard::Up) {
          brush_size_++;
          DrawPlane(window);
        } else if (event_.key.code == sf::Keyboard::Down) {
          if (brush_size_ > 0)
            brush_size_--;
          DrawPlane(window);
        } else if (event_.key.code == sf::Keyboard::Enter) {
          window.close();
        }
      } else if (event_.type == sf::Event::MouseMoved) {
        DrawPlane(window);
      }
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        if (PopulateMousePosition(window, mouse_position)) {
          std::vector<pm::Coord> painted_squares;
          DrawFilledInCircle(mouse_position, painted_squares);
          for (auto &ps : painted_squares)
            plane_.GetCell(ps) =  current_brush_state_;

          DrawPlane(window);
        }

      } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {

        if (PopulateMousePosition(window, mouse_position)) {

          std::vector<pm::Coord> painted_squares;
          DrawFilledInCircle(mouse_position, painted_squares);

          for (auto &ps : painted_squares)
            plane_.GetCell(ps) =  Cell::State::AIR;

          DrawPlane(window);
        }
      }
    }
    DrawPlane(window);
  }

  window.close();
}
void Painter::DrawPlane(sf::RenderWindow &window) {
  View screen_texture(plane_);

  switch (current_brush_state_) {

  case Cell::State::FLUID:
    screen_texture.HighlightCells(GetHighlightedPositions(window),
                                  sf::Color(0, 255, 255));
    break;
  case Cell::State::AIR:
    screen_texture.HighlightCells(GetHighlightedPositions(window),
                                  sf::Color(195, 195, 195));
    break;
  case Cell::State::BARRIER:
    screen_texture.HighlightCells(GetHighlightedPositions(window),
                                  sf::Color(27, 28, 29));
    break;
  }
  screen_texture.Draw(window);
  window.display();
}

bool Painter::PopulateMousePosition(const sf::RenderWindow &window,
                                    pm::Coord &mouse_position) {

  int m_px_pos_x = sf::Mouse::getPosition(window).y / cell_size_;
  int m_px_pos_y = sf::Mouse::getPosition(window).x / cell_size_;
  if (m_px_pos_x >= 0 and m_px_pos_x < plane_.GetWidth() and m_px_pos_y >= 0 and
      m_px_pos_y < plane_.GetHeight()) {
    mouse_position = {m_px_pos_x, m_px_pos_y};
    return true;
  }
  return false;
}
std::vector<pm::Coord>
Painter::GetHighlightedPositions(const sf::RenderWindow &window) {
  pm::Coord mouse;

  if (not PopulateMousePosition(window, mouse))
    return {};

  std::vector<pm::Coord> highlights;
  DrawFilledInCircle(mouse, highlights);

  return highlights;
}
void Painter::CheckBoundariesAndPush(const pm::Coord &position,
                                     std::vector<pm::Coord> &push_target) {
  if (position.x >= 0 and position.x < plane_.GetWidth() and position.y >= 0 and
      position.y < plane_.GetHeight()) {
    push_target.push_back(position);
  }
}
void Painter::DrawCircle(const pm::Coord &center,
                         std::vector<pm::Coord> &target, int radius) {
  int x = radius;
  int y = 0;
  int err = 0;

  while (x >= y) {
    CheckBoundariesAndPush({center.y + y, center.x + x}, target);
    CheckBoundariesAndPush({center.y + x, center.x + y}, target);
    CheckBoundariesAndPush({center.y + x, center.x - y}, target);
    CheckBoundariesAndPush({center.y + y, center.x - x}, target);
    CheckBoundariesAndPush({center.y - y, center.x - x}, target);
    CheckBoundariesAndPush({center.y - x, center.x - y}, target);
    CheckBoundariesAndPush({center.y - x, center.x + y}, target);
    CheckBoundariesAndPush({center.y - y, center.x + x}, target);
    if (err <= 0) {
      ++y;
      err += 2 * y + 1;
    } else {
      --x;
      err -= 2 * x + 1;
    }
  }
}
void Painter::DrawFilledInCircle(const pm::Coord &center,
                                 std::vector<pm::Coord> &target) {
  for (int r = 0; r < brush_size_; r++) {
    DrawCircle(center, target, r);
  }
}
const Plane &Painter::GetPlane() const { return plane_; }

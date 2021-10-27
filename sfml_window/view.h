//
// Created by piotr on 24/10/2021.
//

#ifndef THELOCKSCREENQUESTION_SFML_WINDOW_VIEW_H_
#define THELOCKSCREENQUESTION_SFML_WINDOW_VIEW_H_

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <coord/coord.h>
#define BACKGROUND_COLOR sf::Color(27,29,28) // good gray
//#define FOREGROUND_COLOR sf::Color(104,255,66) // good green
//#define FOREGROUND_COLOR sf::Color(0,255,255) //  good cyan
#define FOREGROUND_COLOR sf::Color(247,56,56) // good red
#include "../CellularSimulationEngine/plane.h"
class View {
public:
  View() = default;
  View(const View &other) = default;
  View &operator=(const View &other) = default;
  View(const Plane &data);
  void Draw(sf::RenderWindow &window);

  void HighlightCells(const std::vector<pm::Coord>& cells_to_highlight, sf::Color color);

protected:
  Plane data_;
  std::vector<std::pair<sf::Vector2f,sf::Color>>  highlights_;
  static sf::Font font_;
};
#endif // THELOCKSCREENQUESTION_SFML_WINDOW_VIEW_H_

//
// Created by piotr on 24/10/2021.
//
#include "view.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cmath>
#include <iostream>
#define PI 3.14159265

sf::Font View::font_;

void View::Draw(sf::RenderWindow &window) {
  window.clear(sf::Color(195,195,195));

  float window_height = window.getSize().y;
  float window_width = window.getSize().x;

  float cell_width = (float) window_width / (float) data_.GetWidth();
  float cell_height = (float) window_height / (float) data_.GetHeight();

  float cell_size = cell_height < cell_width ? cell_height : cell_width;

  std::vector<sf::RectangleShape> display;
  display.reserve(data_.GetWidth() * data_.GetHeight());

  sf::RectangleShape square;
  square.setSize(sf::Vector2f(cell_size, cell_size));
  square.setOutlineThickness(0);

  float x_pixel_shift = (window_width - (data_.GetWidth() * cell_size)) / 2;
  float y_pixel_shift = (window_height - (data_.GetHeight() * cell_size)) / 2;

  for (int x = 0; x < data_.GetWidth(); x++)
    for (int y = 0; y < data_.GetHeight(); y++) {
      switch(data_.GetCell({x,y}).state){
      case Cell::State::AIR:
        continue;
      case Cell::State::FLUID:
        square.setFillColor(sf::Color(0,255,255));
        break;
      case Cell::State::BARRIER:
        square.setFillColor(sf::Color(27,28,29));
        break;
      }
      square.setPosition(x_pixel_shift + x * cell_size, y_pixel_shift + y * cell_size);
      window.draw(square);
    }

  square.setOutlineThickness(1);
  square.setOutlineColor(sf::Color(247,56,56));
  for (auto h : highlights_) {
    square.setPosition(x_pixel_shift + h.first.x * cell_size, y_pixel_shift + h.first.y * cell_size);
    square.setFillColor(h.second);
    window.draw(square);
  }

}
View::View(const Plane &data) : data_(data) {}
void View::HighlightCells(const std::vector<pm::Coord>& cells_to_highlight,
                          sf::Color color) {

  for (auto c :cells_to_highlight) {
    highlights_.push_back({{(float)c.x,(float)c.y},color});
  }

}

#pragma once

#include <SFML/Graphics.hpp>

class Cell {
 public:
  enum State {
    ALIVE,
    DEAD,
  };

  void setShape(const sf::RectangleShape& shape) { m_shape = shape; }
  const sf::RectangleShape& getShape() const { return m_shape; }
  sf::RectangleShape& getShape() { return m_shape; }

  void live() {
    m_state = State::ALIVE;
    m_shape.setFillColor(sf::Color::White);
  }

  void die() {
    m_state = State::DEAD;
    m_shape.setFillColor(sf::Color::Black);
  }

  bool isAlive() const { return m_state == State::ALIVE; }
  bool isDead() const { return m_state == State::DEAD; }

  sf::Color getColor() const { return m_shape.getFillColor(); }

  unsigned int getNeighbours() const { return m_neighbours; }
  void addNeighbour(unsigned int neighbour) { m_neighbours += neighbour; }
  void resetNeighbours() { m_neighbours = 0; }

 private:
  State m_state = State::DEAD;
  unsigned int m_neighbours = 0;
  sf::RectangleShape m_shape;
};
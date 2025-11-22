#pragma once

#include <SFML/Graphics.hpp>

class Cell {
 public:
  enum State {
    ALIVE,
    DEAD,
  };

  void live() {
    m_state = State::ALIVE;
    m_color = sf::Color::White;
  }

  void die() {
    m_state = State::DEAD;
    m_color = sf::Color::Black;
  }

  bool isAlive() const { return m_state == State::ALIVE; }
  bool isDead() const { return m_state == State::DEAD; }

  sf::Color getColor() const { return m_color; }

  unsigned int getNeighbours() const { return m_neighbours; }
  void addNeighbour(unsigned int neighbour) { m_neighbours += neighbour; }
  void resetNeighbours() { m_neighbours = 0; }

 private:
  State m_state = State::DEAD;
  sf::Color m_color = sf::Color::Black;
  unsigned int m_neighbours = 0;
};
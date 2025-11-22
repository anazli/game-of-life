#pragma once

#include <cell.h>
#include <game.h>

#include <SFML/Graphics.hpp>
#include <vector>

class Grid {
 public:
  Grid(size_t rows, size_t cols) : m_rows(rows), m_cols(cols) {
    m_grid = std::vector<std::vector<Cell>>(rows, std::vector<Cell>(cols));
  }

  void init(int cell_size) {
    for (int row = 0; row < m_rows; ++row) {
      for (int col = 0; col < m_cols; ++col) {
        sf::RectangleShape cell_shape(sf::Vector2f(cell_size, cell_size));
        cell_shape.setPosition(static_cast<float>(col * cell_size),
                               static_cast<float>(row * cell_size));
        m_grid[row][col].setShape(cell_shape);
        if (drand48() > 0.01) {
          m_grid[row][col].die();
        } else {
          m_grid[row][col].live();
        }
      }
    }
  }

  void resurrect(int row, int col) {
    if (row < m_rows && col < m_cols && row >= 0 && col >= 0) {
      m_grid[row][col].live();
    }
  }

  void iterate() {
    auto next_grid = m_grid;
    for (int row = 0; row < static_cast<int>(m_rows); ++row) {
      for (int col = 0; col < static_cast<int>(m_cols); ++col) {
        auto& cell = next_grid[row][col];
        cell.resetNeighbours();
        cell.addNeighbour(getNeighbourState(row - 1, col - 1));
        cell.addNeighbour(getNeighbourState(row - 1, col));
        cell.addNeighbour(getNeighbourState(row - 1, col + 1));
        cell.addNeighbour(getNeighbourState(row, col - 1));
        cell.addNeighbour(getNeighbourState(row, col + 1));
        cell.addNeighbour(getNeighbourState(row + 1, col - 1));
        cell.addNeighbour(getNeighbourState(row + 1, col));
        cell.addNeighbour(getNeighbourState(row + 1, col + 1));
        m_game.applyRulesFor(cell);
      }
    }
    m_grid = std::move(next_grid);
  }

  void draw(sf::RenderWindow& window) const {
    for (int row = 0; row < static_cast<int>(m_rows); ++row) {
      for (int col = 0; col < static_cast<int>(m_cols); ++col) {
        window.draw(m_grid[row][col].getShape());
      }
    }
  }

 private:
  unsigned int getNeighbourState(int row, int col) const {
    if (row < static_cast<int>(m_rows) && col < static_cast<int>(m_cols) &&
        row >= 0 && col >= 0) {
      return m_grid[row][col].isAlive() ? 1 : 0;
    }
    return 0;
  }

  std::vector<std::vector<Cell>> m_grid;
  size_t m_rows;
  size_t m_cols;
  Game m_game;
};
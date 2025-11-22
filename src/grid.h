#pragma once

#include <cell.h>
#include <game.h>

#include <vector>

class Grid {
 public:
  Grid(size_t rows, size_t cols) : m_rows(rows), m_cols(cols) {
    m_grid = std::vector<Cell>(rows, std::vector<Cell>(cols));
  }

  void iterate() {
    for (int row = 0; row < m_rows; ++row) {
      for (int col = 0; col < m_cols; ++col) {
        auto& cell = m_grid[row][col];
        cell.addNeighbour(getNeighbourState(row - 1, col));
        cell.addNeighbour(getNeighbourState(row + 1, col));
        cell.addNeighbour(getNeighbourState(row, col - 1));
        cell.addNeighbour(getNeighbourState(row, col + 1));
        m_game.applyRulesFor(cell);
      }
    }
  }

 private:
  unsigned int getNeighbourState(size_t row, size_t col) const {
    if (row < m_rows && col < m_cols && row >= 0 && col >= 0) {
      return m_grid[row][col].isAlive() ? 1 : 0;
    }
    return 0;
  }

  std::vector<std::vector<Cell>> m_grid;
  size_t m_rows;
  size_t m_cols;
  Game m_game;
};
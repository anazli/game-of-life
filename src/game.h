#pragma once

#include <cell.h>

class Game {
 public:
  void applyRulesFor(Cell& cell) {
    auto neighbours = cell.getNeighbours();
    if (cellShouldDie(neighbours)) {
      cell.die();
    } else if (cellShouldLive(neighbours)) {
      cell.live();
    }
    cell.resetNeighbours();
  }

 private:
  bool cellShouldLive(unsigned int neighbours_sum) {
    return neighbours_sum == 2 || neighbours_sum == 3;
  }

  bool cellShouldDie(unsigned int neighbours_sum) {
    return neighbours_sum <= 1 || neighbours_sum >= 4;
  }
};
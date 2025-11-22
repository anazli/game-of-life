#include <cell.h>
#include <grid.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

constexpr int CELL_SIZE = 5;
constexpr int GRID_WIDTH = 200;
constexpr int GRID_HEIGHT = 200;
constexpr int WINDOW_WIDTH = GRID_WIDTH * CELL_SIZE;
constexpr int WINDOW_HEIGHT = GRID_HEIGHT * CELL_SIZE;

int main() {
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "Conway's Game of Life");
  window.setFramerateLimit(60);
  Grid grid(GRID_HEIGHT, GRID_WIDTH);
  grid.init(CELL_SIZE);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        auto mouseX = event.mouseButton.x;
        auto mouseY = event.mouseButton.y;

        int gridX = mouseX / CELL_SIZE;
        int gridY = mouseY / CELL_SIZE;
        grid.resurrect(gridY, gridX);
      }
    }
    grid.iterate();
    window.clear(sf::Color::Black);
    grid.draw(window);
    window.display();
  }

  return 0;
}

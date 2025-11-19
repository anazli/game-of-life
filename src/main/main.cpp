#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

constexpr int CELL_SIZE = 30;
constexpr int GRID_WIDTH = 20;
constexpr int GRID_HEIGHT = 15;
constexpr int WINDOW_WIDTH = GRID_WIDTH * CELL_SIZE;
constexpr int WINDOW_HEIGHT = GRID_HEIGHT * CELL_SIZE;

int main() {
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "Conway's Game of Life");
  window.setFramerateLimit(60);
  std::vector<std::vector<sf::RectangleShape>> grid;
  grid.resize(GRID_HEIGHT);

  // Init grid
  for (int row = 0; row < GRID_HEIGHT; ++row) {
    grid.resize(GRID_WIDTH);
    for (int col = 0; col < GRID_WIDTH; ++col) {
      sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
      cell.setPosition(static_cast<float>(col * CELL_SIZE),
                       static_cast<float>(row * CELL_SIZE));
      cell.setFillColor(sf::Color::Green);
      cell.setOutlineThickness(1.0f);
      cell.setOutlineColor(sf::Color::Black);
      grid[row][col] = cell;
    }
  }

  // Main Loop
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

        if (gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 &&
            gridY < GRID_WIDTH) {
          if (grid[gridY][gridX].getFillColor() == sf::Color::Green) {
            grid[gridY][gridX].setFillColor(sf::Color::White);
          } else {
            grid[gridY][gridX].setFillColor(sf::Color::Green);
          }
        }
      }
    }
    window.clear(sf::Color::Black);

    for (int row = 0; row < GRID_HEIGHT; ++row) {
      for (int col = 0; col < GRID_WIDTH; ++col) {
        window.draw(grid[row][col]);
      }
    }
    window.display();
  }

  return 0;
}

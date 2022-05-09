#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "params.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  static bool OccupiedCell(const int& x, const int& y, const std::vector<SDL_Point>& obstacles, const std::vector<SDL_Point>& player_occupied_cells);
  std::vector<SDL_Point> player_occupied_cells;
  static std::mutex _mtx_occupied_cells;

 private:
  Snake _player_snake;
  AutomatedSnake _cpu_snake;
  SDL_Point _food;
  const std::size_t _grid_width;
  const std::size_t _grid_height;
  std::vector<SDL_Point> _obstacles;

  std::random_device _dev;
  std::mt19937 _engine;
  std::uniform_int_distribution<int> _random_w;
  std::uniform_int_distribution<int> _random_h;

  int _player_score{0};
  int _cpu_score{0};
  int _level{0};
  int _points_per_level{1};
  void PlaceFood();
  void PlaceObstacles();
  void Update();
};

#endif
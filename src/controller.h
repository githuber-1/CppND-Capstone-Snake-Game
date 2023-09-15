#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <string>

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake) const;
  void HandleTyping(bool &running, std::string &inputString) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif
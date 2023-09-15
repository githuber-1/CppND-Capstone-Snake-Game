#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
}

void Controller::HandleTyping(bool &running, std::string &inputString) const
{
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type)
    {
      case SDL_QUIT:
        std::cout << "running is false\n";
        running = false;
        break;
      
      case SDL_TEXTINPUT:
        if (e.text.text[0] != ' ')
        {
          inputString += e.text.text;
          break;
        }
        
      case SDL_KEYDOWN:
        if (e.key.keysym.sym == SDLK_BACKSPACE && !inputString.empty())
        {
          inputString.pop_back();
          break;
        }

        if (e.key.keysym.sym == SDLK_RETURN)
        {
          running = false;
          break;
        }
    }
  }
}
#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include <SDL2/SDL_ttf.h>
#include "snake.h"
#include "high_score.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, HighScoreData high_score, int fps);
  void Update();
  void RenderText(const std::string &text1, const std::string &text2);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Color textColor = {255, 255, 255}; // White color
  TTF_Font* font;
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Hello, SDL2!", textColor);
  SDL_Texture* textTexture = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);

  const char *kPathToFont = "./fonts/lazy.ttf";

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
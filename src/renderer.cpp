#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

   //Initialize SDL_ttf
  if( TTF_Init() == -1 )
  {
    std::cerr << "SDL_ttf could not initialize.\n";
    std::cerr << "SDL_ttf Error: " << TTF_GetError() << "\n";
  }

    // Get font
    this->font = TTF_OpenFont(kPathToFont, 48);
    if (!font) 
    {
        // Handle font loading error
        std::cerr << "SDL_ttf could not get ttf font.\n";
    }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, HighScoreData high_score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + 
                    " || High Score: " + std::to_string(high_score.high_score) +
                    " by " + high_score.name + 
                    " || FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::RenderText(const std::string &text1, const std::string &text2)
{
  if (text1.length() > 0)
  {
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text1.c_str(), textColor);
      if (textSurface) {
          SDL_Texture* textTexture = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);
          if (textTexture) {
              int x = 20;
              int y = screen_height / 8;
              SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
              SDL_RenderCopy(sdl_renderer, textTexture, nullptr, &textRect);
              SDL_DestroyTexture(textTexture);
          }
          SDL_FreeSurface(textSurface);
      } else {
          // Handle text rendering error
          SDL_Log("Text rendering failed: %s", TTF_GetError());
          // Handle the error as needed
      }
  }

  if (text2.length() > 0)
  {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text2.c_str(), textColor);
      if (textSurface) {
          SDL_Texture* textTexture = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);
          if (textTexture) {
              int x = screen_width / 4;
              int y = screen_height / 4;
              SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
              SDL_RenderCopy(sdl_renderer, textTexture, nullptr, &textRect);
              SDL_DestroyTexture(textTexture);
          }
          SDL_FreeSurface(textSurface);
      } else {
          // Handle text rendering error
          SDL_Log("Text rendering failed: %s", TTF_GetError());
          // Handle the error as needed
      }
  }
  SDL_RenderPresent(sdl_renderer);

}
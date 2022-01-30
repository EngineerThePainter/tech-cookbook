#ifndef LESSON13_TEXTURE_HPP
#define LESSON13_TEXTURE_HPP

#include <memory>
#include <string>

#include <SDL2/SDL.h>
#include <SDL_image.h>

namespace sdl_lazyfoo
{
namespace lesson13
{
class Texture
{
public:
  Texture(SDL_Renderer* renderer);
  ~Texture();

  bool LoadFromFile(const std::string& path);
  void DeallocateTexture();
  void Render(const int x, const int y, SDL_Rect* clip = nullptr);
  // Uint8 comes from SDL
  void SetColor(Uint8 red, Uint8 green, Uint8 blue);

  int GetWidth() const;
  int GetHeight() const;

private:
  SDL_Renderer* renderer_;
  SDL_Texture* texture_;
  int width_;
  int height_;
};
} // namespace lesson13
} // namespace sdl_lazyfoo

#endif // LESSON13_TEXTURE_HPP
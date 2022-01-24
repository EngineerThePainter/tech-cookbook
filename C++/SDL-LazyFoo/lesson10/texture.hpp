#ifndef LESSON10_TEXTURE_HPP
#define LESSON10_HLESSON10_TEXTURE_HPPPP

#include <memory>
#include <string>

#include <SDL2/SDL.h>
#include <SDL_image.h>

namespace sdl_lazyfoo
{
namespace lesson10
{
class Texture
{
public:
  Texture(SDL_Renderer* renderer);
  ~Texture();

  bool LoadFromFile(const std::string& path);
  void DeallocateTexture();
  void Render(const int x, const int y);

  int GetWidth() const;
  int GetHeight() const;

private:
  SDL_Renderer* renderer_;
  SDL_Texture* texture_;
  int width_;
  int height_;
};
} // namespace lesson10
} // namespace sdl_lazyfoo

#endif // LESSON10_TEXTURE_HPP
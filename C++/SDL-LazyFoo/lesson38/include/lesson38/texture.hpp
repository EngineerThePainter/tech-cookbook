#ifndef lesson38_TEXTURE_HPP
#define lesson38_TEXTURE_HPP

#include <memory>
#include <string>

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace sdl_lazyfoo
{
namespace lesson38
{
class Texture
{
public:
  Texture(SDL_Renderer* renderer);
  ~Texture();

  bool LoadFromFile(const std::string& path);
  bool LoadTextFromfile(const std::string& path);
  bool LoadFromRenderedText(const std::string& texture_text, SDL_Color text_color);
  void DeallocateTexture();
  void Render(const int x, const int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr,
              SDL_RendererFlip flip = SDL_FLIP_NONE);
  // Uint8 comes from SDL
  void SetColor(Uint8 red, Uint8 green, Uint8 blue);
  void SetBlendMode(SDL_BlendMode mode);
  void SetAlpha(Uint8 alpha);

  void SetWidth(const int width) { width_ = width; };
  void SetHeight(const int height) { height_ = height; };

  int GetWidth() const;
  int GetHeight() const;

private:
  SDL_Renderer* renderer_;
  SDL_Texture* texture_;
  TTF_Font* font_;
  int width_;
  int height_;
};
} // namespace lesson38
} // namespace sdl_lazyfoo

#endif // lesson38_TEXTURE_HPP
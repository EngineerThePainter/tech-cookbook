#include "lesson17/button.hpp"

namespace sdl_lazyfoo
{
namespace lesson17
{
Button::Button()
{
  position_.x = 0;
  position_.y = 0;
  current_sprite_ = ButtonSprite::BUTTON_SPRITE_MOUSE_OUT;

  for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
    sprite_clips_[i].x = 0;
    sprite_clips_[i].y = i * 200;
    sprite_clips_[i].w = BUTTON_WIDTH;
    sprite_clips_[i].h = BUTTON_HEIGHT;
  }
}

void Button::SetTexture(Texture* texture) { current_texture_ = texture; }

void Button::SetPosition(int x, int y)
{
  position_.x = x;
  position_.y = y;
}

void Button::HandleEvent(SDL_Event* event)
{
  const auto& type = event->type;
  if (type == SDL_MOUSEMOTION || type == SDL_MOUSEBUTTONDOWN || type == SDL_MOUSEBUTTONUP) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    // Check if mouse is inside button
    bool inside = true;
    if (x < position_.x) {
      inside = false;
    } else if (x > position_.x + BUTTON_WIDTH) {
      inside = false;
    } else if (y < position_.y) {
      inside = false;
    } else if (y > position_.y + BUTTON_HEIGHT) {
      inside = false;
    }

    if (!inside) {
      current_sprite_ = ButtonSprite::BUTTON_SPRITE_MOUSE_OUT;
    } else {
      switch (type) {
      case SDL_MOUSEMOTION:
        current_sprite_ = ButtonSprite::BUTTON_SPRITE_MOUSE_OVER_MOTION;
        break;

      case SDL_MOUSEBUTTONDOWN:
        current_sprite_ = ButtonSprite::BUTTON_SPRITE_MOUSE_DOWN;
        break;

      case SDL_MOUSEBUTTONUP:
        current_sprite_ = ButtonSprite::BUTTON_SPRITE_MOUSE_UP;
        break;
      }
    }
  }
}

void Button::Render() { current_texture_->Render(position_.x, position_.y, &sprite_clips_[current_sprite_]); }

} // namespace lesson17
} // namespace sdl_lazyfoo

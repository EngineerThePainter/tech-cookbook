#ifndef AIFG_KINEMATIC_COMMON_HPP
#define AIFG_KINEMATIC_COMMON_HPP

struct ALLEGRO_COLOR;
struct ALLEGRO_FONT;

namespace aifg
{
const constexpr float kMaxSpeed = 300.0f;
const constexpr float kSatisfactionRadius = 100.0f;
const constexpr float kTimeToTarget = 0.25f;
const constexpr float kMaxRotation = 8.0f;

class KinematicBody;

void drawBody(const KinematicBody& body, const ALLEGRO_COLOR& color, const ALLEGRO_FONT* font);

} // namespace aifg

#endif
#ifndef AIFG_KINEMATIC_COMMON_HPP
#define AIFG_KINEMATIC_COMMON_HPP

struct ALLEGRO_COLOR;
struct ALLEGRO_FONT;

namespace aifg
{
const constexpr float kMaxSpeed = 250.0f;
const constexpr float kSatisfactionRadius = 50.0f;
const constexpr float kTimeToTargetSpeed = 0.1f;
const constexpr float kMaxRotation = 2.0f;
const constexpr float kMaxAcceleration = 100.0f;
const constexpr float kSatisfactionRotation = 0.1f;
const constexpr float kTime = 1.0f / 60.0f;
const constexpr float kSlowRadius = 60.0f;
const constexpr float kSlowRotation = 0.8f;
const constexpr float kMaxAngularAcceleration = 0.1f;

float mapToPiRange(float angleInRadians);

class KinematicBody;

void drawMovingBody(const KinematicBody& body, const ALLEGRO_COLOR& color, const ALLEGRO_FONT* font);

} // namespace aifg

#endif
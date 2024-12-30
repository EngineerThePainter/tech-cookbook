#ifndef KINEMATIC_DATA_HPP_
#define KINEMATIC_DATA_HPP_

namespace aifg
{
struct KinematicSteeringOutput {
  float velocity_x_ = 0.0f;
  float velocity_y_ = 0.0f;
  float rotation_ = 0.0f;
};

struct KinematicBody {
  float position_x_;
  float position_y_;
  float velocity_x_;
  float velocity_y_;
  float orientation_;
  float rotation_;

  KinematicBody(float position_x, float position_y, float velocity_x, float velocity_y, float orientation,
                float rotation)
      : position_x_(position_x), position_y_(position_y), velocity_x_(velocity_x), velocity_y_(velocity_y),
        orientation_(orientation), rotation_(rotation)
  {
  }
  KinematicBody(const KinematicBody&) = default;
  KinematicBody& operator=(const KinematicBody&) = default;
  KinematicBody(KinematicBody&&) = default;
  KinematicBody& operator=(KinematicBody&&) = default;
  void ResetToCenter();
  void Update(const KinematicSteeringOutput& steering, float time);
  float NewOrientation(const float& current_orientation, const int& velocity_x, const int& velocity_y);
};

} // namespace aifg

#endif // KINEMATIC_DATA_HPP_

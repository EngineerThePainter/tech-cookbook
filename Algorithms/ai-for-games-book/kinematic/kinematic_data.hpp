#ifndef KINEMATIC_DATA_HPP_
#define KINEMATIC_DATA_HPP_

namespace aifg
{
struct SteeringOutput {
  int linear_x_;
  int linear_y_;
  float angular_;
};

struct KinematicSteeringOutput {
  int velocity_x_;
  int velocity_y_;
  float rotation_;
};

struct KinematicBody {
  int position_x_;
  int position_y_;
  int velocity_x_;
  int velocity_y_;
  float orientation_;
  float rotation_;

  KinematicBody(int position_x, int position_y, int velocity_x, int velocity_y, float orientation, float rotation)
      : position_x_(position_x), position_y_(position_y), velocity_x_(velocity_x), velocity_y_(velocity_y),
        orientation_(orientation), rotation_(rotation)
  {
  }
  KinematicBody(const KinematicBody&) = default;
  KinematicBody& operator=(const KinematicBody&) = default;
  KinematicBody(KinematicBody&&) = default;
  KinematicBody& operator=(KinematicBody&&) = default;

  void Update(const KinematicSteeringOutput& steering, float time);
  float NewOrientation(const float& current_orientation, const int& velocity_x, const int& velocity_y);
};

} // namespace aifg

#endif // KINEMATIC_DATA_HPP_

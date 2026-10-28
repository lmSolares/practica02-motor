#include "engine/Component.hpp"
#include "math/Vector2.hpp"

enum class MovingTo { start, middle, end };

class BoomerangComponent : public Component {
public:
  Vector2 pos{-200.0f, 0.0f};
  float speed{900.0f};
  bool on_the_move = false;
  MovingTo moving_to;
  MovingTo start_in;
  Vector2 start;
  Vector2 middle;
  Vector2 end;

  void FollowRoute(float);
  void SetRoute(Vector2 start, Vector2 middle, Vector2 end);
  void FixedUpdate(float) override;
};

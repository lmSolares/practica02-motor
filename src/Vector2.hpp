#pragma once
#include <cmath>
#include <cstddef>

struct Vector2 {
  float x{0.0f};
  float y{0.0f};

  constexpr Vector2() = default;
  constexpr Vector2(float x, float y) : x(x), y(y) {}

  Vector2 operator+(const Vector2 &other) const {
    return {x + other.x, y + other.y};
  }

  Vector2 operator-(const Vector2 &other) const {
    return {x - other.x, y - other.y};
  }

  Vector2 operator*(float scalar) const { return {x * scalar, y * scalar}; }

  float length_squared() const { return x * x + y * y; }

  float length() const { return std::sqrt(length_squared()); }

  Vector2 normalized() const {
    float len = length();
    if (len > 0.0001f) {
      return {x / len, y / len};
    }
    return {0.0f, 0.0f};
  }

  Vector2 clamp(const Vector2 &min_val, const Vector2 &max_val) const {
    float clamped_x = x;
    float clamped_y = y;

    if (clamped_x < min_val.x) {
      clamped_x = min_val.x;
    } else if (clamped_x > max_val.x) {
      clamped_x = max_val.x;
    }

    if (clamped_y < min_val.y) {
      clamped_y = min_val.y;
    } else if (clamped_y > max_val.y) {
      clamped_y = max_val.y;
    }

    return Vector2{clamped_x, clamped_y};
  }
};

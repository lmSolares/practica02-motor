#pragma once

struct Vector2 {
  float x{0.0f};
  float y{0.0f};

  constexpr Vector2() = default;
  constexpr Vector2(float x, float y) : x(x), y(y) {}

  Vector2 operator+(const Vector2 &other) const;

  Vector2 operator-(const Vector2 &other) const;

  Vector2 operator*(float scalar) const;

  float length_squared() const;

  float length() const;

  Vector2 normalized() const;

  Vector2 clamp(const Vector2 &min_val, const Vector2 &max_val) const;

  static Vector2 Lerp(const Vector2 &a, const Vector2 &b, float t);
};

#include "math.h"


float vec2::magnitude()
{
  return std::sqrt(x * x + y * y);
}
vec2 vec2::unit()
{
  float len = magnitude();
  if(len < 0.0001)
  {
    return vec2{0.f, 0.f};
  }
  return vec2{x/len, y/len};
}
float vec2i::magnitude()
{
  return std::sqrt(x * x + y * y);
}



float rad(float d)
{
  return PI * d/180;
}
float deg(float r)
{
  return 180 * r/PI;
}

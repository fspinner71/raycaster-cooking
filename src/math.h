#ifndef MATH_H
#define MATH_H

#include <math.h>

#define PI 3.141592653589793238462643383279502884197169399375

struct vec2
{
  float x, y;
  float magnitude();
  vec2 unit();
};
struct vec3
{
  float x, y, z;
};
struct vec4
{
  float x, y, z, w;
};
struct vec2i
{
  int x, y;
  float magnitude();
};


float rad(float d);
float deg(float r);

#endif

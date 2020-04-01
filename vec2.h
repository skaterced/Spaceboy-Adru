#ifndef _VEC2_ 
#define _VEC2_ 
//from Mystic Balloon from Team ARG
//added a few things...

//#include "globals.h"

struct vec2
{
  int x;
  int y;

  vec2() : x(0), y(0) {}
  vec2(int vx, int vy) : x(vx), y(vy) {}

  vec2 &operator+=(const vec2 &rhs)
  {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  
  vec2 &operator-=(const vec2 &rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  vec2 &operator=(const vec2 &rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }
};

boolean operator!=(vec2 lhs, const vec2 &rhs)
{    
    return (!(lhs.x==rhs.x&&lhs.y==rhs.y));
}

vec2 operator+(vec2 lhs, const vec2 &rhs)
{
    //vec2 t = lhs;
    //t += rhs;
    return (lhs += rhs);
}

vec2 operator-(vec2 lhs, const vec2 &rhs)
{
    //vec2 t = lhs;
    //t -= rhs;
    return (lhs -= rhs);
}

vec2 operator/(vec2 lhs, const int &rhs)
{
    lhs.x /= rhs;
    lhs.y /= rhs;
    return lhs;
}
vec2 operator*(vec2 lhs, const int &rhs)
{
    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;
}
vec2 operator%(vec2 lhs, const int &rhs)
{
    lhs.x %= rhs;
    lhs.y %= rhs;
    return lhs;
}
vec2 operator<<(vec2 lhs, const int &rhs)
{
    lhs.x <<= rhs;
    lhs.y <<= rhs;
    return lhs;
}
vec2 operator>>(vec2 lhs, const int &rhs)
{
    lhs.x >>= rhs;
    lhs.y >>= rhs;
    return lhs;
}


int magn(vec2 a){
  if (abs(a.x)>120||abs(a.y)>120)
    return -1;
  //return sqrt((double)a.x*(double)a.x+(double)a.y*(double)a.y);
  return sqrt(a.x*a.x+a.y*a.y);
}

#endif

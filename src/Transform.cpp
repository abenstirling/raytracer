
#include "../include/Transform.h"
#include <iostream>

#include <cmath>
// Helper rotation function.  Please implement this.
//
float radians(float degrees){
    return degrees * (M_PI / 180.0);
}

mm::mat3 Transform::rotate(const float degrees, const mm::vec3& axis)
{
  mm::vec3 norm_axis = mm::normalize(mm::vec3(0.0));
  float x = norm_axis.x;
  float y = norm_axis.y;
  float z = norm_axis.z;
  float theta = radians(degrees);

  return cos(theta) * mm::mat3(1.0) +
        (1 - cos(theta)) * mm::mat3(x*x, y*x, z*x,
                                    x*y, y*y, z*y,
                                    x*z, y*z, z*z) +
        sin(theta) * mm::mat3(0, -z, y,
                              z, 0, -x,
                              -y, x, 0);

}

void Transform::left(float degrees, mm::vec3& eye, mm::vec3& up)
{
  eye = rotate(degrees, up) * eye;
  up = mm::normalize(rotate(degrees, up) * up);
}

void Transform::up(float degrees, mm::vec3& eye, mm::vec3& up)
{
  mm::vec3 left = mm::normalize(mm::cross(eye,up));
  eye = rotate(degrees, left) * eye;
  up = rotate(degrees, left) * up;
}

mm::mat4 Transform::lookAt(const mm::vec3 &eye, const mm::vec3 &center, const mm::vec3 &up)
{
  mm::vec3 a = eye-center;
  mm::vec3 b = up;

  mm::vec3 w = mm::normalize(a);
  mm::vec3 u = mm::normalize(mm::cross(b,a));
  mm::vec3 v = mm::normalize(mm::cross(w,u));

  // return mm::mat4(u.x,v.x,w.x,0,   u.y,v.y,w.y,0,   u.z,v.z,w.z,0,   -(u*eye), -(v*eye), -(w*eye), 1);
  return mm::mat4(u.x, u.y, u.z, -(u*eye),
                  v.x, v.y, v.z, -(v*eye),
                  w.x, w.y, w.z, -(w*eye),
                  0.0, 0.0, 0.0, 1.0);
}

mm::mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  float rads = tan(radians(fovy)/2);
  mm::mat4 P(0.0f);
  P(0,0) = 1.0 / (aspect * rads);
  P(1,1) = 1.0 / (rads);

  float f = zFar;
  float n = zNear;
  float A = -(f+n)/(f-n);
  float B =-(2.0*f*n)/(f-n);

  P(2,2) = A;
  P(2,3) = B;   //NOTE might need to switch 2,3 to 3,2 and same for line below. i switched the order because glm is col major and my lib is row major
  P(3,2) = -1.0;

  return P;
}

mm::mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
  // return mm::mat4(sx,0,0,0, 0,sy,0,0, 0,0,sz,0, 0,0,0,1);
  return mm::mat4(sx, 0.0, 0.0, 0.0,
                  0.0, sy, 0.0, 0.0,
                  0.0, 0.0, sz, 0.0,
                  0.0, 0.0, 0.0, 1.0);

}

mm::mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
  // return mm::mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, tx, ty, tz, 1);
  mm::mat4 ret(1.0);
  ret(0,3) = tx;
  ret(1,3) = ty;
  ret(2,3) = tz;
  return ret;
}

// To normalize the up direction and construct a coordinate frame.
// As discussed in the lecture.  May be relevant to create a properly
// orthogonal and normalized up.
// This function is provided as a helper, in case you want to use it.
// Using this function (in readfile.cpp or display.cpp) is optional.

mm::vec3 Transform::upvector(const mm::vec3 &up, const mm::vec3 & zvec)
{
  mm::vec3 x = mm::cross(up,zvec);
  mm::vec3 y = mm::cross(zvec,x);
  mm::vec3 ret = mm::normalize(y);
  return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}

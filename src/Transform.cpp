
#include "../include/Transform.h"
#include <iostream>

#include <cmath>
// Helper rotation function.  Please implement this.
mm::mat3 Transform::rotate(const float degrees, const mm::vec3& axis)
{
  mm::vec3 norm_axis = mm:normalize(axis);
  float x = norm_axis.x;
  float y = norm_axis.y;
  float z = norm_axis.z;
  float theta = radians(degrees);

  return cos(theta) * mm::mat3(1.0) +
    (1 - cos(theta)) * mm::mat3(x*x, x*y, x*z, y*x, y*y, y*z, z*x, z*y, z*z) +
    sin(theta) * mm::mat3(0, z, -y, -z, 0, x, y, -x, 0);
  // mat3 ret;
  // return ret;
}

void Transform::left(float degrees, vec3& eye, vec3& up)
{
  eye = rotate(degrees, up) * eye;
  up = glm::normalize(rotate(degrees, up) * up);
}

void Transform::up(float degrees, vec3& eye, vec3& up)
{
  glm::vec3 left = glm::normalize(glm::cross(eye,up));
  eye = rotate(degrees, left) * eye;
  up = rotate(degrees, left) * up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
  glm::vec3 a = eye-center;
  glm::vec3 b = up;

  glm::vec3 w = glm::normalize(a);
  glm::vec3 u = glm::normalize(glm::cross(b,a));
  glm::vec3 v = glm::normalize(glm::cross(w,u));

  return glm::mat4(u.x,v.x,w.x,0, u.y,v.y,w.y,0, u.z,v.z,w.z,0, -glm::dot(u,eye), -glm::dot(v,eye), -glm::dot(w,eye), 1);

}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  float rads = glm::tan(glm::radians(fovy)/2);
  glm::mat4 P(0.0f);
  P[0][0] = 1.0 / (aspect * rads);
  P[1][1] = 1.0 / (rads);

  float f = zFar;
  float n = zNear;
  float A = -(f+n)/(f-n);
  float B =-(2.0*f*n)/(f-n);

  P[2][2] = A;
  P[3][2] = B;
  P[2][3] = -1.0;

  return P;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
  return glm::mat4(sx,0,0,0, 0,sy,0,0, 0,0,sz,0, 0,0,0,1);

  // mat4 ret;
  // return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
  return glm::mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, tx, ty, tz, 1);

  // mat4 ret;
  // return ret;
}

// To normalize the up direction and construct a coordinate frame.
// As discussed in the lecture.  May be relevant to create a properly
// orthogonal and normalized up.
// This function is provided as a helper, in case you want to use it.
// Using this function (in readfile.cpp or display.cpp) is optional.

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec)
{
  vec3 x = glm::cross(up,zvec);
  vec3 y = glm::cross(zvec,x);
  vec3 ret = glm::normalize(y);
  return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}

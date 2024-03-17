
#include "../include/Transform.h"
#include <iostream>

#include <cmath>
// Helper rotation function.  Please implement this.
//
float radians(float degrees){
    return degrees * (M_PI / 180.0);
}

Eigen::Matrix3f Transform::rotate(const float degrees, const Eigen::Vector3f& axis)
{
  Eigen::Vector3f norm_axis = axis.normalized();
  float x = norm_axis[0];
  float y = norm_axis[1];
  float z = norm_axis[2];
  float theta = radians(degrees);

  Eigen::Matrix3f K;
  K << 0, -z, y,
        z, 0, -x,
        -y, x, 0;
  Eigen::Matrix3f KK;
  KK << x*x, x*y, x*z,
        x*y, y*y, y*z,
        x*z, y*z, z*z;
  return cos(theta) * Eigen::Matrix3f::Identity() +
        (1 - cos(theta)) * KK +
        sin(theta) * K;


}

void Transform::left(float degrees, Eigen::Vector3f& eye, Eigen::Vector3f& up)
{
  eye = rotate(degrees, up) * eye;
  up = (rotate(degrees, up) * up).normalized();
}

void Transform::up(float degrees, Eigen::Vector3f& eye, Eigen::Vector3f& up)
{
  Eigen::Vector3f left = (eye.cross(up)).normalized();
  eye = rotate(degrees, left) * eye;
  up = rotate(degrees, left) * up;
}

Eigen::Matrix4f Transform::lookAt(const Eigen::Vector3f &eye, const Eigen::Vector3f &center, const Eigen::Vector3f &up)
{
  Eigen::Vector3f a = eye-center;
  Eigen::Vector3f b = up;

  Eigen::Vector3f w = a.normalized();
  Eigen::Vector3f u = b.cross(a).normalized();// (Eigen::cross(b,a)).normalize();
  Eigen::Vector3f v = w.cross(u).normalized();// (Eigen::cross(w,u)).normalize();

  // return Eigen::Matrix4f(u[0],v[0],w[0],0,   u[1],v[1],w[1],0,   u[2],v[2],w[2],0,   -(u*eye), -(v*eye), -(w*eye), 1);

  Eigen::Matrix4f ret;
  ret << u[0], u[1], u[2], -(u.dot(eye)),
        v[0], v[1], v[2], -(v.dot(eye)),
        w[0], w[1], w[2], -(w.dot(eye)),
        0.0, 0.0, 0.0, 1.0;
  return ret;
}

Eigen::Matrix4f Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  float rads = tan(radians(fovy)/2);
  Eigen::Matrix4f P = Eigen::Matrix4f::Zero();
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

Eigen::Matrix4f Transform::scale(const float &sx, const float &sy, const float &sz){

    Eigen::Matrix4f ret =  Eigen::Matrix4f::Identity();
    ret(0,0) = sx;
    ret(1,1) = sy;
    ret(2,2) = sz;
    return ret;
}

Eigen::Matrix4f Transform::translate(const float &tx, const float &ty, const float &tz){
  // return Eigen::Matrix4f(1,0,0,0, 0,1,0,0, 0,0,1,0, tx, ty, tz, 1);

    Eigen::Matrix4f ret = Eigen::Matrix4f::Identity();
    ret(0,3) = tx;
    ret(1,3) = ty;
    ret(2,3) = tz;
    return ret;
}

// To Eigen::normalize the up direction and construct a coordinate frame.
// As discussed in the lecture.  May be relevant to create a properly
// orthogonal and Eigen::normalized up.
// This function is provided as a helper, in case you want to use it.
// Using this function (in readfile.cpp or display.cpp) is optional.

Eigen::Vector3f Transform::upvector(const Eigen::Vector3f &up, const Eigen::Vector3f & zvec){
    Eigen::Vector3f x = up.cross(zvec);
    Eigen::Vector3f y = zvec.cross(x);
    Eigen::Vector3f ret = y.normalized();
    return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}

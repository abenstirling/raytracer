
#pragma once

#include "My_math.h"
#include "Transform.h"
#include "Eigen/Dense"


class Transform
{
public:
	Transform();
	virtual ~Transform();
	static void left(float degrees, Eigen::Vector3f& eye, Eigen::Vector3f& up);
	static void up(float degrees, Eigen::Vector3f& eye, Eigen::Vector3f& up);
	static Eigen::Matrix4f lookAt(const Eigen::Vector3f& eye, const Eigen::Vector3f &center, const Eigen::Vector3f& up);
	static Eigen::Matrix4f perspective(float fovy, float aspect, float zNear, float zFar);
    static Eigen::Matrix3f rotate(const float degrees, const Eigen::Vector3f& axis);
    static Eigen::Matrix4f scale(const float &sx, const float &sy, const float &sz);
    static Eigen::Matrix4f translate(const float &tx, const float &ty, const float &tz);
    static Eigen::Vector3f upvector(const Eigen::Vector3f &up, const Eigen::Vector3f &zvec);
};

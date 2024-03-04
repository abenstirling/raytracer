
#pragma once

#include "My_math.h"
#include "Transform.h"


class Transform
{
public:
	Transform();
	virtual ~Transform();
	static void left(float degrees, mm::vec3& eye, mm::vec3& up);
	static void up(float degrees, mm::vec3& eye, mm::vec3& up);
	static mm::mat4 lookAt(const mm::vec3& eye, const mm::vec3 &center, const mm::vec3& up);
	static mm::mat4 perspective(float fovy, float aspect, float zNear, float zFar);
    static mm::mat3 rotate(const float degrees, const mm::vec3& axis);
    static mm::mat4 scale(const float &sx, const float &sy, const float &sz);
    static mm::mat4 translate(const float &tx, const float &ty, const float &tz);
    static mm::vec3 upvector(const mm::vec3 &up, const mm::vec3 &zvec);
};

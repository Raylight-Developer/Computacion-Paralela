#pragma once

#include "Shared.hpp"

struct alignas(16) Particle {
	vec4 pos;
	vec4 color;

	Particle(const vec4& pos = vec4(0.0), const vec4& color = vec4(1.0)) :
		pos(pos),
		color(color)
	{}
};

vec4 palette(const vec1& time);
vec4 getPattern(vec2 uv, const vec1& steps, const vec1& time);
vector<Particle> generatePattern(const vec2& grid_size, const vec1& particle_size, const vec1& steps, const vec1& time);

enum struct Rotation_Type {
	QUATERNION,
	AXIS,
	XYZ,
	XZY,
	YXZ,
	YZX,
	ZXY,
	ZYX
};

struct Transform {
	Rotation_Type rotation_type;
	dvec3 euler_rotation;
	dvec3 axis_rotation;
	dquat quat_rotation;
	dvec3 position;
	dvec3 scale;

	Transform(const dvec3& position = dvec3(0.0), const dvec3& rotation = dvec3(0.0), const dvec3& scale = dvec3(1.0), const Rotation_Type& type = Rotation_Type::XYZ);
	Transform(const dvec3& position, const dvec3& axis, const dvec3& rotation, const dvec3& scale, const Rotation_Type& type = Rotation_Type::AXIS);
	Transform(const dvec3& position, const dquat& rotation, const dvec3& scale, const Rotation_Type& type = Rotation_Type::QUATERNION);

	Transform operator+(const Transform& other) const;
	Transform operator-(const Transform& other) const;
	Transform operator*(const Transform& other) const;
	Transform operator/(const Transform& other) const;

	Transform operator*(const dvec1& other) const;

	void moveLocal(const dvec3& value);
	void rotate(const dvec3& value);

	dmat4 getMatrix() const;
};
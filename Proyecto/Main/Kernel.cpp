#include "Kernel.hpp"

vec3 mandelbulb(const vec3& p, const vec1& time) {
	vec3 z = p;

	for (int i = 0; i < MAX_ITERATIONS; ++i) {
		vec1 r = length(z);
		if (r > BAILOUT) break;

		vec1 theta = acos(z.z / r);
		vec1 phi = atan2(z.y, z.x);
		vec1 zr = pow(r, time);

		z = zr * vec3(
			sin(theta * time) * cos(phi * time),
			sin(theta * time) * sin(phi * time),
			cos(theta * time)
		) + p;
	}
	return z;
}

vector<Particle> generateMandelbulb(const vec2& gridSize, const vec1& step, const vec1& time) {
	vector<Particle> points;
	const ivec2 grid_size = f_to_i(gridSize / step);

	#pragma omp parallel for collapse(2)
	for (int x = -grid_size.x; x < grid_size.x; x++) {
		for (int y = -grid_size.y; y < grid_size.y; y++) {
			const vec3 p = i_to_f(ivec3(x, y, 0)) * step;
			const vec3 result = mandelbulb(p, time);
			if (length(result) < BAILOUT) {
				#pragma omp critical
				points.push_back(Particle(vec4(p, 1.0)));
			}
		}
	}
	return points;
}

vec2 mandelbrot(const vec2& c, const vec1& time) {
	vec1 zoomLevel = 1.0 + 0.5 * sin(time * 0.2);
	vec2 zoomCenter = vec2(sin(time * 0.1), cos(time * 0.1));

	vec2 z = c;
	for (int i = 0; i < MAX_ITERATIONS; ++i) {
		if (length(z) > 2.0) break;
		z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
	}

	vec2 adjustedC = (c - zoomCenter) / zoomLevel;
	float zoomFactor = 1.0 + 0.5 * sin(time * 0.5);
	vec2 zoomedC = adjustedC * zoomFactor;

	return zoomedC;
}

vector<Particle> generateMandelbrot(const vec2& gridSize, const vec1& step, const vec1& time) {
	vector<Particle> points;
	const ivec2 grid_size = f_to_i(gridSize / step);

	#pragma omp parallel for collapse(2)
	for (int x = -grid_size.x; x < grid_size.x; x++) {
		for (int y = -grid_size.y; y < grid_size.y; y++) {
			const vec2 c = i_to_f(vec2(x, y)) * step - vec2(2.0, 1.0);
			const vec2 result = mandelbrot(c, time);
			if (length(result) < BAILOUT) {
				#pragma omp critical
				points.push_back(Particle(vec4(c, 0.0f, 0.0f)));
			}
		}
	}
	return points;
}

vec4 palette(const vec1& time) {
	vec3 a = vec3(0.5, 0.5, 0.5);
	vec3 b = vec3(0.5, 0.5, 0.5);
	vec3 c = vec3(1.0, 1.0, 1.0);
	vec3 d = vec3(0.263, 0.416, 0.557);

	return vec4(a + b * cos(6.28318f * (c * time + d)), 1.0);
}

bool getPattern(vec2 uv, const vec1& time) {
	vec2 uv_0 = uv;
	vec1 val = 0.0f;
	for (float i = 0.0f; i < 2.0f; i++) {
		uv = glm::fract(uv * 1.5f) - 0.5f;

		float d = length(uv) * exp(-length(uv_0));

		d = sin(d * 8.0f + time) / 8.0f;
		d = abs(d);

		d = pow(0.01f / d, 1.2f);

		val += d;
	}
	if (val >= 0.9) {
		return true;
	}
	return false;
}

vector<Particle> generatePattern(const vec2& gridSize, const vec1& step, const vec1& time) {
	vector<Particle> points;
	const ivec2 grid_size = f_to_i(gridSize / step);

	#pragma omp parallel for collapse(2)
	for (int x = -grid_size.x; x < grid_size.x; x++) {
		for (int y = -grid_size.y; y < grid_size.y; y++) {
			const vec2 uv = i_to_f(vec2(x, y)) * step;
			if (getPattern(uv, time)) {
				const vec4 color = palette(length(uv) + time * 0.4);
				#pragma omp critical
				points.push_back(Particle(vec4(uv, 0.0f, 0.0f), color));
			}
		}
	}
	return points;
}

Transform::Transform(const dvec3& position, const dvec3& rotation, const dvec3& scale, const Rotation_Type& type) :
	rotation_type(type),
	position(position),
	euler_rotation(rotation),
	scale(scale)
{
	quat_rotation = dquat(1.0, 0.0, 0.0, 0.0);
	axis_rotation = dvec3(0.0);
}

Transform::Transform(const dvec3& position, const dvec3& axis, const dvec3& rotation, const dvec3& scale, const Rotation_Type& type) :
	rotation_type(type),
	position(position),
	euler_rotation(rotation),
	scale(scale),
	axis_rotation(axis)
{
	quat_rotation = dquat(1.0, 0.0, 0.0, 0.0);
}

Transform::Transform(const dvec3& position, const dquat& rotation, const dvec3& scale, const Rotation_Type& type) :
	rotation_type(type),
	position(position),
	quat_rotation(rotation),
	scale(scale)
{
	euler_rotation = dvec3(0.0);
	axis_rotation = dvec3(0.0);
}
// TODO account for different rotation modes
Transform Transform::operator+(const Transform& other) const {
	Transform result;
	result.position       = position       + other.position;
	result.euler_rotation = euler_rotation + other.euler_rotation;
	result.axis_rotation  = axis_rotation  + other.axis_rotation;
	//result.quat_rotation  = quat_rotation  + other.quat_rotation;
	result.scale          = scale          + other.scale;
	return result;
}
Transform Transform::operator-(const Transform& other) const {
	Transform result;
	result.position       = position       - other.position;
	result.euler_rotation = euler_rotation - other.euler_rotation;
	result.axis_rotation  = axis_rotation  - other.axis_rotation;
	//result.quat_rotation  = quat_rotation  - other.quat_rotation;
	result.scale          = scale          - other.scale;
	return result;
}
Transform Transform::operator*(const Transform& other) const {
	Transform result;
	result.position       = position       * other.position;
	result.euler_rotation = euler_rotation * other.euler_rotation;
	result.axis_rotation  = axis_rotation  * other.axis_rotation;
	//result.quat_rotation  = quat_rotation  * other.quat_rotation;
	result.scale          = scale          * other.scale;
	return result;
}
Transform Transform::operator/(const Transform& other) const {
	Transform result;
	result.position       = position       / other.position;
	result.euler_rotation = euler_rotation / other.euler_rotation;
	result.axis_rotation  = axis_rotation  / other.axis_rotation;
	//result.quat_rotation  = quat_rotation  / other.quat_rotation;
	result.scale          = scale          / other.scale;
	return result;
}

Transform Transform::operator*(const dvec1& other) const {
	Transform result;
	result.position       = position       * other;
	result.euler_rotation = euler_rotation * other;
	result.axis_rotation  = axis_rotation  * other;
	//result.quat_rotation  = quat_rotation  * other;
	result.scale          = scale          * other;
	return result;
}

void Transform::moveLocal(const dvec3& value) {
	const dmat4 matrix = glm::yawPitchRoll(euler_rotation.y * DEG_RAD, euler_rotation.x * DEG_RAD, euler_rotation.z * DEG_RAD);
	const dvec3 x_vector = matrix[0];
	const dvec3 y_vector = matrix[1];
	const dvec3 z_vector = matrix[2];
	position += value.x * x_vector;
	position += value.y * y_vector;
	position += value.z * z_vector;
}

void Transform::rotate(const dvec3& value) {
	euler_rotation += value;

	if (euler_rotation.x > 89.0)  euler_rotation.x = 89.0;
	if (euler_rotation.x < -89.0) euler_rotation.x = -89.0;
}

dmat4 Transform::getMatrix() const {
	const dmat4 translation_matrix = glm::translate(dmat4(1.0), position);
	const dmat4 scale_matrix = glm::scale(dmat4(1.0), scale);
	dmat4 rotation_matrix = dmat4(1.0);

	switch (rotation_type) {
		case Rotation_Type::QUATERNION: {
			rotation_matrix = glm::toMat4(quat_rotation);
			break;
		}
		case Rotation_Type::XYZ: {
			const dmat4 rotationX = glm::rotate(dmat4(1.0), euler_rotation.x * DEG_RAD, dvec3(1.0, 0.0, 0.0));
			const dmat4 rotationY = glm::rotate(dmat4(1.0), euler_rotation.y * DEG_RAD, dvec3(0.0, 1.0, 0.0));
			const dmat4 rotationZ = glm::rotate(dmat4(1.0), euler_rotation.z * DEG_RAD, dvec3(0.0, 0.0, 1.0));
			rotation_matrix =  rotationZ * rotationY * rotationX;
			break;
		}
	}
	return translation_matrix * rotation_matrix * scale_matrix;
}
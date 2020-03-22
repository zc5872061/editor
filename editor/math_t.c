#include "math_t.h"
#include <math.h>

vec3_t vec3_new(float x, float y, float z)
{
	vec3_t v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

vec3_t vec3_add(vec3_t v1, vec3_t v2)
{
	return vec3_new(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

vec3_t vec3_sub(vec3_t v1, vec3_t v2)
{
	return vec3_new(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

vec3_t vec3_mul(vec3_t v, float s)
{
	return vec3_new(v.x * s,v.y * s ,v.z *s);
}

float vec3_dot(vec3_t v1, vec3_t v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3_t vec3_div(vec3_t v, float s)
{
	return vec3_new(v.x / s, v.y / s, v.z / s);
}

vec3_t vec3_normalize(vec3_t v)
{
	return vec3_div(v, vec3_length(v));
}

vec3_t vec3_cross(vec3_t v1, vec3_t v2)
{
	float x = v1.y * v2.z - v1.z * v2.y;
	float y = v1.z * v2.x - v1.x * v2.z;
	float z = v1.x * v2.y - v1.y * v2.x;
	return vec3_new(x, y, z);
}

float vec3_length(vec3_t v)
{
	return sqrt(vec3_dot(v, v));
}

mat4_t mat4_identity(void)
{
	mat4_t m = { {
		{ 1,0,0,0},
		{ 0,1,0,0 },
		{ 0,0,1,0 },
		{ 0,0,0,1 },
	} };
	return m;
}

/*
* eye: the position of the eye point
* target: the position of the target point
* up: the direction of the up vector
*
* x_axis.x  x_axis.y  x_axis.z  -dot(x_axis,eye)
* y_axis.x  y_axis.y  y_axis.z  -dot(y_axis,eye)
* z_axis.x  z_axis.y  z_axis.z  -dot(z_axis,eye)
*        0         0         0                 1
*
* z_axis: normalize(eye-target), the backward vector
* x_axis: normalize(cross(up,z_axis)), the right vector
* y_axis: cross(z_axis,x_axis), the up vector
*
* see http://www.songho.ca/opengl/gl_camera.html
*/
mat4_t mat4_lookat(vec3_t eye, vec3_t target, vec3_t up)
{
	vec3_t z_axis = vec3_normalize(vec3_sub(eye, target));
	vec3_t x_axis = vec3_normalize(vec3_cross(up, z_axis));
	vec3_t y_axis = vec3_cross(z_axis, x_axis);
	
	mat4_t m = mat4_identity();

	m.m[0][0] = x_axis.x;
	m.m[1][0] = x_axis.y;
	m.m[2][0] = x_axis.z;

	m.m[0][1] = y_axis.x;
	m.m[1][1] = y_axis.y;
	m.m[2][1] = y_axis.z;

	m.m[0][2] = z_axis.x;
	m.m[1][2] = z_axis.y;
	m.m[2][2] = z_axis.z;

	m.m[3][0] = -vec3_dot(x_axis, eye);
	m.m[3][1] = -vec3_dot(y_axis, eye);
	m.m[3][2] = -vec3_dot(z_axis, eye);

	return m;
}

/*
* left, right: the coordinates for the left and right clipping planes
* bottom, top: the coordinates for the bottom and top clipping planes
* near, far: the distances to the near and far depth clipping planes
*
* 2/(r-l)        0         0  -(r+l)/(r-l)
*       0  2/(t-b)         0  -(t+b)/(t-b)
*       0        0  -2/(f-n)  -(f+n)/(f-n)
*       0        0         0             1
*
* see http://docs.gl/gl2/glOrtho
*/
mat4_t mat4_ortho(float left, float right, float bottom, float top,
	float near, float far) {
	float x_range = right - left;
	float y_range = top - bottom;
	float z_range = far - near;
	mat4_t m = mat4_identity();
	m.m[0][0] = 2 / x_range;
	m.m[1][1] = 2 / y_range;
	m.m[2][2] = -2 / z_range;
	m.m[0][3] = -(left + right) / x_range;
	m.m[1][3] = -(bottom + top) / y_range;
	m.m[2][3] = -(near + far) / z_range;
	return m;
}

/*
* right: the coordinates for the right clipping planes (left == -right)
* top: the coordinates for the top clipping planes (bottom == -top)
* near, far: the distances to the near and far depth clipping planes
*
* 1/r    0         0             0
*   0  1/t         0             0
*   0    0  -2/(f-n)  -(f+n)/(f-n)
*   0    0         0             1
*
* this is the same as
*     float left = -right;
*     float bottom = -top;
*     mat4_ortho(left, right, bottom, top, near, far);
*
* see http://www.songho.ca/opengl/gl_projectionmatrix.html
*/
mat4_t mat4_orthographic(float right, float top, float near, float far) {
	float z_range = far - near;
	mat4_t m = mat4_identity();
	m.m[0][0] = 1 / right;
	m.m[1][1] = 1 / top;
	m.m[2][2] = -2 / z_range;
	m.m[2][3] = -(near + far) / z_range;
	return m;
}

/*
* fovy: the field of view angle in the y direction, in radians
* aspect: the aspect ratio, defined as width divided by height
* near, far: the distances to the near and far depth clipping planes
*
* 1/(aspect*tan(fovy/2))              0             0           0
*                      0  1/tan(fovy/2)             0           0
*                      0              0  -(f+n)/(f-n)  -2fn/(f-n)
*                      0              0            -1           0
*
* this is the same as
*     float half_h = near * (float)tan(fovy / 2);
*     float half_w = half_h * aspect;
*     mat4_frustum(-half_w, half_w, -half_h, half_h, near, far);
*
* see http://www.songho.ca/opengl/gl_projectionmatrix.html
*/
mat4_t mat4_perspective(float fovy, float aspect, float near, float far) {
	float radians = fovy * M_PI / 180;
	float z_range = far - near;
	mat4_t m = mat4_identity();

	float f = 1 / (float)tan(fovy / 2);
	m.m[0][0] = f / aspect;
	m.m[1][1] = f;
	m.m[2][2] = -(near + far) / z_range;
    m.m[2][3] = -1;
	m.m[3][2] = -2 * near * far / z_range;
	m.m[3][3] = 0;
	return m;
}
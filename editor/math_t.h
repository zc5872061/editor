#pragma once

#define M_PI                   3.14159265358979323846f

typedef struct { float x, y; } vec2_t;
typedef struct { float x, y, z; } vec3_t;
typedef struct { float x, y, z, w; } vec4_t;
typedef struct { float m[3][3]; }mat3_t;
typedef struct { float m[4][4]; } mat4_t;

//vec2 function
vec2_t vec2_new(float x, float y);
vec2_t vec2_add(vec2_t x, vec2_t y);
vec2_t vec2_sub(vec2_t x, vec2_t y);
vec2_t vec2_mul(vec2_t x, float s);
vec2_t vec2_div(vec2_t x, float s);


//vec3 function
vec3_t vec3_new(float x, float y, float z);
vec3_t vec3_add(vec3_t v1, vec3_t v2);
vec3_t vec3_sub(vec3_t v1, vec3_t v2);
vec3_t vec3_mul(vec3_t v, float s);
float vec3_dot(vec3_t v1, vec3_t v2);
vec3_t vec3_div(vec3_t v, float s);
vec3_t vec3_normalize(vec3_t v);
vec3_t vec3_cross(vec3_t v1, vec3_t v2);
float vec3_length(vec3_t v);

//mat3 function

//mat4 function
mat4_t mat4_identity(void);
mat4_t mat4_lookat(vec3_t eye, vec3_t target, vec3_t up);
mat4_t mat4_ortho(float left, float right, float bottom, float top,
	float near, float far);

mat4_t mat4_orthographic(float right, float top, float near, float far);
mat4_t mat4_perspective(float fovy, float aspect, float near, float far);
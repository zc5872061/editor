#pragma once

#include "math_t.h"

typedef struct camera{
	vec3_t position;
	vec3_t target;
	float aspect;
} camera_t;

camera_t* camera_create(vec3_t position,vec3_t target, float aspect);
void camera_release(camera_t* c);
void camera_set_transform();

vec3_t camera_get_position(camera_t* c);
vec3_t camera_get_forward(camera_t* c);
mat4_t camera_get_view_matrix(camera_t* c);
mat4_t camera_get_proj_matrix(camera_t* c);
#include "camera_t.h"

camera_t* camera_create(vec3_t position, vec3_t target, float aspect)
{
	camera_t* camera;
	camera = (camera_t*)malloc(sizeof(camera_t));
	camera->position = position;
	camera->target = target;
	camera->aspect = aspect;
	return camera;
}

void camera_release(camera_t* c)
{
	free(c);
}

//todo
void camera_set_transform()
{

}

//todo
vec3_t camera_get_position(camera_t* c)
{

}

//todo
vec3_t camera_get_forward(camera_t* c)
{

}

mat4_t camera_get_view_matrix(camera_t* c)
{
	mat4_t mat;
	mat.m[1][1] = 0;
	return mat;
}

mat4_t camera_get_proj_matrix(camera_t* c)
{
	mat4_t mat;
	mat.m[1][1] = 0;
	return mat;
}
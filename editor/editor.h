#include <GL\glew.h>
#include "math_t.h"

typedef struct editor
{
	struct
	{
		vec3_t offset;
		vec3_t rotation;

		mat4_t view_mat;
		mat4_t proj_mat;
	} camera;
}editor_t ;

int create_program(const char* vertexShader, const char* fragShader, const char* include);
void delete_programe(int prog);

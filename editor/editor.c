#include "editor.h"
#include <stdio.h>

static int compile_shader(int shader, const char* code ,const char* include)
{
	int status,len;
	char* log;
	const char* sources = code ;
	glShaderSource(shader, 1, (const char*)&sources, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		log = malloc(len + 1);
		printf("Compile shader error:");
		glGetShaderInfoLog(shader, len, &len, log);
		printf("%s", log);
		free(log);
	}
	return 0;
}

int create_program(const char* vertex_shader_code, const char* frag_shader_code, const char* include)
{	
	int status;
	int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

	if (compile_shader(vertex_shader, vertex_shader_code, include))
		return 0;
	if (compile_shader(frag_shader, frag_shader_code, include))
		return 0;

	int prog = glCreateProgram();
	glAttachShader(prog, vertex_shader);
	glAttachShader(prog, frag_shader);
	glLinkProgram(prog);
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		printf("Link Error");
		int len;
		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
		char* log;
		log = malloc(len + 1);
		glGetProgramInfoLog(prog, len, &len, log);
		printf("%s", log);
		return 0;
	}
	return prog;
}

void delete_programe(int prog)
{

}
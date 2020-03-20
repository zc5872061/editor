
#include <stdlib.h>
#include <GL/glew.h>    
#include <Windows.h>
#include <GLFW/glfw3.h>   
#include "editor.h"
#include "math_t.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions    
const GLuint WIDTH = 800, HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
	
	// Init GLFW    
	glfwInit();
	// Set all the required options for GLFW    
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions    
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "test", NULL, NULL);
	if (window == NULL)
	{
		
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	// Initialize GLEW to setup the OpenGL Function pointers    
	if (glewInit() != GLEW_OK)
	{
		//std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Define the viewport dimensions    
	glViewport(0, 0, WIDTH, HEIGHT);

	editor_t editor;
	editor.camera.proj_mat


	int shaderProgram = create_program(vertexShaderSource, fragmentShaderSource, NULL);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // add a new set of vertices to form a second triangle (a total of 6 vertices); the vertex attribute configuration remains the same (still one 3-float position vector per vertex)
     vec3_t vertices[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
        // second triangle
         0.0f, -0.5f, 0.0f,  // left
         0.9f, -0.5f, 0.0f,  // right
         0.45f, 0.5f, 0.0f   // top 
    }; 

    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	// Game loop    
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions    
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glDrawArrays(GL_LINES, 0, 6); // set the count to 6 since we're drawing 6 vertices now (2 triangles); not 3!
		
		glfwSwapBuffers(window);
		Sleep(20);
	}
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	//glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.    
	glfwTerminate();
	return 0;
}

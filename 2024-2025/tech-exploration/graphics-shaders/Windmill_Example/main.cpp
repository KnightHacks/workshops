#include <iostream>
#include <fstream>
#include <sstream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <math.h>
using namespace std;

string read_shader_file(const string filename) {
	ifstream input(filename);
	stringstream ss;
	ss << input.rdbuf();
	return ss.str();
}

GLfloat gwidth = 800, gheight = 600;
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
	gwidth = width;
	gheight = height;
}

int main() {
	//Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create Window and Context
	GLFWwindow *window = glfwCreateWindow(gwidth, gheight, "Shaders", NULL, NULL);
	if (!window) return -1;
	glfwMakeContextCurrent(window);

	//Load GLAD
	gladLoadGL();
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    GLfloat verticies[] = {
        -1.0f,  1.0f, 0.0f,  // top-left
         1.0f,  1.0f, 0.0f,  // top-right
         1.0f, -1.0f, 0.0f,  // bottom-right
        -1.0f, -1.0f, 0.0f   // bottom-left
    };
	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	string vertexShaderSource = read_shader_file("shaders/shader.vert");
	string fragmentShaderSource = read_shader_file("shaders/shaderWind.frag");
	const GLchar *VertexShaderCode = vertexShaderSource.c_str();
	const GLchar *FragmentShaderCode = fragmentShaderSource.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VertexShaderCode, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FragmentShaderCode, NULL);
	glCompileShader(fragmentShader);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	//Link program to GPU
	glLinkProgram(program);
	GLuint iResolution = glGetUniformLocation(program, "iResolution");
	GLfloat iTime = glGetUniformLocation(program, "iTime");
	
	//Delete unused shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	while(!glfwWindowShouldClose(window)) {
		//Use the shader program
		glUseProgram(program);
		//Tell it how to read in the data with the VAO
		glBindVertexArray(VAO);
		
		float timeValue = glfwGetTime();

		glUniform2f(iResolution, gwidth, gheight);
		glUniform1f(iTime, timeValue);
		glClear(GL_COLOR_BUFFER_BIT);
		//Cover the screen so the shader can have access to all pixels
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		//Get rid of the VAO vertex bind
		glBindVertexArray(0);

		//Swap buffers and poll
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
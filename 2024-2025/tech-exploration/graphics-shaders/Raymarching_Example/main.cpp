#include <iostream>
#include <fstream>
#include <sstream>
#include "glad.h"
#include <GLFW/glfw3.h>

#include <vector>
#include <cmath>
using namespace std;

string read_shader(const string filename) {
	ifstream input(filename);
	stringstream s;
	s << input.rdbuf();
	return s.str();
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	float width = 800, height = 800;
	GLFWwindow *window = glfwCreateWindow(width, height, "Shaders", NULL, NULL);
	if (window == NULL) return -1;
	glfwMakeContextCurrent(window);

	gladLoadGL();

	GLfloat verts[] = {
		-1.0f, 1.0f, 0.0f, //top-left
		1.0f, 1.0f, 0.0f, //top-right
		1.0f, -1.0f, 0.0f, //bottom-right
		-1.0f, -1.0f, 0.0f //bottom-left
	};

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	string vertexShaderSource = read_shader("shaders/shader.vert");
	string fragmentShaderSource = read_shader("shaders/shader.frag");
	const GLchar* vertexShaderCode = vertexShaderSource.c_str();
	const GLchar* fragmentShaderCode = fragmentShaderSource.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	GLuint iTime = glGetUniformLocation(program, "iTime");
	GLuint iMouse = glGetUniformLocation(program, "iMouse");
	GLuint iResolution = glGetUniformLocation(program, "iResolution");


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	while (!glfwWindowShouldClose(window)) {

		glUseProgram(program);
		glBindVertexArray(VAO);

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		glUniform1f(iTime, glfwGetTime());
		glUniform2f(iMouse, xpos, ypos);
		glUniform2f(iResolution, width, height);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
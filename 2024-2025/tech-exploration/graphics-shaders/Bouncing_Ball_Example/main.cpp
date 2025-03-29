#include <iostream>
#include <fstream>
#include <sstream>
#include "glad.h"
#include <GLFW/glfw3.h>
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

	string VertexShaderSource = read_shader_file("shaders/shader.vert");
	string FragmentShaderSource = read_shader_file("shaders/shader.frag");
	const GLchar *VertexShaderCode = VertexShaderSource.c_str();
	const GLchar *FragmentShaderCode = FragmentShaderSource.c_str();

	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &VertexShaderCode, NULL);
	glCompileShader(VertexShader);

	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &FragmentShaderCode, NULL);
	glCompileShader(FragmentShader);

	GLuint program = glCreateProgram();
	glAttachShader(program, VertexShader);
	glAttachShader(program, FragmentShader);

	glLinkProgram(program);
	GLuint iCenter = glGetUniformLocation(program, "iCenter");
	GLuint iRadius = glGetUniformLocation(program, "iRadius");
	GLuint iResolution = glGetUniformLocation(program, "iResolution");

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	GLfloat x = gwidth/2, y = gheight/2, radius = 50;
	GLfloat x_vel = 2, y_vel = 2;
	while (!glfwWindowShouldClose(window)) {
		glUseProgram(program);
		glBindVertexArray(VAO);

		glUniform2f(iCenter, x, y);
		glUniform2f(iResolution, gwidth, gheight);
		glUniform1f(iRadius, radius);


		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glBindVertexArray(0);

		GLfloat next_x = x+x_vel, next_y = y+y_vel;
		if (next_x < radius || next_x > gwidth-radius) {
			if (next_x < radius) x = radius;
			else x = gwidth-radius;

			x_vel *= -1;
		} else {
			x = next_x;
		}

		if (next_y < radius || next_y > gheight-radius) {
			if (next_y < radius) y = radius;
			else y = gheight-radius;

			y_vel *= -1;
		} else {
			y = next_y;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
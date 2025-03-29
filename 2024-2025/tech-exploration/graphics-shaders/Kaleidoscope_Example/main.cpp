#include <iostream>
#include <fstream>
#include <sstream>

#include "glad.h"
#include <GLFW/glfw3.h>
using std::ifstream;
using std::stringstream;

std::string readShaderFile(const char* filename) {
	ifstream s(filename);
	stringstream ss;
	ss << s.rdbuf();
	return ss.str();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 800, "Shaders", NULL, NULL);
	if (window == NULL) return -1;

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;
    glViewport(0, 0, 800, 800);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    GLfloat verticies[] = {
        -1.0f,  1.0f, 0.0f,  // top-left
         1.0f,  1.0f, 0.0f,  // top-right
         1.0f, -1.0f, 0.0f,  // bottom-right
        -1.0f, -1.0f, 0.0f   // bottom-left
    };
	GLuint VAO, VBO;
	//Create VAO and VBO buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Bind buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Send data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	//Define data in VAO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Unbind VBO & VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Pull shader code
	std::string vertexShaderCode = readShaderFile("shaders/shader.vert");
	std::string fragmentShaderCode = readShaderFile("shaders/shader.frag");
	const GLchar* vertexShaderSource = vertexShaderCode.c_str();
	const GLchar* fragmentShaderSource = fragmentShaderCode.c_str();

	//Initilize vertex and fragment shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragShader);

	//Create GPU program
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragShader);

	//Link program to GPU
	glLinkProgram(program);
	
	//Delete unused shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	while(!glfwWindowShouldClose(window)) {
		//Use the shader program
		glUseProgram(program);
		//Tell it how to read in the data with the VAO
		glBindVertexArray(VAO);


		float timeValue = glfwGetTime();

		// Get the location of the time uniform
		GLuint timeLocation = glGetUniformLocation(program, "iTime");

		// Pass the time to the shader
		glUniform1f(timeLocation, timeValue);

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
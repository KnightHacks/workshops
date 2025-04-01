#include <iostream>
#include <fstream>
#include <sstream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <math.h>

int main() {
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow *window = glfwCreateWindow(800, 800, "Shaders", NULL, NULL);
    if (window == NULL) return -1;
    
    gladLoadGL();
    
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
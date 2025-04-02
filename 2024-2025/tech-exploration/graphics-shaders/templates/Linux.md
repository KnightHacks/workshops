## Linux Setup

You'll want to first install the GLFW library, the easiest way to do that is with a simple install command.
```
sudo apt install libglfw3-dev libgl1-mesa-dev
```

Download the Linux Template zip and extract

To use GLFW and GLAD in your program you're going to want to include them with GLAD being the first include.
```
#include "glad.h"
#include <GLFW/glfw3.h>
```

When compiling your code you're going to need the correct flags. Lucky for you we made a makefile which you can download and just write ``make`` to compile your program. 

## Compile
Here is the example code
```
#include "glad.h"
#include <GLFW/glfw3.h>

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow *window = glfwCreateWindow(800, 800, "Shaders", NULL, NULL);
    if (window == NULL) return -1;
    glfwMakeContextCurrent(window);
    
    gladLoadGL();
    
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
```
Make sure you have g++ and call the file main.cpp, then run the Makefile.

You can compile manually like this 
``g++ ${FILENAME}.cpp glad.c -o ${EXENAME} -lglfw -lGL -lX11 -lpthread -lXrandr -ldl -lm``

Some of the flags may not be needed.
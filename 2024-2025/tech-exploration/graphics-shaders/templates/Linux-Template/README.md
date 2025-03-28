## Linux Setup

You'll want to first install the GLFW library, the easiest way to do that is with a simple install command.
```
sudo apt install libglfw3-dev libgl1-mesa-dev
```

After doing this you'll want to install GLAD

To install glad you can go to this [link](https://glad.dav1d.de/) and download the required files. Alternatively you can just download ``glad.c`` and ``glad.h`` from this file.

To use GLFW and GLAD in your program you're going to want to include them with GLAD first.
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
``g++ ${FILENAME}.cpp glad.c -o ${EXENAME} -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm``

Some of the flags may not be needed.
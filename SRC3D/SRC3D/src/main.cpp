#include <GL/glew.h> //Siempre Arriva
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;


int main(void)
{
    GLFWwindow* window;

    //Inicializa la libreria
    if (!glfwInit())
        return -1;

 

    //Crea la ventana
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    //Todo el cdigo deve ir despues de esta linea de codigo 
    glfwMakeContextCurrent(window);


    if (glewInit() != GLEW_OK)
    {
        cout << "ERROR DE INICIACION " << "\n";
    }

    cout << glGetString(GL_VERSION) << "\n";

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        //RENDERIZADO

        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
#include <GL/glew.h> //Siempre Arriva
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;


static int createShader(const string& vertexShader, const string& fragmentShader)
{
    unsigned int program = glCreateProgram();
}


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

    float positions[6] = {
        -0.5f, -0.5f, 
         0.0f,  0.5f, 
         0.5f,  0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glDisableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        //RENDERIZADO
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
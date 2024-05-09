#include <GL/glew.h> //Siempre Arriva
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct  ShaderProgramSource
{
    string VertexSource;
    string FragmentSource;
};


static ShaderProgramSource ParseShader(const string& filepath)
{
    ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };


    string line;

    stringstream ss[2];

    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != string::npos) 
        {
            if (line.find("vertex") != string::npos) //setea modo para verticec 
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != string::npos) //setea modo para fragmentado
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << "\n";
        } 
    }

    return { ss[0].str(),ss[2].str() };
}


static unsigned int CompileShader(unsigned int type, const string& source )
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char)); //=======
        glGetShaderInfoLog(id, length, &length, message);
        cout << "Filed to compile" << (type == GL_VERTEX_SHADER? "vertex" : "fragment") << "Shader!" << "\n";
        cout << message << "\n";
        glDeleteShader(id);
        return 0;
    }
    return id;
}


static int createShader(const string& vertexShader, const string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteProgram(vs);
    glDeleteProgram(fs);


    return program;
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

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);


    ShaderProgramSource source = ParseShader("res/Shaders/Basic.shader");

    cout << "VERTEX" << "\n";
    cout << source.VertexSource << "\n";
    cout << "FRAGMENT" << "\n";
    cout << source.FragmentSource << "\n";

    //unsigned int Shader = createShader(vertexShader, fragmentShader);
    //glUseProgram(Shader);


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

    //glDeleteProgram(Shader);
    glfwTerminate();
    return 0;
}
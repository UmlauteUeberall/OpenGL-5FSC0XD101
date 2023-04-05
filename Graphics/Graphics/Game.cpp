#include "Game.h"

int CGame::Initialize()
{
    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    if (!m_window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -2;
    }

    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -3;
    }

    glClearColor(0, 0.5f, 1, 1);

    // Vertexshader führt Umrechnungen in anderen Koordinatensyteme durch
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &m_vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[1024];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 1024, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -4;
    }

    return 0;
}

int CGame::Run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    return 0;
}

void CGame::Finalize()
{
    glfwTerminate();
}

void FrameBufferSizeCallback(GLFWwindow* _window, int _width, int _height)
{
    glViewport(0, 0, _width, _height);
}

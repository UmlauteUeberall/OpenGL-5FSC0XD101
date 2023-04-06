#include "Game.h"
#include "Vertex.h"

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

    m_defaultShader = new CShader("defaultShader.vs", "defaultShader.fs");


    Vertex vertices[]
    {
        {Vector3(-0.5f, 0.5, 0.0), Vector3(0.882f, 0.0313f, 0.91f)},
        {Vector3(0.5f, 0.5, 0.0), Vector3(1,0,0)},
        {Vector3(0.5f, -0.5, 0.0), Vector3(1,1,0)},
        {Vector3(-0.5f, -0.5, 0.0), Vector3(0.2f,0.49f,0.82f)},
    };

    unsigned int indices[]
    {
        0, 1, 3,
        1, 2, 3
    };
    

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, sizeof(Vector3)/sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, sizeof(Vector3) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    return 0;
}

int CGame::Run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        m_defaultShader->Use();
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glBindVertexArray(0);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    return 0;
}

void CGame::Finalize()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);

    m_defaultShader->CleanUp();
    glfwTerminate();
}

void FrameBufferSizeCallback(GLFWwindow* _window, int _width, int _height)
{
    glViewport(0, 0, _width, _height);
}

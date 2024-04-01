#include "baseopengl.h"

void BaseOpenGL::InitVertex()
{
    ClearVertexArray();
    vertices.push_back({-1,-1});
    vertices.push_back({1,1});
    vertices.push_back({1,-1});
    vertices.push_back({-1,1});
    vertices.push_back({0,-1});
    vertices.push_back({0,1});
    vertices.push_back({-1,0});
    vertices.push_back({1,0});


}

void BaseOpenGL::InitComponents()
{

    // Компиляция и связывание шейдеров
    // Создание вершинного шейдера
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Создание фрагментного шейдера
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Создание шейдерной программы
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Удаление шейдеров
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Создание буфера вершин и массива атрибутов вершин

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, 2*vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void BaseOpenGL::ClearVertexArray()
{
    vertices.clear();
}

bool BaseOpenGL::AddVertexArray(float t_x, float t_y)
{
    auto t_size = vertices.size();
    vertices.push_back({t_x,t_y});
    if (t_size == vertices.size()) return false;
    return true;
}

bool BaseOpenGL::isEmptyVertexArray()
{
    if (!vertices.empty()) return false;
    return true;
}

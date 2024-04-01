#pragma once
#include <glad/glad.h>
#include <iostream>
#include <vector>

class BaseOpenGL
{
    const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 position;
    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)";

    const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    uniform float vRed;
    uniform float vGreen;
    uniform float vBlue;
    void main()
    {
        FragColor = vec4(vRed, vGreen, vBlue, 1.0);
    }
)";

public:
    BaseOpenGL() = default;
    ~BaseOpenGL()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);
    }
    void InitVertex();

    //Инициализация шейдеров и создание шейдерной программмы,
    //Инициализация буферов VAO и VBO
    void InitComponents();

    //Получить адрес шейдерной программы
    GLuint  GetShadersProgram()
    {
        return shaderProgram;
    }
    //Получить адрес VAO
    GLuint  GetVAO()
    {
        return VAO;
    }

    //Получить количество вершин: если 6 вершин, можно построить 3 отрезка
    size_t GetNumberVertex()
    {
        return std::size(vertices);
    }

    //Очистить массив вершин
    void ClearVertexArray();

    //Добавить вершину в контейнер
    bool AddVertexArray(float, float);


    bool isEmptyVertexArray();


private:
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint VBO, VAO;
    GLuint shaderProgram;
    std::vector <std::pair<float, float>>  vertices;

};


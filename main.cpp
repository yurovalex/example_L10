#include <glad/glad.h>
#include <glm/glm.hpp>
#include "guidialog.h"
#include "baseopengl.h"
#include "buildonplate.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
void reshapeWindows (GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


int main()
{
    //Инициализация GLFW
    if (!glfwInit()) {
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);                // 4x Сглаживание
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //Версия OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Не используем старый OpenGL


    //Размеры окна
    const GLuint WIDTH = 1024, HEIGHT = 768;

    //Создание окна приложения
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GLFW GLAD ImGUI", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Инициализация GLAD
    gladLoadGL();

    //Определение размеров вывода на плоскость экрана
    glViewport(0, 0, WIDTH, HEIGHT);


    //Инициализация объекта класса OpenGL
    BaseOpenGL objGL;

    //Инициализация интерфейса ImGui
    GuiDialog objImGui(window);

    //Инициализация модуля геометрических построений
    BuildOnPlate objAlgo(objGL, WIDTH, HEIGHT);
    //Расчет точек для эллипса
    objAlgo.DrawEllipse();
    //Расчет точек для гиперболы
    objAlgo.DrawHyperbola();


    //Настройка параметров OpenGL. Построение контрольных точек должно быть выполнено ранее. Это важно!
    objGL.InitComponents();

    //Режим отслеживания нажатия клавиш в приложении
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glfwSetFramebufferSizeCallback(window, reshapeWindows);

    //Основной цикл, при нажатии на ECS или закрытии приложения работа завершается
    while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           !glfwWindowShouldClose(window))
    {
        //Очиста буфера цвета с одновременным определением цвета фона
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Рендеринг объектов
        glUseProgram(objGL.GetShadersProgram());
        glBindVertexArray(objGL.GetVAO());
        glDrawArrays(GL_LINES, 0, objGL.GetNumberVertex());
        glUniform1f(glGetUniformLocation(objGL.GetShadersProgram(), "vRed"), objImGui.GetParam().valueRed);
        glUniform1f(glGetUniformLocation(objGL.GetShadersProgram(), "vGreen"), objImGui.GetParam().valueGreen);
        glUniform1f(glGetUniformLocation(objGL.GetShadersProgram(), "vBlue"), objImGui.GetParam().valueBlue);


        //Запуск нового окна ImGui frame
        objImGui.CreateGuiDialog();
        // //Отображение ImGui
        objImGui.ShowGui();


        //Обмен данными между передним и задним буфером
        glfwSwapBuffers(window);
        //Опрос и обработка событий
        glfwPollEvents();
    }

    //Уничтожение контекста GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    //Освобождение ресурсов ImGui
    //производится автоматически
    return 0;
}

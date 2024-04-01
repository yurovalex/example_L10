#pragma once
#include <imgui.h>
#include "GLFW/glfw3.h"

class GuiDialog
{
public:
    GuiDialog(GLFWwindow *w);
    void CreateGuiDialog();
    void ShowGui();
    auto GetParam() const
    {
        return objPar;
    }
    virtual ~GuiDialog();


private:
    GLFWwindow* window;

    struct PropertiesObject
    {
        PropertiesObject(float a, float b, float c):
            valueRed(a), valueGreen(b), valueBlue(c)
        {}
        float valueRed;
        float valueGreen;
        float valueBlue;
    };
    PropertiesObject objPar;
};




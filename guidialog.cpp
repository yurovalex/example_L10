#include "guidialog.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

GuiDialog::GuiDialog(GLFWwindow *w):window(w), objPar{0.1,0.5,0.0}
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void GuiDialog::CreateGuiDialog()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    //Элементы интерфейса в окне
    if (ImGui::Begin("Control propeties")) {
        ImGui::Text("Create a point's array");
        ImGui::SliderFloat("Red", &objPar.valueRed, 0.0f, 1.0f);
        ImGui::SliderFloat("Green", &objPar.valueGreen, 0.0f, 1.0f);
        ImGui::SliderFloat("Blue", &objPar.valueBlue, 0.0f, 1.0f);
    }
    ImGui::End();
}

void GuiDialog::ShowGui()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

GuiDialog::~GuiDialog()
{
    //Освобождение ресурсов ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

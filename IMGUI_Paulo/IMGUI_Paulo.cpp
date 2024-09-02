//
// Description: This is a simple example of how to use IMGUI with GLFW and OpenGL
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

// setting up the GLFW library and creating a window with an OpenGL context
GLFWwindow* InitializeGLFW(int width, int height, const char* title)
{
    // Initialize the library
    if (!glfwInit())
        return nullptr;

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    return window;
}

// Function to initialize ImGui
void InitializeImGui(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); 
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

// Function to cleanup ImGui
void CleanupImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

int main()
{
    GLFWwindow* window = InitializeGLFW(1280, 720, "IMGUI Paulo");
    if (!window)
        return -1;

    // Initialize ImGui
    InitializeImGui(window);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll events
        glfwPollEvents();
    }

    // Cleanup
    CleanupImGui();
    glfwTerminate();
    return 0;
}

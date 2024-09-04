//
// Description: This is a simple example of how to use IMGUI with GLFW and OpenGL
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

// Function declarations
GLFWwindow* InitializeGLFW(int width, int height, const char* title);
void InitializeImGui(GLFWwindow* window);
void CleanupImGui();
void RenderFrame();
void DrawImGuiContent();
void NewFrame();


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

        // Clear the screen
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);


        NewFrame();

        DrawImGuiContent();

        RenderFrame();

        // Swap buffers
        glfwSwapBuffers(window);
       
    }

    // Cleanup
    CleanupImGui();
    glfwTerminate();
    return 0;
}



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

void RenderFrame()
{
    // Rendering
    ImGui::Render();
    /*
     Renders the ImGui user interface to the frame buffer.
     In computer graphics, the frame buffer is a region of memory that stores the pixel data
     for the image being displayed on the screen. When the ImGui user interface is rendered
     using this code, the resulting UI elements are drawn directly onto the frame buffer.
     The frame buffer is responsible for holding the final image that is sent to the display
     device, such as a monitor. By rendering the ImGui UI to the frame buffer, the UI elements
     become part of the overall image that is shown on the screen.
    */
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void DrawImGuiContent()
{
    //render the imgui window
    ImGui::Begin("Hello, world!");
    ImGui::Text("This is some useful text.");
    ImGui::End();
}

void NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

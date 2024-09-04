//
// Description: This is a simple example of how to use IMGUI with GLFW and OpenGL
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Function declarations
GLFWwindow* InitializeGLFW(int width, int height, const char* title);
void initializeOpenGL();
GLuint createShaderProgram();
void setupVertexData(GLuint& VAO, GLuint& VBO);
void InitializeImGui(GLFWwindow* window);
void CleanupImGui();
void RenderFrame();
void DrawImGuiContent(bool & drawTriangle);
void NewFrame();
void SetupTriangle(GLuint& VAO, GLuint& VBO, GLuint& shaderProgram);
void DrawTriangle(GLuint VAO, GLuint shaderProgram);


#pragma region shader Source
// Vertex Shader source code
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";
// Fragment Shader source code
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main()
    {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
)";
#pragma endregion


int main()
{
    GLFWwindow* window = InitializeGLFW(1280, 720, "IMGUI Paulo");
    if (!window)
        return -1;

    initializeOpenGL();
    GLuint shaderProgram = createShaderProgram();
    GLuint VAO, VBO;
    setupVertexData(VAO, VBO);
    SetupTriangle(VAO, VBO, shaderProgram);


    // Initialize ImGui
    InitializeImGui(window);
    

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Variables for ImGui controls
        static bool drawTriangle= false;
        // Poll events
        glfwPollEvents();

        // Clear the screen
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle
        if(drawTriangle)
        DrawTriangle(VAO, shaderProgram);

        NewFrame();

        DrawImGuiContent(drawTriangle);

        RenderFrame();

        // Swap buffers
        glfwSwapBuffers(window);
       
    }

    // Cleanup
    CleanupImGui();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
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

void DrawImGuiContent( bool &drawTriangle)
{
    //render the imgui window
    ImGui::Begin("Hello, world!");
    ImGui::Text("This is some useful text.");
//Imgui checkbox for bool drawTraingle
	ImGui::Checkbox("Draw Triangle", &drawTriangle);

    ImGui::End();
}

void NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}


// Setup the triangle (VAO, VBO, and shader program)
void SetupTriangle(GLuint& VAO, GLuint& VBO, GLuint& shaderProgram)
{
    // Set up vertex data and buffers
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Create and compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Draw the triangle
void DrawTriangle(GLuint VAO, GLuint shaderProgram)
{
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

// Function to initialize OpenGL   
void initializeOpenGL()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
    glViewport(0, 0, 800, 800);
}

// Function to create a shader program
GLuint createShaderProgram()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

// Function to setup vertex data
void setupVertexData(GLuint& VAO, GLuint& VBO)
{
    float vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
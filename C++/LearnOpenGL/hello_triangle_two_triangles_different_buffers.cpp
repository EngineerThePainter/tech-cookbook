#include "hello_triangle_two_triangles_different_buffers.hpp"

#include <iostream>

#ifdef _WIN32 | _WIN64
#include <windows.h>
#endif

// Must be before GLFW
#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace
{
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

void framebufferSizeCallback(GLFWwindow* /*window*/, int width, int height) { glViewport(0, 0, width, height); }

void processInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void initialize(const int majorVersion, const int minorVersion)
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Required on MacOS
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void destroy() { glfwTerminate(); }

} // namespace

int helloTriangleTwoTrianglesDifferentBuffers()
{
  initialize(3, 3);

  GLFWwindow* window =
      glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "helloTriangleTwoTrianglesDifferentBuffers", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window\n";
    destroy();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // GLAD must be initialized before any OpenGL function call,
  // as it manages function pointers to the OpenGL
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD\n";
    return -1;
  }

  // Tell the OpenGL the size of the rendering window
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  // Adjust the viewport in case if the window will be resized
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  const float left_triangle[] = {-0.5f, 0.0f, 0.0f,
                                 //
                                 -0.25f, 0.5f, 0.0f,
                                 //
                                 0.0f, 0.0f, 0.0f};
  const float right_triangle[] = {0.0f, 0.0f, 0.0f,
                                  //
                                  0.25f, 0.5f, 0.0f,
                                  //
                                  0.5f, 0.0f, 0.0f};

  // Vertex Array Object
  GLuint VAO[2];
  // Vertex Buffer Object
  GLuint VBO[2];
  // Let's have two different buffers
  glGenVertexArrays(2, VAO);
  glGenBuffers(2, VBO);

  glBindVertexArray(VAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(left_triangle), left_triangle, GL_STATIC_DRAW);
  // In both pointers we could change the stride to 0
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAO[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(right_triangle), right_triangle, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  const char* vertexShaderSource =
      R"shader(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        void main() {
          gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
      )shader";

  GLuint vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // Attach shader source code to the shader object and compile it
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    std::cout << "ERROR SHADER VERTEX COMPILATION FAILED: " << infoLog << std::endl;
  }

  const char* fragmentShaderSource =
      R"fragment(
        #version 330 core
        out vec4 FragColor;
        void main() {
          FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
          }
      )fragment";
  GLuint fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
    std::cout << "ERROR SHADER FRAGMENT COMPILATION FAILED: " << infoLog << std::endl;
  }

  GLuint shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // As shaders were linked, they are in the memory, we do not need them anymore
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  // Main program loop
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    // rendering happens here
    glClearColor(0.1f, 0.1f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  destroy();

  return 0;
}
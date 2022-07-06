#include "shaders.hpp"

#include <iostream>

#ifdef _WIN32
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

void checkShaderCompilation(GLuint shader)
{
  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cout << "SHADER COMPILATION FAILED: " << infoLog << std::endl;
  }
}

// Commented to show how vertex and fragment shader looks like when
// sending the color from one to another.
// const char* vertexShaderSource =
//     R"shader(
//         #version 330 core
//         layout(location = 0) in vec3 aPos;
//         out vec4 vertexColor;
//         void main() {
//           gl_Position = vec4(aPos, 1.0);
//           vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
//         }
//       )shader";

// const char* fragmentShaderSource =
//     R"fragment(
//         #version 330 core
//         out vec4 FragColor;
//         in vec4 vertexColor;
//         void main() {
//           FragColor = vertexColor;
//           }
//       )fragment";

// Shaders for making the changing color triangle
// const char* vertexShaderSource =
//     R"shader(
//         #version 330 core
//         layout(location = 0) in vec3 aPos;
//         void main() {
//           gl_Position = vec4(aPos, 1.0);
//         }
//       )shader";

// const char* fragmentShaderSource =
//     R"fragment(
//         #version 330 core
//         out vec4 FragColor;
//         uniform vec4 ourcolor;
//         void main() {
//           FragColor = ourcolor;
//           }
//       )fragment";

// Shaders for making vertices with extra attributes
const char* vertexShaderSource =
    R"shader(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aColor;

        out vec3 ourColor;
        void main() {
          gl_Position = vec4(aPos, 1.0);
          ourColor = aColor;
        }
      )shader";

const char* fragmentShaderSource =
    R"fragment(
        #version 330 core
        out vec4 FragColor;
        in vec3 ourColor;
        void main() {
          FragColor = vec4(ourColor, 1.0f);
          }
      )fragment";

} // namespace

int shaders()
{
  initialize(3, 3);

  GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
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

  // Triangle used for first shaders and changing color triangle
  // const float triangle[] = {-0.5f, -0.5f, 0.0f,
  //                           //
  //                           0.0f, 0.5f, 0.0f,
  //                           //
  //                           0.5f, -0.5f, 0.0f};

  const float triangle[] = {// Position          // Color
                            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
                            //
                            0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
                            //
                            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f};

  // Vertex Array Object
  GLuint VAO;
  // Vertex Buffer Object
  GLuint VBO;
  // Let's have two different buffers
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
  // Attributes when the traingle was just vertices
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  // glEnableVertexAttribArray(0);

  // Attribtues when triangle contain both position and color
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  GLuint vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // Attach shader source code to the shader object and compile it
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
  checkShaderCompilation(vertexShader);

  GLuint fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);
  checkShaderCompilation(fragmentShader);

  GLuint shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    // rendering happens here
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    // Code for making the triangle to change the color over time
    // float timeValue = glfwGetTime();
    // float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourcolor");
    // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  destroy();
  return 0;
}
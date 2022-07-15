#include "coordinates.hpp"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

// Must be before GLFW
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "thirdparty/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

// Shaders for making vertices with extra attributes
const char* vertexShaderSource =
    R"shader(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec2 aTexCoord;

        out vec2 TexCoord;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main() {
          // multiplication happens from right to left
          gl_Position = projection * view * model * vec4(aPos, 1.0f);
          TexCoord = vec2(aTexCoord.x, aTexCoord.y);
        }
      )shader";

const char* fragmentShaderSource =
    R"fragment(
        #version 330 core
        out vec4 FragColor;

        in vec2 TexCoord;

        uniform sampler2D texture1;
        uniform sampler2D texture2;

        void main() {
          FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
          }
      )fragment";

} // namespace

int camera()
{
  initialize(3, 3);

  GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "transformations", nullptr, nullptr);
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

  // Vertices for plain square
  // const float vertices[] = {
  //     // positions          // texture coords
  //     0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // top right
  //     //
  //     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
  //     //
  //     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
  //     //
  //     -0.5f, 0.5f, 0.0f, 0.0f, 1.0f // top left
  // };

  // Enable depth testing for objects
  glEnable(GL_DEPTH_TEST);
  // Vertices for a cube
  float vertices[] = {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                      //
                      0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
                      //
                      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                      //
                      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                      //
                      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                      //
                      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                      //
                      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                      //
                      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                      //
                      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                      //
                      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                      //
                      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
                      //
                      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                      //
                      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                      //
                      -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                      //
                      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                      //
                      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                      //
                      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                      //
                      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                      //
                      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                      //
                      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                      //
                      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                      //
                      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                      //
                      0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                      //
                      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                      //
                      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                      //
                      0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
                      //
                      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                      //
                      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                      //
                      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                      //
                      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                      //
                      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                      //
                      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                      //
                      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                      //
                      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                      //
                      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
                      //
                      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

  glm::vec3 cubePositions[] = {glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
                               glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
                               glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
                               glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
                               glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

  GLuint indices[] = {0, 1, 3,
                      //
                      1, 2, 3};

  // Vertex Array Object
  GLuint VAO;
  // Vertex Buffer Object
  GLuint VBO;
  // Elemnts buffer object
  GLuint EBO;
  // Let's have two different buffers
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Attribtues when triangle contain both position and color
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
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

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int textureWidth, textureHeight, nrChannels;
  unsigned char* data = stbi_load("images/container.jpg", &textureWidth, &textureHeight, &nrChannels, 0);

  if (data != nullptr) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }

  stbi_image_free(data);

  unsigned int textureFace;
  glGenTextures(1, &textureFace);
  glBindTexture(GL_TEXTURE_2D, textureFace);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int textureFaceWidth, textureFaceHeight, nrChannelsFace;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* faceData =
      stbi_load("images/awesomeface.png", &textureFaceWidth, &textureFaceHeight, &nrChannelsFace, 0);

  if (faceData != nullptr) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureFaceWidth, textureFaceHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 faceData);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }

  // Image was loaded into the texture we can free image data

  stbi_image_free(faceData);

  glUseProgram(shaderProgram);

  glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
  glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

  glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
  // Points in the different direction that is targeting
  glm::vec3 cameraDirection = glm::normaize(cameraPod - cameraTarget);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
  glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    // rendering happens here
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    // Clearing the depth buffer so depth information is always new for each frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureFace);

    glUseProgram(shaderProgram);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 1.0f, 100.0f);

    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    // To have just lying over the floor box
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    for (unsigned int i = 0; i < 10; ++i) {

      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));

      int modelLoc = glGetUniformLocation(shaderProgram, "model");
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  destroy();
  return 0;
}
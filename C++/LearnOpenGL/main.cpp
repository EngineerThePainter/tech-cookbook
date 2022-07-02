#include "hello_triangle.hpp"
#include "hello_triangle_two_triangles.hpp"
#include "hello_triangle_two_triangles_different_buffers.hpp"
#include "hello_triangle_two_triangles_different_shaders.hpp"

int main(int argc, const char* argv[])
{
  int return_value = 0;
  return_value = helloTriangle();
  return_value = helloTriangleTwoTriangles();
  return_value = helloTriangleTwoTrianglesDifferentBuffers();
  return_value = helloTriangleTwoTrianglesDifferentShaders();

  return return_value;
}
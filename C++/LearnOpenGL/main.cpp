#include "hello_triangle.hpp"
#include "hello_triangle_two_triangles.hpp"
#include "hello_triangle_two_triangles_different_buffers.hpp"
#include "hello_triangle_two_triangles_different_shaders.hpp"

#ifdef _DEBUG
#ifdef _WIN32
#define WIN_MEMORY_LEAK_CHECKER
#define _CRTDBG_MAP_ALLOC
#include <cstdio>
#include <stdlib.h>

#include <crtdbg.h>
#endif // _WIN32
#endif // _DEBUG

int main(int argc, const char* argv[])
{

#ifdef WIN_MEMORY_LEAK_CHECKER
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
#endif

  int return_value = 0;
  return_value = helloTriangle();
  return_value = helloTriangleTwoTriangles();
  return_value = helloTriangleTwoTrianglesDifferentBuffers();
  return_value = helloTriangleTwoTrianglesDifferentShaders();

#ifdef WIN_MEMORY_LEAK_CHECKER
  _CrtDumpMemoryLeaks();
  getchar();
#endif // WIN_MEMORY_LEAK_CHECKER

  return return_value;
}
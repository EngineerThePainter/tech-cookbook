#include "coordinates.hpp"
#include "coordinates_container_rotating.hpp"
#include "hello_triangle.hpp"
#include "hello_triangle_two_triangles.hpp"
#include "hello_triangle_two_triangles_different_buffers.hpp"
#include "hello_triangle_two_triangles_different_shaders.hpp"
#include "shaders.hpp"
#include "shaders_color_as_position.hpp"
#include "shaders_horizontal_offset.hpp"
#include "shaders_triangle_upside_down.hpp"
#include "textures.hpp"
#include "textures_centric.hpp"
#include "textures_experiments.hpp"
#include "textures_face_reversed.hpp"
#include "textures_visibility_manipulation.hpp"
#include "transformations.hpp"
#include "transformations_second_container.hpp"

#ifdef _DEBUG
#ifdef _WIN32
#define WIN_MEMORY_LEAK_CHECKER
#define _CRTDBG_MAP_ALLOC
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
  // return_value = helloTriangle();
  // return_value = helloTriangleTwoTriangles();
  // return_value = helloTriangleTwoTrianglesDifferentBuffers();
  // return_value = helloTriangleTwoTrianglesDifferentShaders();
  // return_value = shaders();
  // return_value = shadersTriangleUpsideDown();
  // return_value = shadersHorizontalOffset();
  // return_value = shadersColorAsPosition();
  // return_value = textures();
  // return_value = texturesFaceReversed();
  // return_value = texturesExperiments();
  // return_value = texturesCentric();
  // return_value = texturesVisibilityManipulation();
  // return_value = transformations();
  // return_value = transformationsSecondContainer();
  return_value = coordinates();
  return_value = coordinatesContainerRotating();

#ifdef WIN_MEMORY_LEAK_CHECKER
  _CrtDumpMemoryLeaks();
#endif // WIN_MEMORY_LEAK_CHECKER

  return return_value;
}
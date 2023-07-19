from conans import ConanFile, CMake

class LearnOpenGL(ConanFile):
  settings = "os", "compiler", "build_type", "arch", "arch_build"
   
  generators = "cmake"

  requires = [
    ("opengl/system"),
    ("glad/0.1.35"),
    ("glfw/3.3.7"),
    ("glew/2.2.0"),
    ("glm/0.9.9.8")
    ]

  default_options = {
    "sdl:shared": True
  }

  def imports(self):
    self.copy("*.dll", dst="bin", src="bin") # From bin to bin
    self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin
    self.copy("*.so*", dst="bin", src="lib") # From lib to bin

  def build(self):
    cmake = CMake(self)
    cmake.configure()
    cmake.build()
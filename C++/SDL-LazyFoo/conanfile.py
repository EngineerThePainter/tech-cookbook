from importlib.metadata import requires
from conans import ConanFile, CMake

class SDLLazyFoo(ConanFile):
  settings = "os", "compiler", "build_type", "arch", "arch_build"
   
  generators = "cmake"

  requires = [("sdl/2.0.18"), ("sdl_image/2.0.5")]

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

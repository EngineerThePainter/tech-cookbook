from importlib.metadata import requires
from conans import ConanFile, CMake

class DockerCppSetup(ConanFile):
  settings = "os", "compiler", "build_type", "arch", "arch_build"

  generators = "cmake"

  build_requires = ("gtest/1.10.0")

  def imports(self):
    self.copy("*.dll", dst="bin", src="bin")
    self.copy("*.dylib", dst="bin", src="lib")
    self.copy("*.so", dst="bin", src="lib")

  def build(self):
    cmake = CMake(self)
    cmake.configure()
    cmake.build()
    cmake.test()
    
from conans import ConanFile, CMake

class BoostConan(ConanFile):
   settings = "os", "compiler", "build_type", "arch", "arch_build"
   
   generators = "cmake"
   
   default_options = {"boost:shared": True,
      "boost:without_math": True,
      "boost:without_wave": True,
      "boost:without_container": True,
      "boost:without_contract": True,
      "boost:without_exception": True,
      "boost:without_graph": True,
      "boost:without_iostreams": True,
      "boost:without_locale": True,
      "boost:without_log": True,
      "boost:without_program_options": True,
      "boost:without_random": True,
      "boost:without_regex": True,
      "boost:without_mpi": True,
      "boost:without_serialization": True,
      "boost:without_coroutine": True,
      "boost:without_fiber": True,
      "boost:without_context": True,
      "boost:without_timer": True,
      "boost:without_thread": True,
      "boost:without_chrono": True,
      "boost:without_date_time": True,
      "boost:without_atomic": True,
      "boost:without_filesystem": True,
      "boost:without_system": True,
      "boost:without_graph_parallel": True,
      "boost:without_python": True,
      "boost:without_stacktrace": True,
      "boost:without_test": True,
      "boost:without_type_erasure": True
   }
   
   requires = ("boost/1.73.0") # comma-separated list of requirements


   def imports(self):
      self.copy("*.dll", dst="bin", src="bin") # From bin to bin
      self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin
      self.copy("*.so*", dst="bin", src="lib") # From lib to bin
   
   def build(self):
      cmake = CMake(self)
      cmake.configure()
      cmake.build()
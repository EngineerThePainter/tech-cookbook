set_languages("cxx17", "c++17")
-- The spaces between name and version are mandatory
add_requires("vcpkg::allegro5", "imgui 1.91.1")

target("cpp-xmake-example")

    set_kind("binary")
    add_files("main.cpp")
    set_toolchains("clang")

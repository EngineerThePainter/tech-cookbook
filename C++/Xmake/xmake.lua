local allegro5 = "vcpkg::allegro5"
local loguru = "vcpkg::loguru"

-- The spaces between name and version are mandatory
add_requires(allegro5, loguru, "imgui 1.91.1")

target("cpp-xmake-example")
    set_languages("cxx17", "c++17")
    set_kind("binary")
    add_files("main.cpp")
    set_toolchains("clang")
    add_packages("vcpkg::allegro5", loguru)

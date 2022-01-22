#include <iostream>

#include "lesson1/lesson1.hpp"
#include "lesson2/lesson2.hpp"
#include "lesson3/lesson3.hpp"
#include "lesson4/lesson4.hpp"
#include "lesson5/lesson5.hpp"
#include "lesson6/lesson6.hpp"
#include "lesson7/lesson7.hpp"
#include "lesson8/lesson8.hpp"
#include "lesson9/lesson9.hpp"

int main(int argc, char* args[])
{
    // Hello SDL
    // sdl_lazyfoo::lesson1();

    // Getting an image on the screen
    // sdl_lazyfoo::lesson2::lesson2();

    // Event Driven Programming
    // sdl_lazyfoo::lesson3::lesson3();

    // Key presses
    // sdl_lazyfoo::lesson4::lesson4();

    // Optimized surface loading and Soft Stretchening
    // sdl_lazyfoo::lesson5::lesson5();

    // Extension libraries and loading other image formats
    // sdl_lazyfoo::lesson6::lesson6();

    // Texture Loading and rendering
    // sdl_lazyfoo::lesson7::lesson7();

    // Geometry rendering
    // sdl_lazyfoo::lesson8::lesson8();

    // The viewport
    sdl_lazyfoo::lesson9::lesson9();

    return 0;
}
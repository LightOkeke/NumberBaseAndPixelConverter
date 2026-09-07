# NumberBaseAndPixelConverter
Student: Light Okeke
Course: CS 240

DESCRIPTION

This C++ program contains an ASCII-to-decimal converter, a number-base
converter, a PPM image reader, and a PPM image creator.

The number converter supports binary, decimal, octal, and hexadecimal.
The program also tests zero, the largest 32-bit unsigned value, and -42
as a two's-complement value.

HOW TO RUN

1. Open the project in CLion.
2. Open NumberBaseAndPixelConverter.cpp.
3. Build and run the CS240 executable.
4. Enter a menu choice from 0 through 5.

MENU OPTIONS

1 - Convert an ASCII character to decimal
2 - Convert between number bases
3 - Read a P3 PPM image and print its pixels
4 - Create a P3 PPM image from pixel values
5 - Run boundary tests
0 - Exit

TESTS

ASCII:
A produces decimal 65.

Number conversion:
Binary 101010 produces decimal 42, octal 52, and hexadecimal 2A.

Boundary cases:
Zero produces 0.
The largest 32-bit unsigned value is 4294967295.
The program displays -42 using 32-bit two's-complement encoding.

ACKNOWLEDGMENT

OpenAI Codex assisted with fixing errors and reviewing the program.

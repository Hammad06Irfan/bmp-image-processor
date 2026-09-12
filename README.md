# BMP Image Processor (C++)

A lightweight, dependency-free C++17 command-line application for loading, transforming, and saving uncompressed 24-bit BMP images.

Built using standard C++ file streams and custom image buffers, this project provides fast pixel manipulation utilities with zero external dependencies.

## Visual Demonstrations

### Horizontal Flip

| Original (`test.png`) | Flipped (`flipped.png`) | 
 | ----- | ----- | 
|  |  | 
| Base 2x2 test pattern | Mirrored along the vertical axis | 

### Brightness Adjustments

| Brightness +50 (`Bright.png`) | Brightness -50 (`dark.png`) | 
 | ----- | ----- | 
|  |  | 
| Channel values scaled upward | Channel values scaled downward | 

## Features

* **Zero External Dependencies:** Built solely with the C++ Standard Library (`<iostream>`, `<fstream>`, `<vector>`).

* **Binary File I/O:** Directly parses and serializes standard 24-bit bitmap headers and raw pixel data.

* **Pixel Transformation Pipeline:**

  * **Grayscale:** Converts color images using human perceptual luminance weights.

  * **Invert:** Computes the photographic negative of each color channel.

  * **Flip:** Mirrors pixels horizontally across the vertical center.

  * **Brightness:** Dynamically shifts RGB channels with safe boundary clamping ($0 - 255$).

## Project Structure

```
bmp_processor/
├── BmpHeaders.h    # Struct definitions for BMP File and Info headers
├── Image.h         # Image class definition and method declarations
├── Image.cpp       # Binary I/O and pixel processing algorithms
└── main.cpp        # Command-line interface and argument handling

```

## Building the Application

Ensure you have a modern C++ compiler supporting C++17.

### Linux / macOS (GCC or Clang)

```
g++ -std=c++17 -O2 -Wall -Wextra main.cpp Image.cpp -o bmp_tool

```

### Windows (MSVC)

```
cl /EHsc /std:c++17 /O2 main.cpp Image.cpp /Febmp_tool.exe

```

## Usage

Run the utility from your command line by specifying the input file, output file, and desired filter:

```
./bmp_tool <input.bmp> <output.bmp> <filter> [argument]

```

### Supported Commands

| Filter | Argument | Description | Example | 
 | ----- | ----- | ----- | ----- | 
| `grayscale` | *None* | Converts image to perceptual grayscale | `./bmp_tool test.bmp gray.bmp grayscale` | 
| `invert` | *None* | Inverts all color channels | `./bmp_tool test.bmp invert.bmp invert` | 
| `flip` | *None* | Horizontally flips the image | `./bmp_tool test.bmp flipped.bmp flip` | 
| `brightness` | `[-255 to 255]` | Adjusts image brightness by an offset | `./bmp_tool test.bmp bright.bmp brightness 50` | 

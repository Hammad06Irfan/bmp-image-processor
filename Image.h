#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include "BmpHeaders.h"

class Image {
public:
    Image() = default;

    // File I/O
    bool load(const std::string& filename);
    bool save(const std::string& filename);

    // Image manipulation filters
    void grayscale();
    void invert();
    void flip_horizontal();
    void adjust_brightness(int adjustment);

    // Getters
    int get_width() const { return info_header.width; }
    int get_height() const { return info_header.height; }

private:
    BMPFileHeader file_header;
    BMPInfoHeader info_header;

    // Holds raw pixel bytes: stored as [B, G, R, B, G, R, ...]
    std::vector<uint8_t> pixels;
};
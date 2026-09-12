#include "Image.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>

bool Image::load(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return false;
    }

    file.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    file.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    if (file_header.file_type != 0x4D42) {
        std::cerr << "Error: Not a BMP file.\n";
        return false;
    }

    if (info_header.bit_count != 24 || info_header.compression != 0) {
        std::cerr << "Error: Only uncompressed 24-bit BMPs are supported.\n";
        return false;
    }

    int width = info_header.width;
    int raw_height = info_header.height;
    int height = std::abs(raw_height);

    int row_bytes = width * 3;
    int padding = (4 - (row_bytes % 4)) % 4;

    pixels.resize(width * height * 3);

    file.seekg(file_header.offset_data, std::ios::beg);

    // Read rows; normalize to standard bottom-up order in memory
    for (int y = 0; y < height; ++y) {
        int target_row = (raw_height < 0) ? (height - 1 - y) : y;
        file.read(reinterpret_cast<char*>(&pixels[target_row * row_bytes]), row_bytes);
        file.ignore(padding);
    }

    // Standardize header in memory to positive (bottom-up) height
    info_header.height = height;

    return true;
}

bool Image::save(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not create file " << filename << "\n";
        return false;
    }

    int width = info_header.width;
    int height = std::abs(info_header.height);
    int row_bytes = width * 3;
    int padding = (4 - (row_bytes % 4)) % 4;

    uint32_t row_stride_with_padding = row_bytes + padding;
    info_header.size_image = row_stride_with_padding * height;
    file_header.file_size = file_header.offset_data + info_header.size_image;
    info_header.height = height; // Always write bottom-up

    file.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
    file.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));

    const uint8_t pad_bytes[3] = {0, 0, 0};
    for (int y = 0; y < height; ++y) {
        file.write(reinterpret_cast<const char*>(&pixels[y * row_bytes]), row_bytes);
        if (padding > 0) {
            file.write(reinterpret_cast<const char*>(pad_bytes), padding);
        }
    }

    return true;
}

void Image::grayscale() {
    for (size_t i = 0; i < pixels.size(); i += 3) {
        uint8_t b = pixels[i];
        uint8_t g = pixels[i + 1];
        uint8_t r = pixels[i + 2];
        uint8_t avg = static_cast<uint8_t>((r * 299 + g * 587 + b * 114) / 1000); // Perceptual weights

        pixels[i]     = avg;
        pixels[i + 1] = avg;
        pixels[i + 2] = avg;
    }
}

void Image::invert() {
    for (size_t i = 0; i < pixels.size(); ++i) {
        pixels[i] = static_cast<uint8_t>(255 - pixels[i]);
    }
}

void Image::flip_horizontal() {
    int width = info_header.width;
    int height = std::abs(info_header.height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width / 2; ++x) {
            int left_idx  = (y * width + x) * 3;
            int right_idx = (y * width + (width - 1 - x)) * 3;

            std::swap(pixels[left_idx],     pixels[right_idx]);
            std::swap(pixels[left_idx + 1], pixels[right_idx + 1]);
            std::swap(pixels[left_idx + 2], pixels[right_idx + 2]);
        }
    }
}

void Image::adjust_brightness(int adjustment) {
    std::cout << "Modifying " << pixels.size() << " bytes with adjustment " << adjustment << "...\n";
    for (size_t i = 0; i < pixels.size(); ++i) {
        int val = static_cast<int>(pixels[i]) + adjustment;
        if (val > 255) {
            val = 255;
        } else if (val < 0) {
            val = 0;
        }
        pixels[i] = static_cast<uint8_t>(val);
    }
}
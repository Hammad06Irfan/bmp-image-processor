#pragma once
#include <cstdint>

#pragma pack(push, 1)

// 14 bytes: General file info
struct BMPFileHeader {
    uint16_t file_type{0x4D42}; // Always 'BM' (0x4D42)
    uint32_t file_size{0};       // Total file size in bytes
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offset_data{0};     // Byte position where pixels begin
};

// 40 bytes: Image dimensions, bit depth, format
struct BMPInfoHeader {
    uint32_t size{40};           // Header size (always 40 for standard BMP)
    int32_t  width{0};           // Image width in pixels
    int32_t  height{0};          // Image height in pixels
    uint16_t planes{1};          // Always 1
    uint16_t bit_count{24};      // Bits per pixel (24 = 3 bytes: Blue, Green, Red)
    uint32_t compression{0};     // 0 = uncompressed (BI_RGB)
    uint32_t size_image{0};      // Pixel data size including padding
    int32_t  x_pixels_per_meter{0};
    int32_t  y_pixels_per_meter{0};
    uint32_t colors_used{0};
    uint32_t colors_important{0};
};

#pragma pack(pop)
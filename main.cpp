#include <iostream>
#include <string>
#include "Image.h"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " <input.bmp> <output.bmp> <filter> [arg]\n";
        std::cout << "Filters:\n";
        std::cout << "  grayscale\n";
        std::cout << "  invert\n";
        std::cout << "  flip\n";
        std::cout << "  brightness <value> (e.g. 50 or -50)\n";
        return 1;
    }

    std::string input_path  = argv[1];
    std::string output_path = argv[2];
    std::string filter      = argv[3];

    Image img;
    if (!img.load(input_path)) {
        return 1;
    }

    std::cout << "Loaded " << input_path << " (" << img.get_width() << "x" << img.get_height() << ")\n";

    if (filter == "grayscale") {
        img.grayscale();
    } else if (filter == "invert") {
        img.invert();
    } else if (filter == "flip") {
        img.flip_horizontal();
    } else if (filter == "brightness" || filter == "bright") {
        int adjustment = 50; // default visible bump
        if (argc >= 5) {
            try {
                adjustment = std::stoi(argv[4]);
            } catch (const std::exception& e) {
                std::cerr << "Invalid brightness value: " << argv[4] << "\n";
                return 1;
            }
        }
        std::cout << "Applying brightness adjustment of: " << adjustment << "\n";
        img.adjust_brightness(adjustment);
    } else {
        std::cerr << "Unknown filter: " << filter << "\n";
        return 1;
    }

    if (img.save(output_path)) {
        std::cout << "Successfully saved to " << output_path << "\n";
    }

    return 0;
}
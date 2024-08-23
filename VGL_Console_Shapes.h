#ifndef VGL_CONSOLE_SHAPES_H
#define VGL_CONSOLE_SHAPES_H

#include "VGL_Console.h"

namespace VGL_Console_Shapes {

    // Draw a filled rectangle with plain color and text color matching background
    void drawFilledRectangle(int x, int y, int width, int height, VGL_Console::Color bgColor) {
        VGL_Console::setBackgroundColor(static_cast<VGL_Console::BackgroundColor>(bgColor)); // Set background color for the rectangle
        for (int i = y; i < y + height; ++i) {
            VGL_Console::setColor(bgColor); // Set text color matching background color
            for (int j = x; j < x + width; ++j) {
                std::cout << " ";
            }
            std::cout << "\n";
        }
        VGL_Console::resetColor();
        VGL_Console::resetBackgroundColor();
    }

    // Draw a filled circle with plain color and text color matching background
    void drawFilledCircle(int centerX, int centerY, int radius, VGL_Console::Color bgColor) {
        VGL_Console::setBackgroundColor(static_cast<VGL_Console::BackgroundColor>(bgColor)); // Set background color for the circle
        double radiusSquared = radius * radius;
        for (int y = -radius; y <= radius; ++y) {
            VGL_Console::setColor(bgColor); // Set text color matching background color
            for (int x = -radius; x <= radius; ++x) {
                if (x * x + y * y <= radiusSquared) {
                    std::cout << " ";
                } else {
                    std::cout << "  "; // Adjust for aspect ratio in console
                }
            }
            std::cout << "\n";
        }
        VGL_Console::resetColor();
        VGL_Console::resetBackgroundColor();
    }

} // namespace VGL_Console_Shapes

#endif // VGL_CONSOLE_SHAPES_H
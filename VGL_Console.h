#ifndef VGL_CONSOLE_H
#define VGL_CONSOLE_H

#include <iostream>
#include <string>

namespace VGL_Console {

    enum class Color {
        RESET,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        BLACK,
        BOLD_RED,
        BOLD_GREEN,
        BOLD_YELLOW,
        BOLD_BLUE,
        BOLD_MAGENTA,
        BOLD_CYAN,
        BOLD_WHITE
    };

    enum class BackgroundColor {
        RESET,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        BLACK,
        BRIGHT_RED,
        BRIGHT_GREEN,
        BRIGHT_YELLOW,
        BRIGHT_BLUE,
        BRIGHT_MAGENTA,
        BRIGHT_CYAN,
        BRIGHT_WHITE
    };

    std::string getAnsiCode(Color color) {
        switch (color) {
            case Color::RESET: return "\033[0m";
            case Color::RED: return "\033[31m";
            case Color::GREEN: return "\033[32m";
            case Color::YELLOW: return "\033[33m";
            case Color::BLUE: return "\033[34m";
            case Color::MAGENTA: return "\033[35m";
            case Color::CYAN: return "\033[36m";
            case Color::WHITE: return "\033[37m";
            case Color::BLACK: return "\033[30m";
            case Color::BOLD_RED: return "\033[1;31m";
            case Color::BOLD_GREEN: return "\033[1;32m";
            case Color::BOLD_YELLOW: return "\033[1;33m";
            case Color::BOLD_BLUE: return "\033[1;34m";
            case Color::BOLD_MAGENTA: return "\033[1;35m";
            case Color::BOLD_CYAN: return "\033[1;36m";
            case Color::BOLD_WHITE: return "\033[1;37m";
            default: return "\033[0m";
        }
    }

    std::string getAnsiBackgroundCode(BackgroundColor color) {
        switch (color) {
            case BackgroundColor::RESET: return "\033[0m";
            case BackgroundColor::RED: return "\033[41m";
            case BackgroundColor::GREEN: return "\033[42m";
            case BackgroundColor::YELLOW: return "\033[43m";
            case BackgroundColor::BLUE: return "\033[44m";
            case BackgroundColor::MAGENTA: return "\033[45m";
            case BackgroundColor::CYAN: return "\033[46m";
            case BackgroundColor::WHITE: return "\033[47m";
            case BackgroundColor::BLACK: return "\033[40m";
            case BackgroundColor::BRIGHT_RED: return "\033[101m";
            case BackgroundColor::BRIGHT_GREEN: return "\033[102m";
            case BackgroundColor::BRIGHT_YELLOW: return "\033[103m";
            case BackgroundColor::BRIGHT_BLUE: return "\033[104m";
            case BackgroundColor::BRIGHT_MAGENTA: return "\033[105m";
            case BackgroundColor::BRIGHT_CYAN: return "\033[106m";
            case BackgroundColor::BRIGHT_WHITE: return "\033[107m";
            default: return "\033[0m";
        }
    }

    void setColor(Color color) {
        std::cout << getAnsiCode(color);
    }

    void setBackgroundColor(BackgroundColor color) {
        std::cout << getAnsiBackgroundCode(color);
    }

    void resetColor() {
        std::cout << getAnsiCode(Color::RESET);
    }

    void resetBackgroundColor() {
        std::cout << getAnsiBackgroundCode(BackgroundColor::RESET);
    }

    void printColored(const std::string& text, Color color) {
        setColor(color);
        std::cout << text;
        resetColor();
    }

    void printColored(const std::string& text, Color color, BackgroundColor bgColor) {
        setColor(color);
        setBackgroundColor(bgColor);
        std::cout << text;
        resetColor();
        resetBackgroundColor();
    }
}

#endif // VGL_CONSOLE_H
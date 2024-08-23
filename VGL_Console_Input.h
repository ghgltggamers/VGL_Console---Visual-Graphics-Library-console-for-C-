#ifndef VGL_CONSOLE_INPUT_H
#define VGL_CONSOLE_INPUT_H

#include <iostream>
#include <deque>
#include <mutex>
#include <thread>
#include <condition_variable>

namespace VGL_Console_Input {

    // Enumeration for special keys
    enum SpecialKey {
        KEY_NONE = 0,
        KEY_ARROW_UP,
        KEY_ARROW_DOWN,
        KEY_ARROW_LEFT,
        KEY_ARROW_RIGHT,
        KEY_F1,
        KEY_F2,
        KEY_F3,
        KEY_F4,
        KEY_F5,
        KEY_F6,
        KEY_F7,
        KEY_F8,
        KEY_F9,
        KEY_F10,
        KEY_F11,
        KEY_F12,
        KEY_ENTER,
        KEY_ESCAPE,
        KEY_BACKSPACE,
        KEY_TAB,
        KEY_DELETE,
        KEY_HOME,
        KEY_END,
        KEY_PAGE_UP,
        KEY_PAGE_DOWN,
        KEY_INSERT
        // Add more as needed
    };

    // Class to manage keyboard input
    class Keyboard {
    public:
        Keyboard() : running(true) {
            inputThread = std::thread(&Keyboard::inputLoop, this);
        }

        ~Keyboard() {
            running = false;
            if (inputThread.joinable()) {
                inputThread.join();
            }
        }

        // Function to check if a key is pressed
        static bool keyPressed() {
            std::unique_lock<std::mutex> lock(inputMutex);
            return !keyBuffer.empty();
        }

        // Function to get the next key pressed
        static char getKey() {
            std::unique_lock<std::mutex> lock(inputMutex);
            if (keyBuffer.empty()) {
                return '\0'; // No key pressed
            }
            char key = keyBuffer.front();
            keyBuffer.pop_front();
            return key;
        }

        // Function to check if a special key is pressed
        static SpecialKey getSpecialKey() {
            std::unique_lock<std::mutex> lock(inputMutex);
            if (specialKeyBuffer.empty()) {
                return SpecialKey::KEY_NONE;
            }
            SpecialKey key = specialKeyBuffer.front();
            specialKeyBuffer.pop_front();
            return key;
        }

    private:
        static std::deque<char> keyBuffer;
        static std::deque<SpecialKey> specialKeyBuffer;
        static std::mutex inputMutex;
        std::thread inputThread;
        bool running;

        // Function to process input in a separate thread
        void inputLoop() {
            while (running) {
                char input;
                std::cin.get(input);
                if (input == 27 && std::cin.peek() == '[') {
                    // Escape sequence (possible special key)
                    std::cin.get(input); // Consume '['
                    switch (std::cin.get()) {
                        case 'A': specialKeyBuffer.push_back(SpecialKey::KEY_ARROW_UP); break;
                        case 'B': specialKeyBuffer.push_back(SpecialKey::KEY_ARROW_DOWN); break;
                        case 'C': specialKeyBuffer.push_back(SpecialKey::KEY_ARROW_RIGHT); break;
                        case 'D': specialKeyBuffer.push_back(SpecialKey::KEY_ARROW_LEFT); break;
                        // Add more cases for other special keys as needed
                        default: break;
                    }
                } else {
                    // Regular character input
                    std::unique_lock<std::mutex> lock(inputMutex);
                    keyBuffer.push_back(input);
                }
            }
        }
    };

    // Initialize static members
    std::deque<char> Keyboard::keyBuffer;
    std::deque<SpecialKey> Keyboard::specialKeyBuffer;
    std::mutex Keyboard::inputMutex;

} // namespace VGL_Console_Input

#endif // VGL_CONSOLE_INPUT_H
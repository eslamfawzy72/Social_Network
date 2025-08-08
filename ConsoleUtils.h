#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H
#include <windows.h>

namespace ConsoleUtils {
    inline void setConsoleColor(int color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }
}

#endif
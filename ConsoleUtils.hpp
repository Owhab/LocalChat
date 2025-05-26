#pragma once

// Cross-platform console colors and formatting
#ifdef _WIN32
#include <windows.h>
#define RESET_COLOR ""
#define RED_COLOR ""
#define GREEN_COLOR ""
#define BLUE_COLOR ""
#define YELLOW_COLOR ""
#define MAGENTA_COLOR ""
#define CYAN_COLOR ""
#define BOLD_TEXT ""
#define ITALIC_TEXT ""
#define UNDERLINE_TEXT ""

// Windows console color initialization function
inline void initConsoleColors()
{
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD mode = 0;
  GetConsoleMode(hConsole, &mode);
  mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(hConsole, mode);
}
#else
// ANSI escape codes for Linux/macOS
#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define BLUE_COLOR "\033[34m"
#define YELLOW_COLOR "\033[33m"
#define MAGENTA_COLOR "\033[35m"
#define CYAN_COLOR "\033[36m"
#define BOLD_TEXT "\033[1m"
#define ITALIC_TEXT "\033[3m"
#define UNDERLINE_TEXT "\033[4m"

// No initialization needed for Linux/macOS
inline void initConsoleColors() {}
#endif

// Message formatting templates
#define FORMAT_SYSTEM_MESSAGE(msg) YELLOW_COLOR BOLD_TEXT "[SYSTEM] " RESET_COLOR YELLOW_COLOR + std::string(msg) + RESET_COLOR
#define FORMAT_USER_JOIN(user) GREEN_COLOR "[" + std::string(user) + " joined the chat]" RESET_COLOR
#define FORMAT_USER_LEAVE(user) RED_COLOR "[" + std::string(user) + " left the chat]" RESET_COLOR
#define FORMAT_SENT_MESSAGE(user, msg) CYAN_COLOR BOLD_TEXT "[You] " RESET_COLOR + std::string(msg)
#define FORMAT_RECEIVED_MESSAGE(user, msg) MAGENTA_COLOR BOLD_TEXT "[" + std::string(user) + "] " RESET_COLOR + std::string(msg)
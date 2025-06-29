#pragma once
#include <string>
#include <unordered_map>
#include <vector>

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
#define WHITE_COLOR ""
#define BRIGHT_RED_COLOR ""
#define BRIGHT_GREEN_COLOR ""
#define BRIGHT_BLUE_COLOR ""
#define BRIGHT_YELLOW_COLOR ""
#define BRIGHT_MAGENTA_COLOR ""
#define BRIGHT_CYAN_COLOR ""
#define BRIGHT_WHITE_COLOR ""
#define BOLD_TEXT ""
#define ITALIC_TEXT ""
#define UNDERLINE_TEXT ""
#define DIM_TEXT ""

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
#define WHITE_COLOR "\033[37m"
#define BRIGHT_RED_COLOR "\033[91m"
#define BRIGHT_GREEN_COLOR "\033[92m"
#define BRIGHT_BLUE_COLOR "\033[94m"
#define BRIGHT_YELLOW_COLOR "\033[93m"
#define BRIGHT_MAGENTA_COLOR "\033[95m"
#define BRIGHT_CYAN_COLOR "\033[96m"
#define BRIGHT_WHITE_COLOR "\033[97m"
#define BOLD_TEXT "\033[1m"
#define ITALIC_TEXT "\033[3m"
#define UNDERLINE_TEXT "\033[4m"
#define DIM_TEXT "\033[2m"

// No initialization needed for Linux/macOS
inline void initConsoleColors() {}
#endif

// Border characters and styles
#define TOP_LEFT_CORNER "┌"
#define TOP_RIGHT_CORNER "┐"
#define BOTTOM_LEFT_CORNER "└"
#define BOTTOM_RIGHT_CORNER "┘"
#define HORIZONTAL_LINE "─"
#define VERTICAL_LINE "│"
#define BORDER_PADDING "  "

// User color assignment system using static local variables to avoid multiple definition
inline std::string getUserColor(const std::string &username)
{
  static std::unordered_map<std::string, std::string> userColors;
  static std::vector<std::string> colorPalette = {
      // Extended diverse color palette with 256-color ANSI codes
      "\033[38;5;208m", // Bright orange
      "\033[38;5;129m", // Purple
      "\033[38;5;213m", // Pink
      "\033[38;5;154m", // Lime green
      "\033[38;5;80m",  // Teal
      "\033[38;5;99m",  // Indigo
      "\033[38;5;203m", // Coral
      "\033[38;5;220m", // Gold
      "\033[38;5;177m", // Violet
      "\033[38;5;86m",  // Turquoise
      "\033[38;5;209m", // Salmon
      "\033[38;5;46m",  // Emerald
      "\033[38;5;196m", // Ruby red
      "\033[38;5;33m",  // Sapphire blue
      "\033[38;5;214m", // Amber
      "\033[38;5;160m", // Crimson
      "\033[38;5;22m",  // Forest green
      "\033[38;5;201m", // Hot pink
      "\033[38;5;51m",  // Cyan blue
      "\033[38;5;226m", // Bright yellow
      "\033[38;5;165m", // Magenta pink
      "\033[38;5;39m",  // Sky blue
      "\033[38;5;202m", // Orange red
      "\033[38;5;118m", // Spring green
      "\033[38;5;207m", // Bright magenta
      "\033[38;5;87m",  // Light cyan
      "\033[38;5;228m", // Khaki
      "\033[38;5;171m", // Orchid
      "\033[38;5;75m",  // Steel blue
      "\033[38;5;215m"  // Light orange
  };
  static size_t colorIndex = 0;

  if (userColors.find(username) == userColors.end())
  {
    userColors[username] = colorPalette[colorIndex % colorPalette.size()];
    colorIndex++;
  }
  return userColors[username];
}

// Helper function to create bordered messages
inline std::string createBorderedMessage(const std::string &username, const std::string &message, const std::string &borderColor)
{
  std::string result = "";
  std::string content = username + ": " + message;
  size_t contentLength = content.length();
  size_t boxWidth = std::max(contentLength + 4, static_cast<size_t>(20)); // Minimum width of 20

  // Top border
  result += borderColor + std::string(TOP_LEFT_CORNER);
  for (size_t i = 0; i < boxWidth; ++i)
  {
    result += std::string(HORIZONTAL_LINE);
  }
  result += std::string(TOP_RIGHT_CORNER) + std::string(RESET_COLOR) + "\n";

  // Content with side borders
  result += borderColor + std::string(VERTICAL_LINE) + std::string(RESET_COLOR) + std::string(BORDER_PADDING);
  result += borderColor + std::string(BOLD_TEXT) + username + std::string(RESET_COLOR) + ": " + message;

  // Add padding to reach box width
  size_t paddingNeeded = boxWidth - contentLength - 2;
  for (size_t i = 0; i < paddingNeeded; ++i)
  {
    result += " ";
  }
  result += borderColor + std::string(VERTICAL_LINE) + std::string(RESET_COLOR) + "\n";

  // Bottom border
  result += borderColor + std::string(BOTTOM_LEFT_CORNER);
  for (size_t i = 0; i < boxWidth; ++i)
  {
    result += std::string(HORIZONTAL_LINE);
  }
  result += std::string(BOTTOM_RIGHT_CORNER) + std::string(RESET_COLOR);

  return result;
}

// Enhanced message formatting functions
inline std::string formatSystemMessage(const std::string &msg)
{
  std::string result = std::string(YELLOW_COLOR) + "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" + std::string(RESET_COLOR) + "\n";
  result += std::string(YELLOW_COLOR) + "┃" + std::string(RESET_COLOR) + std::string(BOLD_TEXT) + "  [SYSTEM] " + std::string(RESET_COLOR) + msg;

  size_t padding = 35;
  if (msg.length() < padding)
  {
    result += std::string(padding - msg.length(), ' ');
  }
  result += std::string(YELLOW_COLOR) + "┃" + std::string(RESET_COLOR) + "\n";
  result += std::string(YELLOW_COLOR) + "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" + std::string(RESET_COLOR);

  return result;
}

inline std::string formatUserJoin(const std::string &user)
{
  std::string result = std::string(BRIGHT_GREEN_COLOR) + "╔══════════════════════════════════════════╗" + std::string(RESET_COLOR) + "\n";
  result += std::string(BRIGHT_GREEN_COLOR) + "║" + std::string(RESET_COLOR) + "  🎉 " + std::string(BOLD_TEXT) + user + " joined the chat!" + std::string(RESET_COLOR);

  size_t padding = 32;
  if (user.length() < padding)
  {
    result += std::string(padding - user.length(), ' ');
  }
  result += std::string(BRIGHT_GREEN_COLOR) + "║" + std::string(RESET_COLOR) + "\n";
  result += std::string(BRIGHT_GREEN_COLOR) + "╚══════════════════════════════════════════╝" + std::string(RESET_COLOR);

  return result;
}

inline std::string formatUserLeave(const std::string &user)
{
  std::string result = std::string(BRIGHT_RED_COLOR) + "╔══════════════════════════════════════════╗" + std::string(RESET_COLOR) + "\n";
  result += std::string(BRIGHT_RED_COLOR) + "║" + std::string(RESET_COLOR) + "  👋 " + std::string(BOLD_TEXT) + user + " left the chat" + std::string(RESET_COLOR);

  size_t padding = 33;
  if (user.length() < padding)
  {
    result += std::string(padding - user.length(), ' ');
  }
  result += std::string(BRIGHT_RED_COLOR) + "║" + std::string(RESET_COLOR) + "\n";
  result += std::string(BRIGHT_RED_COLOR) + "╚══════════════════════════════════════════╝" + std::string(RESET_COLOR);

  return result;
}

// Updated macros using the functions
#define FORMAT_SYSTEM_MESSAGE(msg) formatSystemMessage(msg)
#define FORMAT_USER_JOIN(user) formatUserJoin(user)
#define FORMAT_USER_LEAVE(user) formatUserLeave(user)
#define FORMAT_SENT_MESSAGE(user, msg) createBorderedMessage("You", msg, std::string(BRIGHT_CYAN_COLOR))

// Function to format received messages with user-specific colors
inline std::string formatReceivedMessage(const std::string &username, const std::string &message)
{
  std::string userColor = getUserColor(username);
  return createBorderedMessage(username, message, userColor);
}

// Utility function to print a separator line
inline std::string createSeparator()
{
  return std::string(DIM_TEXT) + "─────────────────────────────────────────────────" + std::string(RESET_COLOR);
}
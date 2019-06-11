#ifndef __TGLOBAL_HPP__
#define __TGLOBAL_HPP__

#include <string>
#include <queue>

/**
 * Colors
 */
enum Color {
	COLOR_BLACK = 0, COLOR_BLUE = 1, COLOR_GREEN = 2, COLOR_AQUA = 3,
	COLOR_RED = 4, COLOR_PURPLE = 5, COLOR_YELLOW = 6, COLOR_DEFAULT = 7, COLOR_GRAY = 8,
	COLOR_LIGHT_BLUE = 9, COLOR_LIGHT_GREEN = 10, COLOR_LIGHT_AQUA = 11,
	COLOR_LIGHT_RED = 12, COLOR_LIGHT_PURPLE = 13, COLOR_LIGHT_YELLOW = 14, COLOR_BRIGHT_WHITE = 15
};

void Log(std::string);
void Logerr(std::string);
void NextLine(int lines = 1);

void SetColor(Color color);

/**
 * Utility..
 */
void ClearMessageQueue(std::queue<std::string> &messageQueue);

#endif  // __TGLOBAL_HPP__
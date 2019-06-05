#ifndef __TGLOBAL_HPP__
#define __TGLOBAL_HPP__

#include <string>
#include <queue>

void Display(std::string val);

void Display(long val);

void Display(double val);

void Display(int val);

void Display(float val);

void NewLine(void);

/**
 * Colors
 */
const int COLOR_DEFAULT = 7;
const int COLOR_RED = 12;

void SetColor(int color);

/**
 * Utility..
 */
void ClearMessageQueue(std::queue<std::string> &messageQueue);

#endif  // __TGLOBAL_HPP__
#include "../kernel/include/Tglobal.h"

void ClearMessageQueue(std::queue<std::string> &messageQueue) {
	std::queue<std::string> emptyQueue;
	std::swap(messageQueue, emptyQueue);
}
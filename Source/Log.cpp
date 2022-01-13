#include "Log.h"

void Pong::Log::Print(const char* stringToPrint)
{
#if _DEBUG
	std::cout << stringToPrint << std::endl;
#elif NDEBUG
	//Log to file.
#endif
}
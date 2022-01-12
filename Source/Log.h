#ifndef LOG_H
#define LOG_H

#include <iostream>

namespace Pong
{
	class Log
	{
	public:
		//End line is already added inside the function.
		static void Print(const char* stringToPrint);
	};
}
#endif
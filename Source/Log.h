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

		//Log should not be cloneable.
		Log(Log& other) = delete;
		//Log should not be assignable.
		void operator=(const Log&) = delete;
	private:
		Log() = default;
		~Log() = default;
	};
}
#endif
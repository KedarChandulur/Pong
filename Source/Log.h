#ifndef LOG_H
#define LOG_H

#include <iostream>

namespace Pong
{
	/// <summary>
	/// Base Log struct.
	/// </summary>
	struct Log
	{
	public:
		//End line is already added inside the function.
		static void Print(const char* stringToPrint);

		Log(Log& other) = delete;
		void operator=(const Log&) = delete;
	private:
		Log() = default;
		~Log() = default;
	};
}
#endif
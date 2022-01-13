#ifndef LOG_H
#define LOG_H

#include <iostream>

namespace Pong
{
	/// <summary>
	/// Base Log struct. This struct is not allowed to be instantiated.
	/// </summary>
	struct Log
	{
	public:
		//End line is already added inside the function.
		static void Print(const char* stringToPrint);

		//Guard: Preventing Log struct to be cloneable.
		Log(Log& other) = delete;
		//Guard: Preventing Log to be assignable.
		void operator=(const Log&) = delete;
	private:
		Log() = default;
		~Log() = default;
	};
}
#endif
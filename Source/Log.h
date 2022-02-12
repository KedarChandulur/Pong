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
		template<typename T>
		static void Print(const T& log)
		{
#if _DEBUG
			std::cout << log << std::endl;
#elif NDEBUG
			//Log to file.
#endif
		}

		template<typename T>
		static void Print(const T* log)
		{
#if _DEBUG
			std::cout << log << std::endl;
#elif NDEBUG
			//Log to file.
#endif
		}

		template<typename T>
		static void Print(T& log)
		{
#if _DEBUG
			std::cout << log << std::endl;
#elif NDEBUG
			//Log to file.
#endif
		}

		template<typename T>
		static void Print(T* log)
		{
#if _DEBUG
			std::cout << log << std::endl;
#elif NDEBUG
			//Log to file.
#endif
		}

		Log(Log& other) = delete;
		void operator=(const Log&) = delete;
	private:
		Log() = default;
		~Log() = default;
	};
}
#endif
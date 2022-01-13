#ifndef MATH_H
#define MATH_H

namespace Pong
{
	/// <summary>
	/// Base Math class. This class is not allowed to be instantiated.
	/// </summary>
	class Math
	{
	public:
		static const float& Lerp(const float& a, const float& b, const float& t);
		static const float& Naive_Lerp(const float& a, const float& b, const float& t);

		//Guard: Preventing Math class to be cloneable.
		Math(Math& other) = delete;
		//Guard: Preventing Math to be assignable.
		void operator=(const Math&) = delete;
	private:
		Math() = default;
		~Math() = default;
	};
}
#endif
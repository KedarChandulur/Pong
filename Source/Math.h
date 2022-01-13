#ifndef MATH_H
#define MATH_H

namespace Pong
{
	/// <summary>
	/// Base Math struct. This struct is not allowed to be instantiated.
	/// </summary>
	struct Math
	{
	public:
		static const float& Lerp(const float& a, const float& b, const float& t);
		static const float& Naive_Lerp(const float& a, const float& b, const float& t);

		//Guard: Preventing Math struct to be cloneable.
		Math(Math& other) = delete;
		//Guard: Preventing Math to be assignable.
		void operator=(const Math&) = delete;
	private:
		Math() = default;
		~Math() = default;
	};
}
#endif
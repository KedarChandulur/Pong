#ifndef MATH_H
#define MATH_H

namespace Pong
{
	/// <summary>
	/// Base Math struct.
	/// </summary>
	struct Math
	{
	public:
		static float Lerp(const float& a, const float& b, const float& t);
		static float Naive_Lerp(const float& a, const float& b, const float& t);

		Math(Math& other) = delete;
		void operator=(const Math&) = delete;
	private:
		Math() = default;
		~Math() = default;
	};
}
#endif
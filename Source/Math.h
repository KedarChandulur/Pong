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
		template<typename T>
		static T Lerp(T a, T b, float t)
		{
			return (a * (1.0f - t)) + (b * t);
		}

		template<typename T>
		static T Lerp_ThroughReference(const T& a, const T& b, float& t)
		{
			return (a * (1.0f - t)) + (b * t);
		}

		Math(Math& other) = delete;
		void operator=(const Math&) = delete;
	private:
		Math() = default;
		~Math() = default;
	};
}
#endif
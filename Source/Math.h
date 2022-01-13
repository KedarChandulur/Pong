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
		static float Lerp(float a, float b, float t);
		//Takes variables as const  references
		static float Lerp_ThroughReference(const float& a, const float& b, const float& t);

		Math(Math& other) = delete;
		void operator=(const Math&) = delete;
	private:
		Math() = default;
		~Math() = default;
	};
}
#endif
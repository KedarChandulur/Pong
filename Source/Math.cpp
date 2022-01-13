#include "Math.h"

float Pong::Math::Lerp(const float& a, const float& b, const float& t)
{
	return (a * (1.0f - t)) + (b * t);
}

float Pong::Math::Naive_Lerp(const float& a, const float& b, const float& t)
{
	return a + t * (b - a);
}
#include "Math.h"

float Pong::Math::Lerp(float a, float b, float t)
{
	return (a * (1.0f - t)) + (b * t);
}

float Pong::Math::Lerp_ThroughReference(const float& a, const float& b, const float& t)
{
	return (a * (1.0f - t)) + (b * t);
}
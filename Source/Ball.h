#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball
{
public:
	void Init(const float& width, const float& height, const float& pi);
	void Update(const sf::VideoMode& videoMode, const float& deltaTime);
	sf::CircleShape mainCircleShape;
private:
	//Used for determining ball's move direction(based on angle)
	float ballAngle = 0.0f;
	float ballRadius;
};
#endif
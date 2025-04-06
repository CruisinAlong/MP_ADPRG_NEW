#pragma once
#include <SFML\Graphics.hpp>

class Animation
{

public:

	Animation(sf::Texture* tex, sf::Vector2u frameCount, float switchTime);
	~Animation();


	//Will house the frame currently seen
	sf::IntRect frameRect;

	void Update(int row, float deltaTime);

private:

	sf::Vector2u frameCount;

	sf::Vector2u currentFrame;

	float time;
	float switchTime;

};


#include "Animation.h"


Animation::Animation(sf::Texture* tex, sf::Vector2u frameCount, float switchTime) {

	this->frameCount = frameCount;

	this->switchTime = switchTime;

	time = 0;

	currentFrame.x = 0;

	//To automatically set size of sprite based on details of spritesheet
	frameRect.width = tex->getSize().x / float(frameCount.x);
	frameRect.height = tex->getSize().y / float(frameCount.y);

}

Animation::~Animation() {



}

void Animation::Update(int row, float deltaTime) {

	currentFrame.y = row;

	time += deltaTime;

	//Looping time and animations
	if (time >= switchTime) {

		time -= switchTime;
		currentFrame.x++;

		if (currentFrame.x >= frameCount.x) {

			currentFrame.x = 0;

		}

	}

	frameRect.left = currentFrame.x * frameRect.width;
	frameRect.top = currentFrame.y * frameRect.height;

}
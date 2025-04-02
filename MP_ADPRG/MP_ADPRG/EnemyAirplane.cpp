#include "EnemyAirplane.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "EnemyBehavior.h"


EnemyAirplane::EnemyAirplane(std::string name) : AbstractPoolable(name), CollisionListener() {

}

EnemyAirplane::~EnemyAirplane() {
	delete this->sprite;
}

void EnemyAirplane::initialize() {
	this->sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("avenger"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	this->setPosition(Game::WINDOW_WIDTH - static_cast<int>(textureSize.x) / 2, Game::WINDOW_HEIGHT / 2 - static_cast<int>(textureSize.y) / 2);
	this->getTransformable()->move(rand() % SPAWN_RANGE, 0);
	this->getTransformable()->setRotation(270);

	Renderer* renderer = new Renderer("EnemySprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	EnemyBehavior* behavior = new EnemyBehavior("EnemyBehavior");
	this->attachComponent(behavior);
	behavior->configure(EnemyBehavior::SlowForward, 1.0f);



	this->collider = new Collider("EnemyCollider");
	this->collider->setLocalBounds(sprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);

	std::cout << "BOUNDS: " << sprite->getGlobalBounds().left << ":" << sprite->getGlobalBounds().top << ":" << sprite->getGlobalBounds().width << ":" << sprite->getGlobalBounds().height << std::endl;
}

void EnemyAirplane::onRelease() {
	PhysicsManager::getInstance()->untrackObject(this->collider);
}
void EnemyAirplane::onActivate() {
	EnemyBehavior* behaviour = (EnemyBehavior*)this->findComponentByName("EnemyBehavior");
	behaviour->reset();

	PhysicsManager::getInstance()->trackObject(this->collider);

	this->setPosition(Game::WINDOW_WIDTH - static_cast<int>(sprite->getTexture()->getSize().x) / 2, Game::WINDOW_HEIGHT / 2 - static_cast<int>(sprite->getTexture()->getSize().y) / 2);
	this->getTransformable()->move(rand() % SPAWN_RANGE - rand() % SPAWN_RANGE, 50);
}
AbstractPoolable* EnemyAirplane::clone() {
	AbstractPoolable* copyObj = new EnemyAirplane(this->name);
	return copyObj;
}

void EnemyAirplane::onCollisionEnter(AbstractGameObject* contact) {

	return;
	if (contact->getName().find("PlaneObject") != std::string::npos) {
		GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);
		enemyPool->releasePoolable((AbstractPoolable*)this);
		std::cout << "EnemyAirplane collided with PlaneObject" << std::endl;
	}
}

void EnemyAirplane::onCollisionExit(AbstractGameObject* gameObject) {

}
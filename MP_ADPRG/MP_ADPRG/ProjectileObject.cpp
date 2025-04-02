#include "ProjectileObject.h"

ProjectileObject::ProjectileObject(std::string name) : AbstractPoolable(name), CollisionListener(){


}
void ProjectileObject::initialize(){
	this->sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("bullet"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("EnemySprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	this->projectileMovement = new ProjectileMovement("projectile_movement");
	this->attachComponent(projectileMovement);

	this->collider = new Collider("EnemyCollider");

	collider->setLocalBounds(sprite->getGlobalBounds());
	collider->setCollisionListener(this);
	this->attachComponent(collider);

	std::cout << "BOUNDS: " << sprite->getGlobalBounds().left << ":" << sprite->getGlobalBounds().top << ":" << sprite->getGlobalBounds().width << ":" << sprite->getGlobalBounds().height << std::endl;
	PhysicsManager::initialize("PhysicsManager", this);
}
void ProjectileObject::onRelease(){
	PhysicsManager::getInstance()->untrackObject(this->collider);
}
void ProjectileObject::onActivate(){
	AirplanePlayer* player = (AirplanePlayer*)GameObjectManager::getInstance()->findObjectByName("PlaneObject");
}

AbstractPoolable* ProjectileObject::clone(){
	AbstractPoolable* copyObj = new ProjectileObject(this->name);
	return copyObj;
}

void ProjectileObject::onCollisionEnter(AbstractGameObject* contact){
	if (contact->getName().find("enemy") != std::string::npos && !this->hasHit) {
		this->hasHit = true;
		GameObjectPool* projectilePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECTILE_POOL_TAG);
		projectilePool->releasePoolable((AbstractPoolable*)this);
		std::cout << "HIT" << std::endl;
	}
}
void ProjectileObject::onCollisionExit(AbstractGameObject* contact){
}
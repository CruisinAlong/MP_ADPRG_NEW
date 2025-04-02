#include "ProjectileMovement.h"
#include "AbstractGameObject.h"
#include "ObjectPoolHolder.h"
#include "TextureManager.h"



ProjectileMovement::ProjectileMovement(std::string name) : AbstractComponent(name, Script) {

}
void ProjectileMovement::perform() {
	sf::Transformable* transform = this->getOwner()->getTransformable();
	transform->move(0, -this->deltaTime.asSeconds() * SPEED_MULTIPLIER);
	this->ticks += this->deltaTime.asSeconds();

	if (this->ticks >  3.0f){
		reset();
		ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECTILE_POOL_TAG)->releasePoolable((AbstractPoolable*)this->getOwner());
	}
}
void ProjectileMovement::reset() {
	this->ticks = 0.0f;
}
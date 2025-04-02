#pragma once
#include "AbstractGameObject.h"
#include "AbstractPoolable.h"
#include "ProjectileMovement.h"
#include "PhysicsManager.h"
#include "CollisionListener.h"
#include "TextureManager.h"
#include "AirplanePlayer.h"
#include "GameObjectManager.h"
#include <string>
#include "Renderer.h"
#include "ObjectPoolHolder.h"


class ProjectileObject : public AbstractPoolable, public CollisionListener {
public:
	ProjectileObject(std::string name);
	void initialize();
	void onRelease();
	void onActivate();
	AbstractPoolable* clone();

	void onCollisionEnter(AbstractGameObject* contact);
	void onCollisionExit(AbstractGameObject* contact);

private:
	ProjectileMovement* projectileMovement = nullptr;
	Collider* collider = nullptr;
	bool hasHit = false;
};
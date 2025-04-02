#pragma once
#include "AbstractGameObject.h"

class CollisionListener {
public:
	virtual void onCollisionEnter(AbstractGameObject* gameObjects) = 0;
	virtual void onCollisionExit(AbstractGameObject* gameObjects) = 0;

protected:
	CollisionListener() {}
};
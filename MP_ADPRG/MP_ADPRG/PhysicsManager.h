#pragma once
#include "AbstractComponent.h"
#include "AbstractGameObject.h"
#include <unordered_map>
#include <vector>
#include "Collider.h"

typedef std::vector<Collider*> CollisionList;

class PhysicsManager : public AbstractComponent
{
public:
	static void initialize(std::string name, AbstractGameObject* parent);
	static PhysicsManager* getInstance();

	void trackObject(Collider* object);
	void untrackObject(Collider* object);
	void perform();
	void printTrackedObjects(); 
private:
	PhysicsManager(std::string name) : AbstractComponent(name, Script) {};
	PhysicsManager(PhysicsManager const&) : AbstractComponent(name, Script) {};
	PhysicsManager& operator = (PhysicsManager const&) {};
	static PhysicsManager* sharedInstance;

	CollisionList trackedObjects;
	CollisionList forCleaningObjects;

	void CleanUpObjects();
};
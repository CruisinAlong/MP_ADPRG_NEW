#include "EnemyGroundUnit.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "EnemyBehavior.h"

EnemyGroundUnit::EnemyGroundUnit(std::string name) : AbstractPoolable(name), CollisionListener() {
}

EnemyGroundUnit::~EnemyGroundUnit() {
    delete this->sprite;
}

void EnemyGroundUnit::initialize() {
    this->sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("avenger"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

    this->setPosition(Game::WINDOW_WIDTH + static_cast<int>(textureSize.x) / 2, Game::WINDOW_HEIGHT - static_cast<int>(textureSize.y) / 2);
    this->getTransformable()->move(rand() % SPAWN_RANGE - rand() % SPAWN_RANGE, 0);
    this->getTransformable()->setRotation(0);

    Renderer* renderer = new Renderer("EnemySprite");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);


    EnemyBehavior* behavior = new EnemyBehavior("EnemyBehavior");
    this->attachComponent(behavior);
    behavior->configure(EnemyBehavior::Static);
    EnemyInputController* inputController = new EnemyInputController("EnemyInputController");
    this->attachComponent(inputController);

    this->collider = new Collider("GroundCollider");
    this->collider->setLocalBounds(sprite->getGlobalBounds());
    this->collider->setCollisionListener(this);
    this->attachComponent(this->collider);

	behavior->setInputController(inputController);
    std::cout << "BOUNDS: " << sprite->getGlobalBounds().left << ":" << sprite->getGlobalBounds().top << ":" << sprite->getGlobalBounds().width << ":" << sprite->getGlobalBounds().height << std::endl;
}

void EnemyGroundUnit::onRelease() {
    PhysicsManager::getInstance()->untrackObject(this->collider);
}

void EnemyGroundUnit::onActivate() {
    EnemyBehavior* behaviour = (EnemyBehavior*)this->findComponentByName("EnemyBehavior");
    behaviour->reset();

    PhysicsManager::getInstance()->trackObject(this->collider);

    this->setPosition(Game::WINDOW_WIDTH + static_cast<int>(sprite->getTexture()->getSize().x) / 2, Game::WINDOW_HEIGHT - static_cast<int>(sprite->getTexture()->getSize().y) / 2);
    this->getTransformable()->move(rand() % SPAWN_RANGE - rand() % SPAWN_RANGE, 0);
}

AbstractPoolable* EnemyGroundUnit::clone() {
    AbstractPoolable* copyObj = new EnemyGroundUnit(this->name);
    return copyObj;
}

void EnemyGroundUnit::onCollisionEnter(AbstractGameObject* contact) {
    return;
    if (contact->getName().find("PlaneObject") != std::string::npos) {
        GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);
        enemyPool->releasePoolable((AbstractPoolable*)this);
		std::cout << "Ground Unit collided with PlaneObject" << std::endl;
    }
}

void EnemyGroundUnit::onCollisionExit(AbstractGameObject* gameObject) {
}

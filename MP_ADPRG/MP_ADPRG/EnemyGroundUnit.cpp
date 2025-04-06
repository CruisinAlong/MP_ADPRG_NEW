#include "EnemyGroundUnit.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "EnemyBehavior.h"

EnemyGroundUnit::EnemyGroundUnit(std::string name) : AbstractPoolable(name), CollisionListener() {
}

void EnemyGroundUnit::initialize() {
    this->sprite = new sf::Sprite();
   sprite->setTexture(*TextureManager::getInstance()->getTexture("pot"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

    this->setPosition(Game::WINDOW_WIDTH + static_cast<int>(textureSize.x) / 2, Game::WINDOW_HEIGHT - static_cast<int>(textureSize.y) / 2);
    this->getTransformable()->move(rand() % SPAWN_RANGE, 0);
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
}

AbstractPoolable* EnemyGroundUnit::clone() {
    AbstractPoolable* copyObj = new EnemyGroundUnit(this->name);
    return copyObj;
}

void EnemyGroundUnit::update(sf::Time deltaTime) {
    AbstractGameObject::update(deltaTime);
}
/// <summary>
/// Deducts score on collision.
/// </summary>
/// <param name="contact"></param>
void EnemyGroundUnit::onCollisionEnter(AbstractGameObject* contact) {
	std::cout << "collisionProcessed: " << collisionProcessed << std::endl;
    if (!collisionProcessed && contact->getName().find("PlaneObject") != std::string::npos) {
        collisionProcessed = true;
        std::cout << "Ground Unit collided with PlaneObject" << std::endl;
        UIData* scoreData = UIManager::getInstance()->getUIData(UIManager::SCORE_UI_KEY);
        scoreData->putInt(UIManager::SCORE_UI_KEY, scoreData->getInt(UIManager::SCORE_UI_KEY, 0) - 100);
        scoreData->refreshTextFromData("scoreText", UIManager::SCORE_UI_KEY, "Score: ");
    }
}

void EnemyGroundUnit::onCollisionExit(AbstractGameObject* gameObject) {
    collisionProcessed = false; 
}


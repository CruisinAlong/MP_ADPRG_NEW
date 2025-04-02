#include "AbstractPoolable.h"
#include <string>

AbstractPoolable::AbstractPoolable(std::string name) : AbstractGameObject(name) {
}

sf::Vector2f AbstractPoolable::getPosition() {
    return this->transformable.getPosition();
}
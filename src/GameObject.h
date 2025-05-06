#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class GameObject {
public:
    sf::CircleShape shape;
    b2Body* body = nullptr;

    virtual void update(float dt);
    virtual void createPhysics(b2World& world) = 0;
    virtual ~GameObject() = default;
};

#pragma once
#include "GameObject.h"
#include "constants.h"

class Ball : public GameObject {
public:
    Ball(const sf::Vector2f& position);
    void update(float dt) override;
    void createPhysics(b2World& world) override;
};

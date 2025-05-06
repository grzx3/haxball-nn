#pragma once
#include "GameObject.h"
#include "constants.h"

class Player : public GameObject {
public:
    Player(const sf::Vector2f& position, const sf::Color& color);
    void handleInput(bool up, bool down, bool left, bool right, float dt);
    void update(float dt) override;
    void createPhysics(b2World& world) override;
};

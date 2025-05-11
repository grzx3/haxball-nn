#pragma once
#include "GameObject.h"
#include "constants.h"
#include "Ball.h"

class Player : public GameObject {
public:
    Player(const sf::Vector2f& position, const sf::Color& color, Team team);
    void handleInput(bool up, bool down, bool left, bool right, float dt);
    void update(float dt) override;
    void createPhysics(b2World& world) override;
    void shoot(Ball& ball);

    Team team;

};

#pragma once
#include "GameObject.h"
#include "constants.h"

class GoalPost : public GameObject {
public:
    GoalPost(const sf::Vector2f& position, const sf::Color& color);
    void createPhysics(b2World& world) override;
};

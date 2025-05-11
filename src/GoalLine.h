#pragma once
#include <box2d/box2d.h>
#include "constants.h"

class GoalLine {
public:
    Team ownerTeam;
    b2Body* body = nullptr;

    GoalLine(b2World& world, const b2Vec2& position, float height, Team team);
};

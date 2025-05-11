#include "ContactListener.h"
#include "constants.h"

void ContactListener::BeginContact(b2Contact* contact) {
    b2Fixture* fixA = contact->GetFixtureA();
    b2Fixture* fixB = contact->GetFixtureB();

    b2Body* bodyA = fixA->GetBody();
    b2Body* bodyB = fixB->GetBody();

    auto ptrA = bodyA->GetUserData().pointer;
    auto ptrB = bodyB->GetUserData().pointer;

    GoalLine* goal = nullptr;
    Ball* ball = nullptr;

    if (auto g = reinterpret_cast<GoalLine*>(ptrA); g && fixA->IsSensor())
        goal = g;
    if (auto g = reinterpret_cast<GoalLine*>(ptrB); g && fixB->IsSensor())
        goal = g;

    if (auto b = reinterpret_cast<Ball*>(ptrA))
        ball = b;
    if (auto b = reinterpret_cast<Ball*>(ptrB))
        ball = b;

    if (goal && ball) {
        if (goal->ownerTeam == Team::Blue)
            ++scoreRed;
        else
            ++scoreBlue;
        ball->markedForReset = true;
    }
}

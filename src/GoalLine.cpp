#include "GoalLine.h"

GoalLine::GoalLine(b2World& world, const b2Vec2& position, float height, Team team)
        : ownerTeam(team)
{
    b2BodyDef bd;
    bd.type = b2_staticBody;
    bd.position = position;

    body = world.CreateBody(&bd);

    b2PolygonShape shape;
    shape.SetAsBox(0.01f, height / 2.f);

    b2FixtureDef fd;
    fd.shape = &shape;
    fd.isSensor = true;
    fd.filter.categoryBits = CATEGORY_GOALPOST;
    fd.filter.maskBits = CATEGORY_BALL;

    body->CreateFixture(&fd);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

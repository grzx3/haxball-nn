#include "GoalPost.h"

GoalPost::GoalPost(const sf::Vector2f& position, const sf::Color& color) {
    shape.setRadius(GOAL_RADIUS);
    shape.setOrigin(GOAL_RADIUS, GOAL_RADIUS);
    shape.setFillColor(color);
    shape.setPosition(position);
}

void GoalPost::createPhysics(b2World& world) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(shape.getPosition().x / 100.f, shape.getPosition().y / 100.f);
    bodyDef.type = b2_staticBody;

    body = world.CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius = GOAL_RADIUS / 100.f;

    b2FixtureDef fixture;
    fixture.shape = &circle;
    fixture.density = 0.f;
    fixture.restitution = 0.5f;
    fixture.friction = 0.5f;

    body->CreateFixture(&fixture);
}

#include "Ball.h"

Ball::Ball(const sf::Vector2f& position) {
    shape.setRadius(BALL_RADIUS);
    shape.setOrigin(BALL_RADIUS, BALL_RADIUS);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(position);
}

void Ball::createPhysics(b2World& world) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(shape.getPosition().x / 100.f, shape.getPosition().y / 100.f);
    bodyDef.type = b2_dynamicBody;

    body = world.CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius = BALL_RADIUS / 100.f;

    b2FixtureDef fixture;
    fixture.shape = &circle;
    fixture.density = 1.f;
    fixture.restitution = 0.5f;  //bouncy
    fixture.friction = 0.2f;
    fixture.filter.categoryBits = CATEGORY_BALL;
    fixture.filter.maskBits = CATEGORY_PLAYER | CATEGORY_PITCH_BALL | CATEGORY_GOALPOST;
    body->CreateFixture(&fixture);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

void Ball::update(float dt) {
    if (body) {
        b2Vec2 velocity = body->GetLinearVelocity();
        const float drag = 0.02f;

        b2Vec2 friction = -drag * velocity;
        body->ApplyForceToCenter(friction, true);
    }
    if (body->GetLinearVelocity().Length() < 0.01f)
        body->SetLinearVelocity({0.f, 0.f});

    GameObject::update(dt);
}

void Ball::reset(const sf::Vector2f& position) {
    if (!body) return;
    body->SetLinearVelocity({0.f, 0.f});
    body->SetTransform({position.x / 100.f, position.y / 100.f}, 0.f);
}



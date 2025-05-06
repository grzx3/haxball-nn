#include "Player.h"

Player::Player(const sf::Vector2f& position, const sf::Color& color) {
    shape.setRadius(PLAYER_RADIUS);
    shape.setOrigin(PLAYER_RADIUS, PLAYER_RADIUS);
    shape.setFillColor(color);
    shape.setPosition(position);
}

void Player::createPhysics(b2World& world) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(shape.getPosition().x / 100.f, shape.getPosition().y / 100.f);
    bodyDef.type = b2_dynamicBody;

    body = world.CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius = PLAYER_RADIUS / 100.f;

    b2FixtureDef fixture;
    fixture.shape = &circle;
    fixture.density = 2.f;
    fixture.restitution = 0.5f;
    fixture.friction = 0.6f;

    body->CreateFixture(&fixture);
}

void Player::handleInput(bool up, bool down, bool left, bool right, float dt) {
    b2Vec2 force(0.f, 0.f);

    if (up)    force.y -= PLAYER_SPEED;
    if (down)  force.y += PLAYER_SPEED;
    if (left)  force.x -= PLAYER_SPEED;
    if (right) force.x += PLAYER_SPEED;

    force *= dt;
    body->ApplyForceToCenter(force, true);

    b2Vec2 vel = body->GetLinearVelocity();
    float speed = vel.Length();
    const float maxSpeed = PLAYER_SPEED;
    if (speed > maxSpeed) {
        body->SetLinearVelocity(b2Vec2(
                vel.x * maxSpeed / speed,
                vel.y * maxSpeed / speed
        ));
    }
    const float friction = PLAYER_FRICTION;
    b2Vec2 frictionForce = -friction * vel;
    body->ApplyForceToCenter(frictionForce, true);
}


void Player::update(float dt) {
    GameObject::update(dt);
}


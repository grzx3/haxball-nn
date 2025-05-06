#include "GameObject.h"

void GameObject::update(float dt) {
    if (body) {
        b2Vec2 pos = body->GetPosition();
        float angle = body->GetAngle();
        shape.setPosition(pos.x * 100.f, pos.y * 100.f);
        shape.setRotation(angle * 180.f / b2_pi);
    }
}

#include "Pitch.h"
#include "constants.h"

Pitch::Pitch(const sf::Vector2f& center, float ofst) : offset(ofst) {
    //Pitch outline
    outline.setSize({PITCH_WIDTH, PITCH_HEIGHT});
    outline.setOrigin(PITCH_WIDTH / 2.f, PITCH_HEIGHT / 2.f);
    outline.setPosition(center);
    outline.setOutlineThickness(PITCH_BORDER_THICKNESS);
    outline.setOutlineColor(sf::Color::White);
    outline.setFillColor(sf::Color::Transparent);

    // Goal line visuals
    float x1 = center.x - PITCH_WIDTH / 2.f;
    float x2 = center.x + PITCH_WIDTH / 2.f;

    for (float x : {x1, x2}) {
        sf::RectangleShape line;
        line.setSize({PITCH_BORDER_THICKNESS, GOAL_WIDTH});
        line.setOrigin(PITCH_BORDER_THICKNESS / 2.f, GOAL_WIDTH / 2.f);
        line.setPosition(x, center.y);
        line.setFillColor(sf::Color::Yellow);
        goalLines.push_back(line);
    }
}

void Pitch::createPhysics(b2World& world, const uint16 catBits) {
    // Static borders: top, bottom, left, right (excluding goal area)
    b2BodyDef bd;
    bd.type = b2_staticBody;

    b2PolygonShape wallShape;
    b2FixtureDef fixture;
    fixture.shape = &wallShape;
    fixture.density = 0.f;
    fixture.friction = 0.f;
    fixture.restitution = 0.0f;
    fixture.filter.categoryBits = catBits;
    if (catBits == CATEGORY_PITCH_BALL) {
        fixture.filter.maskBits = CATEGORY_BALL;
    }
    else {
        fixture.filter.maskBits = CATEGORY_PLAYER;
    }

    float halfW = PITCH_WIDTH / 2.f;
    float halfH = PITCH_HEIGHT / 2.f;
    if (catBits == CATEGORY_PITCH_PLAYER) {
        halfW += PLAYER_OUTSIDE_OFFSET;
        halfH += PLAYER_OUTSIDE_OFFSET;
    }
    float wallThick = PITCH_BORDER_THICKNESS;

    auto addWall = [&](sf::Vector2f center, sf::Vector2f size) {
        bd.position.Set(center.x / 100.f, center.y / 100.f);
        wallShape.SetAsBox(size.x / 200.f, size.y / 200.f);
        b2Body* wall = world.CreateBody(&bd);
        wall->CreateFixture(&fixture);
        walls.push_back(wall);
    };

    //Left and Right walls (excluding goal gap)
    addWall({outline.getPosition().x - halfW, outline.getPosition().y - GOAL_WIDTH / 2.f - (halfH - GOAL_WIDTH / 2.f) / 2.f},
            {wallThick, halfH - GOAL_WIDTH / 2.f});
    addWall({outline.getPosition().x - halfW, outline.getPosition().y + GOAL_WIDTH / 2.f + (halfH - GOAL_WIDTH / 2.f) / 2.f},
            {wallThick, halfH - GOAL_WIDTH / 2.f});
    addWall({outline.getPosition().x + halfW, outline.getPosition().y - GOAL_WIDTH / 2.f - (halfH - GOAL_WIDTH / 2.f) / 2.f},
            {wallThick, halfH - GOAL_WIDTH / 2.f});
    addWall({outline.getPosition().x + halfW, outline.getPosition().y + GOAL_WIDTH / 2.f + (halfH - GOAL_WIDTH / 2.f) / 2.f},
            {wallThick, halfH - GOAL_WIDTH / 2.f});

    //walls behind the goal line.
    if (catBits == CATEGORY_PITCH_PLAYER) {
        addWall({outline.getPosition().x - halfW, outline.getPosition().y}, {wallThick, GOAL_WIDTH});
        addWall({outline.getPosition().x + halfW, outline.getPosition().y}, {wallThick, GOAL_WIDTH});
    }
    else {
        addWall({outline.getPosition().x - halfW - PLAYER_OUTSIDE_OFFSET, outline.getPosition().y}, {wallThick, GOAL_WIDTH});
        addWall({outline.getPosition().x + halfW + PLAYER_OUTSIDE_OFFSET, outline.getPosition().y}, {wallThick, GOAL_WIDTH});
        addWall({outline.getPosition().x + PLAYER_OUTSIDE_OFFSET / 2.f + halfW, outline.getPosition().y + GOAL_WIDTH / 2.f},{PLAYER_OUTSIDE_OFFSET, wallThick});
        addWall({outline.getPosition().x + PLAYER_OUTSIDE_OFFSET / 2.f + halfW, outline.getPosition().y - GOAL_WIDTH / 2.f},{PLAYER_OUTSIDE_OFFSET, wallThick});
        addWall({outline.getPosition().x - PLAYER_OUTSIDE_OFFSET / 2.f - halfW, outline.getPosition().y + GOAL_WIDTH / 2.f},{PLAYER_OUTSIDE_OFFSET, wallThick});
        addWall({outline.getPosition().x - PLAYER_OUTSIDE_OFFSET / 2.f - halfW, outline.getPosition().y - GOAL_WIDTH / 2.f},{PLAYER_OUTSIDE_OFFSET, wallThick});
    };

    //Top and bottom walls
    addWall({outline.getPosition().x, outline.getPosition().y - halfH}, {PITCH_WIDTH + 2 * offset, wallThick});
    addWall({outline.getPosition().x, outline.getPosition().y + halfH}, {PITCH_WIDTH, wallThick});
}

void Pitch::draw(sf::RenderWindow& window) {
    window.draw(outline);
    for (auto& line : goalLines)
        window.draw(line);
}
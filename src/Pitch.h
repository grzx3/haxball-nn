#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <vector>

class Pitch {
public:
    Pitch(const sf::Vector2f& center, float offset = 0.0f);
    void createPhysics(b2World& world, const uint16 catBits);
    void draw(sf::RenderWindow& window);
    float offset = 0.f;


private:
    sf::RectangleShape outline;
    std::vector<sf::RectangleShape> goalLines;
    std::vector<b2Body*> walls;
};

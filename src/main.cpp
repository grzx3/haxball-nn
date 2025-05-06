#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Player.h"
#include "Ball.h"
#include "GoalPost.h"
#include "constants.h"

int main() {

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Haxball-nn");
    window.setFramerateLimit(60);

    const sf::Vector2f pitchCenter(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);

    sf::RectangleShape pitchRect;
    pitchRect.setSize({PITCH_WIDTH, PITCH_HEIGHT});
    pitchRect.setOrigin(PITCH_WIDTH / 2.f, PITCH_HEIGHT / 2.f);
    pitchRect.setPosition(pitchCenter);
    pitchRect.setOutlineThickness(PITCH_BORDER_THICKNESS);
    pitchRect.setOutlineColor(sf::Color::White);
    pitchRect.setFillColor(sf::Color::Transparent);

    b2Vec2 gravity(0.f, 0.f);
    b2World world(gravity);

    Player player1({pitchCenter.x - PITCH_WIDTH / 2.f + 100.f, pitchCenter.y}, sf::Color::Blue);
    Player player2({pitchCenter.x + PITCH_WIDTH / 2.f - 100.f, pitchCenter.y}, sf::Color::Red);
    Ball ball(pitchCenter);

    GoalPost goal11({pitchCenter.x - PITCH_WIDTH / 2.f, pitchCenter.y + GOAL_WIDTH / 2.f}, sf::Color::Green);
    GoalPost goal12({pitchCenter.x - PITCH_WIDTH / 2.f, pitchCenter.y - GOAL_WIDTH / 2.f}, sf::Color::Green);
    GoalPost goal21({pitchCenter.x + PITCH_WIDTH / 2.f, pitchCenter.y + GOAL_WIDTH / 2.f}, sf::Color::Green);
    GoalPost goal22({pitchCenter.x + PITCH_WIDTH / 2.f, pitchCenter.y - GOAL_WIDTH / 2.f}, sf::Color::Green);

    std::vector<GameObject*> objects = {&player1, &player2, &ball, &goal11, &goal12, &goal21, &goal22};

    for (auto* obj : objects)
        obj->createPhysics(world);

    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player1.handleInput(
                sf::Keyboard::isKeyPressed(sf::Keyboard::W),
                sf::Keyboard::isKeyPressed(sf::Keyboard::S),
                sf::Keyboard::isKeyPressed(sf::Keyboard::A),
                sf::Keyboard::isKeyPressed(sf::Keyboard::D), dt
        );

        player2.handleInput(
                sf::Keyboard::isKeyPressed(sf::Keyboard::Up),
                sf::Keyboard::isKeyPressed(sf::Keyboard::Down),
                sf::Keyboard::isKeyPressed(sf::Keyboard::Left),
                sf::Keyboard::isKeyPressed(sf::Keyboard::Right), dt
        );

        world.Step(dt, 8, 3);

        for (auto* obj : objects)
            obj->update(dt);

        window.clear(sf::Color::Black);
        window.draw(pitchRect);
        for (auto* obj : objects)
            window.draw(obj->shape);
        window.display();
    }

    return 0;
}

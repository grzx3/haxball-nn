// Game.cpp
#include "Game.h"

Game::Game()
        : window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Haxball-nn"),
          world(b2Vec2(0.f, 0.f)),
          pitch({WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f}),
          playerArea({WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f}, 40.f),
          player1({WINDOW_WIDTH / 2.f - PITCH_WIDTH / 2.f + 100.f, WINDOW_HEIGHT / 2.f}, sf::Color::Blue, Team::Blue),
          player2({WINDOW_WIDTH / 2.f + PITCH_WIDTH / 2.f - 100.f, WINDOW_HEIGHT / 2.f}, sf::Color::Red, Team::Red),
          ball({WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f}),
          goal11({WINDOW_WIDTH / 2.f - PITCH_WIDTH / 2.f, WINDOW_HEIGHT / 2.f + GOAL_WIDTH / 2.f}, sf::Color::Green),
          goal12({WINDOW_WIDTH / 2.f - PITCH_WIDTH / 2.f, WINDOW_HEIGHT / 2.f - GOAL_WIDTH / 2.f}, sf::Color::Green),
          goal21({WINDOW_WIDTH / 2.f + PITCH_WIDTH / 2.f, WINDOW_HEIGHT / 2.f + GOAL_WIDTH / 2.f}, sf::Color::Green),
          goal22({WINDOW_WIDTH / 2.f + PITCH_WIDTH / 2.f, WINDOW_HEIGHT / 2.f - GOAL_WIDTH / 2.f}, sf::Color::Green),
          goalLineLeft(world,
                       b2Vec2((WINDOW_WIDTH / 2.f - PITCH_WIDTH / 2.f) / 100.f, WINDOW_HEIGHT / 2.f / 100.f),
                       GOAL_WIDTH / 100.f,
                       Team::Blue),
          goalLineRight(world,
                        b2Vec2((WINDOW_WIDTH / 2.f + PITCH_WIDTH / 2.f) / 100.f, WINDOW_HEIGHT / 2.f / 100.f),
                        GOAL_WIDTH / 100.f,
                        Team::Red),
          contactListener(scoreBlue, scoreRed)
{
    window.setFramerateLimit(60);

    pitch.createPhysics(world, CATEGORY_PITCH_BALL);
    playerArea.createPhysics(world, CATEGORY_PITCH_PLAYER);

    objects = {&player1, &player2, &ball, &goal11, &goal12, &goal21, &goal22};
    for (auto* obj : objects)
        obj->createPhysics(world);

    world.SetContactListener(&contactListener);

    if (!font.loadFromFile("arial.ttf")) {
        exit(1);
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(20.f, 20.f);
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        handleEvents();
        handleInput(dt);
        update(dt);
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::handleInput(float dt) {
    player1.handleInput(
            sf::Keyboard::isKeyPressed(sf::Keyboard::W),
            sf::Keyboard::isKeyPressed(sf::Keyboard::S),
            sf::Keyboard::isKeyPressed(sf::Keyboard::A),
            sf::Keyboard::isKeyPressed(sf::Keyboard::D), dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        player1.shoot(ball);

    player2.handleInput(
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up),
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down),
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left),
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right), dt);
}

void Game::update(float dt) {
    world.Step(dt, 8, 3);
    for (auto* obj : objects)
        obj->update(dt);

    scoreText.setString(
            "Blue: " + std::to_string(scoreBlue) + "  |  Red: " + std::to_string(scoreRed));

    if (ball.markedForReset) {
        ball.reset({WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f});
        ball.markedForReset = false;
    }
}

void Game::render() {
    window.clear(sf::Color::Black);
    pitch.draw(window);
    for (auto* obj : objects)
        window.draw(obj->shape);
    window.draw(scoreText);
    window.display();
}

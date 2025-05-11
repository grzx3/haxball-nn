#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Player.h"
#include "Ball.h"
#include "GoalPost.h"
#include "constants.h"
#include "Pitch.h"
#include "ContactListener.h"

class Game {
public:
    Game();
    void run();

private:
    void handleEvents();
    void handleInput(float dt);
    void update(float dt);
    void render();

    sf::RenderWindow window;
    b2World world;
    Pitch pitch, playerArea;
    GoalPost goal11, goal12, goal21, goal22;
    GoalLine goalLineLeft;
    GoalLine goalLineRight;
    Player player1, player2;
    Ball ball;
    std::vector<GameObject*> objects;
    ContactListener contactListener;
    sf::Font font;
    sf::Text scoreText;
    int scoreBlue = 0;
    int scoreRed = 0;
    bool resetBallFlag = false;
};

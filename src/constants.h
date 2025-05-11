#pragma once

constexpr unsigned int WINDOW_WIDTH = 1900;
constexpr unsigned int WINDOW_HEIGHT = 1000;

constexpr float PITCH_SCALE = 1.0f;
constexpr float PITCH_WIDTH = 900.f * PITCH_SCALE;
constexpr float PITCH_HEIGHT = 584.f * PITCH_SCALE;
constexpr float GOAL_WIDTH = 180.0f * PITCH_SCALE;
constexpr float PITCH_BORDER_THICKNESS = 1.f;
constexpr float PLAYER_OUTSIDE_OFFSET = 40.f;

constexpr float PLAYER_RADIUS = 20.f;
constexpr float BALL_RADIUS = 8.f;
constexpr float GOAL_RADIUS = 10.f;

constexpr float PLAYER_SPEED = 225.0f;
constexpr float PLAYER_FRICTION = 2.5f;

constexpr uint16 CATEGORY_BALL = 0x0001;
constexpr uint16 CATEGORY_PLAYER = 0x0002;
constexpr uint16 CATEGORY_PITCH_BALL = 0x0004;
constexpr uint16 CATEGORY_PITCH_PLAYER = 0x0008;
constexpr uint16 CATEGORY_GOALPOST = 0x0016;

enum class Team {
    Blue,
    Red
};
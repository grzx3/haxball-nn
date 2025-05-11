#pragma once
#include <box2d/box2d.h>
#include "GoalLine.h"
#include "Ball.h"
#include "constants.h"

class ContactListener : public b2ContactListener {
public:
    int& scoreBlue;
    int& scoreRed;

    ContactListener(int& blue, int& red)
            : scoreBlue(blue), scoreRed(red) {}

    void BeginContact(b2Contact* contact) override;
};

#pragma once

#include "raylib.h"

class Agent {
public:

    Agent(Vector2 position);
    void draw() const;

private:
    Vector2 m_position;
    Vector2 m_velocity;
    float m_maxSpeed;
    float m_radius;
};
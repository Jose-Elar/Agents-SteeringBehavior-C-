#pragma once

#include "raylib.h"

class Agent {
public:
    Agent(Vector2 position);

    void update(Vector2 target, float deltaTime);
    void draw() const;

private:
    Vector2 arrive(Vector2 target);
    void applyForce(Vector2 force,float deltaTime);

    Vector2 m_position;
    Vector2 m_velocity;

    float m_maxSpeed;
    float m_maxForce;
    float m_radius;
    float m_slowingRadius;
};
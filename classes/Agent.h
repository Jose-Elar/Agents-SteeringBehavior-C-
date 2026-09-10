#pragma once

#include "raylib.h"
#include <vector>



class Agent {
public:
    Agent(Vector2 position);

    void update(std::vector<Agent>& otherAgents, float deltaTime);
    void draw() const;

    Vector2 getPosition();
    Vector2 getVelocity();

private:

    Vector2 separation(std::vector<Agent>& otherAgents);
    Vector2 alignment(std::vector<Agent>& otherAgents);
    Vector2 cohesion(std::vector<Agent>& otherAgents);

    //Vector2 arrive(Vector2 target);

    void applyForce(Vector2 force,float deltaTime);

    Vector2 m_position;
    Vector2 m_velocity;
    float m_maxSpeed;
    float m_maxForce;
    float m_radius;
    float m_slowingRadius;
    float m_percepcionRadius;
};
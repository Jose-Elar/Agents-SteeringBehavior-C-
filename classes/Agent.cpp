#include "Agent.h"

Agent::Agent(Vector2 startPosition){
    m_position = startPosition;
    m_velocity = {0.0f, 0.0f};
    m_maxSpeed = 200.0f;
    m_radius = 15.0f;
}

void Agent::draw() const{
    DrawPoly(m_position, 3, m_radius, 0.0f, GREEN);
}
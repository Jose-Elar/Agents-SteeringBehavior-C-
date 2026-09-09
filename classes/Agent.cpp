#include "Agent.h"
#include <raymath.h>

Agent::Agent(Vector2 startPosition){
    m_position = startPosition;
    m_velocity = {0.0f, 0.0f};
    m_maxSpeed = 200.0f;
    m_maxForce = 400.0f;
    m_radius = 15.0f;
    m_slowingRadius = 100.0f;
}

Vector2 Agent::arrive(Vector2 target){ 
    Vector2 toTarget = Vector2Subtract(target, m_position); //Substract to get the direction vector
    float distance = Vector2Length(toTarget);

    float desiredSpeed = m_maxSpeed;
    if (distance < m_slowingRadius) { //Distance when it slow downs
        desiredSpeed = m_maxSpeed * (distance / m_slowingRadius); //Scale speed depending on distance
    }

    Vector2 desired = Vector2Scale(Vector2Normalize(toTarget), desiredSpeed);
    Vector2 steeringForce = Vector2Subtract(desired, m_velocity);

    return steeringForce;
}

void Agent::applyForce(Vector2 force, float deltaTime){
    force = Vector2ClampValue(force, 0.0f, m_maxForce); // Clamp the force to the maximum force
    m_velocity = Vector2Add(m_velocity, Vector2Scale(force, deltaTime)); // Update the velocity based on the force and deltaTime
    m_velocity = Vector2ClampValue(m_velocity, 0.0f, m_maxSpeed); 

    m_position = Vector2Add(m_position, Vector2Scale(m_velocity, deltaTime)); // Update the position based on the velocity and deltaTime
}

void Agent::update(Vector2 target, float deltaTime){
    Vector2 steeringForce = arrive(target); 
    applyForce(steeringForce, deltaTime); 
}


void Agent::draw() const{
    float rotation = 0.0f;

    if(Vector2Length(m_velocity) > 0.0f){
        rotation = atan2f(m_velocity.y, m_velocity.x) * 180 / PI; // Convert to degrees
    }


    DrawPoly(m_position, 3, m_radius, rotation, GREEN);
}
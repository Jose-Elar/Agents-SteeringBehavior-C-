#include "Agent.h"
#include <raymath.h>

Agent::Agent(Vector2 startPosition){
    m_position = startPosition;
    m_velocity = {GetRandomValue(-150,150)/ 10.0f,GetRandomValue(-150,150)/ 10.0f};
    m_maxSpeed = 200.0f;
    m_maxForce = 400.0f;
    m_radius = 15.0f;
    m_slowingRadius = 100.0f;
    m_percepcionRadius = 50.0f;
}

Vector2 Agent::separation(std::vector<Agent>& otherAgents){ //Separation forces in between close agents
    Vector2 steer = Vector2 {0.0f, 0.0f};
    int count = 0;

    for(Agent& other: otherAgents){
        if(&other == this) continue; 

        float distance = Vector2Distance(m_position, other.getPosition());
        if ( distance > 0.0f && distance < m_percepcionRadius) {
            Vector2 diff = Vector2Subtract(m_position, other.m_position);
            diff = Vector2Normalize(diff);
            diff = Vector2Scale(diff,1.0f / distance); // Weight by distance to target
            steer = Vector2Add(steer, diff); //Add of all forces
            count++;
        }
    }

    if (count > 0) {
        steer = Vector2Scale(steer, 1.0f / static_cast<float>(count)); // Average the steering force

         if (Vector2Length(steer) > 0.0f) {
            steer = Vector2Scale(Vector2Normalize(steer), m_maxSpeed); // Scale to max speed, same pattern as alignment/cohesion
            steer = Vector2Subtract(steer, m_velocity); // Reynolds steering: desired - current
        }
    }

    return steer;
}

Vector2 Agent::alignment(std::vector<Agent>& otherAgents){ //Aligment of speed between close agents
    Vector2 averageVelocity = Vector2{0.0f,0.0f};
    int count = 0;

    for(Agent& other : otherAgents){
        if (&other == this) continue;

        float distance = Vector2Distance(m_position,other.getPosition());
        if (distance > 0.0f && distance < m_percepcionRadius){
            averageVelocity = Vector2Add(averageVelocity,other.getVelocity()); //Add of all velocitiy of close agents
            count++;
        }
    }

    if (count > 0){
        averageVelocity = Vector2Scale(averageVelocity,1.0f / static_cast<float>(count)); //Average of all speeds
        Vector2 steer = Vector2Subtract(averageVelocity,m_velocity); //Correct force, between the average and its own speed
        return steer;
    }
    return {0.0f,0.0f};
}

Vector2 Agent::cohesion(std::vector<Agent>& otherAgents){
    Vector2 centerOfMass = Vector2{0.0f,0.0f};
    int count = 0;

    for(Agent& other : otherAgents){
        if(&other == this) continue;

        float distance = Vector2Distance(m_position,other.getPosition());
        if(distance > 0.0f && distance < m_percepcionRadius){
            centerOfMass = Vector2Add(centerOfMass,other.getPosition()); //Add the position of this close agent to the vector
            count++;
        }
    }

    if (count > 0) {
        centerOfMass = Vector2Scale(centerOfMass, 1.0f / static_cast<float>(count)); //Avg of all position of agents close
        Vector2 toCenter = Vector2Subtract(centerOfMass,m_position);
        Vector2 desired = Vector2Scale(Vector2Normalize(toCenter), m_maxSpeed); //Scale vector of the normalized vector to max speed of the agent
        Vector2 steer = Vector2Subtract(desired, m_velocity); //Same as before to calculate the total force of the function
        return steer;
    }

    return Vector2{0.0f,0.0f};
}


void Agent::applyForce(Vector2 force, float deltaTime){

    force = Vector2ClampValue(force, 0.0f, m_maxForce); // Clamp the force to the maximum force
    m_velocity = Vector2Add(m_velocity, Vector2Scale(force, deltaTime)); // Update the velocity based on the force and deltaTime
    m_velocity = Vector2ClampValue(m_velocity, 0.0f, m_maxSpeed); 

    m_position = Vector2Add(m_position, Vector2Scale(m_velocity, deltaTime)); // Update the position based on the velocity and deltaTime
}

void Agent::update(std::vector<Agent>& otherAgents, float deltaTime){
    Vector2 separationForce = separation(otherAgents);
    Vector2 aligmentForce = alignment(otherAgents);
    Vector2 cohesionForce = cohesion(otherAgents);

    //Asign a force to each force so they are stronger than others 
    separationForce = Vector2Scale(separationForce,0.5f);
    aligmentForce = Vector2Scale(aligmentForce,2.0f);
    cohesionForce = Vector2Scale(cohesionForce,0.5f);

    Vector2 totalForce = Vector2Add(separationForce,aligmentForce);
    totalForce = Vector2Add(totalForce,cohesionForce);

    applyForce(totalForce,deltaTime);

    //Vector2 steeringForce = arrive(target); 
    //applyForce(steeringForce, deltaTime); 
}


void Agent::draw() const{
    float rotation = 0.0f;

    if(Vector2Length(m_velocity) > 0.0f){
        rotation = atan2f(m_velocity.y, m_velocity.x) * 180 / PI; // Convert to degrees
    }


    DrawPoly(m_position, 3, m_radius, rotation, GREEN);
}

Vector2 Agent::getPosition() {
    return m_position;
}

Vector2 Agent::getVelocity() {
    return m_velocity;
}

/*
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
*/

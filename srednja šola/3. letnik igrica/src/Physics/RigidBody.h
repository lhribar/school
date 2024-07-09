

#ifndef BLOJZGAME_RIGIDBODY_H
#define BLOJZGAME_RIGIDBODY_H

#include "Vector2D.h"

#define UNI_MASS 1.0f;
#define GRAVITY 9.8f;
#define UPWARD -1
#define DOWNWARD 1

class RigidBody{
private:
    float mass, gravity;

    Vector2D force;
    Vector2D friction;

    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
public:
    RigidBody(){
        mass = UNI_MASS;
        gravity = GRAVITY;
    }

    //Setters for gravity and mass
    void setMass(float mass){ this->mass = mass;}
    void setGravity(float gravity){ this->gravity = gravity;}

    //Functions for force
    void applyForce(Vector2D F){ force = F;}
    void applyForceX(float Fx){ force.x = Fx;}
    void applyForceY (float Fy){ force.y = Fy;}
    void unSetForce(){ force = Vector2D{0, 0};}

    //Functions for friction
    void applyFriction(Vector2D Fr){ friction = Fr;}
    void unSetFriction(){ friction = Vector2D{0, 0};}

    //Getters
    float getMass(){return mass;}
    Vector2D getPosition(){return position;}
    Vector2D getVelocity(){return velocity;}
    Vector2D getAcceleration(){return acceleration;}

    void update(float dt){
        acceleration.x = (force.x + friction.x) / mass;
        acceleration.y = (gravity + force.y) / mass;
        velocity = acceleration * dt;
        position = velocity * dt;
    }
};

#endif //BLOJZGAME_RIGIDBODY_H

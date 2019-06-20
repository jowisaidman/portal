#ifndef TP4_ENERGY_BALL_H
#define TP4_ENERGY_BALL_H

#include "World.h"

class Energy_Ball : public Entity{
    b2Body * energy_ball;
    std::string name;
    float radius;
    bool live;
    bool contact;
    World& world;
    float size;
    b2Vec2 new_velocity;
    bool change_velocity;
    int angle;
    int direction;
    b2Vec2 velocity;
    b2Vec2 position;
public:
    //Contructor de una bola de energia
    Energy_Ball(World& world, float x_pos, float y_pos);

    //Se aplica una fuerza para que la bola de energia se mueva segun la posicion indicada.
    bool Move(char direction);

    //Devuelve la posicion de la bola de energia
    b2Vec2 getPosition();

    //devuelve el valor del angulo de la bola de energia
    float getAngle();

    const std::string& getEntityName() override;
    void startContact(b2Vec2) override;
    void endContact() override;
    void die() override;
    bool lives() override;
    bool setTransform(Entity *) override;
    void changePosition() override;
    void startBouncing() override ;
    void win();
    int getDirection();
    float getRadius();
    ~Energy_Ball() = default;
};
#endif

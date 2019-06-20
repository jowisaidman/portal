#include <math.h>
#include "Energy_Ball.h"
#include "Macros.h"
#include "Metal_Block.h"

Energy_Ball::Energy_Ball(World& world, float x_pos, float y_pos): world(world) {
    Filter_Data data(BALL_BITS);
    data.addMaskBits(CHELL_BITS);
    data.addMaskBits(ROCK_PORTAL_BITS);
    data.addMaskBits(OTHER_BITS);
    energy_ball = world.addCircle(x_pos,y_pos,ENERGY_BALL,false,data,false);
    energy_ball->SetUserData(this);
    energy_ball->SetGravityScale(0);
    contact = false;
    change_velocity = false;
    name = "Energy_Ball";
    live = true;
    radius = ENERGY_BALL;
    direction = 0;
}

bool Energy_Ball::Move(char direction){
    if(direction == 'R'){
        energy_ball->SetLinearVelocity(b2Vec2(ENERGY_BALL_FORCE,ZERO));
        velocity = b2Vec2(ENERGY_BALL_FORCE,ZERO);
        return true;
    }
    if(direction == 'L'){
        energy_ball->SetLinearVelocity(b2Vec2(-ENERGY_BALL_FORCE,ZERO));
        velocity = b2Vec2(-ENERGY_BALL_FORCE,ZERO);
        return true;
    }
    if(direction == 'U'){
        energy_ball->SetLinearVelocity(b2Vec2(ZERO,ENERGY_BALL_FORCE));
        velocity = b2Vec2(ZERO,ENERGY_BALL_FORCE);
        return true;
    }
    if(direction == 'D'){
        energy_ball->SetLinearVelocity(b2Vec2(ZERO,-ENERGY_BALL_FORCE));
        velocity = b2Vec2(ZERO,-ENERGY_BALL_FORCE);
        return true;
    }
    return false;
}

b2Vec2 Energy_Ball::getPosition(){
    if(!live) return b2Vec2(0,0);
    return energy_ball->GetPosition();
}

float Energy_Ball::getAngle() {
    if(!live) return 0;
    return energy_ball->GetAngle();
}

void Energy_Ball::startContact(b2Vec2) {
    std::cout<<"cONTACTOoooooooooooooooooooooooooooooooooooooooooooooooo\n";
    position = energy_ball->GetPosition();
    std::cout<<"veloc: "<<velocity.x<<" "<<velocity.y<<std::endl;
    std::cout<<"cONTACTO\n";
    /*std::cout<<pos.x<<""<<pos.y<<std::endl;
    b2Vec2 ball_velocity = energy_ball->GetLinearVelocity();
    std::cout<<"Veloc "<<ball_velocity.x<<"  "<<ball_velocity.y<<std::endl;

    std::cout<<"Veloc antes"<<new_velocity.x<<"  "<<new_velocity.y<<std::endl;
    std::cout<<(-2.0/3.0) * size<<(-1.0/3.0) * size<<std::endl;
    std::cout<<pos.x - ((-2.0/3) * size)<<"  "<<(pos.y - (-1.0/3) * size)<<std::endl;

    if( ball_velocity.x != 0 && ball_velocity.y != 0){
        printf("entro\n");
        new_velocity = b2Vec2(0,ball_velocity.x);
        change_velocity = true;
    }

    std::cout<<"Veloc dps "<<new_velocity.x<<"  "<<new_velocity.y<<std::endl;*/

    contact = true;
}

void Energy_Ball::endContact() {
    contact = false;
}

const std::string& Energy_Ball::getEntityName() {
    return name;
}

void Energy_Ball::die() {
     live = false;
}

bool Energy_Ball::lives(){
    return live;
}

float Energy_Ball::getRadius() {
    return radius;
}

bool Energy_Ball::setTransform(Entity *) {
    /*angle = dynamic_cast<Metal_Block *>(body)->getAngle();
    size = dynamic_cast<Metal_Block *>(body)->getSizes().x;
    std::cout<<size<<std::endl;*/
    return true;
}

void Energy_Ball::changePosition() {
    if (contact){
        std::cout<<"ENERGY BALL ENTR222222222222\n";
        energy_ball->SetTransform(position,0);
        energy_ball->SetLinearVelocity(velocity);
        contact = false;
    }
}

void Energy_Ball::startBouncing() {}

void Energy_Ball::win(){}

int Energy_Ball::getDirection(){
    b2Vec2 actualVelocity = energy_ball->GetLinearVelocity();
    if(abs(actualVelocity.x) > abs(actualVelocity.y)){
        if(actualVelocity.x > 0) direction = 0;
        if(actualVelocity.x < 0) direction = 1;
    } else {
        if(actualVelocity.y > 0) direction = 2;
        if(actualVelocity.y < 0) direction = 3;
    }
    return direction;
}
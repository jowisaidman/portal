#include "Chell_Player.h"
#include "Macros.h"


Chell_Player::Chell_Player(World &world, float x_pos, float y_pos): world(world),jumper_counter(0){
    name = "Chell_Player";
    contact = 0;
    teleport = false;
    live = true;
    winner = false;
    Filter_Data data(CHELL_BITS);
    data.addMaskBits(OTHER_BITS);
    data.addMaskBits(ROCK_PORTAL_BITS);
    data.addMaskBits(BALL_BITS);
    sizes = b2Vec2(CHELL_HIGH,CHELL_WIDTH);
    footSensor = new Foot_Sensor(this);
    chell = world.addPlayer(x_pos, y_pos, CHELL_WIDTH/2, CHELL_HIGH/2.f,data,footSensor);
    chell->SetUserData(this);
    direction_right = true;
    rock = nullptr;
    take = false;
    taking = false;
    inmortal = false;
    gravity = false;
}

bool Chell_Player::Jump(){
    if(!live) return false;
    std::cout<<"contact"<<contact<<" jumper_counter "<<jumper_counter<<std::endl;
    if (gravity){
        chell->SetLinearVelocity(b2Vec2(ZERO,CHELL_MOVE_FORCE/2.f));
        return true;
    } else if (contact >= 1 && jumper_counter == 0){
       chell->ApplyForceToCenter(b2Vec2(ZERO,CHELL_JUMP_FORCE),true);
       jumper_counter = 1;
       return true;
    }
    return false;
}

bool Chell_Player::Move(char &direction) {
    b2Vec2 actual_speed = this->chell->GetLinearVelocity();
    if(!live) return false;
    if(direction == 'd'){
        direction_right = true;
        if (actual_speed.y != 0) {
            chell->SetLinearVelocity(b2Vec2(CHELL_MOVE_FORCE/2.f,actual_speed.y));
        } else {
            chell->SetLinearVelocity(b2Vec2(CHELL_MOVE_FORCE,ZERO));
        }
        return true;
    } else if(direction == 'a'){
        direction_right = false;
        if (actual_speed.y != 0) {
            chell->SetLinearVelocity(b2Vec2(-CHELL_MOVE_FORCE/2.f,actual_speed.y));
        } else {
            chell->SetLinearVelocity(b2Vec2(-CHELL_MOVE_FORCE,ZERO));
        }
        return true;
    } else if(direction == 's') {
        if(gravity){
            chell->SetLinearVelocity(b2Vec2(ZERO,-CHELL_MOVE_FORCE/2.f));
        } else if (actual_speed.y != 0) {
            chell->ApplyLinearImpulseToCenter(b2Vec2(ZERO,-CHELL_MOVE_FORCE/2.f),true);
        }
        return true;
    } else if (direction == 'z'){
        this->Brake();
        return true;
    }
    return false;
}

void Chell_Player::Brake(){
    if(chell->GetLinearVelocity().y == 0){
        chell->SetLinearVelocity(b2Vec2(0,0));
    } else{
        if(chell->GetLinearVelocity().x < 0){
            chell->ApplyForceToCenter(b2Vec2(CHELL_MOVE_FORCE,0),true);
        }
        if(chell->GetLinearVelocity().x > 0){
            chell->ApplyForceToCenter(b2Vec2(-CHELL_MOVE_FORCE,0),true);
        }
    }
}

int Chell_Player::getStatus(){
    if(!live) return CHELL_DYING;
    if(winner) return CHELL_DANCING;
    b2Vec2 velocity = chell->GetLinearVelocity();
    if(velocity.x == 0 && velocity.y == 0) return CHELL_QUIET;
    if(velocity.y < 0) return CHELL_FALLING;
    if(velocity.y > 0) return CHELL_JUMPING;
    if(velocity.x != 0) return CHELL_RUNNING;
    return CHELL_DANCING;
}

int Chell_Player::getDirection() {
    return direction_right;
} 

b2Vec2 Chell_Player::getPosition() {
    if(!live) return teleport_pos;
    return chell->GetPosition();
}

float Chell_Player::getAngle() {
    if(!live) return 0;
    return chell->GetAngle();
}

bool Chell_Player::setTransform(Entity * body) {
    if(!live) return false;
    jumper_counter = 0;
    if(body->getEntityName() == "Rock" && take){
        rock = (Rock *)body;
        taking = true;
    }
    if (body->getEntityName() == "Portal") {
        if(!dynamic_cast<Portal *>(body)->havePartner()) return false;
        if(dynamic_cast<Portal *>(body)->getPartnerPortal() == nullptr) return false;
        if(!dynamic_cast<Portal *>(body)->getPartnerPortal()->lives()) return false;

        teleport_pos = dynamic_cast<Portal *>(body)->getPartnerPortal()->getPosition();
        b2Vec2 normal = dynamic_cast<Portal *>(body)->getPartnerPortal()->getNormal();
    
        teleport = true;
        if(normal.x > ZERO){
            teleport_pos = teleport_pos + b2Vec2(CHELL_X_DELTA,ZERO);
        } else if(normal.x < ZERO){
            teleport_pos = teleport_pos - b2Vec2(CHELL_X_DELTA,ZERO);
        }
        if(normal.y > ZERO){
            teleport_pos = teleport_pos + b2Vec2(ZERO,CHELL_Y_DELTA);
        } else if (normal.y < ZERO){
            teleport_pos = teleport_pos - b2Vec2(ZERO,CHELL_Y_DELTA);
        }
    
        velocity = b2Vec2(CHELL_VELOCITY * normal.x,CHELL_VELOCITY * normal.y);
    }
    return true;
}

void Chell_Player::changePosition() {
    if(taking && rock != nullptr && take){
        if(direction_right){
            rock->changePositionChell(chell->GetPosition() + b2Vec2(0.8f,0.1f));

        } else{
            rock->changePositionChell(chell->GetPosition() + b2Vec2(-0.8f,0.1f));
        }
        jumper_counter = 0;
    }
    if(!teleport) return;
    chell->SetTransform(teleport_pos,chell->GetAngle());
    chell->SetLinearVelocity(velocity);
    if(velocity.x > 0) direction_right = 1;
    else direction_right = 0;
    jumper_counter = 0;
    teleport = false;
}

void Chell_Player::startBouncing(){}

void Chell_Player::startContact(b2Vec2) {
    ++contact;
    jumper_counter = 0;
}

void Chell_Player::endContact() {
    if(chell->GetLinearVelocity().y != 0){
        jumper_counter = 1;
    }
    --contact;
}

const std::string& Chell_Player::getEntityName() {
    return name;
}

Portal * Chell_Player::shotPortalIn(float x_pos, float y_pos) {
    if(!live) return nullptr;
    b2Vec2 position = chell->GetPosition();
    Portal * ball = portals.shotPortalIn(world,position.x - DELTA_POSITION,position.y - DELTA_POSITION,x_pos,y_pos);
    return ball;
}

Portal * Chell_Player::shotPortalOut(float x_pos, float y_pos) {
    if(!live) return nullptr;
    b2Vec2 position = chell->GetPosition();
    Portal * ball = portals.shotPortalOut(world,position.x - DELTA_POSITION,position.y - DELTA_POSITION,x_pos,y_pos);
    return ball;
}

void Chell_Player::die() {
    if(inmortal) return;
    teleport_pos = chell->GetPosition();
    live = false;
}

bool Chell_Player::lives() {
    return live;
}

b2Vec2 Chell_Player::getSizes() {
    return sizes;
}

Portal* Chell_Player::getPortalIn() {
    return this->portals.getPortalIn();
}

Portal* Chell_Player::getPortalOut() {
    return this->portals.getPortalOut();
}

void Chell_Player::win(){
    winner = true;
}

void Chell_Player::grabARock() {
    if(rock != nullptr && take) dropTheRock();
    else take = true;
}

void Chell_Player::dropTheRock() {
    take = false;
    taking = false;
    rock->setVelocity(b2Vec2(ZERO,ZERO));
    rock = nullptr;
    jumper_counter = 0;
}


//respuesta: o (oscuridad)
void Chell_Player::inmortalChell(){
    std::cout<<"cheat activado1\n";
    if (inmortal) inmortal = false;
    else inmortal = true;
}


//respuesta: v (viento)
void Chell_Player::antiGravity() {

    std::cout<<"cheat activado\n";
    std::cout<<chell->GetGravityScale()<<std::endl;
    if(gravity){
        std::cout<<chell->GetGravityScale()<<std::endl;
        std::cout<<world.getGravity()<<std::endl;
        chell->SetGravityScale(1);
        gravity = false;
    }
    else{
        chell->SetGravityScale(ZERO);
        gravity = true;
    }
}
#include "Portal.h"
#include "Macros.h"
#include "Metal_Block.h"
#include "Ground.h"

Portal::Portal(World& world, float x_pos, float y_pos): world(world) {
    Filter_Data data(ROCK_PORTAL_BITS);
    data.addMaskBits(OTHER_BITS);
    data.addMaskBits(BARRIER_BITS);
    data.addMaskBits(BALL_BITS);
    portal = world.addCircle(x_pos,y_pos,ENERGY_BALL,false,data);
    portal->SetGravityScale(ZERO);
    portal->SetUserData(this);
    contact = false;
    have_partner = false;
    name = "Portal";
    live = true;
    ball = true;
    send_it = false;
    position = portal->GetPosition();
    radius = ENERGY_BALL;
    sizes = b2Vec2(PORTAL_WIDTH,PORTAL_HIGH);
    orientation = 0;

}

bool Portal::Move(float x_pos, float y_pos){
    b2Vec2 position = portal->GetPosition();

    b2Vec2 velocity(0,0);

    std::cout<<"Posicion del portal: "<<position.x<<"   "<< position.y<<std::endl;
    std::cout<<"Posicion mapa: "<<x_pos<<"   "<<-y_pos<<std::endl;

    float angle = atan2((-y_pos) - position.y, x_pos - position.x);

    std::cout<<"angle: "<<angle<<std::endl;

    float force =  5.f;

    velocity = b2Vec2(force * cos(angle), force * sin(angle));

    portal->SetLinearVelocity(velocity);
    std::cout<<"Velocity final "<<velocity.x<<" "<<velocity.y<<std::endl;
    return true;
}

void Portal::changePosition() {
    if(!contact) return;
    if(contact){
        std::cout<<"resta: "<<abs(body_pos.x) - abs(position.x)<<" "<<abs(body_pos.y) - abs(position.y)<<std::endl;
        if(abs(body_pos.x) - abs(position.x == 0)){
            printf("Horizontal\n");
            std::cout<<"Orientacion antes "<<orientation <<std::endl;
            orientation = 0;
            std::cout<<"Orientacion despues"<<orientation <<std::endl;
            if(body_pos.y < position.y) normal = b2Vec2(1.f,2.f);
            if(body_pos.y > position.y) normal = b2Vec2(1.f,-2.f);
        }
        if(abs(body_pos.y) - abs(position.y) == 0){
            printf("Vertical\n");
            std::cout<<"Orientacion antes "<<orientation <<std::endl;
            orientation = 2;
            std::cout<<"Orientacion despues"<<orientation <<std::endl;
                orientation = 2;
                if(body_pos.x < position.x) normal = b2Vec2(2.f,1.f);

                if(body_pos.x > position.x) normal = b2Vec2(-2.f,1.f);
        }
        if(abs(body_pos.x - position.x) != 0 && abs(body_pos.y - position.y) != 0){
            std::cout<<"Orientacion antes "<<orientation <<std::endl;
            orientation = 3;
            std::cout<<"Orientacion despues"<<orientation <<std::endl;
        }
        Filter_Data data(ROCK_PORTAL_BITS);
        data.addMaskBits(OTHER_BITS);
        data.addMaskBits(CHELL_BITS);
        data.addMaskBits(ROCK_PORTAL_BITS);
        if(orientation == 2){
            float delta = - PORTAL_WIDTH/2.f;
            if(position.x > 0) delta = PORTAL_WIDTH/2.f;
            portal = world.addPolygon(position.x - DELTA_POSITION + delta
                    ,position.y - DELTA_POSITION,PORTAL_WIDTH/2.F,PORTAL_HIGH/2.F,true,data);
        }
        if (orientation == 0) {
            float delta = - PORTAL_WIDTH/2.f;
            if(position.y > 0) delta = PORTAL_WIDTH/2.f;
            portal = world.addPolygon(position.x - DELTA_POSITION,position.y - DELTA_POSITION + delta ,PORTAL_HIGH/2.F,
                    PORTAL_WIDTH/2.F,true,data);
        }
        portal->SetUserData(this);
        contact = false;
        ball = false;
        send_it = false;
        live = true;
    }
    portal->SetLinearVelocity(b2Vec2(0,0));
}

b2Vec2 Portal::getPosition(){
    if(!live) return b2Vec2(0,0);
    return portal->GetPosition();// + b2Vec2(0.2,0);
}

bool Portal::isValid() {
    bool result = !ball && !send_it;
    send_it = true;
    return result;
}

int Portal::getOrientation() {
    return this->orientation;
}

b2Vec2 Portal::getNormal() {
    return normal;
}

float Portal::getAngle() {
    if(!live) return 0;
    return portal->GetAngle();
}

void Portal::startContact(b2Vec2 pos) {
    contact = true;
    position = pos;
    portal->SetLinearVelocity(b2Vec2(0,0));
}

void Portal::endContact() {
    contact = false;
}

const std::string& Portal::getEntityName() {
    return name;
}

void Portal::die() {
    live = false;
}

bool Portal::lives(){
    return live;
}

bool Portal::setPartner(Portal *portal) {
    partner = portal;
    have_partner = true;
    return true;
}

Portal * Portal::getPartnerPortal() {
    if(!partner) return nullptr;
    return partner;
}

bool Portal::changePortalPosition(float x_pos, float y_pos) {
    if(!world.validPosition(x_pos,y_pos)) return false;
    world.eraseBody(portal);
    Filter_Data data(ROCK_PORTAL_BITS);
    data.addMaskBits(OTHER_BITS);
    data.addMaskBits(BARRIER_BITS);
    data.addMaskBits(BALL_BITS);
    portal = world.addCircle(x_pos,y_pos,ENERGY_BALL,false,data);
    portal->SetGravityScale(ZERO);
    portal->SetUserData(this);
    contact = false;
    ball = true;
    send_it = true;
    return true;
}

bool Portal::havePartner() {
    return have_partner;
}

float Portal::getradius() {
    return radius;
}

b2Vec2 Portal::getSizes() {
    return sizes;
}

bool Portal::setTransform(Entity * body){

    if(body->getEntityName() == "Metal_Block"){
        body_pos = dynamic_cast<Metal_Block *>(body)->getPosition();


    }

    if(body->getEntityName() == "Ground"){
        body_pos = b2Vec2(portal->GetPosition().x,dynamic_cast<Ground *>(body)->getPosition().y);
    }
    return true;
}

void Portal::startBouncing() {}
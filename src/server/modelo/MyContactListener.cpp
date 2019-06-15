#include "MyContactListener.h"

void chell_validation(Entity * bodyA, Entity * bodyB){

    std::string nameBodyA = (bodyA)->getEntityName();
    std::string nameBodyB = (bodyB)->getEntityName();

    if(nameBodyA == "Chell_Player" && nameBodyB == "Portal") bodyA->setTransform(bodyB);
    if(nameBodyA == "Chell_Player" && nameBodyB == "Energy_Ball") bodyA->die();
    if(nameBodyA == "Chell_Player" && nameBodyB == "Acid") bodyA->die();

    if(nameBodyB == "Chell_Player" && nameBodyA == "Portal") bodyB->setTransform(bodyB);
    if(nameBodyB == "Chell_Player" && nameBodyA == "Energy_Ball") bodyB->die();
    if(nameBodyB == "Chell_Player" && nameBodyA == "Acid") bodyB->die();
}

void chell_colitions(b2Body * bodyA,b2Body * bodyB){

    void * userDataA = static_cast<Entity *>(bodyA->GetUserData());
    void * userDataB = static_cast<Entity *>(bodyB->GetUserData());

    std::string nameBodyA = static_cast<Entity *>(userDataA)->getEntityName();
    std::string nameBodyB = static_cast<Entity *>(userDataB)->getEntityName();

    std::cout<<"Colisionaron "<<nameBodyA<<" con "<<nameBodyB<<std::endl;

    if (nameBodyA == "Chell_Player" && (nameBodyB == "Ground" || nameBodyB == "Bottom" || nameBodyB == "Rock")) {
        static_cast<Entity *>(userDataA)->startBouncing();
    }

    if (nameBodyA == "Chell_Player" && (nameBodyB == "Metal_Block" || nameBodyB == "Stone_Block")) {
        static_cast<Entity *>(userDataA)->startBouncing();
    }

    if (nameBodyB == "Chell_Player" && (nameBodyA == "Ground" || nameBodyA == "Bottom" || nameBodyA == "Rock")) {
        static_cast<Entity *>(userDataB)->startBouncing();
    }

    if (nameBodyB == "Chell_Player" && (nameBodyA == "Metal_Block" || nameBodyA == "Stone_Block")) {
        static_cast<Entity *>(userDataB)->startBouncing();
    }

    chell_validation(static_cast<Entity *>(userDataA),static_cast<Entity *>(userDataB));

}

void foot_sensor_colitions(Entity * foot_sensor, b2Body * body){

    std::string nameBody =  static_cast<Entity *>(body->GetUserData())->getEntityName();

    if(nameBody == "Ground" || nameBody == "Bottom" || nameBody == "Rock"){
        foot_sensor->startContact(body->GetPosition());
    }

    if(nameBody == "Metal_Block" || nameBody == "Stone_Block"){
        foot_sensor->startContact(body->GetPosition());
    }

}

void portal_colitions(b2Body * bodyA,b2Body * bodyB,b2Vec2 colition_point){
    void * userDataA = static_cast<Entity *>(bodyA->GetUserData());
    void * userDataB = static_cast<Entity *>(bodyB->GetUserData());

    std::string nameBodyA = static_cast<Entity *>(userDataA)->getEntityName();
    std::string nameBodyB = static_cast<Entity *>(userDataB)->getEntityName();

    std::cout<<"position colision: "<<colition_point.x<<"  "<<colition_point.y<<std::endl;

    if(nameBodyA != "Portal" && nameBodyB != "Portal") return;

    if(nameBodyA == "Portal" && nameBodyB == "Metal_Block"){
        std::cout<<"Metal Block: x: "<<bodyB->GetPosition().x<<" y:"<<bodyB->GetPosition().y<<std::endl;
        static_cast<Entity *>(userDataA)->startContact(bodyB->GetPosition() + colition_point);
        std::cout<<"Metal Block + delta: x: "<<bodyB->GetPosition().x + colition_point.x<<" y:"<<bodyB->GetPosition().y + colition_point.y<<std::endl;
        static_cast<Entity *>(userDataA)->setTransform(static_cast<Entity *>(userDataB));
    }

    if(nameBodyA == "Portal" && nameBodyB == "Ground"){

        b2Vec2 pos = b2Vec2(bodyA->GetPosition().x,bodyB->GetPosition().y);

        std::cout<<"Ground : x: "<<bodyB->GetPosition().x<<" y:"<<bodyB->GetPosition().y<<std::endl;
        static_cast<Entity *>(userDataA)->startContact(pos + colition_point);
        std::cout<<"Ground + delta: x: "<<bodyB->GetPosition().x + colition_point.x<<" y:"<<bodyB->GetPosition().y + colition_point.y<<std::endl;
        static_cast<Entity *>(userDataA)->setTransform(static_cast<Entity *>(userDataB));
    }

    if(nameBodyB == "Portal" && nameBodyA == "Metal_Block"){
        std::cout<<"Metal Block: x: "<<bodyA->GetPosition().x<<" y:"<<bodyA->GetPosition().y<<std::endl;
        static_cast<Entity *>(userDataB)->startContact(bodyA->GetPosition() + colition_point);
        std::cout<<"Metal Block + delta: x: "<<bodyA->GetPosition().x + colition_point.x<<" y:"<<bodyA->GetPosition().y + colition_point.y<<std::endl;
        static_cast<Entity *>(userDataB)->setTransform(static_cast<Entity *>(userDataA));
    }

    if(nameBodyB == "Portal" && nameBodyA == "Ground"){
        std::cout<<"Ground: x: "<<bodyB->GetPosition().x<<" y:"<<bodyB->GetPosition().y<<std::endl;
        b2Vec2 pos = b2Vec2(bodyB->GetPosition().x,bodyA->GetPosition().y);
        static_cast<Entity *>(userDataB)->startContact(pos + colition_point);
        std::cout<<"Ground + delta: x: "<<bodyB->GetPosition().x + colition_point.x<<" y:"<<bodyB->GetPosition().y + colition_point.y<<std::endl;
        static_cast<Entity *>(userDataB)->setTransform(static_cast<Entity *>(userDataA));
    }

}

void bottom_colitions(b2Body * bodyA,b2Body * bodyB){
    void * userDataA = static_cast<Entity *>(bodyA->GetUserData());
    void * userDataB = static_cast<Entity *>(bodyB->GetUserData());

    std::string nameBodyA = static_cast<Entity *>(userDataA)->getEntityName();
    std::string nameBodyB = static_cast<Entity *>(userDataB)->getEntityName();

    if(nameBodyA != "Bottom" && nameBodyB != "Bottom") return;

    if(nameBodyA == "Bottom" && (nameBodyB == "Rock" || nameBodyB == "Chell_Player")){
        static_cast<Entity *>(userDataA)->startContact(bodyB->GetPosition());
    }

    if(nameBodyB == "Bottom" && (nameBodyA == "Rock" || nameBodyA == "Chell_Player")){
        static_cast<Entity *>(userDataB)->startContact(bodyA->GetPosition());
    }
}

void energy_ball_colition(b2Body * bodyA,b2Body * bodyB){
    void * userDataA = static_cast<Entity *>(bodyA->GetUserData());
    void * userDataB = static_cast<Entity *>(bodyB->GetUserData());

    std::string nameBodyA = static_cast<Entity *>(userDataA)->getEntityName();
    std::string nameBodyB = static_cast<Entity *>(userDataB)->getEntityName();

    if(nameBodyA != "Energy_Ball" && nameBodyB != "Energy_Ball") return;

    if(nameBodyA == "Energy_Ball" && nameBodyB == "Energy_Emitter"){
        static_cast<Entity *>(userDataA)->die();
        static_cast<Entity *>(userDataB)->startContact(b2Vec2(0,0));
    }

    if(nameBodyB == "Energy_Ball" && nameBodyA == "Energy_Emitter"){
        static_cast<Entity *>(userDataB)->die();
        static_cast<Entity *>(userDataA)->startContact(b2Vec2(0,0));
    }
}

void energy_barrier_colition(b2Body * bodyA,b2Body * bodyB){
    void * userDataA = static_cast<Entity *>(bodyA->GetUserData());
    void * userDataB = static_cast<Entity *>(bodyB->GetUserData());

    std::string nameBodyA = static_cast<Entity *>(userDataA)->getEntityName();
    std::string nameBodyB = static_cast<Entity *>(userDataB)->getEntityName();

    if(nameBodyA != "Energy_Barrier" && nameBodyB != "Energy_Barrier") return;

    if(nameBodyA == "Energy_Barrier" && (nameBodyB == "Rock" || nameBodyB == "Portal")){
        static_cast<Entity *>(userDataB)->die();
    }

    if(nameBodyB == "Energy_Barrier" && (nameBodyA == "Rock" || nameBodyA == "Portal")){
        static_cast<Entity *>(userDataA)->die();
    }
}

void MyContactListener::BeginContact(b2Contact * contact){
    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    b2Vec2 colition_point = contact->GetManifold()->localPoint;

    //if(!contact->GetFixtureA()->GetUserData() && !contact->GetFixtureB()->GetUserData()) printf("NO hay data\n");

    if(contact->GetFixtureA()->GetUserData()){
       // printf("Foot_ sensor deberia estar aca\n");
        void * foot_sensor = contact->GetFixtureA()->GetUserData();
        std::cout<<static_cast<Entity *>(foot_sensor)->getEntityName()<<std::endl;
        if(static_cast<Entity *>(foot_sensor)->getEntityName() == "Foot_Sensor"){
            foot_sensor_colitions(static_cast<Entity *>(foot_sensor),contact->GetFixtureB()->GetBody());
        }
    }

    if(contact->GetFixtureB()->GetUserData()){
        //printf("o aca\n");
        void * foot_sensor = contact->GetFixtureB()->GetUserData();
        std::cout<<static_cast<Entity *>(foot_sensor)->getEntityName()<<std::endl;
        if(static_cast<Entity *>(foot_sensor)->getEntityName() == "Foot_Sensor") {
            foot_sensor_colitions(static_cast<Entity *>(foot_sensor), contact->GetFixtureA()->GetBody());
        }
    }

    std::cout<<"position colision: "<<colition_point.x<<"  "<<colition_point.y<<std::endl;

    if (!bodyUserDataA || !bodyUserDataB) return;
    chell_colitions(contact->GetFixtureA()->GetBody(),contact->GetFixtureB()->GetBody());
    portal_colitions(contact->GetFixtureA()->GetBody(),contact->GetFixtureB()->GetBody(),colition_point);
    bottom_colitions(contact->GetFixtureA()->GetBody(),contact->GetFixtureB()->GetBody());
    energy_ball_colition(contact->GetFixtureA()->GetBody(),contact->GetFixtureB()->GetBody());
    energy_barrier_colition(contact->GetFixtureA()->GetBody(),contact->GetFixtureB()->GetBody());

}

void chell_endContact(void * userDataA, void * userDataB){
    std::string nameBodyA = static_cast<Entity *>(userDataA)->getEntityName();
    std::string nameBodyB = static_cast<Entity *>(userDataB)->getEntityName();

    std::cout<<"Se separo "<<nameBodyA<<" de "<<nameBodyB<<std::endl;

    if(nameBodyA != "Chell_Player" && nameBodyB != "Chell_Player") return;

    if(nameBodyA == "Chell_Player" && nameBodyB == "Ground") static_cast<Entity *>(userDataA)->endContact();
    printf("llega aca\n");
    if(nameBodyA == "Chell_Player" && nameBodyB == "Metal_Block"){
        static_cast<Entity *>(userDataA)->endContact();
        return;
    }
    printf("y aca\n");
    if(nameBodyA == "Chell_Player" && nameBodyB == "Stone_Block") static_cast<Entity *>(userDataA)->endContact();
    if(nameBodyA == "Chell_Player" && nameBodyB == "Bottom") static_cast<Entity *>(userDataA)->endContact();

    if(nameBodyB == "Chell_Player" && nameBodyA == "Ground") static_cast<Entity *>(userDataB)->endContact();
    if(nameBodyB == "Chell_Player" && nameBodyA == "Metal_Block") {
        static_cast<Entity *>(userDataB)->endContact();
        return;
    }
    printf("y aca2\n");
    if(nameBodyB == "Chell_Player" && nameBodyA == "Stone_Block") static_cast<Entity *>(userDataB)->endContact();
    if(nameBodyB == "Chell_Player" && nameBodyA == "Bottom") static_cast<Entity *>(userDataB)->endContact();
}

void bottom_endContact(void * userDataA, void * userDataB){
    std::string nameBodyA = static_cast<Entity *>(userDataA)->getEntityName();
    std::string nameBodyB = static_cast<Entity *>(userDataB)->getEntityName();
    if(nameBodyA != "Bottom" && nameBodyB != "Bottom") return;

    if(nameBodyA == "Bottom" && nameBodyB == "Chell_Player") static_cast<Entity *>(userDataA)->endContact();
    if(nameBodyA == "Bottom" && nameBodyB == "Rock") static_cast<Entity *>(userDataA)->endContact();

    if(nameBodyB == "Bottom" && nameBodyA == "Chell_Player") static_cast<Entity *>(userDataB)->endContact();
    if(nameBodyB == "Bottom" && nameBodyA == "Rock") static_cast<Entity *>(userDataB)->endContact();
}

void foot_sensor_end_contact(Entity * foot_sensor, b2Body * body){

    std::string nameBody =  static_cast<Entity *>(body->GetUserData())->getEntityName();

    std::cout<<"name: "<<nameBody<<std::endl;

    if(nameBody == "Ground" || nameBody == "Bottom" || nameBody == "Rock"){
        foot_sensor->endContact();
    }

    if(nameBody == "Metal_Block" || nameBody == "Stone_Block"){
        foot_sensor->endContact();
    }

}


void MyContactListener::EndContact(b2Contact* contact){
    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    if(contact->GetFixtureA()->GetUserData()){
        void * foot_sensor = contact->GetFixtureA()->GetUserData();
        if(static_cast<Entity *>(foot_sensor)->getEntityName() == "Foot_Sensor"){
            std::cout<<"FOOT SENSOR END\n";
            foot_sensor_end_contact(static_cast<Entity *>(foot_sensor),contact->GetFixtureB()->GetBody());
        }
    }

    if(contact->GetFixtureB()->GetUserData()){
        void * foot_sensor = contact->GetFixtureB()->GetUserData();
        if(static_cast<Entity *>(foot_sensor)->getEntityName() == "Foot_Sensor") {
            std::cout<<"FOOT SENSOR END\n";
            foot_sensor_end_contact(static_cast<Entity *>(foot_sensor), contact->GetFixtureA()->GetBody());
        }
    }

    if (!bodyUserDataA || !bodyUserDataB) return;
    //chell_endContact(bodyUserDataA,bodyUserDataB);
    bottom_endContact(bodyUserDataA,bodyUserDataB);
}
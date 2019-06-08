#include "Encoder.h"

Encoder :: Encoder(ProtectedDataBase *data_base,Sender *sender) {
    this->data_base = data_base;
    this->sender = sender;
}

void Encoder :: sendPlayerIds() {
    int id(1);
    std::vector<std::string> ids = this->data_base->getIds();
    for (size_t i = 0; i<ids.size(); i++) {
        std::string msg;
        msg = "0," + std::to_string(id);
        this->sender->sendMessageTo(ids[i],msg);
        id++;      
    }  
}

void Encoder :: sendPlayersPositions() {
    int id(1);
    std::vector<Chell_Player*> chells = this->data_base->getPlayers();
    for ( size_t i = 0; i<chells.size(); i++ ) {
        b2Vec2 position = chells[i]->Get_Position();
        std::string msg = "1,"+std::to_string(id)+ "," + std::to_string(position.x) + "," + 
        std::to_string(position.y) + "," + std::to_string(CHELL_WIDTH)+ "," + 
        std::to_string(CHELL_HIGH);
        this->sender->addMessageToSend(msg);
        id++;        
    }  
}

void Encoder :: sendMetalBlocks() {
    std::vector<Metal_Block*> metal_blocks = this->data_base->getMetalBlocks();
    for ( size_t i = 0; i<metal_blocks.size(); i++ ) {
        std::string msg;
        b2Vec2 pos = metal_blocks[i]->Get_Position();
        msg = "2,1," + std::to_string(pos.x) + "," + std::to_string(pos.y) +
        "," + std::to_string(metal_blocks[i]->Get_Size()) + "," + std::to_string(metal_blocks[i]->Get_Size());
        this->sender->addMessageToSend(msg);
    }
}

void Encoder :: sendAcids() {
    std::vector<Acid*> acids = this->data_base->getAcids();
    for ( size_t i = 0; i<acids.size(); i++ ) {
        std::string msg;
        b2Vec2 pos = acids[i]->Get_Position();
        msg = "5,"+ std::to_string(pos.x) + "," + std::to_string(pos.y) +
        "," + std::to_string(acids[i]->Get_Large()) + ",0.30";
        this->sender->addMessageToSend(msg);
    }
}


//void Encoder ::sendWorldSizes() {  //Se necesita?¡?¡?¡?¡?¡?¡?¡¡?
//    b2Vec2 high_b = this->world->getHigh();
//    b2Vec2 width_b = this->world->getWidth();
//    std::string msg("0," + std::to_string(width_b.x * 2) + "," + std::to_string(high_b.x * 2) + "\n");
//    this->sender->addMessageToSend(msg);
//}
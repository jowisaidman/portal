#ifndef GAME_ROOM_H
#define GAME_ROOM_H
#include <string>
#include <list>
#include <queue>
#include "../server/server_model.h"
#include "../common/Thread.h"
#include "../server/server_sender.h"
#include "../common/common_cola_protegida.h"

class RoomGame : public Thread {
    private:
        std::string name;
        ColaProtegida *messages;
        size_t size;
        std::mutex m;
        std::list<std::string> players;
        Sender sender;
        void sendMessageFrom(std::string &player,std::string &message);
        bool continue_running;
        void splitMessage(std::string &message,std::string &first_place,
        std::string &second_place);

    public:
        RoomGame(std::string &name,size_t size);
        ~RoomGame();

        void endExecution();

        virtual void run() override;

        //Recibe como parametro un jugador y lo agrega a la sala
        bool addPlayer(std::string &name);

        //Envia un mensaje al resto de los jugadores que estan en
        //la sala del jugador que recibe por parametro
        //void sendMessageFrom(Player &player,std::string message);
        
        bool playerInRoom(const std::string &name);

        void addMessageToSend(std::string &message);

        std::string getName();

        Sender* getSender();

        void imprimirJugadores(); //HAY QUE BORRAR 
        std::string getJugadores(); //HAY QUE BORRAR 
};

#endif

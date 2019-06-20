#ifndef PROTECTED_DATA_BASE_H
#define PROTECTED_DATA_BASE_H
#include <string>
#include <map>
#include <mutex>
#include <vector>
#include "../common/Constants.h"
#include "modelo/World.h"
#include "modelo/Ground.h"
#include "modelo/Chell_Player.h"
#include "modelo/MyContactListener.h"
#include "modelo/Acid.h"
#include "modelo/Energy_Ball.h"
#include "modelo/Entity.h"
#include "modelo/Filter_Data.h"
#include "modelo/Metal_Block.h"
#include "modelo/Rock.h"
#include "modelo/Stone_Block.h"
#include "modelo/Player_Portals.h"
#include "modelo/Gate.h"
#include "modelo/Button.h"
#include "modelo/Energy_Barrier.h"
#include "modelo/Energy_Emitters.h"
#include "modelo/Cake.h"

class ProtectedDataBase {
private:
    std::mutex m;
    std::map<std::string,size_t> player_ids;
    std::map<std::string, Chell_Player*> players;
    std::map<std::string,std::string> vote_to_kill;
    std::map<std::string,bool> player_reach_cake;
    std::map<size_t, Rock*> rocks;
    std::map<size_t, Acid*> acids;
    std::map<size_t, Energy_Ball*> energy_balls;
    std::map<size_t, Metal_Block*> metal_blocks;
    std::map<size_t, Stone_Block*> stone_blocks;
    std::map<size_t, Gate*> gates;
    std::map<size_t, Button*> buttons;
    std::map<size_t, Energy_Barrier*> barriers;
    std::map<size_t, Energy_Emitters*> emitters;
    std::map<Button*,std::vector<size_t>> pending_buttons;
    std::map<size_t, Cake*> cakes;
    int width;
    int height;
    bool win_state = false;
    void setVotes(std::map<std::string, size_t> &votes);
    std::string getPlayerToKill();
    void checkPlayerToKill(std::string &player_to_kill);
    void resetPlayers();
    void resetAcids();
    void resetRocks();
    void resetEnergyBalls();
    void resetMetalBlocks();
    void resetStoneBlocks();
    void resetGates();
    void resetButtons();
    void resetEnergyBarriers();
    void resetEnergyEmitters();

public:
    ProtectedDataBase() = default;
    ~ProtectedDataBase();

    void setLevel(World &world);

    void makePlayerJump(std::string &player);
    void makePlayerMove(std::string &player,char &direction);
    void makePlayerMoveRock(std::string &player);
    void shootPortal(World &world,std::string &player,float x_destiny, float y_destiny,int portal_num);
    void voteToKill(std::string &voter);
    void killPlayer(std::string &player_name);
    void setWinState();
    void makePlayerInmortal(std::string &player);
    void makePlayerAntiGravity(std::string &player);


    //Asocia todos los botones a su respectiva puerta
    void addButtonToDoor();


    void addPlayer(World &world,std::string &player);
    void addRock(World &world,float x_pos, float y_pos, float radius);
    void addAcid(World &world,float x_pos, float y_pos, float large);
    void addEnergyBall(World &world,float x_pos, float y_pos);
    void addMetalBlock(World &world,float x_pos, float y_pos,float size);
    void addStoneBlock(World &world,float x_pos, float y_pos,float size);
    void addButton(World &world, float x_pos, float y_pos,int door_id,int state_to_open_door);
    void addGate(World &world, float x_pos, float y_pos);
    void addEmitter(World &world,float x_pos, float y_pos, float size,
      int direction, bool charged);
    void addEnergyBarrier(World &world,float x_pos, float y_pos, float large, int orientation);
    void addCake(World &world, float x_pos, float y_pos);
    void addTriangularBlock(World &world, float x_pos, float y_pos, float size, int type);
    //Getters
    std::vector<std::string> getIds();
    std::vector<Chell_Player*> getPlayers();
    std::vector<Acid*> getAcids();
    std::vector<Metal_Block*> getMetalBlocks();
    std::vector<Rock*> getRocks();
    std::vector<Energy_Ball*> getEnergyBalls();
    std::vector<Stone_Block*> getStoneBlocks();
    std::vector<Gate*> getGates();
    std::vector<Button*> getButtons();
    std::vector<Energy_Barrier*> getBarriers();
    std::vector<Energy_Emitters*> getEmitters(); 
    std::vector<Cake*> getCakes();     
    float getWidth();
    float getHeight();
    std::map<std::string,Chell_Player*> getPlayersMap();
    std::string getPlayersName();
    bool getWinState();
    std::map<std::string,std::string> getVoteToKill();  

    void resetDataBase();
};

#endif

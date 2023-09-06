//
// Created by Ethan's Macbook on 8/2/23.
//

#ifndef HOMEWORK_1_ROOM_H
#define HOMEWORK_1_ROOM_H


#include "Creature.h"
#include "Global.h"
#include <string>

#define MAX_CREATURES_ALLOWED_IN_ROOM 10


class Room{


public:

    //create vector of pointers to creatures to allow any type to be added to the vector
    std::vector<Creature*> *creatures;

    int north_neighbor, south_neighbor, west_neighbor, east_neighbor, room_number;


   //constructor/destructors
   Room();
   ~Room();

   //setters
    void setState(Global::State passedState);
    void setNorthNeighbor(int north);
    void setSouthNeighbor(int south);
    void setWestNeighbor(int west);
    void setEastNeighbor(int east);
    void setRoomNumber(int room_number);

    //getters
    Global::State getState();
    int getNorthNeighbor();
    int getSouthNeighbor();
    int getWestNeighbor();
    int getEastNeighbor();
    int getRoomNumber();

    //methods for creatures
    void addCreature(int creature);
    void removeCreaturePermanent(int creature);
    void addCreature(Creature* creature);
    Creature* removeCreature(int creature);
    Creature* getPCFromRoom();
    Creature* getNextNPCFromRoom();
    Creature* getNextAnimalFromRoom();
    bool containsNPC();
    bool containsAnimal();
    //helper functions for printing room info
    void printCreaturesInRoom();
    void printNeighbors();
    //static so this method can be used without needing instantiation of the class
    static std::string creatureTypeToString(Global::Creature type);





private:
    Global::State state;




};


#endif //HOMEWORK_1_ROOM_H

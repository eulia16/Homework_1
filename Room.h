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
    //use unique pointer so memory manages itself
    std::vector<std::unique_ptr<Creature>> creatures;

    enum State{ CLEAN, HALF_DIRTY, DIRTY };

   //constructor/destructors
   Room();
   ~Room();
    [[maybe_unused]] Room (State state, int north, int south, int west, int east, int roomNumber);

   //setters
    void setState(State passedState);
    void setNorthNeighbor(int north);
    void setSouthNeighbor(int south);
    void setWestNeighbor(int west);
    void setEastNeighbor(int east);
    void setRoomNumber(int room_number);

    //getters
    State getState();
    int getNorthNeighbor();
    int getSouthNeighbor();
    int getWestNeighbor();
    int getEastNeighbor();
    int getRoomNumber();

    //methods for creatures
    void addCreature(int creature);
    void removeCreature(int creature);
    void addCreature(int creature, Global::Creature creatureType);
    void removeCreature(int creature, Global::Creature creatureType);
    void containsAnimal(Global::Creature creatureType);
    void containsNPC(Global::Creature creatureType);
    void printCreaturesInsideRoom();
    int getNumberOfCreaturesInside();
    //static so this method can be used without needing instantiation of the class
    static std::string creatureTypeToString(Global::Creature type);


private:
    State state;
    int north_neighbor, south_neighbor, west_neighbor, east_neighbor, room_number;



};


#endif //HOMEWORK_1_ROOM_H

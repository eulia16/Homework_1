//
// Created by Ethan's Macbook on 8/2/23.
//

#ifndef HOMEWORK_1_ROOM_H
#define HOMEWORK_1_ROOM_H


#include "Creature.h"
#include "Global.h"
#include <string>

#define MAX_CREATURES 10


class Room{


public:

    std::vector<Creature> creatures;

    enum State{ CLEAN, HALF_DIRTY, DIRTY };
    enum Creature{ PC=0, ANIMAL=1, NPC=2 };


   //constructor/destructors
   Room();
   ~Room();
    [[maybe_unused]] Room (State state, int north, int south, int west, int east);

   //setters
    void setState(State passedState);
    void setNorthNeighbor(int north);
    void setSouthNeighbor(int south);
    void setWestNeighbor(int west);
    void setEastNeighbor(int east);

    //getters
    State getState();
    int getNorthNeighbor();
    int getSouthNeighbor();
    int getWestNeighbor();
    int getEastNeighbor();

    //methods for creatures
    void addCreature(int creature);
    void removeCreature(int creature);
    void addCreature(int creature, Room::Creature creatureType);
    void removeCreature(int creature, Room::Creature creatureType);
    void containsAnimal(Room::Creature creatureType);
    void containsNPC(Room::Creature creatureType);
    void printCreaturesInsideRoom();
    //static so this method can be used without needing instantiation of the class
    static std::string creatureTypeToString(Creature type);







//will follow a sentinal based head and tail doubly linked list data structure scheme to keep
//track of the animals inside of each room, allowing for ease of removal and addition to a room

private:
    State state;
    int north_neighbor, south_neighbor, west_neighbor, east_neighbor;

    //hidden abstraction methods for adding/deleting creatures

    void insertNode(Node *node);
    Node *deleteNode(Node* node);
    Node *deleteNode(std::string node);
    Node *deleteNode(int creature);
    Node *findNode();


};


#endif //HOMEWORK_1_ROOM_H

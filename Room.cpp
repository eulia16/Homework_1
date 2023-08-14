//
// Created by Ethan's Macbook on 8/2/23.
//
#include <iostream>
#include "Room.h"

//constructors/destructorst;
[[maybe_unused]] Room::Room (State state, int north, int south, int west, int east){
        this->state = state;
        this->north_neighbor = north;
        this->south_neighbor = south;
        this->east_neighbor = east;
        this->west_neighbor = west;
    }

    Room::Room() {
        std::cout << "Constructor was invoked" << std::endl;
        std::cout << "trinity waz here" << std::endl;
    }

    Room::~Room(){
        //delete all the creatures from the room when the game ends
        delete[] *creatures;

        std::cout << "Destructor was invoked" << std::endl;
    }

    //setters
    void Room::setNorthNeighbor(int north){
        this->north_neighbor = north;
    }
    void Room::setSouthNeighbor(int south){
        this->south_neighbor = south;
    }
    void Room::setWestNeighbor(int west){
        this->west_neighbor = west;
    }
    void Room::setEastNeighbor(int east){
        this->east_neighbor = east;
    }

    void Room::setState(State passedState){
        this->state = passedState;
    }

    //getters
    Room::State Room::getState(){
        return this->state;
    }
   int Room::getNorthNeighbor(){
    return this->north_neighbor;
   }
    int Room::getSouthNeighbor(){
        return this->south_neighbor;
    }
    int Room::getEastNeighbor(){
        return this->east_neighbor;
    }
    int Room::getWestNeighbor(){
        return this->west_neighbor;
    }

    //functionality of room
    void Room::addCreature(int creature){
        Room::creatures.push_back(new Creature(creature));

    }

    void Room::removeCreature(int creature){

    }
    void Room::addCreature(int creature, Room::Creature creatureType){

    }
    void Room::removeCreature(int creature, Room::Creature creatureType){

    }




//private abstraction methods of rooms for adding/searching/removing node(creatures)

    void Room::insertNode(Room::Node *node) {
        node->next = HEAD->next;
        HEAD->next = node;
        node->prev = HEAD;
        node->next->prev  = node;
    }

    Room::Node *Room::deleteNode(Room::Node *node) {



    }

    Room::Node *Room::deleteNode(std::string node){

    }

    Room::Node *Room::deleteNode(int creature){

    }

    Room::Node* Room::findNode(){

    }


    void Room::printCreaturesInsideRoom(){

    for(auto node : Room::creatures){
        Room::Creature temp = node->type;
        std::cout <<"Creature Name: "<<node->name << ", Creature Type: " << creatureTypeToString(temp);
    }

    }

    std::string Room::creatureTypeToString(Room::Creature type){

    switch(type){
        case Room::Creature::PC:
            return "PC";
        case Room::Creature::ANIMAL:
            return "ANIMAL";
        case Room::Creature::NPC:
            return "NPC";
    }

    }









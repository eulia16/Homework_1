//
// Created by Ethan's Macbook on 8/2/23.
//
#include <iostream>
#include "Room.h"
#include "Creature.h"
#include "Animal.h"
#include "NPC.h"
#include "PC.h"
#include "Global.h"

//constructors/destructors;
[[maybe_unused]] Room::Room (State state, int north, int south, int west, int east, int room_number){
        this->state = state;
        this->north_neighbor = north;
        this->south_neighbor = south;
        this->east_neighbor = east;
        this->west_neighbor = west;
        this->room_number = room_number;
        this->creatures = new std::vector<Creature*> ;

    }

    Room::Room() {
        std::cout << "Constructor was invoked" << std::endl;
        std::cout << "trinity waz here" << std::endl;
        this->creatures = new std::vector<Creature*> ;
    }

    Room::~Room(){
        //delete all the creatures from the room when the game ends
        delete this->creatures;


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
    void Room::setRoomNumber(int room_number) {
        this->room_number = room_number;
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
    int Room::getRoomNumber() {
        return this->room_number;
    }

    //functionality of room
    void Room::addCreature(int creature) {
        //check if room is full
        if (this->creatures->size() == MAX_CREATURES_ALLOWED_IN_ROOM) {
            std::cout << "There are already 10 creatures inside of room: " << this->getRoomNumber();
            return;
        }

        if (creature == Global::Creature::ANIMAL) {
            auto* animal = new Animal();
            this->creatures->push_back(animal);
            return;
        }

        if (creature == Global::Creature::NPC) {
            NPC* npc = new NPC();
            this->creatures->push_back(npc);
            return;
        }

        if(creature == Global::Creature::PC){
            if(Global::PC_is_in_game()) {
                std::cout << "The PC is already in the game in room: " << Global::PC_LOCATION << std::endl;
                return;
            }
            else {
                std::cout << "Adding PC to game: " << Global::PC_LOCATION<< std::endl;
                PC* pc = new PC();
                this->creatures->push_back(pc);
                Global::pc_has_entered_game(true);
                Global::update_pc_location(this->getRoomNumber());
                return;
        }
        }
    }


    void Room::removeCreaturePermanent(int creature){
        this->creatures.
    }
    void Room::addCreature(Creature* creature){
    if(this->creatures->size() > 9){
        std::cout << "There are already 10 creatures in this room, find another room";
        return;
    }
        this->creatures->push_back(creature);
    }
    Creature* Room::removeCreature(int creature){

    }



    std::string Room::creatureTypeToString(Global::Creature type){

    switch(type){
        case Global::Creature::PC:
            return "PC";
        case Global::Creature::ANIMAL:
            return "ANIMAL";
        case Global::Creature::NPC:
            return "NPC";
    }

    }









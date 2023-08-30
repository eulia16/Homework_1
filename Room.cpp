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


    }

    Room::Room() {
        std::cout << "Constructor was invoked" << std::endl;
        std::cout << "trinity waz here" << std::endl;
    }

    Room::~Room(){
        //delete all the creatures from the room when the game ends
        for (auto& ptr : creatures) {
            ptr.reset();
        }


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
        if (this->creatures.size() == MAX_CREATURES_ALLOWED_IN_ROOM) {
            std::cout << "There are already 10 creatures inside of room: " << this->getRoomNumber();
            return;
        }

        if (creature == Global::Creature::ANIMAL)
            this->creatures.push_back(std::make_unique<Animal>());

        if (creature == Global::Creature::NPC)
            this->creatures.push_back(std::make_unique<NPC>());
        else
            if(Global::PC_is_in_game())
                std::cout << "The PC is already in the game in room: " << Global::PC_LOCATION;
            else {
                this->creatures.push_back(std::make_unique<PC>());
                Global::pc_has_entered_game(true);
                Global::update_pc_location(this->getRoomNumber());
            }
    }


    void Room::removeCreature(int creature){
        //this->creatures.erase()
    }
    void Room::addCreature(int creature, Global::Creature creatureType){

    }
    void Room::removeCreature(int creature, Global::Creature creatureType){

    }

        [[maybe_unused]] int Room::getNumberOfCreaturesInside(){
        return this->creatures.size();
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









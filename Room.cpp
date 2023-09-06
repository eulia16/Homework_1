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




    Room::Room() {
        std::cout << "Constructor was invoked" << std::endl;
        std::cout << "trinity waz here" << std::endl;
        this->creatures = new std::vector<Creature*> ;
    }

    Room::~Room(){
        //delete all the creatures from the room when the game ends
        delete this->creatures;
        std::cout << "Destructor for room << " << this->room_number<<" was invoked" << std::endl;
    }

    //setters
    void Room::setNorthNeighbor(int north){
    std::cout << "setting north neighbor to: " << north <<std::endl;
        this->north_neighbor = north;
        std::cout << north_neighbor <<std::endl;
    }
    void Room::setSouthNeighbor(int south){
        std::cout << "setting south neighbor to: " << south <<std::endl;

        this->south_neighbor = south;
        std::cout << south_neighbor <<std::endl;
    }
    void Room::setWestNeighbor(int west){
        std::cout << "setting west neighbor to: " << west <<std::endl;

        this->west_neighbor = west;
        std::cout << west_neighbor <<std::endl;

    }
    void Room::setEastNeighbor(int east){
        std::cout << "setting east neighbor to: " << east <<std::endl;

        this->east_neighbor = east;
        std::cout << east_neighbor <<std::endl;
    }
    void Room::setState(Global::State passedState){
        this->state = passedState;
    }
    void Room::setRoomNumber(int room_number) {
        this->room_number = room_number;
    }

    //getters
    Global::State Room::getState(){
        return this->state;
    }

    int Room::getNorthNeighbor(){
    return north_neighbor;
   }

    int Room::getSouthNeighbor(){
        return south_neighbor;
    }
    int Room::getEastNeighbor(){
        return east_neighbor;
    }
    int Room::getWestNeighbor(){
        return west_neighbor;
    }
    int Room::getRoomNumber() {
        return this->room_number;
    }

    //helpers when printing room info
    void Room::printNeighbors(){
        //std::cout << "print neighbors function: "<< this->north_neighbor << this->south_neighbor << this->east_neighbor<< this->west_neighbor << std::endl;

        if(this->getNorthNeighbor() != -1)
            std::cout << "Neighbor "<< this->getNorthNeighbor() << " to the North" << std::endl;
        if(this->getEastNeighbor() != -1)
            std::cout << "Neighbor "<< this->getEastNeighbor() << " to the East" << std::endl;
        if(this->getWestNeighbor() != -1)
            std::cout << "Neighbor "<< this->getWestNeighbor() << " to the West" << std::endl;
        if(this->getSouthNeighbor() != -1)
            std::cout << "Neighbor "<< this->getSouthNeighbor() << " to the South" << std::endl;
    }

   void Room::printCreaturesInRoom(){
    //no need to check if room is empty because a room will never be emtpy as a PC will always be in
    //a room when using the look command
    for(auto creature : *this->creatures){
        if(creature->getType() == Global::Creature::NPC)
            std::cout << "NPC " << creature->get_creature_number() << std::endl;
        if(creature->getType() == Global::Creature::PC)
            std::cout << "PC" << std::endl;
        if(creature->getType() == Global::Creature::ANIMAL)
            std::cout << "Animal " << creature->get_creature_number() << std::endl;

    }

    }

    bool Room::containsNPC(){
        for(auto temp : *this->creatures){
            if(temp->getType() == Global::Creature::NPC)
                 return true;
         }
        return false;
    }
    bool Room::containsAnimal() {
        for(auto temp : *this->creatures){
            if(temp->getType() == Global::Creature::ANIMAL)
                return true;
        }
        return false;
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


    //appears to be working correctly
    void Room::removeCreaturePermanent(int creature){
        int ctr=0;
        for(auto temp : *this->creatures){
            if(temp->get_creature_number() == creature) {
                std::cout << "Creature" <<temp->get_creature_number() << ": has been permanently removed from the game(what a loser)" << std::endl;
                this->creatures->erase(creatures->begin() + ctr);
                return;
            }
            ctr++;
        }
    }
    void Room::addCreature(Creature* creature){
    if(this->creatures->size() > 9){
        std::cout << "There are already 10 creatures in this room, find another room";
        return;
    }
        this->creatures->push_back(creature);
    }

    Creature* Room::getPCFromRoom(){
    for(auto temp : *this->creatures){
        if(temp->getType() == Global::Creature::PC){
            auto PCHolder = removeCreature(temp->get_creature_number());
            std::cout << "returned PC" << std::endl;
            return PCHolder;
        }
    }
        std::cout << "PC was not found" << std::endl;
    return nullptr;
    }


    Creature* Room::removeCreature(int creature){
        int ctr=0;
        for(auto temp : *this->creatures){
            if(temp->get_creature_number() == creature) {
                std::cout << "Creature" <<temp->get_creature_number() << ": has been returned for transferring to other rooms" << std::endl;
                this->creatures->erase(creatures->begin() + ctr);
                return temp;
            }
            ctr++;
        }
    }

    Creature* Room::getNextNPCFromRoom(){
        for(auto creature : *this->creatures){
            if(creature->getType() == Global::Creature::NPC){
                return this->removeCreature(creature->get_creature_number());
            }
        }
        std::cout << "There are no NPC's left in this room." << std::endl;
        return nullptr;
    }

    Creature* Room::getNextAnimalFromRoom() {
        for(auto creature : *this->creatures){
            if(creature->getType() == Global::Creature::ANIMAL){
                return this->removeCreature(creature->get_creature_number());
            }
        }
        std::cout << "There are no Animals's left in this room." << std::endl;
        return nullptr;

    }

   int Room::getNumCreaturesInRoom(){
    return this->creatures->size();
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









//
// Created by Ethan's Macbook on 8/2/23.
//

#include <iostream>
#include "NPC.h"




void NPC::happy_noise(){
    std::cout << "NPC makes happy noise, respect has been increased by 1" << std::endl;
    Global::RESPECT++;
    std::cout << "Respect is now: " <<Global::RESPECT << std::endl;
}



void NPC::sad_noise(){
    std::cout << "NPC makes sad noise, respect has been decreased by 1" << std::endl;
    Global::RESPECT--;
    std::cout << "Respect is now: " <<Global::RESPECT << std::endl;
}


int NPC::get_creature_number(){
    return this->creature_number;
}


void NPC::setCreatureNumber(int creature_num){
    this->creature_number = creature_num;
}

int NPC::getType() {
    return 2;
}

Creature* NPC::getThis(){
    return this;
}
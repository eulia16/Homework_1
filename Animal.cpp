//
// Created by Ethan's Macbook on 8/2/23.
//

#include "Animal.h"
#include "Global.h"
#include <iostream>





void Animal::happy_noise(){
    std::cout << "Animal makes happy noise, respect has been increased by 1";
    Global::RESPECT++;
}



void Animal::sad_noise(){
    std::cout << "Animal makes sad noise, respect has been decreased by 1";
    Global::RESPECT++;
}


int Animal::get_creature_number(){

    return this->creature_number;
}

void Animal::setCreatureNumber(int creature_num){
    this->creature_number = creature_num;
}

int Animal::getType() {
    return 1;
}


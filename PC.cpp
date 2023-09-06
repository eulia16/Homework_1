//
// Created by Ethan's Macbook on 8/2/23.
//

#include <iostream>
#include "PC.h"




void PC::happy_noise(){
    std::cout << "The PC will never be happy"<< std::endl;
}



void PC::sad_noise(){
    std::cout << "The PC will never be sad"<< std::endl;
}


void PC::large_happy_noise(){
    std::cout << "never used" << std::endl;

}

void PC::large_sad_noise(){
    std::cout << "never used"<< std::endl;

}



int PC::get_creature_number(){
    return this->creature_number;
}

void PC::setCreatureNumber(int creature_num){
    this->creature_number = creature_num;
}

int PC::getType(){
    return 0;
};


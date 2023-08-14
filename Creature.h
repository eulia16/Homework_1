//
// Created by Ethan's Macbook on 8/2/23.
//


#ifndef HOMEWORK_1_CREATURE_H
#define HOMEWORK_1_CREATURE_H

#include "Global.h"


class Creature {

public:
    //will be overridden for runtime polymorphism by children functions
    virtual void happy_noise(){
    }

    virtual void sad_noise(){
    }

};


#endif //HOMEWORK_1_CREATURE_H

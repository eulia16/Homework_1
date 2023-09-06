//
// Created by Ethan's Macbook on 8/2/23.
//


#ifndef HOMEWORK_1_CREATURE_H
#define HOMEWORK_1_CREATURE_H

#include "Global.h"


class Creature {

public:


    //will be overridden for runtime polymorphism by children functions
    virtual void happy_noise()=0;

    virtual void sad_noise()=0;

    virtual void large_happy_noise()=0;

    virtual void large_sad_noise()=0;

    virtual int get_creature_number()=0;

    virtual void setCreatureNumber(int creature_num)=0;

    virtual int getType()=0;



private:
    int creature_number;

};


#endif //HOMEWORK_1_CREATURE_H

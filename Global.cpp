//
// Created by Ethan's Macbook on 8/2/23.
//

#include "Global.h"


namespace Global{
    int RESPECT = 40;
    int PC_LOCATION;
    int NAME =0;
    //respect methods implemented
    void increment_respect(int increment_value){
        RESPECT = RESPECT + increment_value;
    }
    void decrement_respect(int decrement_value){
        RESPECT = RESPECT - decrement_value;
    }
    //pc location methods implemented
    void update_pc_location(int location){
        PC_LOCATION = location;
    }
    //maybe have global methods for isAnimal, isNPC, and isPC
    bool isAnimal(int comparator){
        return Global::ANIMAL == comparator;
    }

    bool isNPC(int comparator){
        return Global::NPC == comparator;
    }

    bool isPC(int comparator){
        return Global::PC == comparator;
    }

}
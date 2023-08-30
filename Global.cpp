//
// Created by Ethan's Macbook on 8/2/23.
//
#include <iostream>
#include "Global.h"


namespace Global{
    int RESPECT = 40;
    int PC_LOCATION;
    int NAME =0;
    bool PC_IS_IN_GAME = false;


    //respect methods implemented
    void increment_respect(int increment_value){
        RESPECT = RESPECT + increment_value;
    }

    void pc_has_entered_game(bool pc_in_game){
        PC_IS_IN_GAME = true;
    }

    bool PC_is_in_game(){
        return PC_IS_IN_GAME;
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
        return Global::Creature::ANIMAL == comparator;
    }

    bool isNPC(int comparator){
        return Global::Creature::NPC == comparator;
    }

     bool isPC(int comparator){
        return Global::Creature::PC == comparator;
    }

    void printRespect(){
        std::cout << Global::RESPECT;
    }

}
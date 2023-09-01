//
// Created by Ethan's Macbook on 8/2/23.
//

#ifndef HOMEWORK_1_NPC_H
#define HOMEWORK_1_NPC_H

#include "Creature.h"
#include "Global.h"


class NPC : public Creature{

public:

    void happy_noise();



    void sad_noise();


    int get_creature_number();

    void setCreatureNumber(int creature_num);

    int getType();


private:
    int creature_number;

};


#endif //HOMEWORK_1_NPC_H

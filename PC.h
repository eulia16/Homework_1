//
// Created by Ethan's Macbook on 8/2/23.
//

#ifndef HOMEWORK_1_PC_H
#define HOMEWORK_1_PC_H

#include "Creature.h"
#include "Global.h"


class PC : public Creature{


public:

    void happy_noise();



    void sad_noise();


    int get_creature_number();

private:
    int creature_number;


};


#endif //HOMEWORK_1_PC_H

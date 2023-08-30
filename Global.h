
#ifndef HOMEWORK_1_GLOBAL_H
#define HOMEWORK_1_GLOBAL_H


namespace Global {
    extern int RESPECT;
    extern int PC_LOCATION;
    extern int NAME;
    extern bool PC_IS_IN_GAME;

    //extern v
    enum Creature {PC=0, ANIMAL=1, NPC=2};

    void increment_respect(int increment_value);

    void pc_has_entered_game(bool pc_in_game);

    bool PC_is_in_game();

    void decrement_respect(int decrement_value);

    //pc location methods implemented
    void update_pc_location(int location);

    //maybe have global methods for isAnimal, isNPC, and isPC
    bool isAnimal(int comparator);

    bool isNPC(int comparator);

    bool isPC(int comparator);

    void printRespect();


};



#endif //HOMEWORK_1_GLOBAL_H

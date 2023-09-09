
#ifndef HOMEWORK_1_GLOBAL_H
#define HOMEWORK_1_GLOBAL_H


namespace Global {
    extern int RESPECT;
    extern int PC_LOCATION;
    extern bool PC_IS_IN_GAME;

    enum Creature {PC=0, ANIMAL=1, NPC=2};
    enum State{ CLEAN, HALF_DIRTY, DIRTY };

    void pc_has_entered_game(bool pc_in_game);
    bool PC_is_in_game();
    void setNumber(int name);
    int getNumber();
    //pc location methods implemented
    void update_pc_location(int location);
    void printState(int state);


};



#endif //HOMEWORK_1_GLOBAL_H

//standard libraries
#include <iostream>

//user defined headers/classes
#include "Global.h"
#include "Animal.h"
#include "NPC.h"
#include "PC.h"
#include "Room.h"


using namespace std;


//functions prototypes
void setRoomShit(Room *room ,Room::State state, int tempN, int tempS, int tempW, int tempE);
void cleanupAllocatedMemory(Room *rooms);
int getNumberOfRooms();
void getRoomInformation(Room *rooms, int num_rooms);
void getCreatureInformation(Room *rooms);

int main() {
    int num_rooms;

    cout << Global::RESPECT << endl;

    Global::RESPECT++;

    cout << Global::RESPECT << endl;

    //get number of rooms from user input
    num_rooms = getNumberOfRooms();

    //initialize the pseduo-global vector of rooms that will live for the remainder of the game
    //yet remain a fixed size;
    Room *rooms = new Room[num_rooms];

    //obtain room information from user
     getRoomInformation(rooms, num_rooms);

    //read creature information from user
    getCreatureInformation(rooms);

    //enter main game loop
    //enterGame();

    //clean up allocated memory
    cleanupAllocatedMemory(rooms);

    return 0;

}


//helper functions for main program

void setRoomShit(Room *room, Room::State state, int tempN, int tempS, int tempW, int tempE){
    room->setState(state);
    room->setNorthNeighbor(tempN);
    room->setSouthNeighbor(tempS);
    room->setEastNeighbor(tempE);
    room->setWestNeighbor(tempW);
}

void cleanupAllocatedMemory(Room *rooms){
    delete[] rooms;
}

int getNumberOfRooms(){
    int num_rooms;
    //num rooms  info
    while(num_rooms < 0 || num_rooms > 100) {
        cout << "Please enter the nnumber of rooms(must be between 0 and 100 ): " << endl;
        cin >> num_rooms;
        cout << "num_rooms: " << num_rooms << endl;
    }

    return num_rooms;
}

void getRoomInformation(Room *rooms, int num_rooms){
    int tempState, tempN, tempS, tempW, tempE;
    for(int i=0; i<num_rooms; ++i){
        cout << "Please enter each rooms information" << endl;


        cin >> tempState >> tempN >> tempS >> tempE >> tempW;
        //initialize cast_state to allow creating room w proper state from enum
        auto cast_state = (Room::State) tempState;
        setRoomShit(&rooms[i], cast_state, tempN, tempS, tempE, tempW);
        cout << "Room Information printed" << endl << rooms[i].getState()
             << rooms[i].getNorthNeighbor() << rooms[i].getSouthNeighbor() <<
             rooms[i].getWestNeighbor() << rooms[i].getEastNeighbor() << endl;


    }
}

void getCreatureInformation(Room *rooms) {
    int num_creatures;

    //get number of creatures for game
    cout << "Please enter the number of creatures that will be in this game..." << endl;
    cin >> num_creatures;
    cout << "Please enter the information for each creature and what room they'll be in" << endl;

    int creature_type, creature_room;
    for (int i = 0; i < num_creatures; ++i) {
        cout << "Enter another creatures information" << endl;
        cin >> creature_type >> creature_room;
        if (creature_type == Global::PC) {
            cout << "PC will start in room: " << creature_room;
            Global::PC_LOCATION = creature_room;
        }
        rooms[creature_room].addCreature(creature_type);

    }

}



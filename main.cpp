//standard libraries
#include <iostream>
#include <string.h>
//user defined headers/classes
#include "Global.h"
#include "Animal.h"
#include "NPC.h"
#include "PC.h"
#include "Room.h"


using namespace std;


//functions prototypes
void cleanupAllocatedMemory(Room *rooms);
int getNumberOfRooms();
void getRoomInformation(Room *rooms, int num_rooms);
void getCreatureInformation(Room *rooms);
void enterGame(Room* room);
//game commands
void look(Room* rooms);
void help();
void North(Room* rooms, int creatureNumber);
void South(Room* rooms, int creatureNumber);
void West(Room* rooms, int creatureNumber);
void East(Room* rooms, int creatureNumber);
void Clean(Room* rooms, int creatureNumber);
void Dirty(Room* rooms, int creatureNumber);

//helper functions
int getRandomRoom(Room* rooms);

int main() {
    int num_rooms;
    //get number of rooms from user input
    num_rooms = getNumberOfRooms();

    //initialize the pseduo-global vector of rooms that will live for the remainder of the game
    //yet remain a fixed size;
    Room *rooms = new Room[num_rooms];

    //obtain room information from user
    getRoomInformation(rooms, num_rooms);
    cout << "outside function " << endl;

    //read creature information from user
    getCreatureInformation(rooms);

    //enter main game loop
    enterGame(rooms);

    //clean up allocated memory
    cleanupAllocatedMemory(rooms);

    return 0;

}


//main game loop
void enterGame(Room* room){

    cout << "You are now entering the game(hint: enter help or look for more info while in the game)" << endl;

    while(Global::RESPECT > 0 && Global::RESPECT < 80){
        string command;
        cout << ">>>";
        cin >> command;

        //I think the list of commands a user is allowed to enter is the following:
        /*
         * PC commands:
         * look
         * help
         * north
         * south
         * east
         * west
         * clean
         * dirty
         * exit
         *
         * Other(colon) commands:
         * X:clean
         * X:dirty
         * X:north
         * X:south
         * X:west
         * X:east
         * */

        //first determing if the string contains a colon, if the string contains a colon,
        //then we know the command is for a specific creature and can proceed w/ those commands,
        //else we can go to normal PC commands
        char colon = ':';
        command.find(colon);

        auto colon_present = command.find(colon);

        if(colon_present != std::string::npos) {
            string creature = command.substr(0, colon_present);
            //convert creature string to int
            int intValue=0;
            try {
                intValue = std::stoi(creature); // Convert the string to an integer
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << "\nYou Entered a malformed command." <<  std::endl;
                continue;
            }
            string newCommand = command.substr(colon_present+1, command.length());

            if(newCommand == "north"){
                North(room, intValue);
            }
            if(newCommand == "south"){
                South(room, intValue);
            }
            if(newCommand == "west"){
                West(room, intValue);
            }
            if(newCommand == "east"){
                East(room, intValue);
            }
            if(newCommand == "clean"){
                Clean(room, intValue);
            }
            if(newCommand == "dirty"){
                Dirty(room, intValue);
            }

        }

        else {
            if(command == "help"){
                help();
            }
            if(command == "look"){
                look(room);
            }
            if(command == "north"){
                North(room, Global::getNumber());
            }
            if(command == "south"){
                South(room, Global::getNumber());
            }
            if(command == "west"){
                West(room, Global::getNumber());
            }
            if(command == "east"){
                East(room, Global::getNumber());
            }
            if(command == "clean"){
                Clean(room, Global::getNumber());
            }
            if(command == "dirty"){
                Dirty(room, Global::getNumber());
            }
            if(command == "exit"){
                cleanupAllocatedMemory(room);
                exit(0);
            }

        }
        cout << endl;
    }


}

//clean and dirty methods for pc
void Clean(Room* room, int creatureNumber){
    if(room[Global::PC_LOCATION].getState() == Global::State::CLEAN){
        cout << "The clean command does not work on clean rooms" << endl;
        return;
    }


    if(room[Global::PC_LOCATION].getState() == Global::State::DIRTY)
        room[Global::PC_LOCATION].setState(Global::State::HALF_DIRTY);
    else
        room[Global::PC_LOCATION].setState(Global::State::CLEAN);


    //respect dealings
    int numNPCs=0;
    for(auto creature : *room[Global::PC_LOCATION].creatures){
        if(creature->getType() == Global::Creature::NPC) {
            if(creatureNumber == creature->get_creature_number())
                creature->large_sad_noise();
            else
                creature->sad_noise();
            numNPCs++;
        }
        else{
            if(creatureNumber == creature->get_creature_number())
                creature->large_happy_noise();
            else
                creature->happy_noise();
        }

    }
    //if room is fully clean, all npc's must leave to other rooms
    if(room[Global::PC_LOCATION].containsNPC() && room[Global::PC_LOCATION].getState() == Global::State::CLEAN){

        for(int i =0; i<numNPCs; ++i){
            //get the creature from the room
            int randomRoom = getRandomRoom(room);

            auto NPC = room[Global::PC_LOCATION].getNextNPCFromRoom();
            if(randomRoom == -1){
                cout << "You have forced creature " << NPC->get_creature_number() << " out of the room, you will regret this..."<< endl;
                delete NPC;
                //have every creature remaining in the room shame the player for his transgressions
                for(auto creature : *room[Global::PC_LOCATION].creatures){
                    creature->sad_noise();
                }
                return;

            }

            room[randomRoom].addCreature(NPC);
            //then we will change the state of the room the creature just transferred to in case it is also clean
            if(room[randomRoom].getState() == Global::State::CLEAN)
                room[randomRoom].setState(Global::State::HALF_DIRTY);
            cout <<"creature " << NPC->get_creature_number() << " will leave to room: " << randomRoom << endl;


        }
    }


}


void Dirty(Room* room, int creatureNumber){
    if(room[Global::PC_LOCATION].getState() == Global::State::DIRTY){
        cout << "The dirty command does not work on dirty rooms" << endl;
        return;
    }

    if(room[Global::PC_LOCATION].getState() == Global::State::CLEAN)
        room[Global::PC_LOCATION].setState(Global::State::HALF_DIRTY);
    else
        room[Global::PC_LOCATION].setState(Global::State::DIRTY);

    int numAnimals=0;
    for(auto creature : *room[Global::PC_LOCATION].creatures){
        if(creature->getType() == Global::Creature::ANIMAL) {
            if(creatureNumber == creature->get_creature_number())
                creature->large_sad_noise();
            else
                creature->sad_noise();
            numAnimals++;
        }
        else{
            if(creatureNumber == creature->get_creature_number())
                creature->large_happy_noise();
            else
                creature->happy_noise();
        }

    }
    //if room is fully clean, all npc's must leave to other rooms
    if(room[Global::PC_LOCATION].containsAnimal() && room[Global::PC_LOCATION].getState() == Global::State::DIRTY){

        for(int i =0; i<numAnimals; ++i){
            //get the creature from the room
            int randomRoom = getRandomRoom(room);
            //check to see if random room returned -1(no neighbors available)
            //if so we will force the creature out of the game
            auto Animal = room[Global::PC_LOCATION].getNextAnimalFromRoom();
            if(randomRoom == -1){
                cout << "You have forced creature " << Animal->get_creature_number() << " out of the room, you will regret this..."<< endl;
                //have every creature remaining in the room shame the player for his transgressions
                delete Animal;
                for(auto creature : *room[Global::PC_LOCATION].creatures){
                    creature->sad_noise();
                }
                return;

            }
            room[randomRoom].addCreature(Animal);
            //then we will change the state of the room the creature just transferred to in case it is also clean
            if(room[randomRoom].getState() == Global::State::CLEAN)
                room[randomRoom].setState(Global::State::HALF_DIRTY);
            cout <<"creature " << Animal->get_creature_number() << " will leave to room: " << randomRoom << endl;


        }
    }



}

int getRandomRoom(Room* room){
    std::vector<int> *neighborHolder = new std::vector<int>;
    //add them to vector if they exist
    if(room[Global::PC_LOCATION].getNorthNeighbor() != -1 && room[room[Global::PC_LOCATION].getNorthNeighbor()].getNumCreaturesInRoom() < 10)
        neighborHolder->push_back(room[Global::PC_LOCATION].getNorthNeighbor());
    if(room[Global::PC_LOCATION].getSouthNeighbor() != -1 && room[room[Global::PC_LOCATION].getSouthNeighbor()].getNumCreaturesInRoom() < 10)
        neighborHolder->push_back(room[Global::PC_LOCATION].getSouthNeighbor());
    if(room[Global::PC_LOCATION].getEastNeighbor() != -1 && room[room[Global::PC_LOCATION].getEastNeighbor()].getNumCreaturesInRoom() < 10)
        neighborHolder->push_back(room[Global::PC_LOCATION].getEastNeighbor());
    if(room[Global::PC_LOCATION].getWestNeighbor() != -1 && room[room[Global::PC_LOCATION].getWestNeighbor()].getNumCreaturesInRoom() < 10)
        neighborHolder->push_back(room[Global::PC_LOCATION].getWestNeighbor());
    if(neighborHolder->empty())
        return -1;

    return (neighborHolder->at(rand() % neighborHolder->size()));

}

//movement of pc between rooms function

void North(Room* room, int creatureNumber){
    if(room[Global::PC_LOCATION].getNorthNeighbor() == -1) {
        cout << "There is no neighbor to the North"<< endl;
        return;
    }
    else {
        //move PC like normal
        if(Global::getNumber() == creatureNumber) {
            if(room[room[Global::PC_LOCATION].getNorthNeighbor()].getNumCreaturesInRoom() >9)
                return;
            room[room[Global::PC_LOCATION].getNorthNeighbor()].addCreature(room[Global::PC_LOCATION].getPCFromRoom());
            Global::PC_LOCATION = room[Global::PC_LOCATION].getNorthNeighbor();
            cout << "PC leaves North to room: " << Global::PC_LOCATION << endl;
        }
        else{
            if(room[room[Global::PC_LOCATION].getNorthNeighbor()].getNumCreaturesInRoom() > 9){
                cout << "The north room is full, creature " << creatureNumber << "cannot move there"<< endl;
                auto temp = room[Global::PC_LOCATION].removeCreature(creatureNumber);
                temp->sad_noise();
                room[Global::PC_LOCATION].addCreature(temp);
                return;
            }
            room[room[Global::PC_LOCATION].getNorthNeighbor()].addCreature(room[Global::PC_LOCATION].removeCreature(creatureNumber));
            cout << "Creature "<< creatureNumber << " has moved North. " << endl;
        }
    }
}

void South(Room* room, int creatureNumber){
    if(room[Global::PC_LOCATION].getSouthNeighbor() == -1) {
        cout << "There is no neighbor to the South"<< endl;
        return;
    }
    else {
        if(Global::getNumber() == creatureNumber) {
            if(room[room[Global::PC_LOCATION].getSouthNeighbor()].getNumCreaturesInRoom() >9)
                return;
            room[room[Global::PC_LOCATION].getSouthNeighbor()].addCreature(room[Global::PC_LOCATION].getPCFromRoom());
            Global::PC_LOCATION = room[Global::PC_LOCATION].getSouthNeighbor();
            cout << "PC leaves South to room: " << Global::PC_LOCATION << endl;
        }
        else{
            if(room[room[Global::PC_LOCATION].getSouthNeighbor()].getNumCreaturesInRoom() > 9){
                cout << "The north room is full, creature " << creatureNumber << "cannot more there"<< endl;
                auto temp = room[Global::PC_LOCATION].removeCreature(creatureNumber);
                temp->sad_noise();
                room[Global::PC_LOCATION].addCreature(temp);
                return;
            }
            room[room[Global::PC_LOCATION].getSouthNeighbor()].addCreature(room[Global::PC_LOCATION].removeCreature(creatureNumber));
            cout << "Creature "<< creatureNumber << " has moved South. " << endl;
        }
    }
}

void East(Room* room, int creatureNumber){
    if(room[Global::PC_LOCATION].getEastNeighbor() == -1) {
        cout << "There is no neighbor to the East"<< endl;
        return;
    }
    else {
        if(Global::getNumber() == creatureNumber) {
            if(room[room[Global::PC_LOCATION].getEastNeighbor()].getNumCreaturesInRoom() >9)
                return;
            room[room[Global::PC_LOCATION].getEastNeighbor()].addCreature(room[Global::PC_LOCATION].getPCFromRoom());
            Global::PC_LOCATION = room[Global::PC_LOCATION].getEastNeighbor();
            cout << "PC leaves East to room: " << Global::PC_LOCATION << endl;
        }
        else{
            if(room[room[Global::PC_LOCATION].getNorthNeighbor()].getNumCreaturesInRoom() > 9){
                cout << "The north room is full, creature " << creatureNumber << "cannot more there"<< endl;
                auto temp = room[Global::PC_LOCATION].removeCreature(creatureNumber);
                temp->sad_noise();
                room[Global::PC_LOCATION].addCreature(temp);
                return;
            }
            room[room[Global::PC_LOCATION].getEastNeighbor()].addCreature(room[Global::PC_LOCATION].removeCreature(creatureNumber));
            cout << "Creature "<< creatureNumber << " has moved East. " << endl;
        }
    }
}

void West(Room* room, int creatureNumber){
    if(room[Global::PC_LOCATION].getWestNeighbor() == -1) {
        cout << "There is no neighbor to the West"<< endl;
        return;
    }
    else {
        if(Global::getNumber() == creatureNumber) {
            if(room[room[Global::PC_LOCATION].getWestNeighbor()].getNumCreaturesInRoom() >9)
                return;
            room[room[Global::PC_LOCATION].getWestNeighbor()].addCreature(room[Global::PC_LOCATION].getPCFromRoom());
            Global::PC_LOCATION = room[Global::PC_LOCATION].getWestNeighbor();
            cout << "PC leaves West to room: " << Global::PC_LOCATION << endl;
        }
        else{
            if(room[room[Global::PC_LOCATION].getNorthNeighbor()].getNumCreaturesInRoom() > 9){
                cout << "The north room is full, creature " << creatureNumber << "cannot more there"<< endl;
                auto temp = room[Global::PC_LOCATION].removeCreature(creatureNumber);
                temp->sad_noise();
                room[Global::PC_LOCATION].addCreature(temp);
                return;
            }
            room[room[Global::PC_LOCATION].getWestNeighbor()].addCreature(room[Global::PC_LOCATION].removeCreature(creatureNumber));
            cout << "Creature "<< creatureNumber << " has moved West. " << endl;
        }
    }
}



void look(Room* room){
   cout << "Room: " << room[Global::PC_LOCATION].getRoomNumber();
   cout << ", ";
   Global::printState(room[Global::PC_LOCATION].getState());
   room[Global::PC_LOCATION].printNeighbors();
   cout << "Contains: " << endl;
   room[Global::PC_LOCATION].printCreaturesInRoom();

}

void help(){
        cout << "This is the help command, it will explain all of the rules of the game to you as well as all of the commands you can use the goal of the game is to(obviously win) get your respect to 80, and avoid losing(respect goes to 0) You will enter data to create your world, and then will travel the world as the PC, forcing creatures to clean and dirty rooms, pretty messed up but you chose to play this game so anyways, here is a list of commands that you can use to force these poor creatures to play this cruel game(also the commands are case-sensitive)\n";
        cout << "help: you can enter this command to display all of the commands you can use\nlook: you can enter this commmand to see various different things about the current room you are in, i.e. it shows you the rooms neighbors and the different kinds of animals inside it\nnorth/south...: you can enter a direction to travel and change rooms, if you enter a direction that doesn't exist, you wont be able to move there(obviously)\nclean: This command will clean a given room, it will raise your respect if there are more Animals in a given room than NPC's\ndirty: the same as the clean command but reversed\nexit: This command will allow you to leave this god-forsaken land\ncreatureType:command: this command will allow you to force a creature to do the any of the commands stated above, such as leave towards the east, or clean a given room, ex. (1:clean) would make creature 1 to clean the room, this command will have 3x the effect of the normal clean, in this case\n" << endl;
}

void cleanupAllocatedMemory(Room *rooms){
    delete[] rooms;
}

int getNumberOfRooms(){
    int num_rooms =-1;
    //num rooms  info
    while(num_rooms < 0 || num_rooms > 100) {
        cout << "Please enter the number of rooms(must be between 0 and 100 ): " << endl;
        cin >> num_rooms;
        cout << "num_rooms: " << num_rooms << endl;
    }

    return num_rooms;
}

void getRoomInformation(Room *rooms, int num_rooms){
    int tempState=0, tempN=0, tempS=0, tempW=0, tempE=0;
    for(int i=0; i<num_rooms; ++i){
        cout << "Please enter each rooms information" << endl;
        cin >> tempState >> tempN >> tempS >> tempE >> tempW;
        //initialize cast_state to allow creating room w proper state from enum
        auto cast_state = (Global::State) tempState;
          //setRoomShit(&room, cast_state, tempN, tempS, tempE, tempW, i);
        rooms[i].setRoomNumber(i);
        rooms[i].setNorthNeighbor(tempN);
        rooms[i].setState(cast_state);
        rooms[i].setEastNeighbor(tempE);
        rooms[i].setSouthNeighbor(tempS);
        rooms[i].setWestNeighbor(tempW);
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
            cout << "PC will start in room: " << creature_room << endl;
            Global::setNumber(i);
        }
        rooms[creature_room].addCreature(creature_type);
        Creature* temp = rooms[creature_room].creatures->back();
        temp->setCreatureNumber(i);
    }

}



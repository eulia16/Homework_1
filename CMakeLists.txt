cmake_minimum_required(VERSION 3.26)
project(Homework_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Homework_1 main.cpp
        Animal.cpp
        Animal.h
        Creature.cpp
        Creature.h
        Global.cpp
        Global.h
        NPC.cpp
        NPC.h
        PC.cpp
        PC.h
        Room.cpp
        Room.h)

cmake_minimum_required(VERSION 3.21)
project(Projet_generateur_de_mots C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Projet_generateur_de_mots
        Functions.c
        Functions.h
        main.c
        node.c
        node.h
        tree.c
        tree.h)

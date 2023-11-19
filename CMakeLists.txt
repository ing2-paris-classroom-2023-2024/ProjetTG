cmake_minimum_required(VERSION 3.25)
project(ProjetTG C)

set(CMAKE_C_STANDARD 23)

add_executable(ProjetTG main.c Lecture_Fichier.c


        MatriceNiveau.h
        MatriceNiveau.c algo_remplissage.c algo_remplissage.h
        Exclusions.c
        Exclusions.h)

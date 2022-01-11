#ifndef JOC_H_INCLUDED
#define JOC_H_INCLUDED
#include "Board.h"


struct animal {
    int x, y, color;//pozitia pe tabla; x-coloana,y-rand
};

struct optiuniJoc {
    struct animal dogs[4];
    struct animal fox;
    int margin;
    int boxsize, dificultate;
    //definite pentru pvp: urmeazaMiscare, aFostFoxUltimaMiscare
    bool urmeazaMiscare;
    bool aFostFoxUltimaMiscare;
    int xSelectat, ySelectat;
    int counter_dog;
    int istoric_fox_x[100], istoric_fox_y[100];//array pentru coordonate
    int care_dog[100], istoric_dog_x[100], istoric_dog_y[100];
    int counter_miscari_dog, counter_miscari_fox;
    int intDogs[10], intFox[3];
};


#endif // JOC_H_INCLUDED

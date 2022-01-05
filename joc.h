#ifndef JOC_H_INCLUDED
#define JOC_H_INCLUDED
#include "Board.h"


struct animal {
    int x, y,color;//pozitia pe tabla; x-coloana,y-rand
};

struct optiuniJoc {
    struct animal dogs[4];
    struct animal fox;
    int margin;
    int boxsize, dificultate;
    //definite pentru pvp: urmeazaMiscare, aFostFoxUltimaMiscare
    bool urmeazaMiscare;
    bool aFostFoxUltimaMiscare;
    int xSelectat,ySelectat;
    int counter_dog;
};


#endif // JOC_H_INCLUDED

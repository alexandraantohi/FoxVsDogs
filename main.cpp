#include <graphics.h>
#include<iostream>
#include "nameIntro.h"
#include "meniu.h"
#include "Board.h"
#include "gameOver.h"

///BOARD X

///NAMEINTRO X

///gamvoer X

///CLASAMENT X

void functionare(){
    int meniu=mainMenu();
    if(meniu!=3){
        if(meniu==1)
            apelareNume();
        else
            joc_pvp();
    }
}
int main()
{
    functionare();
return 0;
}

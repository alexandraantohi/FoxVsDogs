#include <graphics.h>
#include<iostream>
#include "nameIntro.h"
#include "meniu.h"
#include "Board.h"
#include "gameOver.h"

void functionare(){
    int meniu=mainMenu();
    if(meniu!=3){
        int name=apelareNume();
        if(name==1){
            closegraph();
            functionare();
        }
        else{
            joc_pvp();
            int terminat=paginaGameOver();
            if(terminat==1){
                closegraph();
                functionare();
            }
            else{
                afisareGrafix();
            }
        }
    }
}
int main()
{
    functionare();
/*
int mode = 0;
mode = mainMenu();
if(mode!=3){
    //generateBoard();
    joc_pvp();
}*/
//paginaGameOver();
//generateBoard();
//afisareGrafix();
//mainMenu();
return 0;
}

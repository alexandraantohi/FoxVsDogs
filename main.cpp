#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdio.h>
#include<iostream>
#include "Clasament.h"
#include "meniu.h"
#include "Board.h"
#include "joc.h"

int main()
{
int mode = 0;
mode = mainMenu();
if(mode==2){
    //generateBoard();
    joc_pvp();
}
//generateBoard();
//afisareGrafix();
//mainMenu();
return 0;
}

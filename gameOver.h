#ifndef GAMEOVER_H_INCLUDED
#define GAMEOVER_H_INCLUDED

#include <iostream>
#include <string.h>
#include <time.h> ///pentru time_t
#include <graphics.h>
#include <conio.h> ///culoare text
#include "Clasament.h"
#include "Board.h"
using namespace std;


///Apelarea acestui header se face prin functia: paginaGameOver()



///pentru functie mouse:
struct position2{
    int i, j;
}menuCoordinates2;
void getCoordonates2(int x1,int y1){
    menuCoordinates2.i=x1;
    menuCoordinates2.j=y1;
};

///toDo: implementarea cronometrului se face prin stocarea timpului la care incepe jocul, din care se
///       scade timpul la care termina jocul



///Functie ce tine loc de main


///face din numerele secunde si minute un string + alte informatii:
void sir(int minute, int secunde, char cronometru[60]){
    char minuteSir[3], secundeSir[3] ;
    itoa(minute, minuteSir, 10);
    itoa(secunde, secundeSir, 10);
    strcpy(cronometru, "\0");
    strcpy(cronometru, "Timpul tau este ");
    strcat(cronometru, minuteSir);
    strcat(cronometru, " minute si ");
    strcat(cronometru, secundeSir);
    strcat(cronometru, " secunde.");
}

///interfata pentru sfarsit de joc:
void paginaGameOver(time_t timpFinal, bool castigator, char acestNume[]){
    ///timp.start=time(NULL); => se utilizeaza in functia 'initializareTimp()' pt a putea fi apelat din alt header
    int high=720, width=720;
    initwindow(high, width); //init. interfata
    int midx, midy;
    midx=getmaxx()/2;
    midy=getmaxy()/2;
    readimagefile("background.JPG", 0, 0, 720, 720);

    setbkcolor(COLOR(33,36,41)); ///culoarea pt gri 'background'!!
    settextstyle(1,0,7);
    settextjustify(1,1);
    outtextxy(midx, midy-200, "GAME OVER");

    int minute=0, secunde=0;
    minute=timpFinal/60;
    secunde=timpFinal%60;
    float timpTotal=secunde;
    timpTotal/=100;
    timpTotal+=minute;
    cout<<"\ntimpul scos: "<<timpFinal<<"\ncu minute si sec: "<<minute<<' '<<secunde<<"\n si in float: "<<timpTotal;
    ///toDo: minutele si secundele vor fi puse in "Clasament.h" pentru noul usr, la un loc cu numele resp.

    char cronometru[60];
    sir(minute, secunde, cronometru);

    ///afisare cine a castiga:
    settextstyle(4,0,5);
    //setbkcolor(RED);
    if(castigator){
        outtextxy(midx, midy, "A catigat vulpea!");
    }
    else{
        outtextxy(midx, midy, "Au catigat cainii!");
    }

    ///conditie daca nu s-a jucat pvp:
    if(acestNume[0]!='1'){
        ///afisare cronometru:
        setcolor(12);
        settextstyle(3,0,3);
        //setbkcolor(BLACK);
        outtextxy(midx-20, midy+170, cronometru); ///afisarea cronometrului
    }

    ///implementare buton exit & top:
    settextstyle(6,0,4);
    setcolor(BLACK);
    setbkcolor(YELLOW);

    ///conditie daca nu s-a jucat pvp:
    if(acestNume[0]!='1')
        outtextxy(midx-200, midy+250, "Afisare Top");
    outtextxy(midx+170, midy+250, "   EXIT   ");
    //outtextxy(midx+170, midy+250, "Play again");

    ///folosirea butoanelor:
    registermousehandler(WM_LBUTTONDOWN, getCoordonates2);
    int click=3;
    while(click==3){
        if(acestNume[0]!='1' && menuCoordinates2.i>=midx-310 && menuCoordinates2.i<=midx-95 && menuCoordinates2.j>=midy+224
            && menuCoordinates2.j<=midy+250+6)
                 click=2; ///afisare top
        if(menuCoordinates2.i>=midx+66 && menuCoordinates2.i<=midx+260 && menuCoordinates2.j>=midy+224
            && menuCoordinates2.j<=midy+250+6)
                click=1; ///reincepe joc
                }

    //getch();
    closegraph();

    ///click==1 => se joaca din nou
    ///click==2 => se afiseaza clasamentul
    ///return click;
    if(click==2 && acestNume[0]!='1')
        afisareGrafix(timpTotal, acestNume);
}

#endif // GAMEOVER_H_INCLUDED

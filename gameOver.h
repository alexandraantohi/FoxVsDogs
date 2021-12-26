#ifndef GAMEOVER_H_INCLUDED
#define GAMEOVER_H_INCLUDED

#include <iostream>
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

///struct pt timp:
struct{
    time_t start, finish;
}timp;

///Functie ce tine loc de main


///face din numerele secunde si minute un string + alte informatii:
void sir(int minute, int secunde, char cronometru[60]){
    char minuteSir[3], secundeSir[3] ;
    itoa(minute, minuteSir, 3);
    itoa(secunde, secundeSir, 3);
    strcpy(cronometru, "\0");
    strcpy(cronometru, "Timpul tau este ");
    strcat(cronometru, minuteSir);
    strcat(cronometru, " minute si ");
    strcat(cronometru, secundeSir);
    strcat(cronometru, " secunde.");
}

///interfata pentru sfarsit de joc:
int paginaGameOver(){
    timp.start=time(NULL);
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
    timp.finish=time(NULL) - timp.start;
    minute=timp.finish/60;
    secunde=timp.finish%60;
    joacaAcum.timp=secunde;
    ///toDo: minutele si secundele vor fi puse in "Clasament.h" pentru noul usr, la un loc cu numele resp.

    char cronometru[60];
    sir(minute, secunde, cronometru);

    ///afisare cine a castiga:
    settextstyle(4,0,5);
    bool castigaVulpea=true; ///doar de proba
    //setbkcolor(RED);
    if(castigaVulpea){
        outtextxy(midx, midy, "A catigat vulpea!");
    }
    else{
        outtextxy(midx, midy, "Au catigat cainii!");
    }

    ///afisare cronometru:
    setcolor(12);
    settextstyle(3,0,3);
    //setbkcolor(BLACK);
    outtextxy(midx-20, midy+170, cronometru); ///afisarea cronometrului

    ///implementare buton exit & top:
    settextstyle(6,0,4);
    setcolor(BLACK);
    setbkcolor(YELLOW);
    outtextxy(midx-200, midy+250, "Afisare Top");
    outtextxy(midx+170, midy+250, "Play again");

    ///folosirea butoanelor:
    registermousehandler(WM_LBUTTONDOWN, getCoordonates2);
    int click=3;
    while(click==3){
        if(menuCoordinates2.i>=midx-310 && menuCoordinates2.i<=midx-95 && menuCoordinates2.j>=midy+224
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
    return click;
}

#endif // GAMEOVER_H_INCLUDED

#ifndef NAMEINTRO_H_INCLUDED
#define NAMEINTRO_H_INCLUDED

#include<stdio.h>
#include<conio.h>
#include <iostream>
#include<graphics.h>
#include "Clasament.h"
#include "Board.h"
using namespace std;
struct position3{
    int i, j;
}menuCoordinates3;
void getCoordonates3(int x1,int y1){
    menuCoordinates3.i=x1;
    menuCoordinates3.j=y1;
};
///se apeleaza prin apelareNume()

void apelareNume(){
    int gd=DETECT, gm;
    //char nume[100];
    initwindow(720, 720, "NUME PLAYER");
    readimagefile("background.jpg",0,0,720,720);
    settextstyle(0,0,5);
    //setbkcolor(COLOR(33,36,41));
    setbkcolor(RED);
    char linie1[]="->IMPORTANT<-";
    outtextxy(100,100, linie1);
    char linie2[]="     Pentru continuarea jocului trebuie sa oferi un nume.";
    char linie3[]="Numele trebuie sa inceapa cu o litera si nu poate contine";
    char linie4[]="spatiu/spatii.";
    char linie5[]="Numele poate fi introdus in terminal(prima fereastra)";
    setbkcolor(COLOR(33,36,41));
    settextstyle(6,0,2);
    outtextxy(10,300, linie2);
    outtextxy(10, 330, linie3);
    outtextxy(10, 360, linie4);
    outtextxy(10, 390, linie5);

    ///pt test nume are val predefinita


    char deCititNume[300];
    cin>>deCititNume;
    //strcpy(nume, "Teodor");
    char numeContinuare[300]= "Numele tau va fi: ";
    strcat(numeContinuare, deCititNume);
    outtextxy(50, 500, numeContinuare);

    settextstyle(6, 0, 3);
    outtextxy(240, 600, "Vrei sa continui?");

    ///butoane:
    settextstyle(6, 0, 6);
    setbkcolor(YELLOW);
    setcolor(BLACK);
    outtextxy(100, 640, "   DA  ");
    outtextxy(400, 640, "   NU  ");
    registermousehandler(WM_LBUTTONDOWN, getCoordonates3);
    int click=3;
    int midx, pozY;
    midx=getmaxx()/2;
    pozY=640;
    while(click==3){
        if(menuCoordinates3.i>=midx-260 && menuCoordinates3.i<=midx-57 && menuCoordinates3.j>=pozY
            && menuCoordinates3.j<=pozY+54){
                  ///apasare DA
                 click=2;}
        if(menuCoordinates3.i>=midx+40  && menuCoordinates3.i<=midx+244 && menuCoordinates3.j>=pozY
            && menuCoordinates3.j<=pozY+54){
                 ///reincepe NU
                click=1;
                }
    }
    //getch();
    closegraph();
    if(click==2){ ///continuare e pentru modul de joc: player vs player / player vs pc
        int dificultate = menuGameMode();
        joc_pvc(deCititNume, dificultate);
    }
    //t.mode=click;
    //return t; ///returneaza ce trebuie apelat:
            ///pentru 1: apelare meniu
            ///pentru 2: apelare board
}


#endif // NAMEINTRO_H_INCLUDED

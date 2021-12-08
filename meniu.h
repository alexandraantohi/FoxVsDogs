#ifndef MENIU_H_INCLUDED
#define MENIU_H_INCLUDED
#include <iostream>
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
int mode = 0;
struct position {
    int i, j;
}menuCoordinates;

void getCoordonates(int x1,int y1){
    menuCoordinates.i=x1;
    menuCoordinates.j=y1;
}
void mainMenu(){
    int style, midx, midy;
    int size = 1;

    initwindow(720, 720);
    readimagefile("background.jpg",0,0,720,720);
    setcolor(COLOR(255,100,0));

    midx = getmaxx() / 2;
    midy = getmaxy() / 2;

    settextstyle(10, HORIZ_DIR, 7);
    settextjustify(1,1);
    outtextxy(midx, 120, "FOX AND HOUNDS");

    registermousehandler(WM_LBUTTONDOWN, getCoordonates);
    /* draw a rectangle */
    settextstyle(10, HORIZ_DIR, 5);
    while(mode==0){

       outtextxy(midx, midy-50, "PLAYER VS COMPUTER");
       outtextxy(midx, midy+50, "PLAYER VS PLAYER");
       outtextxy(midx, midy+150, "EXIT");

       if(menuCoordinates.i>=140 && menuCoordinates.i<=580 &&menuCoordinates.j<=335 && menuCoordinates.j>=285)
            mode = 1;
       if(menuCoordinates.i>=150 && menuCoordinates.i<=540 &&menuCoordinates.j<=435 && menuCoordinates.j>=385)
            mode = 2;
       if(menuCoordinates.i>=300 && menuCoordinates.i<=420 &&menuCoordinates.j<=535 && menuCoordinates.j>=485)
            mode = 3;
    }

    closegraph();

}

#endif // MENIU_H_INCLUDED

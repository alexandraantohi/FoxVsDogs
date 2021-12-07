#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdio.h>
#include<iostream>


using namespace std;

int margin = 70, boxsize = 70;

struct animal {
    int x, y;//pozitia pe tabla
};
struct animal dogs[4];
struct animal fox;

void drawPiece(int a, int b, int color){
    int x=margin + a*boxsize+boxsize/2;
    int y=margin + b*boxsize+boxsize/2;
    setcolor(color);
    setfillstyle(SOLID_FILL,color);
    circle(x,y,10);
    floodfill(x+1,y+1,color);
}

void drawAnimals() {
    for(int i=0; i< 4; i++){
        drawPiece(dogs[i].x,dogs[i].y,BLUE);
    }
    drawPiece(fox.x, fox.y,RED);
}

void initAnimals(){
    fox.x=3;
    fox.y=0;
    for(int i=0; i< 4; i++){
        dogs[i].x=2*i;
        dogs[i].y=7;
    }
}

void movement(animal &e, int a, int b){

    drawPiece(e.x,e.y, BLACK);
    drawPiece(a,b,RED);
    e.x = a;
    e.y = b;
}


void click_handler(int x, int y)
{
    if(x<margin || y<margin || x>margin + 8*boxsize|| y>margin+8*boxsize) return;
    x=x-margin;
    x=x/boxsize;
    y=y-margin;
    y=y/boxsize;
    movement(fox,x,y);
}

void generateBoard(){
    int gr = DETECT, gm;
    int r, c, x, y;
    x=margin;
    y=margin;
    bool black = false;
    initwindow(1000, 800);
    for (r = 0; r < 8; r++) {
        for (c = 1; c <= 8; c++) {
            if (black) {
                setfillstyle(SOLID_FILL, BLACK);
                rectangle(x, y, x + boxsize, y + boxsize);
                floodfill(x + 1, y + 1, WHITE);
            }
            else {
                setfillstyle(SOLID_FILL, WHITE);
                rectangle(x, y, x + boxsize, y + boxsize);
                floodfill(x + 1, y + 1, WHITE);
            }
            x = x + boxsize;
            black=!black;
        }
        black=!black;

        x = margin;
        y = boxsize + y;
    }
    //drawPiece(0,0);
    //drawPiece(0,1);
    //drawPiece(5,5);
    //drawPiece(0,2);
    //drawPiece(0,3);
    //drawPiece(1,2);
    initAnimals();
    drawAnimals();
    delay(1000);
    movement(fox,0,1);
    registermousehandler(WM_LBUTTONDOWN, click_handler);

    getch();
    closegraph();
}



#endif // BOARD_H_INCLUDED

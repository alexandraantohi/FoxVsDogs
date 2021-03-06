#ifndef GAMEMODE_H_INCLUDED
#define GAMEMODE_H_INCLUDED
#include <iostream>
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
struct positionn {
    int i, j;
}menuCoordinatess;

void getCoordonatess(int x1, int y1) {
    menuCoordinatess.i = x1;
    menuCoordinatess.j = y1;
}
int menuGameMode() {
    int style, midx, midy;
    int size = 1;
    int mode = 0;

    initwindow(720, 720);
    readimagefile("background.jpg", 0, 0, 720, 720);
    setbkcolor(YELLOW);
    setcolor(BLACK);

    midx = getmaxx() / 2;
    midy = getmaxy() / 2;

    settextstyle(10, HORIZ_DIR, 7);
    settextjustify(1, 1);

    registermousehandler(WM_LBUTTONDOWN, getCoordonatess);

    settextstyle(10, HORIZ_DIR, 5);
    while (mode == 0) {

        outtextxy(midx, midy - 50, "NORMAL");
        outtextxy(midx, midy + 50, "HARD");


        if (menuCoordinatess.i >= 310 && menuCoordinatess.i <= 410 && menuCoordinatess.j <= 335 && menuCoordinatess.j >= 285)
            mode = 1;
        if (menuCoordinatess.i >= 310 && menuCoordinatess.i <= 410 && menuCoordinatess.j <= 435 && menuCoordinatess.j >= 385)
            mode = 2;
    }
    settextstyle(10, HORIZ_DIR, 5);
    outtextxy(midx - 200, midy + 300, "Reluare Joc");
    outtextxy(midx + 250, midy + 300, "Joc Nou");
    int ok = 0;
    midy += 300;
    while (!ok) {
        if (menuCoordinatess.i >= midx - 338 && menuCoordinatess.i <= midx - 66 && menuCoordinatess.j<midy + 10 && menuCoordinatess.j>midy - 34)
            ok = 1; ///joc din fisier
        if (menuCoordinatess.i >= midx + 162 && menuCoordinatess.i <= midx + 336 && menuCoordinatess.j<midy + 10 && menuCoordinatess.j>midy - 34)
            ok = 2; ///joc nou
    }
    if (ok == 1)
        mode = -mode;
    closegraph();
    return mode;

}


#endif // GAMEMODE_H_INCLUDED

#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdio.h>
#include<iostream>
#include "gameOver.h"
using namespace std;

int margin = 70, boxsize = 70;

struct animal {
    int x, y,color;//pozitia pe tabla; x-coloana,y-rand
};
struct animal dogs[4];
struct animal fox;

void drawPiece(int a, int b, int color){
    //deseneaza piesa pe tabla la pozitia a, b de culoarea color
    int x=margin + a*boxsize+boxsize/2;
    int y=margin + b*boxsize+boxsize/2;
    setcolor(color);
    setfillstyle(SOLID_FILL,color);
    circle(x,y,10);
    floodfill(x+1,y+1,color);
}

void drawAnimals(){
    //deseneaza pe tabla toate piesele
    for(int i=0; i< 4; i++){
        drawPiece(dogs[i].x,dogs[i].y,dogs[i].color);
    }
    drawPiece(fox.x, fox.y,fox.color);
}

void initAnimals(){
    //initializeaza pozitiile de start pentru joc
    fox.x=3;
    fox.y=0;
    fox.color = RED;
    for(int i=0; i< 4; i++){
        dogs[i].x=2*i;
        dogs[i].y=7;
        dogs[i].color = BLUE;
    }
}

void movement(animal &e, int a, int b){
    //muta fox la pozitia a,b
    drawPiece(e.x,e.y, BLACK);
    drawPiece(a,b,e.color);
    e.x = a;
    e.y = b;
}

bool celulaOcupata(int x,int y){
    for(int i=0;i<4;i++)
        if(dogs[i].x == x && dogs[i].y == y)
            return true;
    if(fox.x == x && fox.y == y )
        return true;
    return false;
}


bool movement_dog(animal &dog, int x, int y){
    if(celulaOcupata(x,y))
        return false; //daca e ocupata de alta piesa nu putem muta
    if(x<0 || x>7 || y<0 || y>7)
        return false; // in afara tablei
    if(dog.y - 1 != y || (dog.x -1 != x&& dog.x+1 != x))
        return false; //mutare ilegala
    movement(dog,x,y);
}

bool movement_fox(animal &fox, int x, int y){
    if(celulaOcupata(x,y))
        return false; //daca e ocupata de alta piesa nu putem muta
    if(x<0 || x>7 || y<0 || y>7)
        return false; // in afara tablei

    int newX,newY,pozitiiFox[] = {-1,-1,  -1,1,   1,-1,   1,1}; // mutari posibile
    bool ok = false;
    for(int i=0;i<8;i+=2)
        {
            newX = fox.x + pozitiiFox[i];
            newY = fox.y + pozitiiFox[i+1];
            if(newX == x && newY == y)
                ok = true; // am gasit o mutare ok
        }
    if(!ok)
        return false;

    //if(fox.y - 1 != y || (fox.x -1 != x&& fox.x+1 != x))
    //    return false; //mutare ilegala
    movement(fox,x,y);
}

bool urmeazaMiscare = false;
bool aFostFoxUltimaMiscare = false;
int xSelectat,ySelectat;

int verificaScenariuCastig()
{
    if(fox.y == 7) // daca a ajuns pe ultimul rand, a castigat fox
        return 2;
    int newX,newY,pozitiiFox[] = {-1,-1,  -1,1,   1,-1,   1,1}; // mutari posibile
    for(int i=0; i<8; i+=2)
    {
        newX = fox.x + pozitiiFox[i];
        newY = fox.y + pozitiiFox[i+1];
        if(newX >= 0 && newX <8 && newY >= 0 && newY <8)
            if(!celulaOcupata(newX, newY))
                return 0;//daca fox are unde sa se duca
    }
    return 1;// daca fox nu are unde sa se duca si nici nu a ajuns jos, castiga dogs
}

void closeBoard()
{
    //getch();
    closegraph();
}

bool transforma_coordonate_in_pozitie(int &x, int &y){
    //calculeaza in care celula de pe tabla a fost dat click
    if(x<margin || y<margin || x>margin + 8*boxsize|| y>margin+8*boxsize) return false;//verifica daca click-ul a fost pe tabla si nu pe langa
    x=x-margin;
    x=x/boxsize;
    y=y-margin;
    y=y/boxsize;
    return true;
}

void muta_piesa(int sursa_x, int sursa_y, int destinatie_x, int destinatie_y){
    int castig;
    if(!aFostFoxUltimaMiscare)
        {
            if(sursa_x == fox.x && sursa_y == fox.y)
            {
                if(movement_fox(fox,destinatie_x,destinatie_y))
                {
                    aFostFoxUltimaMiscare = true;
                }
            }
        }
    else
    {
        for(int i=0; i<4; i++)
        {
            if(sursa_x == dogs[i].x && sursa_y == dogs[i].y) // daca a fost selectat un dog
            {
                if(movement_dog(dogs[i],destinatie_x,destinatie_y)) // daca a mutat dog cu succes
                {
                    aFostFoxUltimaMiscare = false;
                }
                // else
                // {
                //     //trebuie ales alt dog
                // }
            }
        }
    }
    castig = verificaScenariuCastig();
    if(castig != 0)
    {
        if(castig == 1)
            cout<<"Dogs win";
        else cout<<"Fox wins";
        closeBoard();
    }
}

void click_select(int x, int y){
    if(!transforma_coordonate_in_pozitie(x,y)) return;
    xSelectat = x;
    ySelectat = y;
}

void click_drop(int x, int y){
    if(!transforma_coordonate_in_pozitie(x,y)) return;
    muta_piesa(xSelectat, ySelectat, x, y);
}

void click_handler(int x, int y)
{
    //-nu chiar-muta fox in casuta pe care se da click
    int castig;
    if(!transforma_coordonate_in_pozitie(x,y)) return;
    /*
    // cod mutat in transforma_coordonate_in_pozitie()
    if(x<margin || y<margin || x>margin + 8*boxsize|| y>margin+8*boxsize) return;//verifica daca click-ul a fost pe tabla si nu pe langa
    x=x-margin;
    x=x/boxsize;
    y=y-margin;
    y=y/boxsize;

    //calculeaza in care celula de pe tabla a fost dat click
    */
    if(urmeazaMiscare)
    {
        if(!aFostFoxUltimaMiscare)
        {
            if(xSelectat == fox.x && ySelectat == fox.y)
            {
                if(movement_fox(fox,x,y))
                {
                    aFostFoxUltimaMiscare = true;
                    urmeazaMiscare = false;
                }
                urmeazaMiscare = false;
            }
        }
        else
        {
            for(int i=0; i<4; i++)
            {
                if(xSelectat == dogs[i].x && ySelectat == dogs[i].y) // daca a fost selectat un dog
                {
                    if(movement_dog(dogs[i],x,y)) // daca a mutat dog cu succes
                    {
                        aFostFoxUltimaMiscare = false;
                        urmeazaMiscare = false;
                    }
                    else
                    {
                        //trebuie ales alt dog
                        urmeazaMiscare = false;
                    }
                }

            }
        }
    }
    else
    {
        urmeazaMiscare = true;
        xSelectat = x;
        ySelectat = y;
        //memoreaza coordonatele unde a fost click
    }
    //cout<<x<<"---"<<y<<endl;
    //cout<<"Urmeaza dog"<<aFostFox<<endl;
    castig = verificaScenariuCastig();
    if(castig != 0)
    {
        if(castig == 1)
            cout<<"Dogs win";
        else cout<<"Fox wins";
        closeBoard();
    }
}

void generateBoard()
{
    //deseneaza tabla de sah si piesele pe tabla
    int gr = DETECT, gm;
    int r, c, x, y;
    x=margin;
    y=margin;
    bool black = false;
    initwindow(720, 720);
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
    //initAnimals();
    //drawAnimals();
    //delay(1000);
    //movement(fox,0,1);
    //registermousehandler(WM_LBUTTONDOWN, click_handler);


}

void joc_pvp(){
    timp.start=time(NULL);
    generateBoard();
    initAnimals();
    drawAnimals();
    // registermousehandler(WM_LBUTTONDOWN, click_handler);
    registermousehandler(WM_LBUTTONDOWN, click_select);
    registermousehandler(WM_LBUTTONUP, click_drop);

    closeBoard();
    paginaGameOver();
}


#endif // BOARD_H_INCLUDED

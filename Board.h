#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdio.h>
#include<iostream>
#include "gameOver.h"
#include "joc.h"
using namespace std;

struct optiuniJoc joc;

struct {
    time_t start, finish;
    char numeBoard[300];
}timp;//pentru cronometru


void initJoc() {
    joc.margin = 70;
    joc.boxsize = 70;
    joc.dificultate = 1;
    joc.urmeazaMiscare = false;
    joc.aFostFoxUltimaMiscare = false;
    joc.counter_dog = -1;//care caine a fost mutat ultimul pentru pvc
    joc.counter_miscari_dog = 0;//cate miscari a fost pentru dog
    joc.counter_miscari_fox = 0;
    joc.istoric_fox_x[0] = 3;//pozitiile la care a fost fox
    joc.istoric_fox_y[0] = 0;

}

void drawPiece(int a, int b, int color){
    //deseneaza piesa pe tabla la pozitia a, b de culoarea color
    int x=joc.margin + a*joc.boxsize+ joc.boxsize/2;
    int y=joc.margin + b* joc.boxsize+ joc.boxsize/2;
    setcolor(color);
    setfillstyle(SOLID_FILL,color);
    circle(x,y,10);
    floodfill(x+1,y+1,color);
}

void drawAnimals(){
    //deseneaza pe tabla toate piesele
    for(int i=0; i< 4; i++){
        drawPiece(joc.dogs[i].x,joc.dogs[i].y,joc.dogs[i].color);
    }
    drawPiece(joc.fox.x, joc.fox.y,joc.fox.color);
}

void initAnimals(){
    //initializeaza pozitiile de start pentru joc
    joc.fox.x=3;
    joc.fox.y=0;
    joc.fox.color = RED;
    for(int i=0; i< 4; i++){
        joc.dogs[i].x=2*i;
        joc.dogs[i].y=7;
        joc.dogs[i].color = BLUE;
    }
}

void movement(animal &e, int a, int b){
    //muta piesa la pozitia a,b
    drawPiece(e.x,e.y, BLACK);
    drawPiece(a,b,e.color);
    e.x = a;
    e.y = b;
}

bool celulaOcupata(int x,int y){
    if(x<0 || x>7 || y<0 || y>7)
        return true; // in afara tablei
    for(int i=0;i<4;i++)
        if(joc.dogs[i].x == x && joc.dogs[i].y == y)
            return true;
    if(joc.fox.x == x && joc.fox.y == y )
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

    joc.counter_miscari_dog++;
    joc.care_dog[joc.counter_miscari_dog] = joc.counter_dog;
    joc.istoric_dog_x[joc.counter_miscari_dog] = dog.x;//vechile valori ale lui x
    joc.istoric_dog_y[joc.counter_miscari_dog] = dog.y;

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
    joc.counter_miscari_fox++;
    joc.istoric_fox_x[joc.counter_miscari_fox] = x;//vechile valori ale lui x
    joc.istoric_fox_y[joc.counter_miscari_fox] = y;

    movement(fox,x,y);
}

void undo_fox()
{   if(joc.counter_miscari_fox < 1) return;
    joc.counter_miscari_fox--;
    movement(joc.fox, joc.istoric_fox_x[joc.counter_miscari_fox],joc.istoric_fox_y[joc.counter_miscari_fox]);
}

void undo_dog()
{
    int care_dog;
    if(joc.counter_miscari_dog < 1) return;
    care_dog = joc.care_dog[joc.counter_miscari_dog];


    movement(joc.dogs[care_dog],joc.istoric_dog_x[joc.counter_miscari_dog], joc.istoric_dog_y[joc.counter_miscari_dog]);
    joc.counter_miscari_dog--;
}

int verificaScenariuCastig()
{
    if(joc.fox.y == 7) // daca a ajuns pe ultimul rand, a castigat fox
        return 2;
    int newX,newY,pozitiiFox[] = {-1,-1,  -1,1,   1,-1,   1,1}; // mutari posibile
    for(int i=0; i<8; i+=2)
    {
        newX = joc.fox.x + pozitiiFox[i];
        newY = joc.fox.y + pozitiiFox[i+1];
        if(newX >= 0 && newX <8 && newY >= 0 && newY <8)
            if(!celulaOcupata(newX, newY))
                return 0;//daca fox are unde sa se duca
    }
    return 1;// daca fox nu are unde sa se duca si nici nu a ajuns jos, castiga dogs
}

void closeBoard()
{
    getch();
    closegraph();
}

bool transforma_coordonate_in_pozitie(int &x, int &y){
    //calculeaza in care celula de pe tabla a fost dat click
    if(x<joc.margin || y<joc.margin || x>joc.margin + 8* joc.boxsize|| y>joc.margin+8* joc.boxsize) return false;//verifica daca click-ul a fost pe tabla si nu pe langa
    x=x-joc.margin;
    x=x/joc.boxsize;
    y=y-joc.margin;
    y=y/joc.boxsize;
    return true;
}

void muta_piesa(int sursa_x, int sursa_y, int destinatie_x, int destinatie_y){
    int castig;
    if(!joc.aFostFoxUltimaMiscare)
        {
            if(sursa_x == joc.fox.x && sursa_y == joc.fox.y)
            {
                if(movement_fox(joc.fox,destinatie_x,destinatie_y))
                {
                    joc.aFostFoxUltimaMiscare = true;
                }
            }
        }
    else
    {
        for(int i=0; i<4; i++)
        {
            if(sursa_x == joc.dogs[i].x && sursa_y == joc.dogs[i].y) // daca a fost selectat un dog
            {
                joc.counter_dog = i;
                if(movement_dog(joc.dogs[i],destinatie_x,destinatie_y)) // daca a mutat dog cu succes
                {
                    joc.aFostFoxUltimaMiscare = false;

                }
                // else
                // {
                //     //trebuie ales alt dog
                // }
            }
        }
    }
    castig = verificaScenariuCastig();
    cout<<castig;
    if (castig != 0)
    {
        bool castigaVulpeaGameOver = true;
        if (castig == 1) {
            cout << "Dogs win";
            castigaVulpeaGameOver = false;
        }
        else cout << "Fox wins";
        //closeBoard();
        timp.finish = time(NULL) - timp.start;
        paginaGameOver(timp.finish, castigaVulpeaGameOver, timp.numeBoard);
    }
}

void muta_piesa_pvc(int sursa_x, int sursa_y, int destinatie_x, int destinatie_y){
    int castig;

    if (sursa_x == joc.fox.x && sursa_y == joc.fox.y)
    {
        if (movement_fox(joc.fox, destinatie_x, destinatie_y))
        {
            joc.aFostFoxUltimaMiscare = true;
        }
        else return;
    }
    else return;

    //for(int i=counter_dog; i<4; i++)
    bool ok = false;
    int new_x, new_x_dificultate_2, new_y;
    while (!ok)
    {
        joc.counter_dog++;
        joc.counter_dog = joc.counter_dog % 4; //trece la urmatorul caine si de la capat
        new_y = joc.dogs[joc.counter_dog].y -1;
        if (joc.dogs[joc.counter_dog].y % 2 != 0)
        {
            //facem mutare la dreapta
            new_x = joc.dogs[joc.counter_dog].x + 1;
            new_x_dificultate_2 = joc.dogs[joc.counter_dog].x - 1;
        }
        else
        {
            //face mutare la stanga
            new_x = joc.dogs[joc.counter_dog].x - 1;
            new_x_dificultate_2 = joc.dogs[joc.counter_dog].x + 1;
        }
        if(joc.dificultate == 1)//verifica daca celula un trebuie sa mute este libera
        {
            if (celulaOcupata(new_x, new_y) == false)
            {
                movement_dog(joc.dogs[joc.counter_dog], new_x, new_y);
                ok = true;
            }
        }
        else
        //pe dificultate 1 daca stanga, dreapta sunt libere si diferite de vulpe ca sa putem muta un caine
        {
            bool pas_1, pas_2;
            pas_1 = !celulaOcupata(new_x, new_y);
            if (new_x_dificultate_2 >= 0 && new_x_dificultate_2 < 8)
            {
                if(joc.fox.x == new_x_dificultate_2 && joc.fox.y == new_y)
                {
                    pas_2 = false;
                }
                else
                {
                    pas_2 = true;
                }
            }
            else
            {
                pas_2 = true;
            }

            if (pas_1 && pas_2)
            {
                movement_dog(joc.dogs[joc.counter_dog], new_x, new_y);
                ok = true;
            }
        }
    }
    castig = verificaScenariuCastig();

    if (castig != 0)
    {
        bool castigaVulpeaGameOver = true;
        if (castig == 1) {
            cout << "Dogs win";
            castigaVulpeaGameOver = false;
        }
        else cout << "Fox wins";
        //closeBoard();
        timp.finish = time(NULL) - timp.start;
        paginaGameOver(timp.finish, castigaVulpeaGameOver, timp.numeBoard);
    }
}

void click_select(int x, int y){
    if(!transforma_coordonate_in_pozitie(x,y)) return;
    joc.xSelectat = x;
    joc.ySelectat = y;
}

void click_drop(int x, int y){
    if(!transforma_coordonate_in_pozitie(x,y)) return;
    muta_piesa(joc.xSelectat, joc.ySelectat, x, y);
}

void click_drop_pvc(int x, int y){
    if(!transforma_coordonate_in_pozitie(x,y)) return;
    muta_piesa_pvc(joc.xSelectat, joc.ySelectat, x, y);
}

void click_undo(int x, int y){
    if(x > 100 && x < 200 && y > 640 && y < 800) {
    undo_fox();
    undo_dog();
    }

}

void click_undo_pvp(int x, int y) {
    if(x > 100 && x < 200 && y > 640 && y < 800) {
        if(joc.aFostFoxUltimaMiscare)
        {
            undo_fox();
        }
        else
        {
            undo_dog();
        }
        joc.aFostFoxUltimaMiscare = !joc.aFostFoxUltimaMiscare;
    }
}

void generateBoard()
{
    //deseneaza tabla de sah si piesele pe tabla
    int gr = DETECT, gm;
    int r, c, x, y;
    x=joc.margin;
    y=joc.margin;
    bool black = false;
    initwindow(720, 720);
    for (r = 0; r < 8; r++) {
        for (c = 1; c <= 8; c++) {
            if (black) {
                setfillstyle(SOLID_FILL, BLACK);
                rectangle(x, y, x + joc.boxsize, y + joc.boxsize);
                floodfill(x + 1, y + 1, WHITE);
            }
            else {
                setfillstyle(SOLID_FILL, WHITE);
                rectangle(x, y, x + joc.boxsize, y + joc.boxsize);
                floodfill(x + 1, y + 1, WHITE);
            }
            x = x + joc.boxsize;
            black=!black;
        }
        black=!black;

        x = joc.margin;
        y = joc.boxsize + y;
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
    settextstyle(6, 0, 5);
    setbkcolor(YELLOW);
    setcolor(BLACK);
    outtextxy(100, 640, " Undo ");


}

void joc_pvp() {
    strcpy(timp.numeBoard, "1");
    timp.start = time(NULL);
    initJoc();
    generateBoard();
    initAnimals();
    drawAnimals();
    // registermousehandler(WM_LBUTTONDOWN, click_handler);
    registermousehandler(WM_LBUTTONDOWN, click_select);
    registermousehandler(WM_LBUTTONUP, click_drop);
    registermousehandler(WM_RBUTTONDOWN, click_undo_pvp);
    closeBoard();

}

void joc_pvc(char* numeTastaturaNameIntro, int dificultate) {
    strcpy(timp.numeBoard, numeTastaturaNameIntro);
    timp.start = time(NULL);
    initJoc();
    joc.dificultate = dificultate;
    generateBoard();
    initAnimals();
    drawAnimals();
    registermousehandler(WM_LBUTTONDOWN, click_select);
    registermousehandler(WM_LBUTTONUP, click_drop_pvc);
    registermousehandler(WM_RBUTTONDOWN, click_undo);//click dreapta
    closeBoard();
}


#endif // BOARD_H_INCLUDED

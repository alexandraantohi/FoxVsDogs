#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdio.h>
#include<iostream>
#include "gameOver.h"
#include "joc.h"
#define MAX 50
using namespace std;

struct optiuniJoc joc;

struct {
    time_t start, finish;
    char numeBoard[300];
}timp;//pentru cronometru


/// de la linia 20
/// se ocupa cu salvarea schemei care se joaca in acest moment



void schimb(char s[], int c) {
    s[0] = '\0';
    int x = 0;
    bool zero = false;
    if (c % 10 == 0)
        zero = true;
    while (c) {
        x = c % 10 + x * 10;
        c /= 10;
    }
    int j = 0;
    while (x) {
        s[j++] = x % 10 + 48;
        x /= 10;
    }
    if (zero)
        s[j++] = 48;
    s[j] = '\0';
}

void dinTextInInt(char text[], int valR[], unsigned n) {
    text[0] = '\0';
    int j = 0;
    for (int i = 0; i < n;i++) {
        char p[30];
        p[0] = '\0';
        schimb(p, valR[i]);
        strcat(text, p);
        strcat(text, " ");
    }
    strcat(text, "\n");
}


void afara() {
    char* numeFisier = "fisierAfara.txt";
    FILE* fis;
    fis = fopen(numeFisier, "w");

    int Caini[30], Vulpea[30];
    for (int i = 0;i < 7;i += 2) {
        Caini[i] = joc.intDogs[i];
        Caini[i + 1] = joc.intDogs[i + 1];
    }
    Vulpea[0] = joc.intFox[0];
    Vulpea[1] = joc.intFox[1];
    char s[30];

    dinTextInInt(s, Vulpea, 2); ///pt vulpe e 2 {0,1}
    fprintf(fis, "%s", s);

    dinTextInInt(s, Caini, 8); /// pt caini e 8 ->dimnensiunea
    fprintf(fis, "%s", s);

    fclose(fis);
}

void salvareSchita() {
    joc.intFox[0] = joc.fox.x;
    joc.intFox[1] = joc.fox.y;
    joc.intDogs[0] = joc.dogs[0].x;
    joc.intDogs[1] = joc.dogs[0].y;
    joc.intDogs[2] = joc.dogs[1].x;
    joc.intDogs[3] = joc.dogs[1].y;
    joc.intDogs[4] = joc.dogs[2].x;
    joc.intDogs[5] = joc.dogs[2].y;
    joc.intDogs[6] = joc.dogs[3].x;
    joc.intDogs[7] = joc.dogs[3].y;
    afara();
    cout << '\n' << "\n_S-a notat modificarea si se va salva la iesire din modul joc!\n";
}

///de la linia 99 se ocupa cu jucarea unei scheme primite in fisier
void pozitieTextPiese(char textDogs[]) {
    int pozitieTabla[10] = { 0 };
    int xBoard = 0;
    int yBoard = 0;
    bool randX = true;
    int j = 0;
    for (int i = 0;i < strlen(textDogs); i++) {
        if (textDogs[i] > 47 && textDogs[i] < 58) ///codul ascii pt 0..9
        {
            int c = (int)textDogs[i];
            c -= 48;
            if (randX) {
                xBoard = xBoard * 10 + c;
            }
            else {
                yBoard = yBoard * 10 + c;
            }
        }
        else {
            if (randX == true)
                randX = false;
            else {
                randX = true;
                pozitieTabla[j++] = xBoard;
                pozitieTabla[j++] = yBoard;
                xBoard = 0;
                yBoard = 0;
            }
        }
    }
    if (j > 2) {
        for (int k = 0;k < j;k++)
            joc.intDogs[k] = pozitieTabla[k];
    }
    else {
        joc.intFox[0] = pozitieTabla[0];
        joc.intFox[1] = pozitieTabla[1];
    }
}

void citire()
{
    char* numeFisier = "fisierContinuare.txt";
    FILE* fis;
    fis = fopen(numeFisier, "r");
    char textFox[MAX];
    char textDogs[MAX];
    if ((fis = fopen(numeFisier, "r")) != NULL) {
        fgets(textFox, MAX, fis);
        fgets(textDogs, MAX, fis);

        pozitieTextPiese(textDogs);
        pozitieTextPiese(textFox);
        fclose(fis);
    }
}


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

void drawPiece(int a, int b, int color) {
    //deseneaza piesa pe tabla la pozitia a, b de culoarea color
    int x = joc.margin + a * joc.boxsize + joc.boxsize / 2;
    int y = joc.margin + b * joc.boxsize + joc.boxsize / 2;
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    circle(x, y, 10);
    floodfill(x + 1, y + 1, color);
}

void drawAnimals() {
    //deseneaza pe tabla toate piesele
    for (int i = 0; i < 4; i++) {
        drawPiece(joc.dogs[i].x, joc.dogs[i].y, joc.dogs[i].color);
    }
    drawPiece(joc.fox.x, joc.fox.y, joc.fox.color);
}

void initAnimals() {
    //initializeaza pozitiile de start pentru joc
    joc.fox.x = 3;
    joc.fox.y = 0;
    joc.fox.color = RED;
    for (int i = 0; i < 4; i++) {
        joc.dogs[i].x = 2 * i;
        joc.dogs[i].y = 7;
        joc.dogs[i].color = BLUE;
    }
}

void initAnimalsFisier() {
    //initializeaza pozitiile de start pentru joc
    joc.fox.x = joc.intFox[0];
    joc.fox.y = joc.intFox[1];
    joc.fox.color = RED;
    int contor = 0;
    for (int i = 0; i < 8; i += 2) {
        joc.dogs[contor].x = joc.intDogs[i];
        joc.dogs[contor].y = joc.intDogs[i + 1];
        joc.dogs[contor++].color = BLUE;
    }
}

void movement(animal& e, int a, int b) {
    //muta piesa la pozitia a,b
    drawPiece(e.x, e.y, BLACK);
    drawPiece(a, b, e.color);
    e.x = a;
    e.y = b;
}

bool celulaOcupata(int x, int y) {
    if (x < 0 || x>7 || y < 0 || y>7)
        return true; // in afara tablei
    for (int i = 0;i < 4;i++)
        if (joc.dogs[i].x == x && joc.dogs[i].y == y)
            return true;
    if (joc.fox.x == x && joc.fox.y == y)
        return true;
    return false;
}


bool movement_dog(animal& dog, int x, int y) {
    if (celulaOcupata(x, y))
        return false; //daca e ocupata de alta piesa nu putem muta
    if (x < 0 || x>7 || y < 0 || y>7)
        return false; // in afara tablei
    if (dog.y - 1 != y || (dog.x - 1 != x && dog.x + 1 != x))
        return false; //mutare ilegala

    joc.counter_miscari_dog++;
    joc.care_dog[joc.counter_miscari_dog] = joc.counter_dog;
    joc.istoric_dog_x[joc.counter_miscari_dog] = dog.x;//vechile valori ale lui x
    joc.istoric_dog_y[joc.counter_miscari_dog] = dog.y;

    movement(dog, x, y);
}

bool movement_fox(animal& fox, int x, int y) {
    if (celulaOcupata(x, y))
        return false; //daca e ocupata de alta piesa nu putem muta
    if (x < 0 || x>7 || y < 0 || y>7)
        return false; // in afara tablei

    int newX, newY, pozitiiFox[] = { -1,-1,  -1,1,   1,-1,   1,1 }; // mutari posibile
    bool ok = false;
    for (int i = 0;i < 8;i += 2)
    {
        newX = fox.x + pozitiiFox[i];
        newY = fox.y + pozitiiFox[i + 1];
        if (newX == x && newY == y)
            ok = true; // am gasit o mutare ok
    }
    if (!ok)
        return false;

    //if(fox.y - 1 != y || (fox.x -1 != x&& fox.x+1 != x))
    //    return false; //mutare ilegala
    joc.counter_miscari_fox++;
    joc.istoric_fox_x[joc.counter_miscari_fox] = x;//vechile valori ale lui x
    joc.istoric_fox_y[joc.counter_miscari_fox] = y;

    movement(fox, x, y);
}

void undo_fox()
{
    if (joc.counter_miscari_fox < 1) return;
    joc.counter_miscari_fox--;
    movement(joc.fox, joc.istoric_fox_x[joc.counter_miscari_fox], joc.istoric_fox_y[joc.counter_miscari_fox]);
}

void undo_dog()
{
    int care_dog;
    if (joc.counter_miscari_dog < 1) return;
    care_dog = joc.care_dog[joc.counter_miscari_dog];


    movement(joc.dogs[care_dog], joc.istoric_dog_x[joc.counter_miscari_dog], joc.istoric_dog_y[joc.counter_miscari_dog]);
    joc.counter_miscari_dog--;
}

int verificaScenariuCastig()
{
    if (joc.fox.y == 7) // daca a ajuns pe ultimul rand, a castigat fox
        return 2;
    int newX, newY, pozitiiFox[] = { -1,-1,  -1,1,   1,-1,   1,1 }; // mutari posibile
    for (int i = 0; i < 8; i += 2)
    {
        newX = joc.fox.x + pozitiiFox[i];
        newY = joc.fox.y + pozitiiFox[i + 1];
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
            if (!celulaOcupata(newX, newY))
                return 0;//daca fox are unde sa se duca
    }
    return 1;// daca fox nu are unde sa se duca si nici nu a ajuns jos, castiga dogs
}

void closeBoard()
{
    getch();
    closegraph();
}

bool transforma_coordonate_in_pozitie(int& x, int& y) {
    //calculeaza in care celula de pe tabla a fost dat click
    if (x<joc.margin || y<joc.margin || x>joc.margin + 8 * joc.boxsize || y>joc.margin + 8 * joc.boxsize) return false;//verifica daca click-ul a fost pe tabla si nu pe langa
    x = x - joc.margin;
    x = x / joc.boxsize;
    y = y - joc.margin;
    y = y / joc.boxsize;
    return true;
}

void muta_piesa(int sursa_x, int sursa_y, int destinatie_x, int destinatie_y) {
    int castig;
    if (!joc.aFostFoxUltimaMiscare)
    {
        if (sursa_x == joc.fox.x && sursa_y == joc.fox.y)
        {
            if (movement_fox(joc.fox, destinatie_x, destinatie_y))
            {
                joc.aFostFoxUltimaMiscare = true;
            }
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            if (sursa_x == joc.dogs[i].x && sursa_y == joc.dogs[i].y) // daca a fost selectat un dog
            {
                joc.counter_dog = i;
                if (movement_dog(joc.dogs[i], destinatie_x, destinatie_y)) // daca a mutat dog cu succes
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
    cout << castig;
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

void muta_piesa_pvc(int sursa_x, int sursa_y, int destinatie_x, int destinatie_y) {
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
        new_y = joc.dogs[joc.counter_dog].y - 1;
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
        if (joc.dificultate == 1)//verifica daca celula un trebuie sa mute este libera
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
                if (joc.fox.x == new_x_dificultate_2 && joc.fox.y == new_y)
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

void click_select(int x, int y) {
    if (!transforma_coordonate_in_pozitie(x, y)) return;
    joc.xSelectat = x;
    joc.ySelectat = y;
}

void click_drop(int x, int y) {
    if (!transforma_coordonate_in_pozitie(x, y)) return;
    muta_piesa(joc.xSelectat, joc.ySelectat, x, y);
}

void click_drop_pvc(int x, int y) {
    if (!transforma_coordonate_in_pozitie(x, y)) return;
    muta_piesa_pvc(joc.xSelectat, joc.ySelectat, x, y);
}

void click_undo(int x, int y) {
    if (x > 100 && x < 200 && y > 640 && y < 800) {
        undo_fox();
        undo_dog();
    }
    if (x > 458 && x < 608 && y>640 && y < 680) {
        salvareSchita();
    }
}

void click_undo_pvp(int x, int y) {
    if (x > 100 && x < 200 && y>640 && y < 680) {
        if (joc.aFostFoxUltimaMiscare)
        {
            undo_fox();
        }
        else
        {
            undo_dog();
        }
        joc.aFostFoxUltimaMiscare = !joc.aFostFoxUltimaMiscare;
    }
    if (x > 458 && x < 608 && y>640 && y < 680) {
        salvareSchita();
    }
}

void generateBoard()
{
    //deseneaza tabla de sah si piesele pe tabla
    int gr = DETECT, gm;
    int r, c, x, y;
    x = joc.margin;
    y = joc.margin;
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
            black = !black;
        }
        black = !black;

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
    outtextxy(460, 640, " Save ");

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
    bool jocNou = true;
    if (dificultate < 0) {
        jocNou = false;
        dificultate = -dificultate;
    }
    joc.dificultate = dificultate;
    generateBoard();
    if (!jocNou) {
        citire();
        initAnimalsFisier();
    }
    else
        initAnimals();
    drawAnimals();
    registermousehandler(WM_LBUTTONDOWN, click_select);
    registermousehandler(WM_LBUTTONUP, click_drop_pvc);
    registermousehandler(WM_RBUTTONDOWN, click_undo);//click dreapta
    closeBoard();
}


#endif // BOARD_H_INCLUDED

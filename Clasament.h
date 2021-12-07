#ifndef CLASAMENT_H_INCLUDED
#define CLASAMENT_H_INCLUDED
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <wingdi.h>
#include <cstdlib>
using namespace std;
struct clasament{ //struct pentru top cu TImp &Nume
    float timp;
    char nume[100];
};

clasament scriereFisier(); //Numele si timpul jucatorului actual
int citireDinFisierInMatrice(clasament usr[10]); //citirea din fisier a topului si actualizarea lui + transmiterea spre afisare
void afisareGrafix(); //afisarea in Fereastra
int citireDinFisierInMatrice(clasament usr[10]){
    //pregatire fisier:
    FILE *fptr;
    const char *fileN="input.txt"; //locatie fisier daca nu e in folderul sursa
    fptr=fopen(fileN, "r");

    //pregatire stocare in struct
    int i=0;
    while(!feof(fptr)){
        float c;
        char rand[100];
        fscanf(fptr, "%f", &c);
        fgets(rand, 100, fptr);
        strcpy(usr[i].nume, rand);
        usr[i].timp=c;
        i++;
    }
    i-=2;
    bool actualizeazaFisier=false; //daca se v or actualiza in fisier datele
    clasament jucator=scriereFisier();
    if(usr[0].timp>jucator.timp || usr[i].timp>jucator.timp){ //cautare daca noul jucator poate fi in top
        int j;
        for(j=i-1;(j>=0 && usr[j].timp>jucator.timp); j--)
            usr[j+1]=usr[j];
        usr[j]=jucator; //punere in top
        i++;
        actualizeazaFisier=true;
    }
    else if(usr[i].timp<jucator.timp && i<9){ //daca topul nu este plin, se pune indiferent de timpul scos
        i++;
        usr[i]=jucator;
        actualizeazaFisier=true;
    }
    if(i>9)
        i=9;
    fclose(fptr);
    if(actualizeazaFisier==true){ //memorarea noului top in fisier
        FILE *fpts;
        fpts=fopen(fileN, "w+");
        for(int k=0;k<i;k++)
            fprintf(fpts, "%f%s%s", usr[k].timp, usr[k].nume, "\n");
        fclose(fpts);
    }
    return i; //returneaza numarul de elemente din top pentru a putea fi afisate
}
clasament scriereFisier(){
    clasament usr;
    strcpy(usr.nume, "YO");
    usr.timp=20;
    return usr;
}
void afisareGrafix(){
    int high=800, width=800;
    initwindow(high, width); //init. interfata
    int midx=getmaxx()/2;
    int y=100;
    int random=rand()%10+1; //culoare font "top player.." aleasa random
    setbkcolor(12); //culoare
    cleardevice();
    settextstyle(4, 0, 6); //stil titul
    settextjustify(1,1);
    outtextxy(midx, y, "Top 10 playeri"); //pozitie titlu
    clasament usr[10];
    int n=citireDinFisierInMatrice(usr); //nr de elemente din top
    settextstyle(10, 0, 4);
    setbkcolor(12); //culoare
    y+=200;
    for(int i=0;i<=n;i++){
        char numar[10], total[300];
        sprintf(numar, "%.2f", usr[i].timp); //conversie de la float la string
        strcpy(total, numar);
        strcat(total, " ");
        strcat(total, usr[i].nume);
        outtextxy(midx, y, total); //afisarea cu timpul truncchiat
        y+=35;
    }
    getch();
    closegraph();
}



#endif // CLASAMENT_H_INCLUDED

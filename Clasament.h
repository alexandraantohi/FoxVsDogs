#ifndef CLASAMENT_H_INCLUDED
#define CLASAMENT_H_INCLUDED
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <wingdi.h>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <wingdi.h>
#include <cstdlib>
#include <string>
#include <cctype>
using namespace std;
struct clasament{ ///struct pentru top cu TImp &Nume
    float timp;
    char nume[100];
}joacaAcum;

void numePlayer(char *numeClasament){
    strcpy(joacaAcum.nume, numeClasament);
}
void timpPlayer(float timpJucator){
    joacaAcum.timp=timpJucator;
}

///TO DO: citirea numelui in timpul jocului! (in scriereFisier();

unsigned citireDinFisierInMatrice(clasament tp[]); ///citirea din fisier a topului si actualizarea lui + transmiterea spre afisare
void afisareGrafix(); ///afisarea in Fereastra
void desparteCuvant(char *p, float &c); ///Din string scoate float ul si lasa doar caracterele
clasament scriereFisier(); ///Numele si timpul jucatorului actual
bool combinare(clasament tp[], int &n); ///aici actualizez vectorul de clasamente si pun noul jucator daca e cazul


bool combinare(clasament tp[], int &n){
    clasament p=scriereFisier(); ///se ia noul player
    if(n==0){ ///daca nu exista top
        tp[0]=p;
        n++;
        return true;
    }
    int i;
    for(i=0;i<n;i++){
        if(tp[i].timp>p.timp && tp[i].timp!=p.timp){ ///se cauta pozitia pe care ar trebui sa fie in top noul player
            clasament ultim=tp[n-1];
            for(int j=n-1;j>i;j--) ///se face spatiu pentru player daca e in interiorul topului
                tp[j]=tp[j-1];
            tp[i]=p;
            if(n<10){ ///daca are cel mai mic timp dar topul nu e plin, se pune la final
                tp[n]=ultim;
                n++;
            }
            return true;/// = s-a facut modificare in vectorul top => se actualizeaza fisierul cu info
        }
    }
    if(n<10){ ///se testeaza daca topul nu e plin, din nou
        tp[n]=p;
        n++;
        return true;
    }
    return false;
}
unsigned citireDinFisierInMatrice(clasament tp[]){
    char *f1n="input.txt";
    FILE *f1 ,*f2;
    int i=0;
    if(f1=fopen(f1n, "r")){ ///daca exista top anterior
        while(!feof(f1) && i<10){
            char rand[100];
            if(fgets(rand, 100, f1)){ ///se citeste linia de chars*
                    float c;
                    desparteCuvant(rand, c); ///desparte linia de chars* in timp si nume si se pun valorile in vectorul top
                    tp[i].timp=c;
                    strcpy(tp[i].nume, rand);
                    i++; ///se noteaza si numarul de elemente din vectorul top
                }
        }
    }
    fclose(f1);
    bool fisier=combinare(tp, i); ///daca s-a facut modificari in vectorul top cu noul user, se modifica fisierul
    if(fisier){
        f2=fopen(f1n, "w");
        for(int k=0;k<i;k++){
            fprintf(f2, "%f%s", tp[k].timp, tp[k].nume);
        }
        fclose(f2);
    }
    return i; ///se returneaza nr de elemente din top pt afisarea grafica a topului
}
///TO DO: citirea numelui in timpul jocului! (in scriereFisier();
clasament scriereFisier(){
    clasament usr;
    strcpy(usr.nume, joacaAcum.nume); ///utlerior se va lua de la tastatura
    strcpy(usr.nume+strlen(usr.nume),"\n"); ///memorarea cu tot cu rand nou pt a facilita scrierea in fisier
    usr.timp=joacaAcum.timp;
    return usr; ///se returneaza un camp de tipul struct cu datele userului
}

void desparteCuvant(char *p, float &c){ ///se face dintr- un string, informatie utila (timp si nume)
    c=(float)strtof(p, NULL);
    int k=0;
    for(int i=0;i<strlen(p); i++){
        if(p[i]>='0' && p[i]<='9' || p[i]=='.')
            k++;
        else
            i=strlen(p)+1;
    }
    char copie[100];
    strcpy(copie, p+k);
    strcpy(p, copie);
}
void afisareGrafix(float timpTotal, char *acestNume){ ///afisarea in grafica a topului
    cout<<"\nAfisare din Clasament a timpului: "<<timpTotal;
    joacaAcum.timp=timpTotal;
    strcpy(joacaAcum.nume, acestNume);
    int high=720, width=720;
    initwindow(high, width); //init. interfata
    setbkcolor(COLOR(128,128,128));
    int midx=getmaxx()/2;
    int y=100;
    int random=rand()%10+1; //culoare font "top player.." aleasa random
    setcolor(12);
    cleardevice();
    readimagefile("background.jpg",0,0,high,width);
    settextstyle(4, 0, 6); //stil titul
    settextjustify(1,1);
    outtextxy(midx, y, "Top 10 playeri");//pozitie titlu
    clasament usr[10];
    unsigned n=citireDinFisierInMatrice(usr); //nr de elemente din top
    settextstyle(10, 0, 4);
    setcolor(12); //culoare
    y+=200;
    for(int i=0;i<n;i++){
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

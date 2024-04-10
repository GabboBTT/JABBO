#ifndef SPARO
#define SPARO

#include <ncurses.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "enemy.h"
#include "player.h"

using namespace std;

struct lista{      
    int x;          //altezza proiettile
    int y;          //distanza da sinistra proiettile
    int direzione;  //direzione dello sparo(alto,basso,destra,sinistra)
    bool attivo;    //determina se è ancora attivo lo sparo
    lista *next;
};
typedef lista *p_lista;

class Sparo{    
    protected:
        chtype character;   //carattere dello sparo = '*'
        WINDOW *win;        //WINDOW con la mappa
        Player *p;          //valori relativi al player
        enemy *e;           //valori relativi al primo nemico
        enemy *e2;          //valori relativi al secondo nemico
        enemy *e3;          //valori relativi al terzo nemico

    public:
        Sparo(WINDOW *win, Player *p, enemy *e, enemy *e2, enemy *e3);
        void display(p_lista l);
        bool libero(int x, int y);
        void cancella(int x, int y);
};

Sparo::Sparo(WINDOW *win, Player *p, enemy *e, enemy *e2, enemy *e3){   //costruttore
    this->character = '*';
    this->p = p;
    this->win = win;
    this->e = e;
    this->e2 = e2;
    this->e3 = e3;
}

void Sparo::display(p_lista l){     //stampa lo sparo sulla mappa
    p_lista tmp = l;
	while(tmp!=NULL){
        if(tmp->attivo)
	        mvwaddch(this->win,tmp->x, tmp->y, this->character);
        tmp = tmp->next;
	}
    wrefresh(this->win);
}

bool Sparo::libero(int x, int y){       //controlla se la casella in cui deve andare lo sparo è libera
    if(mvwinch(this->win, x, y)==' '){
        if((y<this->p->m->xMin)||(y>this->p->m->xMax)||(x<this->p->m->yMin)||(x>this->p->m->yMax)){
            return(false);
        } else {
        return(true);
        }
    } else {
        return(false);
    }
}

void Sparo::cancella(int x, int y){         //cancella il carattere dello sparo precedente dalla casella
    if(mvwinch(this->win, x, y)==this->character)
        mvwaddch(this->win, x, y, ' ');
    wrefresh(this->win);
}

#endif 
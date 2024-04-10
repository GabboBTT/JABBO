#ifndef SPARONEMICO
#define SPARONEMICO

#include <ncurses.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "enemy.h"
#include "player.h"
#include "sparo.h"

using namespace std;

class Sparonemico: public Sparo{    //sottoclasse di sparo
    protected:
        p_lista l;  //lista di spari
        int num_e;  //rappresenta di quale nemico è lo sparo
    public:
        Sparonemico(WINDOW *win, Player *p, enemy *e, enemy *e2, enemy *e3, int num_e);
        void display();             //mettere in sparo
        void movimento();
        void eliminate(int x, int y, int direzione);    
        void controlloplayer(int x, int y);
        void insert();
};

Sparonemico::Sparonemico(WINDOW *win, Player *p, enemy *e, enemy *e2, enemy *e3, int num_e):Sparo(win, p, e, e2, e3){   //costruttore
    this->l = NULL;
    this->num_e = num_e;
}

void Sparonemico::display(){    //stampa lo sparo sulla mappa
    switch(this->num_e){
        case 1:
            if(this->e->num>0)
                Sparo::display(this->l);
            else
                this->l = NULL;
        break;
        case 2:
            if(this->e2->num>0)
                Sparo::display(this->l);
            else
                this->l = NULL;
        break;
        case 3:
            if(this->e3->num>0)
                Sparo::display(this->l);
            else
                this->l = NULL;
        break;
    }
}

void Sparonemico::controlloplayer(int x, int y){    //controlla se colpisce il player
    if(mvwinch(this->win, x, y)=='P')
        this->p->modificavite(-1);
}

void Sparonemico::movimento(){      //muove lo sparo
    p_lista tmp = this->l;
    while(tmp!=NULL){
        switch(tmp->direzione){
            case 0:
                if(Sparo::libero(tmp->x-1, tmp->y)!=true){
                    Sparo::cancella(tmp->x,tmp->y);
                    controlloplayer(tmp->x-1, tmp->y);
                    eliminate(tmp->x,tmp->y,tmp->direzione);
                    tmp->attivo = false;
                } else {
                    Sparo::cancella(tmp->x,tmp->y);
                    tmp->x = tmp->x-1;
                }
            break;
            case 1:
                if(Sparo::libero(tmp->x+1, tmp->y)!=true){
                    Sparo::cancella(tmp->x,tmp->y);
                    controlloplayer(tmp->x+1, tmp->y);
                    eliminate(tmp->x,tmp->y,tmp->direzione);
                    tmp->attivo = false;
                } else {
                    Sparo::cancella(tmp->x,tmp->y);
                    tmp->x = tmp->x+1;
                }
            break;
        }
        tmp = tmp->next;
    }
}

void Sparonemico::eliminate(int x, int y, int direzione){   //elimina lo sparo dalla lista
    p_lista aux = this->l;
	p_lista prec = NULL;
	p_lista tmp;
	while(aux!=NULL){
		if((aux->x==x)&&(aux->y==y)&&(aux->direzione==direzione)){
			tmp = aux;
            aux->attivo = false;
			if(prec == NULL){
				this->l = this->l->next ;
			}else {
				prec->next = aux->next ;
			}
			aux = aux->next;
			delete (tmp);
		}
		else{
			prec = aux ;
			aux = aux->next ;
		}
	}
}

void Sparonemico::insert(){  //inserisce due spari nella lista
	p_lista head = new lista;
    switch(this->num_e){
        case 1:
            head->x = this->e->x;
            head->y = this->e->y;
        break;
        case 2:
            head->x = this->e2->x;
            head->y = this->e2->y;
        break;
        case 3:
            head->x = this->e3->x;
            head->y = this->e3->y;
        break;
    }
    head->direzione = 0;
    head->attivo = true;
    head->next = this->l;
    this->l = head;
    p_lista head2 = new lista;
    switch(this->num_e){
        case 1:
            head2->x = this->e->x;
            head2->y = this->e->y;
        break;
        case 2:
            head2->x = this->e2->x;
            head2->y = this->e2->y;
        break;
        case 3:
            head2->x = this->e3->x;
            head2->y = this->e3->y;
        break;
    }
    head2->direzione = 1;
    head2->attivo = true;
    head2->next = this->l;
    this->l = head2;
}


#endif 
#ifndef SPAROPERSONAGGIO
#define SPAROPERSONAGGIO

#include <ncurses.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "enemy.h"
#include "player.h"
#include "sparo.h"

using namespace std;

class Sparopersonaggio: public Sparo{   //sottoclasse di sparo
    protected:
        p_lista l;
    public:
        Sparopersonaggio(WINDOW *win, Player *p, enemy *e, enemy *e2, enemy *e3);
        void display();
        void controllonemico(int x, int y);
        void movimento();
        void insert();
        void eliminate(int x, int y, int direzione);
};


Sparopersonaggio::Sparopersonaggio(WINDOW *win, Player *p, enemy *e, enemy *e2, enemy *e3):Sparo(win, p, e, e2, e3){ //costruttore
    this->l = NULL;
}

void Sparopersonaggio::display(){   //stampa lo sparo sulla mappa
    Sparo::display(this->l);
}

void Sparopersonaggio::controllonemico(int x, int y){  //controlla se lo sparo colpisce il nemico
    if((x==this->e->x)&&((y==this->e->y-1)||(y==this->e->y)||(y==this->e->y+1)||(y==this->e->y-2)||(y==this->e->y+2))){
            this->e->eliminate(this->p->att);
        } else if((x==this->e2->x)&&((y==this->e2->y-1)||(y==this->e2->y)||(y==this->e2->y+1)||(y==this->e2->y-2)||(y==this->e2->y+2))){
            this->e2->eliminate(this->p->att);
        } else if((x==this->e3->x)&&((y==this->e3->y-1)||(y==this->e3->y)||(y==this->e3->y+1)||(y==this->e3->y-2)||(y==this->e3->y+2))){
            this->e3->eliminate(this->p->att);
        }
}

void Sparopersonaggio::eliminate(int x, int y, int direzione){   //elimina lo sparo dalla lista quando non c'è uno spazio libero nella mappa
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

void Sparopersonaggio::movimento(){     //muove lo sparo
    p_lista tmp = this->l;
    while(tmp!=NULL){
        switch(tmp->direzione){
            case 1:
                if(Sparo::libero(tmp->x, tmp->y-1)!=true){
                    Sparo::cancella(tmp->x,tmp->y);
                    controllonemico(tmp->x, tmp->y-1);
                    eliminate(tmp->x,tmp->y,tmp->direzione);
                    tmp->attivo = false;
                } else {
                    Sparo::cancella(tmp->x,tmp->y);
                    tmp->y = tmp->y-1;
                }
            break;
            case 2:
                if(Sparo::libero(tmp->x, tmp->y+1)!=true){
                    Sparo::cancella(tmp->x,tmp->y);
                    controllonemico(tmp->x, tmp->y+1);
                    eliminate(tmp->x,tmp->y,tmp->direzione);
                    tmp->attivo = false;
                } else {
                    Sparo::cancella(tmp->x,tmp->y);
                    tmp->y = tmp->y+1;
                }
            break;
            case 3:
                if(Sparo::libero(tmp->x+1, tmp->y)!=true){
                    Sparo::cancella(tmp->x,tmp->y);
                    controllonemico(tmp->x+1, tmp->y);
                    eliminate(tmp->x,tmp->y,tmp->direzione);
                    tmp->attivo = false;
                } else {
                    Sparo::cancella(tmp->x,tmp->y);
                    tmp->x = tmp->x+1;
                }
            break;
            case 4:
                if(Sparo::libero(tmp->x-1, tmp->y)!=true){
                    Sparo::cancella(tmp->x,tmp->y);
                    controllonemico(tmp->x-1, tmp->y);
                    eliminate(tmp->x,tmp->y,tmp->direzione);
                    tmp->attivo = false;
                } else {
                    Sparo::cancella(tmp->x,tmp->y);
                    tmp->x = tmp->x-1;
                }
            break;
        }
        tmp = tmp->next;
    }
}

void Sparopersonaggio::insert(){  //inserisce in testa il nuovo sparo del player
    
	p_lista head = new lista;
    head->x = this->p->yLoc;
    head->y = this->p->xLoc;
    switch(this->p->lastmove){
        case 'u':
            head->direzione = 4;
        break;
        case 'd':
            head->direzione = 3;
        break;
        case 'l':
            head->direzione = 1;
        break;
        default:
            head->direzione = 2;
        break;
    }
    head->attivo = true;
    head->next = this->l;
    this->l = head;
}

#endif 
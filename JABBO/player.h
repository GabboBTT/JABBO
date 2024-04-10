#ifndef PLAYER
#define PLAYER
#include "mappa.h"
#include "enemy.h"
#include <ncurses.h>
#include <iostream>

using namespace std;

class Player
{
    protected:
        int xMax, yMax, xMin, yMin;     //valori minimi e massimi della mappa in cui poter stampare lo sparo       
        char character;                 //carattere del player = 'P'
        int lifes;                      //vite del player
        WINDOW * curwin;                //WINDOW in cui si trova la mappa
        bool scudo;                     //scudo del player
        
    public:
        Player(WINDOW * win, char c, int p, Mappa *m, enemy *e);    //costruttore
        Mappa *m;                       //mappa di gioco

        void mvup();    //muove il alto il player
        void mvdown();  //muove in basso il player
        void mvleft();  //muove a sinistra il player
        void mvright(); //muove a destra il player
        int getmv();    //prende la mossa da tastiera 
        int vite();     //ritorna le vite del player    
        void display(); //stampa il player sulla mappa
        void chiave();  //se il player prende la chiave sblocca il passaggio alla mappa successiva
        void potere(char);  //quando il player prende un artefatto attiva il potere relativo
        void modificavite(int); //modifica le vite del player di un valore int
        void controllolettera(char);    //controlla quale lettera è stata raccolta dal player
        void scudoattivo();             //attiva lo scudo del player se si trova l'artefatto 'S'
        void modificaattacco();         //aumenta l'attacco del player se si trova l'artefatto 'A'
        char lastmove;          //indica l'ultima mossa compiuta dal player per indirizzare lo sparo nella stessa direzione
        int xLoc, yLoc;         //valori x e y in cui si trova il player
        int att;                //valore dell'attacco del player
};

Player::Player(WINDOW * win, char c, int p, Mappa *m, enemy *e)
{
	start_color();
    this->curwin = win;
    switch(m->n){
        case 1:
            this->yLoc = m->yMax-2;
            this->xLoc = m->xMin+8;
        break;
        case 2:
            this->yLoc = m->yMax-2;
            this->xLoc = m->xMin+8;
        break;
        case 3:
            this->yLoc = m->yMax-2;
            this->xLoc = m->xMin+8;
        break;
        case 4:
            this->yLoc = m->yMax-5;
            this->xLoc = m->xMin+6;
        break;
        case 5:
            this->yLoc = m->yMax-5;
            this->xLoc = m->xMin+6;
        break;
        case 6:
            this->yLoc = m->yMin+2;
            this->xLoc = m->xMin+30;
        break;
        case 7:
            this->yLoc = m->yMin+2;
            this->xLoc = m->xMin+30;
        break;
        case 8:
            this->yLoc = m->yMax-5;
            this->xLoc = m->xMax-2;
        break;

    }
    this->xMin = m->xMin;
    this->yMin = m->yMin;
    this->xMax = m->xMax;
    this->yMax = m->yMax;
    keypad(this->curwin, true);
    this->character = c;
    this->lifes = p/10;
    //Controllo se sono alle vita massime
    if(this->lifes>=3){
        mvwprintw(this->curwin, 9, 62, "max vite");
    }
    this->m = m;
    this->scudo = false;
    this->att = 1;
    this->lastmove = 'r';
}

void Player::mvup()
{
    mvwaddch(this->curwin, this->yLoc, this->xLoc, ' ');
    this->yLoc--;
    if((mvwinch(this->curwin,this->yLoc,this->xLoc)=='-')||(mvwinch(this->curwin,this->yLoc,this->xLoc)=='|')||(mvwinch(this->curwin,this->yLoc,this->xLoc)=='/')){
        this->yLoc++;
    }
    if((mvwinch(this->curwin,this->yLoc,this->xLoc)!=' ')){
        controllolettera(mvwinch(this->curwin,this->yLoc,this->xLoc));
    }
    if((this->yLoc < this->yMin+1)&&(mvwinch(this->curwin,this->yLoc,this->xLoc)!=' ')){
        this->yLoc = this->yMin+1;
    } else if((this->yLoc < this->yMin+1)&&(mvwinch(this->curwin,this->yLoc,this->xLoc)==' ')){
        this->m->n++;
    }
    this->lastmove = 'u';
}

void Player::mvdown()
{
    mvwaddch(this->curwin, this->yLoc, this->xLoc, ' ');
    this->yLoc++;
    if((mvwinch(this->curwin,this->yLoc,this->xLoc)=='-')||(mvwinch(this->curwin,this->yLoc,this->xLoc)=='|')||(mvwinch(this->curwin,this->yLoc,this->xLoc)=='/')){
        this->yLoc--;
    }
    if((mvwinch(this->curwin,this->yLoc,this->xLoc)!=' ')){
        controllolettera(mvwinch(this->curwin,this->yLoc,this->xLoc));
    }
    if((this->yLoc > this->yMax-1)&&(mvwinch(this->curwin,this->yLoc,this->xLoc)!=' ')){
        this->yLoc = this->yMax-1;
    } else if((this->yLoc > this->yMax-1)&&(mvwinch(this->curwin,this->yLoc,this->xLoc)==' ')){
        this->m->n++;
    }
    this->lastmove = 'd';
}

void Player::mvleft()
{
    mvwaddch(this->curwin, this->yLoc, this->xLoc, ' ');
    this->xLoc--;
    if((mvwinch(this->curwin,this->yLoc,this->xLoc)=='-')||(mvwinch(this->curwin,this->yLoc,this->xLoc)=='|')||(mvwinch(this->curwin,this->yLoc,this->xLoc)=='/')){
        this->xLoc++;
    }
    if((mvwinch(this->curwin,this->yLoc,this->xLoc)!=' ')){
        controllolettera(mvwinch(this->curwin,this->yLoc,this->xLoc));
    }
    if((this->xLoc < this->xMin+1)&&(mvwinch(this->curwin,this->yLoc,this->xLoc)!=' ')){
        this->xLoc = this->xMin+1;
    } else if((this->xLoc < this->xMin+1)&&(mvwinch(this->curwin,this->yLoc,this->xLoc)==' ')){
        this->m->n++;
    }
    this->lastmove = 'l';
}

void Player::mvright()
{
    mvwaddch(this->curwin, this->yLoc, this->xLoc, ' ');
    this->xLoc++;
    if((mvwinch(this->curwin,this->yLoc,this->xLoc)=='-')||(mvwinch(this->curwin,this->yLoc,this->xLoc)=='|')||(mvwinch(this->curwin,this->yLoc,this->xLoc)=='/')){
        this->xLoc--;
    }
    if((mvwinch(this->curwin,this->yLoc,this->xLoc)!=' ')){
        controllolettera(mvwinch(this->curwin,this->yLoc,this->xLoc));
    }
    if((this->xLoc > this->xMax-1)&&(mvwinch(this->curwin,this->yLoc,this->xLoc)!=' ')){
        this->xLoc = this->xMax-1;
    } else if((this->xLoc > this->xMax-1)&&(mvwinch(this->curwin,this->yLoc,this->xLoc)==' ')){
        this->m->n++;
    }
    this->lastmove = 'r';
}

int Player::getmv()
{
    int choice = wgetch(this->curwin);
    switch(choice)
    {
        case 'w':
            mvup();
            break;
        case 's':
            mvdown();
            break;
        case 'a':
            mvleft();
            break;
        case 'd':
            mvright();
            break;
    }
    return choice;
}

int Player::vite(){
    return(this->lifes);
}

void Player::display()
{
    start_color();
    mvwaddch(this->curwin, this->yLoc, this->xLoc, this->character);
}

void Player::chiave()  //sblocca il passaggio chiuso
{
    for(int i=1; i<6; i++){
        switch(this->m->n){
            case 1:
                mvwaddch(this->curwin, this->yMin, this->xMin+this->m->a+i, ' ');                                //apre uscita
            break;
            case 2:
                mvwaddch(this->curwin, this->yMin, this->xMin+this->m->a+i, ' ');                                //apre uscita
            break;
            case 3:
                mvwaddch(this->curwin, this->yMin+this->m->a+i, this->xMax, ' ');                                //apre uscita
            break;
            case 4:
                mvwaddch(this->curwin, this->yMin+this->m->a+i, this->xMax, ' ');                                //apre uscita
            break;
            case 5:
                mvwaddch(this->curwin, this->yMax, this->xMin+this->m->a+i, ' ');                                //apre uscita
            break;
            case 6:
                mvwaddch(this->curwin, this->yMax, this->xMin+this->m->a+i, ' ');                                //apre uscita
            break;
            case 7:
                mvwaddch(this->curwin, this->yMin+this->m->a+i, this->xMin, ' ');                                //apre uscita
            break;
            case 8:
                mvwaddch(this->curwin, this->yMin, this->xMin+this->m->a+i, ' ');                                //apre uscita
            break;
            case 9:

            break;
        }
    }
    wrefresh(curwin);
}

void Player::scudoattivo()
{
    this->scudo = true;
    mvwprintw(this->curwin, 9 , 101 , "Scudo attivo");
}

void Player::modificavite(int x)
{
    if(x<0){
    if((this->scudo)&&(x<0)){
        this->scudo = false;
        mvwprintw(this->curwin, 9 , 101 , "            ");
    } else {
        this->lifes = this->lifes + x;
        mvwprintw(this->curwin, 9, 59, "                   ");
    }
    } else {
        if(this->lifes<3){
            this->lifes = this->lifes + x;
            if(this->lifes==3)
                mvwprintw(this->curwin, 9, 62, "max vite");
        } else {
            mvwprintw(this->curwin, 9, 62, "max vite");
        }
    }
    
    mvwprintw(this->curwin, 9 , 59 , "%i", this->lifes);
}

void Player::modificaattacco()
{
    this->att = 3;
    mvwprintw(this->curwin, 9 , 134 , "Attacco potenziato attivo");
}

void Player::controllolettera(char ch)
{
    switch(ch){
        case 'E':
            this->lifes = 0;
            mvwprintw(this->curwin, 9 , 59 , "%i", 0);
            exit;
        break;
        case '*':
            modificavite(-1);
        break;
        case 'C':
            chiave();
        break;
        case 'S':
            scudoattivo();
        break;
        case 'V':
            modificavite(1);
        break;
        case 'A':
            modificaattacco();
        break;
    }
}

#endif 
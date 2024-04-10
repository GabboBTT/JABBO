#ifndef ENEMY
#define ENEMY

#include <ncurses.h>
#include <string>
#include <iostream>
#include <stdlib.h>
using namespace std;

//colori
#define Rosso 10

class enemy{
    protected:
        WINDOW *curwin;     //WINDOW della mappa
        bool vivo;          //valore booleano che indica se il nemico è vivo
        int direzione;      //indica la direzione in cui si sta muovendo il nemico

    public:
        enemy(WINDOW *win, int x, int y, int xMax, int yMax, int divx1, int divx2); //costuttore
        void display();         //stampa nemico
        void movimento();       //movimento nemico
        void eliminate(int x);  //libera la casella precdente in cui si trovava il nemico prima del movimento
        chtype en;              //carattere nemico 'E' in rosso
        bool colpito;           //indica se il nemico colpisce il player
        int num;                //indica quante vite ha il nemico (max 3)
        int x;                  //distanza dall'alto nemico
        int y;                  //distanza da sinistra nemico 
        int xMin, yMin, xMax, yMax;     //massimi valori della mappa

};

int random(int max){       //randomizzare un numero ma escono sempre gli stessi numeri (migliorare)
    return(rand()%max+1);
}

enemy::enemy(WINDOW *win, int x, int y, int xMax, int yMax, int divx1, int divx2){
    this->curwin = win;
    this->xMin = xMax/(2.2);
    this->yMin = (yMax/(2.5))+1;
    this->xMax = this->xMin + x;
    this->yMax = this->yMin + y;
    this->vivo = true;
    this->num = 3;   
    this->direzione==1;
    this->colpito = false;

    //colori
    start_color();
    double cambiocolore = 1000 / 255;
    init_color(Rosso, 214*cambiocolore, 34*cambiocolore, 46*cambiocolore);       
    init_pair(36, COLOR_BLACK, Rosso);                  
    //controllo se non vanno i colori
    if(has_colors()==FALSE){ 
        endwin(); 
        printf("Color can't be used"); 
    }
    int b,c;
    int risp = 0;
    
    do{
        risp=1;
        do{
        b = random(10)+this->yMin+2;
        } while ((b==divx1)||(b==divx2));
        c = random(50)+this->xMin+3;
        for(int i=this->xMin+3;i<this->xMin+53;i++){
            if((mvwinch(this->curwin,b,i)!=' ')&&((mvwinch(this->curwin,b,i)!='/'))){
                risp=2;
            }
    }
    } while(risp==2);
    
    this->en = 'E' | A_REVERSE | COLOR_PAIR(36);
        this->x=b;
        this->y=c;}

    

void enemy::display(){
    if(this->num>0){
        mvwaddch(this->curwin, this->x, this->y , this->en);
        if(this->num>1){
            mvwaddch(this->curwin, this->x, this->y-1 , this->en);
            if(this->num>2){
                mvwaddch(this->curwin, this->x, this->y+1 , this->en);
            }
        }
    }
    if(this->direzione==1){
        if(this->num==3){
            if(mvwinch(this->curwin, this->x, this->y+2)==this->en)
            mvwaddch(this->curwin, this->x, this->y+2, ' ');
        } else if (this->num==2){
            if(mvwinch(this->curwin, this->x, this->y+2)==this->en)
            mvwaddch(this->curwin, this->x, this->y+2, ' ');
            if(mvwinch(this->curwin, this->x, this->y+1)==this->en)
            mvwaddch(this->curwin, this->x, this->y+1, ' ');
        } else if(this->num==1){
            if(mvwinch(this->curwin, this->x, this->y+2)==this->en)
            mvwaddch(this->curwin, this->x, this->y+2, ' ');
            if(mvwinch(this->curwin, this->x, this->y+1)==this->en)
            mvwaddch(this->curwin, this->x, this->y+1, ' ');
            if(mvwinch(this->curwin, this->x, this->y-1)==this->en)
            mvwaddch(this->curwin, this->x, this->y-1, ' ');
        } 
    } else {
        if(this->num==3){
            if(mvwinch(this->curwin, this->x, this->y-2)==this->en)
            mvwaddch(this->curwin, this->x, this->y-2, ' ');
        } else if (this->num==2){
            if(mvwinch(this->curwin, this->x, this->y-2)==this->en)
            mvwaddch(this->curwin, this->x, this->y-2, ' ');
            if(mvwinch(this->curwin, this->x, this->y+1)==this->en)
            mvwaddch(this->curwin, this->x, this->y+1, ' ');
        } else if(this->num==1){
            if(mvwinch(this->curwin, this->x, this->y-2)==this->en)
            mvwaddch(this->curwin, this->x, this->y-2, ' ');
            if(mvwinch(this->curwin, this->x, this->y+1)==this->en)
            mvwaddch(this->curwin, this->x, this->y+1, ' ');
            if(mvwinch(this->curwin, this->x, this->y-1)==this->en)
            mvwaddch(this->curwin, this->x, this->y-1, ' ');
        }
    }         
}

void enemy::movimento(){
    if(this->direzione==1){
        if((mvwinch(this->curwin, this->x, this->y-2)!='|')&&(mvwinch(this->curwin, this->x, this->y-2)!='-')&&(mvwinch(this->curwin, this->x, this->y-2)!='/')&&(mvwinch(this->curwin, this->x, this->y-2)==' ')&&(this->y-2>this->xMin)){
            this->y = this->y-1;
        } else if((mvwinch(this->curwin, this->x, this->y-2)=='P')&&(this->num>0)){
            this->colpito = true;
            return;
        } else {
            this->y=this->y+1;
            this->direzione = 2;
        } 
    }else{
        if((mvwinch(this->curwin, this->x, this->y+2)!='|')&&(mvwinch(this->curwin, this->x, this->y+2)!='-')&&(mvwinch(this->curwin, this->x, this->y-2)!='/')&&(mvwinch(this->curwin, this->x, this->y+2)==' ')&&(this->y+2<this->xMax)){
            this->y=this->y+1;
        } else if((mvwinch(this->curwin, this->x, this->y+2)=='P')&&(this->num>0)){
            this->colpito = true;
            return;
        } else {
            this->y = this->y-1;
            this->direzione = 1;
        } 
    }
}

void enemy::eliminate(int x){
    if(x==1){
        if(this->num==1){
            if(mvwinch(this->curwin, this->x, this->y)==this->en)
            mvwaddch(this->curwin, this->x, this->y, ' ');
            this->vivo = false;
            this->num = 0;
        } else {
        this->num = this->num-1;
        }
    } else {
        if(mvwinch(this->curwin, this->x, this->y-1)==this->en)
        mvwaddch(this->curwin, this->x, this->y-1, ' ');
        if(mvwinch(this->curwin, this->x, this->y)==this->en)
        mvwaddch(this->curwin, this->x, this->y, ' ');
        if(mvwinch(this->curwin, this->x, this->y+1)==this->en)
        mvwaddch(this->curwin, this->x, this->y+1, ' ');
        this->num = 0;
        this->vivo = false;
    }
}

#endif 
#ifndef MINIATURA
#define MINIATURA

#include <ncurses.h>
#include <string>
#include <iostream>
using namespace std;

//colore
#define Marrone 6


class miniatura{
    protected:
        WINDOW *curwin;
        int altezza, larghezza, punto_partenza_y, punto_partenza_x, n, piualtezza, piularghezza;

    public:
        miniatura(WINDOW *win, int xMax, int yMax, int n, int x);
};

miniatura::miniatura(WINDOW *win, int xMax, int yMax, int n, int x){
    //Variabili dimensione
    this->curwin = win;
    this->altezza = 25;
    this->larghezza = 49;
    this->punto_partenza_y = yMax/(1.25);
    this->punto_partenza_x = (xMax*3)-1;
    this->n = n;

    //Spostamento a seconda del livello
    switch(this->n){
        case 1:
            this->piualtezza = (this->altezza/3*2)-2;
            this->piularghezza = -1;
            wrefresh(this->curwin);
        break;
        case 2:
            this->piualtezza = (yMax/3)-2;
            this->piularghezza = -1;
            wrefresh(this->curwin);
        break;
        case 3:
            this->piualtezza = -2;
            this->piularghezza = -1;
            wrefresh(this->curwin);
        break;
        case 4:
            this->piualtezza = -2;
            this->piularghezza = (xMax/3+2)-2;
            wrefresh(this->curwin);
        break;
        case 5:
            this->piualtezza = -2;
            this->piularghezza = (xMax/3*2+4)-3;
            wrefresh(this->curwin);
        break;
        case 6:
            this->piualtezza = (yMax/3)-2;
            this->piularghezza = (xMax/3*2+4)-3;
            wrefresh(this->curwin);
        break;
        case 7:
            this->piualtezza = (yMax/3*2)-2;
            this->piularghezza = (xMax/3*2+4)-3;
            wrefresh(this->curwin);
        break;
        case 8:
            this->piualtezza = (yMax/3*2)-2;
            this->piularghezza = (xMax/3+2)-2;
            wrefresh(this->curwin);
        break;
        case 9:
            this->piualtezza = yMax/3;
            this->piularghezza = xMax/3+2;
            wrefresh(this->curwin);
        break;
    }
    this->curwin = newwin(altezza, larghezza, punto_partenza_y, punto_partenza_x);
    box(this->curwin, 0, 0);

    //colore
    start_color();
    double cambiocolore = 1000 / 255;
    init_color(Marrone, 79*cambiocolore, 50*cambiocolore, 32*cambiocolore);      
    init_pair(17, COLOR_BLACK, Marrone);                  


    //Cornice 
    wattron(this->curwin, COLOR_PAIR(17));
    for (int i = 0; i <= this->larghezza; i++){
        mvwprintw(this->curwin, 0, i,  " ");
        mvwprintw(this->curwin, this->altezza-1, i,  " ");
    }
    wrefresh(this->curwin);
    for (int j = 0; j <= this->larghezza; j++){
        mvwprintw(this->curwin, j, 0,  " ");
        mvwprintw(this->curwin, j, this->larghezza-1,  " ");
    }
    wrefresh(this->curwin);
    
    //crea box
    for(int i=1; i<larghezza-1; i++){
        mvwaddch(this->curwin, (altezza/3), i, '-');
        mvwaddch(this->curwin, altezza/3*2, i, '-');
    }
    wrefresh(this->curwin);
    for(int i=1; i<altezza-1; i++){
        mvwaddch(this->curwin, i, larghezza/3, '|');
        mvwaddch(this->curwin, i, larghezza/3*2, '|');
    }
    wrefresh(this->curwin);
    for(int j=0; j<=3; j++){
    for(int i=0; i<=4; i++){
    wattron(this->curwin, A_REVERSE);
        mvwaddch(this->curwin, (this->altezza/3)/2+j+this->piualtezza , ((this->larghezza-4)/3)/2+i+this->piularghezza, ' ');
    wattroff(this->curwin, A_REVERSE);
    }
    wattroff(this->curwin, COLOR_PAIR(17));
    }
    wrefresh(this->curwin);
    //Bandiera arrivo
    mvwprintw(this->curwin, (altezza/3*2)-6, larghezza/2-6, " ___________");
    mvwprintw(this->curwin, (altezza/3*2)-5, larghezza/2-6, "||_ |_| _ |_|");
    mvwprintw(this->curwin, (altezza/3*2)-4, larghezza/2-6, "||_| _ |_| _|");
    mvwprintw(this->curwin, (altezza/3*2)-3, larghezza/2-6, "||__|_|___|_|");
    mvwprintw(this->curwin, (altezza/3*2)-2, larghezza/2-6, "||");
    mvwprintw(this->curwin, (altezza/3*2)-1, larghezza/2-6, "||");
    wrefresh(this->curwin);
}

#endif


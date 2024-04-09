#ifndef BARRA
#define BARRA

#include <ncurses.h>
#include <string>
#include <iostream>
using namespace std;
  
//Colori
#define Marrone 6
#define Rosso 10
#define Giallo 11
#define Purple 12

class barra{
    protected:
        int altezza, larghezza, punto_partenza_y, punto_partenza_x;
        WINDOW * cuswin;
        string title = "LEGENDA";
        string leg[7] = {"Personaggio", "Nemico", "Chiave", "Scudo attivo", "Vita in più", "Attacco potenziato", "Premere per uscire"};
    public:
        barra(WINDOW *win, int xMax, int yMax, int x);
};

barra::barra(WINDOW *win, int xMax, int yMax, int x){
    this->cuswin = win;
    this->altezza = 25;                                                                 //altezza box 
    this->larghezza = 35;                                                               //larghezza box
    this->punto_partenza_y = yMax/(1.25);                                               //punto di partenza altezza della box
    this->punto_partenza_x = (xMax/3)-3;                                                //pun di partenza larghezza della box
    this->cuswin = newwin(altezza, larghezza, punto_partenza_y, punto_partenza_x);

    start_color();
    double cambiocolore = 1000 / 255;
    init_color(Marrone, 79*cambiocolore, 50*cambiocolore, 32*cambiocolore);
    init_color(Rosso, 214*cambiocolore, 34*cambiocolore, 46*cambiocolore);
    init_color(Giallo, 255*cambiocolore, 239*cambiocolore, 0*cambiocolore);     
    init_color(Purple, 160*cambiocolore, 32*cambiocolore, 240*cambiocolore);
    init_pair(15, COLOR_GREEN, COLOR_BLACK);              
    init_pair(17, COLOR_BLACK, Marrone);                  
    init_pair(18, Rosso, COLOR_BLACK);                    
    init_pair(19, COLOR_BLUE, COLOR_BLACK);               
    init_pair(20, Giallo, COLOR_BLACK);                   
    init_pair(21, Purple, COLOR_BLACK);                   

    //Cornice 
    wattron(this->cuswin, COLOR_PAIR(17));
    for (int i = 0; i <= larghezza; i++){
        mvwprintw(this->cuswin, 0, i,  " ");
        mvwprintw(this->cuswin, altezza-1, i,  " ");
    }
    for (int j = 0; j <= altezza; j++){
        mvwprintw(this->cuswin, j, 0,  " ");
        mvwprintw(this->cuswin, j, larghezza-1,  " ");
    }
    wattroff(this->cuswin, COLOR_PAIR(17));
    wrefresh(this->cuswin);

    //stampa legenda
    mvwprintw(this->cuswin, 3, (this->larghezza-7)/2, title.c_str());

    //stampa le lettere associate al loro significato
    int j=0;
    for(int i = 0; i < 7; i++)
        {
            j = j+2;
            switch (i){
                case 0:
                    mvwprintw(this->cuswin, j+4, 3, "P");
                break;
                case 1:
                    wattron(this->cuswin, COLOR_PAIR(18));
                    mvwprintw(this->cuswin, j+4, 3, "E");
                    wattroff(this->cuswin, COLOR_PAIR(18));
                break;
                case 2:
                    wattron(this->cuswin, COLOR_PAIR(15));
                    mvwprintw(this->cuswin, j+4, 3, "C");
                    wattroff(this->cuswin, COLOR_PAIR(15));
                break;
                case 3:
                    wattron(this->cuswin, COLOR_PAIR(19));
                    mvwprintw(this->cuswin, j+4, 3, "S");
                    wattroff(this->cuswin, COLOR_PAIR(19));
                break;
                case 4:
                    wattron(this->cuswin, COLOR_PAIR(20));
                    mvwprintw(this->cuswin, j+4, 3, "V");
                    wattroff(this->cuswin, COLOR_PAIR(20));
                break;
                case 5:
                    wattron(this->cuswin, COLOR_PAIR(21));
                    mvwprintw(this->cuswin, j+4, 3, "A");
                    wattroff(this->cuswin, COLOR_PAIR(21));
                break;
                case 6:
                    mvwprintw(this->cuswin, j+4, 2, "[x]");
                break;
            }
            mvwprintw(this->cuswin, j+4, 10, leg[i].c_str());
        }
    wrefresh(this->cuswin);
}

#endif
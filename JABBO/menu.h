#ifndef MENU
#define MENU

#include <ncurses.h>
#include <string>
#include <iostream>
using namespace std;

//colori
#define Sfondo 1   
#define Grigio 5
#define Marrone 6

class Menu              //menu iniziale 
{
    protected:
        int altezza, larghezza, punto_partenza_y, punto_partenza_x;
        WINDOW * win;
        WINDOW *menuwin;
        int h, l, p_p_y, p_p_x;
        string choices[4] = {"        <Play GAME>         ", "         <Comandi>          ", "         <Crediti>          ", "        <Exit GAME>          "};
        int highlight = 0;              //indica quale possibilità del menu è evidenziata
    public:
        Menu(int stat);     //costruttore
        void getchoice();   //serve per scorrere il menu
        bool exit;          //serve per uscire dal menu
        int scelta;         //indica la scelta dal menu fatta dall'utente
        int stat;           //serve per stampare la grafica finale con la possibile vittoria, sconfitta o ritirata
};

Menu::Menu(int stat)
{
    getmaxyx(stdscr, altezza, larghezza);
    this->exit = false;
    this->altezza;
    this->larghezza;
    this->punto_partenza_y = 0;
    this->punto_partenza_x = 0;
    this->stat = stat;

    int m = (larghezza / 2 )-(51);                  // Punto di partenza da sinistra del PC
    int n = m+22;                                  // Punto di partenza da sinistra della scritta
    int nn = n-10;

    //colori
    double cambiocolore = 1000 / 255;
    start_color();
    init_color(Grigio, 128*cambiocolore, 128*cambiocolore, 128*cambiocolore);
    init_color(Sfondo, 188*cambiocolore, 212*cambiocolore, 230*cambiocolore);
    init_color(Marrone, 79*cambiocolore, 50*cambiocolore, 32*cambiocolore);      
    init_pair(5, COLOR_WHITE, Grigio);                    
    init_pair(6, Sfondo, Sfondo);                         
    init_pair(8, COLOR_BLACK, COLOR_WHITE);               
    init_pair(12, COLOR_BLACK, COLOR_GREEN);              
    init_pair(13, COLOR_WHITE, COLOR_BLUE);               
    init_pair(14, COLOR_WHITE, Marrone);                  
    init_pair(15, COLOR_GREEN, COLOR_BLACK);              
    init_pair(17, COLOR_BLACK, Marrone);                  


    this->win = newwin(this->altezza, this->larghezza, 0, 0);
    box(this->win, 0, 0);
    wrefresh(this->win);

    //Colore sfondo
    wbkgd(this->win, COLOR_PAIR(6));

    //Tavolo
    int t = larghezza - 16;
    wattron(this->win, COLOR_PAIR(14));
    //Colore tavolo
    for (int i = 30; i <= altezza; i++){
        for (int j = 0; j <= larghezza; j++){
            mvwprintw(this->win, i, j, " ");
        }
    }
    wattroff(this->win, COLOR_PAIR(14));
    //Bordi tavolo sx 
    wattron(this->win, COLOR_PAIR(6));
    mvwprintw(this->win,30, 0, "                  ");
    mvwprintw(this->win,31, 0, "                 ");
    mvwprintw(this->win,32, 0, "                ");
    mvwprintw(this->win,33, 0, "               ");
    mvwprintw(this->win,34, 0, "              ");
    mvwprintw(this->win,35, 0, "             ");
    mvwprintw(this->win,36, 0, "            ");
    mvwprintw(this->win,37, 0, "           ");
    mvwprintw(this->win,38, 0, "          ");
    mvwprintw(this->win,39, 0, "         ");
    mvwprintw(this->win,40, 0, "        ");
    mvwprintw(this->win,41, 0, "       ");
    mvwprintw(this->win,42, 0, "      ");
    mvwprintw(this->win,43, 0, "     ");
    mvwprintw(this->win,44, 0, "    ");
    mvwprintw(this->win,45, 0, "   ");
    mvwprintw(this->win,46, 0, "  ");
    mvwprintw(this->win,47, 0, " ");
    wattroff(this->win, COLOR_PAIR(6));
    //Bordi tavolo dx 
    wattron(this->win, COLOR_PAIR(6));
    mvwprintw(this->win,30, larghezza-18,  "                  ");
    mvwprintw(this->win,31, larghezza-17,  "                 ");
    mvwprintw(this->win,32, larghezza-16,  "                ");
    mvwprintw(this->win,33, larghezza-15,  "               ");
    mvwprintw(this->win,34, larghezza-14,  "              ");
    mvwprintw(this->win,35, larghezza-13,  "             ");
    mvwprintw(this->win,36, larghezza-12,  "            ");
    mvwprintw(this->win,37, larghezza-11,  "           ");
    mvwprintw(this->win,38, larghezza-10,  "          ");
    mvwprintw(this->win,39, larghezza-9,   "         ");
    mvwprintw(this->win,40, larghezza-8,   "        ");
    mvwprintw(this->win,41, larghezza-7,   "       ");
    mvwprintw(this->win,42, larghezza-6,   "      ");
    mvwprintw(this->win,43, larghezza-5,   "     ");
    mvwprintw(this->win,44, larghezza-4,   "    ");
    mvwprintw(this->win,45, larghezza-3,   "   ");
    mvwprintw(this->win,46, larghezza-2,   "  ");
    mvwprintw(this->win,47, larghezza-1,   " ");
    wattroff(this->win, COLOR_PAIR(6));

    //Monitor
    wattron(this->win, COLOR_PAIR(5));
    //Bordo alto
    mvwprintw(this->win, 0, m+3, "                                                                                               ");
    mvwprintw(this->win, 1, m+1, "  							                                          ");
    mvwprintw(this->win, 2, m  , "											                   ");
    mvwprintw(this->win, 3, m  , "                                                                                                     ");
    //Bordo sx
    mvwprintw(this->win, 4, m  , "       ");
    mvwprintw(this->win, 5, m  , "       ");
    mvwprintw(this->win, 6, m  , "       ");
    mvwprintw(this->win, 7, m  , "       ");
    mvwprintw(this->win, 8, m  , "       ");
    mvwprintw(this->win, 9, m  , "       ");
    mvwprintw(this->win,10, m  , "       ");
    mvwprintw(this->win,11, m  , "       ");
    mvwprintw(this->win,12, m  , "       ");
    mvwprintw(this->win,13, m  , "       ");
    mvwprintw(this->win,14, m  , "       ");
    mvwprintw(this->win,15, m  , "       ");
    mvwprintw(this->win,16, m  , "       ");
    mvwprintw(this->win,17, m  , "       ");
    mvwprintw(this->win,18, m  , "       ");
    mvwprintw(this->win,19, m  , "       ");
    mvwprintw(this->win,20, m  , "       ");
    mvwprintw(this->win,21, m  , "       ");
    mvwprintw(this->win,22, m  , "       ");
    mvwprintw(this->win,23, m  , "       ");
    mvwprintw(this->win,24, m  , "       ");
    mvwprintw(this->win,25, m  , "       ");
    mvwprintw(this->win,26, m  , "       ");
    mvwprintw(this->win,27, m  , "       ");
    mvwprintw(this->win,28, m  , "       ");
    mvwprintw(this->win,29, m  , "       ");
    mvwprintw(this->win,30, m  , "       ");
    mvwprintw(this->win,31, m  , "       ");
    mvwprintw(this->win,32, m  , "       ");
    mvwprintw(this->win,33, m  , "       ");
    //Bordo dx
    mvwprintw(this->win, 4,m+94, "       ");
    mvwprintw(this->win, 5,m+94, "       ");
    mvwprintw(this->win, 6,m+94, "       ");
    mvwprintw(this->win, 7,m+94, "       ");
    mvwprintw(this->win, 8,m+94, "       ");
    mvwprintw(this->win, 9,m+94, "       ");
    mvwprintw(this->win,10,m+94, "       ");
    mvwprintw(this->win,11,m+94, "       ");
    mvwprintw(this->win,12,m+94, "       ");
    mvwprintw(this->win,13,m+94, "       ");
    mvwprintw(this->win,14,m+94, "       ");
    mvwprintw(this->win,15,m+94, "       ");
    mvwprintw(this->win,16,m+94, "       ");
    mvwprintw(this->win,17,m+94, "       ");
    mvwprintw(this->win,18,m+94, "       ");
    mvwprintw(this->win,19,m+94, "       ");
    mvwprintw(this->win,20,m+94, "       ");
    mvwprintw(this->win,21,m+94, "       ");
    mvwprintw(this->win,22,m+94, "       ");
    mvwprintw(this->win,23,m+94, "       ");
    mvwprintw(this->win,24,m+94, "       ");
    mvwprintw(this->win,25,m+94, "       ");
    mvwprintw(this->win,26,m+94, "       ");
    mvwprintw(this->win,27,m+94, "       ");
    mvwprintw(this->win,28,m+94, "       ");
    mvwprintw(this->win,29,m+94, "       ");
    mvwprintw(this->win,30,m+94, "       ");
    mvwprintw(this->win,31,m+94, "       ");
    mvwprintw(this->win,32,m+94, "       ");
    mvwprintw(this->win,33,m+94, "       ");
    //Bordo basso
    mvwprintw(this->win,34, m  , "                                                                                                     ");
    mvwprintw(this->win,35, m+1, "                                                                                                   ");
    mvwprintw(this->win,36, m+3, "                                                                                               ");
    mvwprintw(this->win,37, m+7, "                                                                                       ");
    mvwprintw(this->win,38, m+9, "                                                                                   ");

    
    //Keybord
    mvwprintw(this->win,40, m, "     ____                                                                         ");
    mvwprintw(this->win,41, m, "    [____] [_]   [_][_][_][_] [_][_][_][_] [_][_][_][_] [_][_][_] [_][_][_][_]    ");
    mvwprintw(this->win,42, m, "                                                   ___                            ");
    mvwprintw(this->win,43, m, "    [_][_] [ ][1][2][3][4][5][6][7][8][9][0][+]['][___] [_][_][_] [_][_][_][_]    ");
    mvwprintw(this->win,44, m, "    [_][_] [__][q][w][e][r][t][y][u][i][o][p][ ][*][  | [_][_][_] [_][_][_][ |    ");
    mvwprintw(this->win,45, m, "    [_][_] [___][a][s][d][f][g][h][j][k][l][@][ ][ ][_|           [_][_][_][_|    ");
    mvwprintw(this->win,46, m, "    [_][_] [_][<][z][x][c][v][b][n][m][;][.][-][______]    [_]    [_][_][_][ |    ");
    mvwprintw(this->win,47, m, "    [_][_] [__][_][__][_____________________][__][_][_] [_][_][_] [____][_][_|    ");
    mvwprintw(this->win,48, m, "                                                                                  ");
    wattroff(this->win, COLOR_PAIR(5));

    //Tappetino mouse
    wattron(this->win, COLOR_PAIR(11));
    mvwprintw(this->win,40, m+88, "                                 ");
    mvwprintw(this->win,41, m+88, "                                 ");
    mvwprintw(this->win,42, m+88, "                                 ");
    mvwprintw(this->win,43, m+88, "                                 ");
    mvwprintw(this->win,44, m+88, "                                 ");
    mvwprintw(this->win,45, m+88, "                                 ");
    mvwprintw(this->win,46, m+88, "                                 ");
    mvwprintw(this->win,47, m+88, "                                 ");
    mvwprintw(this->win,48, m+88, "                                 ");
    wattroff(this->win, COLOR_PAIR(11));
    

    //Mouse
    wattron(this->win, COLOR_PAIR(5));
    mvwprintw(this->win,40, m+101, "       ");
    mvwprintw(this->win,41, m+100, "    |    ");
    mvwprintw(this->win,42, m+100, " ___|___ ");
    mvwprintw(this->win,43, m+100, "         ");
    mvwprintw(this->win,44, m+100, "         ");
    mvwprintw(this->win,45, m+100, "         ");
    mvwprintw(this->win,46, m+100, "         ");
    mvwprintw(this->win,47, m+101, "       ");
    wattroff(this->win, COLOR_PAIR(5));

    //Sfondo PC
    wattron(this->win, COLOR_PAIR(15));
    mvwprintw(this->win, 4, m+7, "                                                                                       ");
    mvwprintw(this->win, 5, m+7, "                                                                                       ");
    mvwprintw(this->win, 6, m+7, "                                                                                       ");
    mvwprintw(this->win, 7, m+7, "                                                                                       ");
    mvwprintw(this->win, 8, m+7, "                                                                                       ");
    mvwprintw(this->win, 9, m+7, "                                                                                       ");
    mvwprintw(this->win,10, m+7, "                                                                                       ");
    mvwprintw(this->win,11, m+7, "                                                                                       ");
    mvwprintw(this->win,12, m+7, "                                                                                       ");
    mvwprintw(this->win,13, m+7, "                                                                                       ");
    mvwprintw(this->win,14, m+7, "                                                                                       ");
    mvwprintw(this->win,15, m+7, "                                                                                       ");
    mvwprintw(this->win,16, m+7, "                                                                                       ");
    mvwprintw(this->win,17, m+7, "                                                                                       ");
    mvwprintw(this->win,18, m+7, "                                                                                       ");
    mvwprintw(this->win,19, m+7, "                                                                                       ");
    mvwprintw(this->win,20, m+7, "                                                                                       ");
    mvwprintw(this->win,21, m+7, "                                                                                       ");
    mvwprintw(this->win,22, m+7, "                                                                                       ");
    mvwprintw(this->win,23, m+7, "                                                                                       ");
    mvwprintw(this->win,24, m+7, "                                                                                       ");
    mvwprintw(this->win,25, m+7, "                                                                                       ");
    mvwprintw(this->win,26, m+7, "                                                                                       ");
    mvwprintw(this->win,27, m+7, "                                                                                       ");
    mvwprintw(this->win,28, m+7, "                                                                                       ");
    mvwprintw(this->win,29, m+7, "                                                                                       ");
    mvwprintw(this->win,30, m+7, "                                                                                       ");
    mvwprintw(this->win,31, m+7, "                                                                                       ");
    mvwprintw(this->win,32, m+7, "                                                                                       ");
    mvwprintw(this->win,33, m+7, "                                                                                       ");
    wattroff(this->win, COLOR_PAIR(15));
    //Stampa base
    wattron(this->win, COLOR_PAIR(15));
    if (this->stat == 0){
        mvwprintw(this->win,7, n+7,      "______ __________ __________ __________ _________");
        mvwprintw(this->win,8, n+6,     "/_____/__________/__________/__________/_________/|");
        mvwprintw(this->win,9, n+6,     "|     |          |    __    |    __    |         ||");
        mvwprintw(this->win,10,n+6,     "|     |    __    |   ||_|   |   ||_|   |         ||");
        mvwprintw(this->win,11,n+6,     "|     |   || |   |   |/_|   |   |/_|   |   ___   ||");
        mvwprintw(this->win,12,n+1,"___  |     |   ||_|   |          |          |  | | |  ||");
        mvwprintw(this->win,13,n, "/__/| |     |   |/_|   |          |          |  | | |  ||");
        mvwprintw(this->win,14,n, "|  ||_|     |          |    __    |    __    |  | |_|  ||");
        mvwprintw(this->win,15,n, "|  |/_|     |          |   ||_|   |   ||_|   |  |/__|  ||");
        mvwprintw(this->win,16,n, "|           |    __    |   |/_|   |   |/_|   |         ||");
        mvwprintw(this->win,17,n, "|           |   ||_|   |          |          |         ||");
        mvwprintw(this->win,18,n, "|___________|___|/ |___|__________|__________|_________|/");
    }
    //Stampa vittoria
    else if (this->stat == 1){
        mvwprintw(this->win,5, nn,     "   _____                            _         _           _             _ ");
        mvwprintw(this->win,6, nn,     "  / ____|                          | |       | |         (_)           (_)");
        mvwprintw(this->win,7, nn,     " | |     ___  _ __   __ _ _ __ __ _| |_ _   _| | __ _ _____  ___  _ __  _ ");
        mvwprintw(this->win,8, nn,     " | |    / _ \\| '_ \\ / _` | '__/ _` | __| | | | |/ _` |_  / |/ _ \\| '_ \\| |");
        mvwprintw(this->win,9, nn,     " | |___| (_) | | | | (_| | | | (_| | |_| |_| | | (_| |/ /| | (_) | | | | |");
        mvwprintw(this->win,10,nn,     "  \\_____\\___/|_| |_|\\__, |_|  \\__,_|\\__|\\__,_|_|\\__,_/___|_|\\___/|_| |_|_|");
        mvwprintw(this->win,11,nn,     "                     __/ |                                                ");
        mvwprintw(this->win,12,nn,     "                    |___/                                                 ");
        mvwprintw(this->win,13,nn,     "                    _           _         _       _                       ");
        mvwprintw(this->win,14,nn,     "                   | |         (_)       (_)     | |                      ");
        mvwprintw(this->win,15,nn,     "                   | |__   __ _ _  __   ___ _ __ | |_ ___                 ");
        mvwprintw(this->win,16,nn,     "                   | '_ \\ / _` | | \\ \\ / / | '_ \\| __/ _ \\                ");
        mvwprintw(this->win,17,nn,     "                   | | | | (_| | |  \\ V /| | | | | || (_) |               ");
        mvwprintw(this->win,18,nn,     "                   |_| |_|\\__,_|_|   \\_/ |_|_| |_|\\__\\___/                ");
    }
    //Stampa sconfitta
    else if (this->stat == 2){
        mvwprintw(this->win,5, nn+4,     "              _    _       _                                               ");
        mvwprintw(this->win,6, nn+4,     "             | |  | |     (_)                                              ");
        mvwprintw(this->win,7, nn+4,     "             | |__| | __ _ _   _ __   ___ _ __ ___  ___                    ");
        mvwprintw(this->win,8,nn+4,      "             |  __  |/ _` | | | '_ \\ / _ \\ '__/ __|/ _ \\                   ");
        mvwprintw(this->win,9,nn+4,      "             | |  | | (_| | | | |_) |  __/ |  \\__ \\ (_) |                  ");
        mvwprintw(this->win,10,nn+4,     "             |_|  |_|\\__,_|_| | .__/ \\___|_|  |___/\\___/                   ");
        mvwprintw(this->win,11,nn+4,     "                              | |                 ");
        mvwprintw(this->win,12,nn+4,     "                              |_|");
        mvwprintw(this->win,13,nn,     "	 _                                 _ _");
        mvwprintw(this->win,14,nn,     "      (_)                               | (_)                              ");
        mvwprintw(this->win,15,nn,     "  _ __ _ _ __  _ __ _____   ______    __| |_   _ __  _   _  _____   _____  ");
        mvwprintw(this->win,16,nn,     " | '__| | '_ \\| '__/ _ \\ \\ / / _` |  / _` | | | '_ \\| | | |/ _ \\ \\ / / _ \\ ");
        mvwprintw(this->win,17,nn,     " | |  | | |_) | | | (_) \\ V / (_| | | (_| | | | | | | |_| | (_) \\ V / (_) |");
        mvwprintw(this->win,18,nn,     " |_|  |_| .__/|_|  \\___/ \\_/ \\__,_|  \\__,_|_| |_| |_|\\__,_|\\___/ \\_/ \\___/ ");
        mvwprintw(this->win,19,nn,     "        | |                                                                ");
        mvwprintw(this->win,20,nn,     "        |_|                                                                ");
    }
    //Stampa ritirata
    else if (this->stat == 3){
        int mm = nn+14;
        mvwprintw(this->win,6, mm+2,     "      _______   _                  _              ");
        mvwprintw(this->win,7, mm+2,     "     |__   __| (_)                (_)             ");
        mvwprintw(this->win,8, mm+2,     "        | |     _     ___    ___   _              ");
        mvwprintw(this->win,9, mm+2,     "        | |    | |   / __|  / _ \\ | |             ");
        mvwprintw(this->win,10, mm+2,    "        | |    | |   \\__ \\ |  __/ | |             ");
        mvwprintw(this->win,11,mm+2,     "        |_|    |_|   |___/  \\___| |_|             ");
        mvwprintw(this->win,12,mm,     "                                                  ");
        mvwprintw(this->win,13,mm,     "         _   _     _                  _           ");
        mvwprintw(this->win,14,mm,     "        (_) | |   (_)                | |          ");
        mvwprintw(this->win,15,mm,     "  _ __   _  | |_   _   _ __    __ _  | |_    ___  ");
        mvwprintw(this->win,16,mm,     " | '__| | | | __| | | | '__|  / _` | | __|  / _ \\ ");
        mvwprintw(this->win,17,mm,     " | |    | | | |_  | | | |    | (_| | | |_  | (_) |");
        mvwprintw(this->win,18,mm,     " |_|    |_|  \\__| |_| |_|     \\__,_|  \\__|  \\___/ ");
    }
    wattroff(this->win, COLOR_PAIR(15));
    wrefresh(this->win);

        this->h = 14;
        this->l = 40;
        this->p_p_y = 19;
        this->p_p_x = n+13;
        this->menuwin = newwin(this->h, this->l, this->p_p_y, this->p_p_x);
        box(this->menuwin, 0, 0);
        wrefresh(this->menuwin);
        wbkgd(this->menuwin, COLOR_PAIR(15));
        
        wattron(this->menuwin, COLOR_PAIR(15));
        for (int i = 0; i <= this->h; i++){
            mvwprintw(this->menuwin, i, 0, " ");
            mvwprintw(this->menuwin, i, this->l-1, " ");
        }
        for (int  j= 0; j <=this->l; j++){
                mvwprintw(this->menuwin, 0, j, " ");
                mvwprintw(this->menuwin, this->h-1, j, " ");
            }
        wrefresh(this->menuwin);
        keypad(this->menuwin, true);
        for(int i = 0; i < 4; i++)
            {
                if (i == this->highlight)
                wattron(this->menuwin, COLOR_PAIR(12));
                mvwprintw(this->menuwin, i+6, 1, choices[i].c_str());
                wattroff(this->menuwin, COLOR_PAIR(12));
            }
        wattroff(this->menuwin, COLOR_PAIR(15));
        wrefresh(this->menuwin);
    }

    void Menu::getchoice()
    {
        //Menu scelta 
        wattron(this->menuwin, COLOR_PAIR(15));
        int choice = wgetch(this->menuwin);
            switch(choice)
            {
                case KEY_UP:
                    this->highlight--;
                    if (this->highlight == -1)
                        this->highlight = 0;
                    break;
                case KEY_DOWN:
                    this->highlight++;
                    if (this->highlight == 4)
                        this->highlight = 3;
                    break;
                case KEY_RIGHT:
                    if(this->highlight==0)
                    this->scelta = 1;
                    if(this->highlight==1)
                    this->scelta = 2;
                    if(this->highlight==2)
                    this->scelta = 3;
                    if (this->highlight==3)
                    this->scelta = 4;
                    this->exit = true;
                    
                break;
            }
        //evidenzia scelta
        for(int i = 0; i < 4; i++)
            {
                if (i == this->highlight)
                    wattron(this->menuwin, COLOR_PAIR(12));
                mvwprintw(this->menuwin, i+6, 1, choices[i].c_str());
                wattroff(this->menuwin, COLOR_PAIR(12));
            }
        wattroff(this->menuwin, COLOR_PAIR(15));
    }

    #endif
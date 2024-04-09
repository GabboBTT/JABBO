#ifndef MAPPA
#define MAPPA
#include <ncurses.h>
#include <stdlib.h>

//colori 
#define Sfondo 1   
#define Platino 3
#define Grigio 5
#define Marrone 6
#define Giallo 11
#define Purple 12

class Mappa
{
    protected:
        WINDOW *curwin;

    public:
        Mappa(WINDOW *win, int x, int y, int xMax, int yMax, int n);
        int xMax;       //massimo numero di colonne
        int yMax;       //massimo numero di righe
        int xMin;       //posizione prima colonna
        int yMin;       //posizione prima riga
        int a;          //primo valore dove si trova la porta da aprire
        int n;          //numero della mappa
        bool attivi[3];
};

int num_random(int max){       
    return(rand()%max+1);
}

Mappa::Mappa(WINDOW *win, int x, int y, int xMax, int yMax, int n)
{
    int h, l;
    getmaxyx(stdscr, h, l);
    this->curwin = win;
    wrefresh(this->curwin);

    int lmin = (yMax/(2.5))+1 ;
    int hmin = xMax/(2.2);
    int lmax = lmin + x;
    int hmax = hmin + y;

    this->xMin = xMax/(2.2);
    this->yMin = (yMax/(2.5))+1;
    this->xMax = this->xMin + x;
    this->yMax = this->yMin + y;
    
    this->n = n;
    keypad(this->curwin, true);

    //colori 
    start_color();
    double cambiocolore = 1000 / 255;
    init_color(Platino, 232*cambiocolore, 231*cambiocolore, 229*cambiocolore);
    init_color(Grigio, 128*cambiocolore, 128*cambiocolore, 128*cambiocolore);
    init_color(Sfondo, 188*cambiocolore, 212*cambiocolore, 230*cambiocolore);
    init_color(Marrone, 79*cambiocolore, 50*cambiocolore, 32*cambiocolore);
    init_color(Giallo, 255*cambiocolore, 239*cambiocolore, 0*cambiocolore);     
    init_color(Purple, 160*cambiocolore, 32*cambiocolore, 240*cambiocolore);    
    init_pair(1, COLOR_WHITE, Platino);                   
    init_pair(5, COLOR_WHITE, Grigio);                   
    init_pair(6, Sfondo, Sfondo);                         
    init_pair(7, Marrone, Marrone);                       
    init_pair(8, COLOR_BLACK, COLOR_WHITE);               
    init_pair(9, COLOR_BLACK, Giallo);             
    init_pair(10, COLOR_BLACK, Purple);            
    init_pair(37, COLOR_BLACK, COLOR_BLUE);               
    
    wrefresh(this->curwin);
    //Bordo computer
    wattron(this->curwin, COLOR_PAIR(5));
        for (int j = 0; j <= l; j++){
	        mvwprintw(this->curwin, 0, j,  " ");
	        mvwprintw(this->curwin, 1, j,  " ");
	        mvwprintw(this->curwin, 2, j,  " ");
            mvwprintw(this->curwin, h, j,  " ");
	        mvwprintw(this->curwin, h-1, j,  " ");
	        mvwprintw(this->curwin, h-2, j,  " ");
            mvwprintw(this->curwin, h-3, j,  " ");
        }
        for (int j = 0; j <= h; j++){
	        mvwprintw(this->curwin, j, 0,  " ");
	        mvwprintw(this->curwin, j, 1,  " ");
	        mvwprintw(this->curwin, j, 2,  " ");
            mvwprintw(this->curwin, j, l,  " ");
	        mvwprintw(this->curwin, j, l-1,  " ");
	        mvwprintw(this->curwin, j, l-2,  " ");
            mvwprintw(this->curwin, j, l-3,  " ");
        }
    wattroff(this->curwin, COLOR_PAIR(5));
    wrefresh(this->curwin);
    
    //Creazione campo 
    for(int i=this->yMin; i<=this->yMax; i++){
        for(int j=this->xMin; j<=this->xMax; j++){
            if((i==this->yMin)||(i==this->yMax)){
                            mvwaddch(this->curwin, i, j, '-');                      //righe campo
            } else if((j==this->xMin)||(j==this->xMax)){
                            mvwaddch(this->curwin, i, j, '|');                      //colonne campo
            } 
        }
    }
    wrefresh(this->curwin);
    for(int i=0; i<3; i++){
        this->attivi[i] = false;
    }
    //angoli
    mvwaddch(this->curwin, this->yMin, this->xMin, '+');
    mvwaddch(this->curwin, this->yMin, this->xMax, '+');
    mvwaddch(this->curwin, this->yMax, this->xMin, '+');     
    mvwaddch(this->curwin, this->yMax, this->xMax, '+');
    int b;
    int c;
    int jj;
    wrefresh(this->curwin);

    switch(this->n){
        case 1:
            this->a = num_random(45)+5;
            for(int i=1; i<6; i++){
                mvwaddch(this->curwin, this->yMin, this->xMin+a+i, '@');                   //uscita chiusa
            }
            b = num_random(6)+7;
            c = num_random(10)+30;
            for(int i=this->xMin+1; i<this->xMin+c; i++){
                mvwaddch(this->curwin, this->yMin+b, i, '-');
            }
            mvwaddch(this->curwin, this->yMin+b, this->xMin, '+');
            do{
                b = num_random(10)+this->yMin+2;
                c = num_random(50)+this->xMin+3;
            } while (mvwinch(this->curwin,b,c)!=' '); //il do while serve per verificare che nello spazio in cui va inserita la nuova lettera non ne sia già presente un'altra
        break;
        case 2:

            this->a = num_random(45)+5;
            for(int i=1; i<6; i++){
                mvwaddch(this->curwin, this->yMin, this->xMin+a+i, '@');                   //uscita chiusa
            }
            b = num_random(6)+7;
            c = num_random(10)+30;
            for(int i=this->xMin+1; i<this->xMin+c; i++){
                mvwaddch(this->curwin, this->yMin+b, i, '-');
            }
            mvwaddch(this->curwin, this->yMin+b, this->xMin, '+');
            for(int i=this->xMin+c+5; i<this->xMax; i++){
                mvwaddch(this->curwin, this->yMin+b, i, '-');
            }
            mvwaddch(this->curwin, this->yMin+b, this->xMax, '+');
            do{
                b = num_random(10)+this->yMin+2;
                c = num_random(50)+this->xMin+3;
            } while (mvwinch(this->curwin,b,c)!=' '); //il do while serve per verificare che nello spazio in cui va inserita la nuova lettera non ne sia già presente un'altra
    
        break;
        case 3:

            this->a = num_random(10)+2;
            for(int i=1; i<6; i++){
                mvwaddch(this->curwin, this->yMin+a+i, this->xMax, '@');                   //uscita chiusa
            }
            b = num_random(6)+7;
            c = num_random(10)+30;
            for(int i=this->xMin+1; i<this->xMin+c; i++){
                mvwaddch(this->curwin, this->yMin+b, i, '-');
            }
            mvwaddch(this->curwin, this->yMin+b, this->xMin, '+');
            b = num_random(4)+3;
            c = num_random(10)+30;
            for(int i=this->yMin+1; i<this->yMin+b; i++){
                mvwaddch(this->curwin, i, this->xMin+c, '|');
            }
            mvwaddch(this->curwin, this->yMin, this->xMin+c, '+');
            do{
                b = num_random(10)+this->yMin+2;
                c = num_random(50)+this->xMin+3;
            } while (mvwinch(this->curwin,b,c)!=' '); //il do while serve per verificare che nello spazio in cui va inserita la nuova lettera non ne sia già presente un'altra
    
        break;
        case 4:

            this->a = num_random(10)+2;
            for(int i=1; i<6; i++){
                mvwaddch(this->curwin, this->yMin+a+i, this->xMax, '@');                   //uscita chiusa
            }
            b = this->yMax-1;
            c = 7;
            jj = 0;
            for(int i=1; i<15; i++){
                mvwaddch(this->curwin, b-jj, this->xMin+c+i, '/');
                jj= jj+1;
            }
            mvwaddch(this->curwin, this->yMax, this->xMin+c, '+');
            b = this->yMin+1;
            c = 15;
            jj = 0;
            for(int i=1; i<15; i++){
                mvwaddch(this->curwin, b+jj, this->xMax-c-i, '/');
                jj= jj+1;
            }
            mvwaddch(this->curwin, this->yMin, this->xMax-c, '+');
            do{
                b = num_random(10)+this->yMin+2;
                c = num_random(50)+this->xMin+3;
            } while (mvwinch(this->curwin,b,c)!=' '); //il do while serve per verificare che nello spazio in cui va inserita la nuova lettera non ne sia già presente un'altra
    
        break;
        case 5:

            this->a = num_random(45)+5;
            for(int i=1; i<6; i++){
                mvwaddch(this->curwin, this->yMax, this->xMin+a+i, '@');                   //uscita chiusa
            }
            b = num_random(6)+7;
            c = num_random(10)+30;
            for(int i=this->xMin+1; i<this->xMin+c; i++){
                mvwaddch(this->curwin, this->yMin+b, i, '-');
            }
            mvwaddch(this->curwin, this->yMin+b, this->xMin, '+');
            b = b+5;
            c = num_random(10)+30;
            for(int i=this->xMax; i>this->xMax-c; i--){
                mvwaddch(this->curwin, this->yMin+b, i, '-');
            }
            mvwaddch(this->curwin, this->yMin+b, this->xMax, '+');
            do{
                b = num_random(10)+this->yMin+2;
                c = num_random(50)+this->xMin+3;
            } while (mvwinch(this->curwin,b,c)!=' '); //il do while serve per verificare che nello spazio in cui va inserita la nuova lettera non ne sia già presente un'altra
    
        break;
        case 6:

            this->a = num_random(45)+5;
            for(int i=1; i<6; i++){
                mvwaddch(this->curwin, this->yMax, this->xMin+a+i, '@');                   //uscita chiusa
            }
            b = num_random(6)+7;
            c = num_random(10)+40;
            for(int i=this->xMin+1; i<this->xMin+c; i++){
                mvwaddch(this->curwin, this->yMin+b, i, '-');
            }
            mvwaddch(this->curwin, this->yMin+b, this->xMin, '+');
            b = b-5;
            c = num_random(10)+40;
            for(int i=this->xMin+1; i<this->xMin+c; i++){
                mvwaddch(this->curwin, this->yMin+b, i, '-');
            }
            mvwaddch(this->curwin, this->yMin+b, this->xMin, '+');
            do{
                b = num_random(10)+this->yMin+2;
                c = num_random(50)+this->xMin+3;
            } while (mvwinch(this->curwin,b,c)!=' '); //il do while serve per verificare che nello spazio in cui va inserita la nuova lettera non ne sia già presente un'altra
    
        break;
        case 7:

            this->a = num_random(10)+2;
            for(int i=1; i<6; i++){
                mvwaddch(this->curwin, this->yMin+a+i, this->xMin, '@');                   //uscita chiusa
            }
            b = this->yMax-6;
            c = num_random(10)+30;
            for(int i=this->xMin+1; i<this->xMin+c; i++){
                mvwaddch(this->curwin, b, i, '-');
            }
            mvwaddch(this->curwin, b, this->xMin, '+');
            for(int i=this->xMin+c+5; i<this->xMax; i++){
                mvwaddch(this->curwin, b, i, '-');
            }
            mvwaddch(this->curwin, b, this->xMax, '+');
            do{
                b = +this->yMax-num_random(4);
                c = num_random(50)+this->xMin+3;
            } while (mvwinch(this->curwin,b,c)!=' '); //il do while serve per verificare che nello spazio in cui va inserita la nuova lettera non ne sia già presente un'altra
    
        break;
        case 8:

            this->a = num_random(45)+5;
            for(int i=1; i<6; i++){
                mvwaddch(this->curwin, this->yMin, this->xMin+a+i, '@');                   //uscita chiusa
            }
            b = num_random(6)+7;
            c = num_random(10)+30;
            for(int i=this->xMin+1; i<this->xMin+c; i++){
                mvwaddch(this->curwin, this->yMin+b, i, '-');
            }
            mvwaddch(this->curwin, this->yMin+b, this->xMin, '+');
            b = b+5;
            c = num_random(10)+30;
            for(int i=this->xMax-1; i>this->xMax-c; i--){
                mvwaddch(this->curwin, this->yMin+b, i, '-');
            }
            mvwaddch(this->curwin, this->yMin+b, this->xMax, '+');
            b = b-9;
            c = num_random(10)+30;
            for(int i=this->xMax-1; i>this->xMax-c; i--){
                mvwaddch(this->curwin, this->yMin+b, i, '-');
            }
            mvwaddch(this->curwin, this->yMin+b, this->xMax, '+');
            do{
                b = num_random(10)+this->yMin+2;
                c = num_random(50)+this->xMin+3;
            } while (mvwinch(this->curwin,b,c)!=' '); //il do while serve per verificare che nello spazio in cui va inserita la nuova lettera non ne sia già presente un'altra
    
        break;
        case 9:

        break;
    }
    wrefresh(this->curwin);

    //controllo colori
    if(has_colors()==FALSE){ 
        endwin(); 
        printf("Color can't be used"); 
    }

    //chiave
    do{
        if(this->n!=7){
            b = num_random(6)+this->yMin+2;
            c = num_random(20)+this->xMin+3;
        } else {
            b = this->yMax-3;
            c = num_random(50)+this->xMin+3;
        }
    } while (mvwinch(this->curwin,b,c)!=' ');
    chtype chiave = 'C' | A_REVERSE | COLOR_PAIR(12);
    mvwaddch(this->curwin, b , c , chiave);  

    //poteri 
    int npoteri = num_random(3);               //decide a sorte quanti poteri mettere (max 3)
    for(int i=1; i<=npoteri; i++){
        int potere = num_random(3);             //decide a sorte quale potere inserire
        do{
        b = num_random(6)+this->yMin+2;
        c = num_random(20)+this->xMin+3;
        } while (mvwinch(this->curwin,b,c)!=' ');
        chtype p;
        switch(potere){
            case 1:
            if(this->attivi[0]==false){
                p = 'S' | A_REVERSE | COLOR_PAIR(37); //scudo  
                mvwaddch(this->curwin, b , c , p);
                this->attivi[0] = true;
            }
            break;
            case 2:
            if(this->attivi[1]==false){
                p = 'A' | A_REVERSE | COLOR_PAIR(10); //attacco potenziato
                mvwaddch(this->curwin, b , c , p);
                this->attivi[1] = true;
            }
            break;
            case 3:
            if(this->attivi[2]==false){
                p = 'V' | A_REVERSE | COLOR_PAIR(9); //vita extra
                mvwaddch(this->curwin, b , c , p);
                this->attivi[2] = true;
            }
            break;
        }
    wrefresh(this->curwin);
    }
}

#endif
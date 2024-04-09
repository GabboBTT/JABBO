#ifndef CREDITS
#define CREDITS

#include <ncurses.h>

//colori 
#define Grigio 5
#define Marrone 6
#define Azzurrino 7
#define Tela 8
#define Arancione 9
#define Rosso 10
#define Giallo 11
#define Purple 12

class credits{
    protected:
        int xMax;
        int yMax;
        WINDOW * cwin;
    public:
        credits(int a);
        void getchoice();
        bool exit;

};

credits::credits(int a){
    int m, n;                                               //Variabili d'appoggio 
    getmaxyx(stdscr, this->yMax, this->xMax);               //Prende le dimensioni schermo 
    m = ((this->xMax / 2) - 80);                      
    n = this->yMax / 1.5;
    this->exit=false;

    //schermata comandi
    if(a==2){	
        //colori
        start_color();
        double cambiocolore = 1000 / 255;
        init_color(Tela, 255*cambiocolore, 250*cambiocolore, 240*cambiocolore);
        init_color(Grigio, 128*cambiocolore, 128*cambiocolore, 128*cambiocolore);
        init_color(Marrone, 79*cambiocolore, 50*cambiocolore, 32*cambiocolore);
        init_color(Azzurrino, 208*cambiocolore, 235*cambiocolore, 255*cambiocolore);
        init_color(Arancione, 255*cambiocolore, 177*cambiocolore, 56*cambiocolore);
        init_color(Rosso, 214*cambiocolore, 34*cambiocolore, 46*cambiocolore);
        init_color(Giallo, 255*cambiocolore, 239*cambiocolore, 0*cambiocolore);
        init_color(Purple, 160*cambiocolore, 32*cambiocolore, 240*cambiocolore);           
        init_pair(5, COLOR_WHITE, Grigio);                    
        init_pair(17, COLOR_BLACK, Marrone);                  
        init_pair(22, Grigio, Giallo);                        
        init_pair(23, Grigio, COLOR_BLUE);                   
        init_pair(24, Grigio, Rosso);                         
        init_pair(25, Grigio, Purple);                        
        init_pair(26, Grigio, Arancione);                     
        init_pair(27, Grigio, COLOR_GREEN);                  
        init_pair(28, COLOR_YELLOW, Azzurrino);               
        init_pair(29, COLOR_BLUE, Azzurrino);                 
        init_pair(30, COLOR_RED, Azzurrino);                  
        init_pair(31, COLOR_MAGENTA, Azzurrino);              
        init_pair(32, COLOR_CYAN, Azzurrino);                 
        init_pair(33, COLOR_GREEN, Azzurrino);                
        init_pair(34, COLOR_BLACK, Tela);                     
        init_pair(35, COLOR_WHITE, Tela);                     
        init_pair(38, COLOR_WHITE, Azzurrino);                

        //setto la box 
        this->cwin = newwin(this->yMax, this->xMax, 0, 0);
        box(this->cwin, 0, 0);
        wrefresh(this->cwin);

        
        //Colore sfondo
        wattron(this->cwin, COLOR_PAIR(38));
        for (int i = 0; i <= this->yMax; i++){
            for (int  j= 0; j < this->xMax; j++){
                mvwprintw(this->cwin, i, j, " ");
            }
        }
        wattroff(this->cwin, COLOR_PAIR(38));
        

        //Cornice
        int k, j;
        k = m+4;
        j = this->yMax;
        wattron(this->cwin, COLOR_PAIR(17));
        mvwprintw(this->cwin,2 ,k+5,     "    ");
        mvwprintw(this->cwin,2 ,k+145,  "    ");
        mvwprintw(this->cwin,3 ,k+5,     "    ");
        mvwprintw(this->cwin,3 ,k+145,  "    ");
        mvwprintw(this->cwin,6 ,k+1, "                                                                                                                                                        ");
        mvwprintw(this->cwin,5 ,k-1 , "                                                                                                                                                            ");
        mvwprintw(this->cwin,4 ,k-3,"                                                                                                                                                                ");
        mvwprintw(this->cwin,7 ,k+5,"     ");       
        mvwprintw(this->cwin,7 ,k+145,"    ");  
        mvwprintw(this->cwin,8 ,k+5,"     ");       
        mvwprintw(this->cwin,8 ,k+145,"    "); 
        mvwprintw(this->cwin,9 ,k+5,"     ");       
        mvwprintw(this->cwin,9 ,k+145,"    "); 
        mvwprintw(this->cwin,10,k+5,"     ");       
        mvwprintw(this->cwin,10,k+145,"    "); 
        mvwprintw(this->cwin,11,k+5,"     ");       
        mvwprintw(this->cwin,11,k+145,"    "); 
        mvwprintw(this->cwin,12,k+5,"     ");       
        mvwprintw(this->cwin,12,k+145,"    "); 
        mvwprintw(this->cwin,13,k+5,"     ");       
        mvwprintw(this->cwin,13,k+145,"    "); 
        mvwprintw(this->cwin,14,k+5,"     ");       
        mvwprintw(this->cwin,14,k+145,"    "); 
        mvwprintw(this->cwin,15,k+5,"     ");       
        mvwprintw(this->cwin,15,k+145,"    "); 
        mvwprintw(this->cwin,16,k+5,"     ");       
        mvwprintw(this->cwin,16,k+145,"    "); 
        mvwprintw(this->cwin,17,k+5,"     ");       
        mvwprintw(this->cwin,17,k+145,"    "); 
        mvwprintw(this->cwin,18,k+5,"     ");       
        mvwprintw(this->cwin,18,k+145,"    "); 
        mvwprintw(this->cwin,19,k+5,"     ");       
        mvwprintw(this->cwin,19,k+145,"    "); 
        mvwprintw(this->cwin,20,k+5,"     ");       
        mvwprintw(this->cwin,20,k+145,"    "); 
        mvwprintw(this->cwin,21,k+5,"     ");       
        mvwprintw(this->cwin,21,k+145,"    "); 
        mvwprintw(this->cwin,22,k+5,"     ");       
        mvwprintw(this->cwin,22,k+145,"    "); 
        mvwprintw(this->cwin,23,k+1,"                                                                                                                                                        ");
        mvwprintw(this->cwin,24,k-1,"                                                                                                                                                            ");
        mvwprintw(this->cwin,25,k-3,"                                                                                                                                                                ");
        mvwprintw(this->cwin,26,k+5,"     ");
        mvwprintw(this->cwin,26,k+145,"     ");
        mvwprintw(this->cwin,27,k+5,"     ");
        mvwprintw(this->cwin,27,k+145,"     ");
        wattroff(this->cwin, COLOR_PAIR(17));
        //Sfondo cornice
        wattron(this->cwin, COLOR_PAIR(35));
        mvwprintw(this->cwin,7 ,k+9,"                                                                                                                                        ");       
        mvwprintw(this->cwin,8 ,k+9,"                                                                                                                                        ");    
        mvwprintw(this->cwin,9 ,k+9,"                                                                                                                                        ");    
        mvwprintw(this->cwin,10,k+9,"                                                                                                                                        ");   
        mvwprintw(this->cwin,11,k+9,"                                                                                                                                        ");    
        mvwprintw(this->cwin,12,k+9,"                                                                                                                                        ");   
        mvwprintw(this->cwin,13,k+9,"                                                                                                                                        ");   
        mvwprintw(this->cwin,14,k+9,"                                                                                                                                        ");    
        mvwprintw(this->cwin,15,k+9,"                                                                                                                                        ");   
        mvwprintw(this->cwin,16,k+9,"                                                                                                                                        ");   
        mvwprintw(this->cwin,17,k+9,"                                                                                                                                        ");   
        mvwprintw(this->cwin,18,k+9,"                                                                                                                                        ");   
        mvwprintw(this->cwin,19,k+9,"                                                                                                                                        ");   
        mvwprintw(this->cwin,20,k+9,"                                                                                                                                        ");   
        mvwprintw(this->cwin,21,k+9,"                                                                                                                                        ");
        mvwprintw(this->cwin,22,k+9,"                                                                                                                                        ");   
        wattroff(this->cwin, COLOR_PAIR(35));

        //Keybord
        wattron(this->cwin, COLOR_PAIR(5));
        mvwprintw(this->cwin,n,m,   "                                                                                                                                                                ");
        mvwprintw(this->cwin,n+1,m, "        ________                                                                                                                                                ");  
        mvwprintw(this->cwin,n+2,m, "      [          ]  [    ]      [    ][    ][    ][    ]  [    ][    ][    ][    ]  [    ][    ][    ][    ]  [    ][    ][    ]  [    ][    ][    ][    ]      "); 
        mvwprintw(this->cwin,n+3,m, "      [ ________ ]  [____]      [____][____][____][____]  [____][____][____][____]  [____][____][____][____]  [____][____][____]  [____][____][____][____]      "); 
        mvwprintw(this->cwin,n+4,m, " 								                                                                                                 ");
        mvwprintw(this->cwin,n+5,m, " 									                            ________						         ");
        mvwprintw(this->cwin,n+6,m, "      [    ][    ]  [    ][    ][    ][    ][    ][    ][    ][    ][    ][    ][    ][    ][    ][        ]  [    ][    ][    ]  [    ][    ][    ][    ]      ");
        mvwprintw(this->cwin,n+7,m, "      [____][____]  [____][____][____][    ][____][____][____][____][____][____][    ][____][____][________]  [____][____][____]  [____][____][____][____]      ");
        mvwprintw(this->cwin,n+8,m, "      [    ][    ]  [        ][    ][    ][    ][    ][    ][    ][    ][    ][    ][    ][    ][    ][    |  [    ][    ][    ]  [    ][    ][    ][    |      "); 
        mvwprintw(this->cwin,n+9,m, "      [____][____]  [________][    ][    ][    ][____][____][____][____][____][____][____][____][____][    |  [____][____][____]  [____][____][____][    |      "); 
        mvwprintw(this->cwin,n+10,m,"      [    ][    ]  [          ][    ][    ][    ][    ][    ][    ][    ][    ][    ][    ][    ][    ][  |                      [    ][    ][    ][    |      "); 
        mvwprintw(this->cwin,n+11,m,"      [____][____]  [__________][____][____][____][____][____][____][____][____][____][____][____][____][__|                      [____][____][____][____|      "); 
        mvwprintw(this->cwin,n+12,m,"      [    ][    ]  [    ][    ][    ][    ][    ][    ][    ][    ][    ][    ][    ][    ][              ]        [    ]        [    ][    ][    ][    |      "); 
        mvwprintw(this->cwin,n+13,m,"      [____][____]  [____][____][____][    ][____][____][____][____][____][____][____][____][______________]        [____]        [____][____][____][    |      "); 
        mvwprintw(this->cwin,n+14,m,"      [    ][    ]  [        ][    ][        ][                                      ][        ][    ][    ]  [    ][    ][    ]  [          ][    ][    |      "); 
        mvwprintw(this->cwin,n+15,m,"      [____][____]  [________][____][________][______________________________________][________][____][____]  [____][____][____]  [__________][____][____|      "); 
        mvwprintw(this->cwin,n+16,m,"                  											                                                         "); 
        mvwprintw(this->cwin,n+17,m,"                                                                                                                                                                "); 
        wattroff(this->cwin, COLOR_PAIR(5));  

        int f = (((k+9)+136)/3);
        int g = (((k+9)+136)/(1.5));
	
        //w 
        wattron(this->cwin, A_BOLD);
        wattron(this->cwin, COLOR_PAIR(22));
        mvwprintw(this->cwin,n+6,m+32,"      ");
        mvwprintw(this->cwin,n+7,m+32,"      ");
        mvwprintw(this->cwin,10,f,"      ");   
        mvwprintw(this->cwin,11,f,"      ");
        wattroff(this->cwin, COLOR_PAIR(22));
        
        //S
        wattron(this->cwin, COLOR_PAIR(23));
        mvwprintw(this->cwin,n+8,m+36, "      ");
        mvwprintw(this->cwin,n+9,m+36, "      ");
        mvwprintw(this->cwin,14,f,"      ");    
        mvwprintw(this->cwin,15,f,"      ");
        wattroff(this->cwin, COLOR_PAIR(23));

        //a 
        wattron(this->cwin, COLOR_PAIR(24));
        mvwprintw(this->cwin,n+8,m+30, "      ");
        mvwprintw(this->cwin,n+9,m+30, "      ");
        mvwprintw(this->cwin,18,f,"      ");   
        mvwprintw(this->cwin,19,f,"      "); 
        wattroff(this->cwin, COLOR_PAIR(24));


        //d
        wattron(this->cwin, COLOR_PAIR(25));
        mvwprintw(this->cwin,n+8,m+42, "      ");
        mvwprintw(this->cwin,n+9,m+42, "      ");
        mvwprintw(this->cwin,10,g,"      ");   
        mvwprintw(this->cwin,11,g,"      ");
        wattroff(this->cwin, COLOR_PAIR(25));

        //p
        wattron(this->cwin, COLOR_PAIR(26));
        mvwprintw(this->cwin,n+6,m+80,"      ");
        mvwprintw(this->cwin,n+7,m+80,"      ");
        mvwprintw(this->cwin,14,g,"      ");    
        mvwprintw(this->cwin,15,g,"      ");
        wattroff(this->cwin, COLOR_PAIR(26));

        //x
        wattron(this->cwin, COLOR_PAIR(27));
        mvwprintw(this->cwin,n+12,m+38,"      ");
        mvwprintw(this->cwin,n+13,m+38,"      ");
        mvwprintw(this->cwin,18,g,"      ");   
        mvwprintw(this->cwin,19,g,"      "); 
        wattroff(this->cwin, COLOR_PAIR(27));
        wattroff(this->cwin, A_BOLD);

        //indicazioni di cosa sono i comandi
        wattron(this->cwin, COLOR_PAIR(34));
        mvwprintw(this->cwin,11,f+10,"per muoversi verso l'alto");
        mvwprintw(this->cwin,15,f+10,"per muoversi verso il basso");
        mvwprintw(this->cwin,19,f+10,"per muoversi verso sinistra"); 
        mvwprintw(this->cwin,11,g+10,"per muoversi verso destra");
        mvwprintw(this->cwin,15,g+10,"sparo del player");
        mvwprintw(this->cwin,19,g+10,"torna alla schermata home");
        wattroff(this->cwin, COLOR_PAIR(34));

    } else {
        //schermata crediti
        this->cwin = newwin(this->yMax, this->xMax, 0, 0);
        box(this->cwin, 0, 0);
        wrefresh(this->cwin);

        mvwprintw(this->cwin,3,5,"Credits to: ");
        mvwprintw(this->cwin,5,5,"Gabriel Betti               n.matricola: 0001028517");
        mvwprintw(this->cwin,7,5,"Giacomo Fornaciari          n.matricola: 0001031838");
    }
}

void credits::getchoice(){
    int choice = wgetch(this->cwin);
    if(choice=='x'){
        this->exit = true;
    }
}

#endif
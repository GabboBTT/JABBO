#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ncurses.h>
#include <iostream>
#include "player.h"
#include "mappa.h"
#include "menu.h"
#include "barra.h"
#include "miniatura.h"
#include "enemy.h"
#include "sparo.h"
#include "credits.h"
#include "sparopersonaggio.h"
#include "sparonemico.h"
using namespace std;

//Colori 
#define Platino 3
#define Tela 8


void vittoria(int &i, int &stat){            //casistica vittoria
    endwin();                                //chiude lo schermo
    i = 0;
    stat = 1;
}

void sconfitta(int &i, int &stat){          //casistica sconfitta
    endwin();                               //chiude lo schermo
    i = 0;
    stat = 2;
}

void ritirata(int &i, int &stat){           //casistica ritirata
    endwin();                               //chiude lo schermo
    i = 0;
    stat = 3;
}

int main(int argc, char *argv[]){
    //Colori
    start_color();
    double cambiocolore = 1000 / 255;
    init_color(Platino, 232*cambiocolore, 231*cambiocolore, 229*cambiocolore);
    init_color(Tela, 255*cambiocolore, 250*cambiocolore, 240*cambiocolore);     
    init_pair(1, COLOR_WHITE, Platino);                   
    init_pair(3, COLOR_BLACK, Platino);                   
    init_pair(4, Tela, Tela);                             
    

    //creazione menu iniziale

    int max = 10000;          //Per uscire dal programma 
    int i = 0;               //Per stare dentro al programma
    int s = 0;              //Per valutare se hai vinto, perso o ti sei ritirato
    do {
        if (i == 0){
            initscr();              //inizializza lo schermo
            noecho();               //i caratteri digitati non vengono scritti sullo schermo       
            cbreak();               //prende l'input senza l'uso dell'INVIO
            curs_set(0);            //rende il cursore invisibile
            Menu * menu = new Menu(s);
            while(menu->exit!=true){
                menu->getchoice();
            }
            endwin();
            if (menu->scelta==1){
                endwin();
                initscr();
                int points=10;           //punti player
                int lifes=points/10;     //vite player
                int nmappa = 1;          //numero mappa corrente
                int yMax, xMax;          //massime dimensioni schermo
                getmaxyx(stdscr, yMax, xMax);
                int choice;             //variabile che contiene l'input da tastiera
                do {
                WINDOW * win = newwin(yMax, xMax, 0, 0);
                nodelay(win, true);
                box(win, 0, 0);
                wrefresh(win);

                //creazione schermata
                Mappa * m = new Mappa(win, 60, 20, xMax-(xMax/4), yMax,nmappa);
                wrefresh(win);
                
                //Menu info play
                int yMm = 10;
                int xMm = xMax-20;
                WINDOW * mapwin = newwin(yMm, xMm, 5 , 10);
                box(mapwin, 0, 0);
                wrefresh(mapwin);
                mvwprintw(mapwin,4,12,"Points: %i                    Lifes: %i",points,lifes);   
                wrefresh(mapwin);

                //Colore cornice
                wattron(mapwin, COLOR_PAIR(17));
                for (int i = 0; i <= yMm; i++){
                    mvwprintw(mapwin,i,0," ");
                    mvwprintw(mapwin,i,xMm-1," ");
                }
                for (int j = 0; j <= xMm; j++){
                    mvwprintw(mapwin,0, j," ");
                    mvwprintw(mapwin,yMm-1, j," ");
                }
                wattroff(mapwin, COLOR_PAIR(17));
                wrefresh(mapwin);

                //Barra nel Menu
                barra * b = new barra(win, xMax-(xMax-(xMax/4))-3, (yMax/2)-2, xMax%4);

                //Miniatura nel menu
                miniatura *min = new miniatura(win, xMax-(xMax-(xMax/4))-3, (yMax/2)-2,nmappa, xMax%4);

                //creazione nemici
                int xx = xMax/4*3;
                int yy = yMax;
                enemy * e = new enemy(win, 60, 20, xx, yy, -1, -1); //nemico n.1

                enemy *e2 = new enemy(win, 60, 20,  xx, yy, e->x, -1);   //nemico n.2

                enemy *e3 = new enemy(win, 60, 20,  xx, yy, e->x, e2->x);    //nemico n.3
                
                //creazione player
                Player * p = new Player(win, 'P', points, m, e);

                //creazione sparo personaggio
                Sparopersonaggio *s = new Sparopersonaggio(win, p, e, e2, e3);
                

                //creazione spari nemici
                Sparonemico *se1 = new Sparonemico(win, p, e, e2, e3, 1);

                Sparonemico *se2 = new Sparonemico(win, p, e, e2, e3, 2);

                Sparonemico *se3 = new Sparonemico(win, p, e, e2, e3, 3);

                int countsparo = 0;
                bool aumentovite = false;
                bool diminuzionevite = false;
                int countcambiovite = 0;

                //movimenti gioco
                do { 
                    countsparo++;
                    choice = p->getmv();
                    if(choice=='p'){
                        s->insert();           //inserisce in lista sparo personaggio quando viene cliccato tasto p
                    }
                    s->movimento();        //muove lo sparo del personaggio
                    s->movimento();        //muove lo sparo del personaggio
                    e->movimento();

                    if(countsparo%40==0){               //se nemico è attivo allora ogni 40 giri (ogni 2s) di while crea due spari, uno in alto e uno in basso
                        se1->insert();                              //inserisce in lista nuovo sparo
                    }

                    se1->movimento();               //muove sparo nemico n.1
                    
                    if(nmappa>3){                                    //se il numero della mappa è maggiore di 3 crea un secondo nemico
                        e2->movimento();
                        if(countsparo%40==0){                        //crea spari secondo nemico
                        se2->insert();                               //inserisce in lista nuovo sparo
                        }

                    se2->movimento();               //muove sparo nemico n.2
                        
                    } else
                        e2->num = 0;
                    if(nmappa>6){                                   //se il numero della mappa è maggiore di 6 crea un terzo nemico
                        e3->movimento();
                        if(countsparo%40==0){                       //crea spari terzo nemico
                        se3->insert();                              //inserisce in lista nuovo sparo
                        }

                    se3->movimento();               //muove sparo nemico n.3
                        
                    } else
                        e3->num = 0;
                    wtimeout(win, 50);                            //timeout di 500 millisecondi
                    wtimeout(mapwin, 100);                            //timeout di 500 millisecondi
                    s->display();                   //stampa sparo player
                    e->display();                   //stampa nemico n.1
                    if(nmappa>3)
                        e2->display();              //stampa nemico n.2
                    if(nmappa>6) 
                        e3->display();              //stampa nemico n.3

                    se1->display();                 //stampa spari nemico n.1
                    se2->display();                 //stampa spari nemico n.2
                    se3->display();                 //stampa spari nemico n.3

                    p->display();                   //stampa player
                    wrefresh(win);
                    wrefresh(mapwin);
                    if((e->colpito)||(e2->colpito)||(e3->colpito)){   //se il personaggio viene colpito dai nemici o si scontra allora gli viene tolta tutta la vita
                        p->modificavite(-p->vite());
                    }
                    if(p->vite()!=lifes){                             //se sono cambiate il numero di vite del personaggio allora vengono aggiornate a schermo
                        if(p->vite()>lifes){
                            aumentovite=true;
                            mvwprintw(mapwin, 6, 42, "+1 Life");
                        } else {
                            diminuzionevite=true;
                            mvwprintw(mapwin, 6, 42, "-1 Life");
                        }
                        countcambiovite=0;
                        lifes = p->vite();
                        points = lifes * 10;
                        mvwprintw(mapwin,4,12,"Points: %i                    Lifes: %i",points,lifes);
                        }
                    if(aumentovite==true){
                        countcambiovite = countcambiovite+1;
                        if(countcambiovite==12){                    //fa 12 giri del ciclo prima di far scomparire la scritta "+1 Life"
                        mvwprintw(mapwin, 6, 42, "       ");
                        wrefresh(mapwin);
                        aumentovite=false;
                        countcambiovite=0;
                        }
                    }
                    if(diminuzionevite==true){
                        countcambiovite=countcambiovite+1;
                        if(countcambiovite==12){                    //fa 12 giri del ciclo prima di far scomparire la scritta "-1 Life"
                        mvwprintw(mapwin, 6, 42, "       ");
                        wrefresh(mapwin);
                        diminuzionevite=false;
                        countcambiovite=0;
                        }
                    }
                } while((m->n==nmappa)&&(lifes>0)&&(choice!='x'));   //continua finchè non si passa alla mappa successiva o il personaggio perde tutte le vite o viene cliccato il tasto x
                    nmappa = m->n;  
                } while((nmappa!=9)&&(lifes>0)&&(choice!='x'));      //continua finchè non si arriva alla mappa finale (n.9) o il personaggio perde tutte le vite o viene cliccato il tasto x
                if(nmappa==9){
                vittoria(i, s);
                } else if(lifes<1){
                sconfitta(i, s);
                } else {
                ritirata(i, s);
                }
            } else if(menu->scelta==2){                              //entra nella finestra relativa ai tasti di gioco
                endwin();
                initscr();
                noecho();
                cbreak();
                credits *cr= new credits(2);                        //crea schermata con i tasti di gioco
                while(cr->exit!=true){
                    cr->getchoice();
                }
                i = 0;
                endwin();
            } else if(menu->scelta==3){                             //entra nella finestra dei crediti
                endwin();
                initscr();
                noecho();
                cbreak();
                credits *cr= new credits(3);                        //crea schermata con i crediti del gioco
                while(cr->exit!=true){
                    cr->getchoice();
                }
                i = 0;
            } else if(menu->scelta==4){                             //esce dal gioco e torna al terminale
                endwin();
                i = max;
            }
        }
    }
 while (i != max);                                                  //ripete il ciclo per ricominciare il gioco senza dover far ripartire il main
 return 0;
 } 
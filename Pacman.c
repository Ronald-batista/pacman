#include <stdlib.h>
#include <curses.h> 
#include <stdio.h>
#include "Biblioteca.h"


#define DIREITA 1
#define BAIXO 2
#define ESQUERDA 3
#define CIMA 4

/*status*/
#define PERSEGUIR 0
#define FUGIR 1


int main(){
    struct heroi{
        int PosLIN;
        int PosCOL;
        int Direcao; };
    struct heroi pacman;
        pacman.PosLIN = 2;
        pacman.PosCOL = 2; 
        pacman.Direcao = 1;

    struct fantasma {
        int PosL;
        int PosC;
        int Status; /* 0 para perseguir, 1 para fugir */  };
    struct fantasma Blinky;
        Blinky.PosL = 15;
        Blinky.PosC = 15;
        Blinky.Status = PERSEGUIR;
    struct fantasma Pinky;
        Pinky.PosL = 20;
        Pinky.PosC = 20;
        Pinky.Status = PERSEGUIR;
    struct fantasma Inky;
        Inky.PosL = 25;
        Inky.PosC = 40;
        Inky.Status = PERSEGUIR;
    struct fantasma Clyde;
        Clyde.PosL = 15;
        Clyde.PosC = 65;
        Clyde.Status = PERSEGUIR;
    int altura, largura;
    char **mapa;
    int key;
    float delay = 3;
    int pontos = 0;
    int vida = 1;
    char padrao;
    int fase = 1;

    IniciarNcurses();
    manual();
    clear();
    fase: MapaConfig(&altura, &largura); /* local onde a fase reinicia ( goto ) */
    mapa = ConstruirMapa(&altura, &largura);
    ConstruirObstaculos(mapa);
    Pastilhas(mapa);
    AdicionarPacman(mapa, &pacman.PosLIN, &pacman.PosCOL );
    if (fase > 1){
        mvprintw(13,30,"Voce avançou de fase, esta eh a fase: %d \n", fase);
    }
    mvprintw(15,30,"PRESSIONE UMA TECLA PARA INICIAR O JOGO");
    halfdelay(30);
    getch();

     do {
        clear();  
        MostrarMapa(mapa,&altura, &largura, &pontos, &vida);
        MoverPacman(mapa,&pacman.Direcao, &pacman.PosLIN, &pacman.PosCOL, &pontos, &vida, &Blinky.Status, &Pinky.Status, &Inky.Status, &Clyde.Status );
        clear();  
        if (Blinky.Status == FUGIR){ /* se um dos fantasmas esta no status FUGIR, entao, todos estao. */
            padrao = '@';
            Fugir(mapa, &Blinky.PosL, &Blinky.PosC, &Blinky.Status, padrao);
            padrao = '&';
            Fugir(mapa, &Pinky.PosL, &Pinky.PosC, &Pinky.Status, padrao); 
            padrao = '%';
            Fugir(mapa, &Inky.PosL, &Inky.PosC, &Inky.Status, padrao); 
            padrao = '?';
            Fugir(mapa, &Clyde.PosL, &Clyde.PosC, &Clyde.Status, padrao);

        } else{ /* executa o movimento caracteristico de cada fantasma */
            MoverBlinky(mapa, &Blinky.PosL, &Blinky.PosC,&pacman.PosLIN, &pacman.PosCOL);
            MoverPinky(mapa, &Pinky.PosL, &Pinky.PosC,pacman.PosLIN, pacman.PosCOL, pacman.Direcao);
            MoverInky(mapa, Blinky.PosL, Blinky.PosC, pacman.PosLIN, pacman.PosCOL, &Inky.PosL, &Inky.PosC);
            MoverClyde(mapa, &Clyde.PosL, &Clyde.PosC, &pacman.PosLIN, &pacman.PosCOL);
        }
      
        MostrarMapa(mapa, &altura, &largura, &pontos, &vida);

        /* verificar se o usuario mudou a direção do pacman */
        halfdelay (delay);
        key = getch();
        if ( key == 258 || key == 259 || key == 260 || key == 261  ){ /* Valores das setas do teclado na tabela ASCII */
            MudarDirecaoPacman(&pacman.Direcao,key);
            MoverPacman(mapa,&pacman.Direcao, &pacman.PosLIN, &pacman.PosCOL, &pontos, &vida, &Blinky.Status, &Pinky.Status, &Inky.Status, &Clyde.Status);
        }
 
        
        clear();    
        MostrarMapa(mapa,&altura, &largura, &pontos, &vida);

        if (pontos >= 49){
             vida = 0;
        } 

    
    }  while (vida > 0); /* condicao de parada */
    

    /* Altera a velocidade de jogo quando o usuario passa de fase */
    if (pontos >= 49){
        delay = delay - (delay * 0.1); 
        pontos = 0;
        vida = 1;
        fase++;
        clear();
        goto fase;
    }

    getch();
    endwin(); /* finaliza ncurses */



    return 0;
}   





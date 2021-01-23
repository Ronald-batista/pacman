#include <stdlib.h>
#include <curses.h> 
#include <stdio.h>


#define DIREITA 1
#define BAIXO 2
#define ESQUERDA 3
#define CIMA 4

#define PERSEGUIR 0
#define FUGIR 1


void IniciarNcurses(){
    initscr();
    /* parametros de inicialização da tela*/ 
    cbreak(); /*  buffer de linha desabilitado.*/ 
    noecho(); /* não da echo() quando usa o getch(). */ 
    keypad(stdscr, TRUE); /* Habilita teclas especiais do teclado (F1,F2, setas, etc).  */ 
    start_color();  /* habilita uso de cores */
    init_color(COLOR_RED, 700, 0, 0);
    init_color(COLOR_MAGENTA, 550, 0, 400);
    init_pair(1, COLOR_BLACK, COLOR_YELLOW); 
    init_pair(2, COLOR_CYAN , COLOR_CYAN);
    init_pair(3, COLOR_WHITE, COLOR_WHITE);
    init_pair(4, COLOR_GREEN , COLOR_GREEN );
    init_pair(5, COLOR_RED, COLOR_RED);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA , COLOR_MAGENTA );
    init_pair(8, COLOR_BLUE , COLOR_BLUE );
    init_pair(9, COLOR_YELLOW , COLOR_YELLOW );


    /* usados nas intrucoes do jogo */
    init_pair(10,COLOR_RED, COLOR_BLACK);
    init_pair(11,COLOR_MAGENTA, COLOR_BLACK);
    init_pair(12,COLOR_BLUE, COLOR_BLACK);
    init_pair(13,COLOR_YELLOW, COLOR_BLACK);

}

void manual(){
    attron(A_BOLD);
    mvprintw(5,5, "INSTRUCOES DO JOGO\n");
    attroff(A_BOLD);
    mvprintw(6,5, "Utilize as setas do teclado para se movimentar. \n");
    mvprintw(7,5, "Cada fase contem 30 pastilhas simples (valem 1 ponto) e 10 pastilhas especiais (Valem 2 pontos). Voce passa de fase ao pegar todos os pontos. \n");
    mvprintw(8,5, "Ao passar de fase a velocidade de movimento do pacman e dos fantasmas aumentam 10% \n");
    mvprintw(9,5, "Ao pegar um ponto especial os fantasmas executam um movimento aleatório. Voce tem somente 1 vida para completar cada fase. \n");
    mvprintw(10,5, "Existem 4 fantasmas que cada um realiza um tipo diferente de movimento, descritos abaixo: \n");
    attron(COLOR_PAIR(10)); 
    mvprintw(11,5, "          BLINK: vai diretamente atrás do Pac-Man. \n");
    attroff(COLOR_PAIR(10));
    attron(COLOR_PAIR(11)); 
    mvprintw(12,5, "          PINKY: Mira seu movimento 5 pontos na frente da posição atual do Pac-Man. \n");
    attroff(COLOR_PAIR(11));
    attron(COLOR_PAIR(12)); 
    mvprintw(13,5, "          INKY:  Mira na média (o meio) entre a posição do Pac-Man e do Blinky \n");
    attroff(COLOR_PAIR(12));
    attron(COLOR_PAIR(13)); 
    mvprintw(14,5, "          CLYDE: Movimenta-se aleatoriamente, a menos que o pacman esteja a 15 pontos de distancia, quando ele vai diretamente atras dele \n");
    attroff(COLOR_PAIR(13));
    halfdelay(120);
    getch();
}

void MapaConfig(int *altura, int *largura){
    *altura = 30;
    *largura = 80;
}

char **ConstruirMapa(int *altura, int *largura){
     /*   printw("\n%d\n", *altura);
        printw("\n%d\n", &altura);
        printw("\n%d\n", altura);*/
          int i, j;
          char **map;
       map = (char**) malloc(*altura *sizeof(char*));        /**/
      
       for(i = 0; i < *altura; i++)
       {
           map[i] = (char*) malloc(*largura *sizeof(char));  /**/
           for(j = 0; j < *largura; j++)
           {
             
               /*Preenchendo o mapa*/
               if( i==0 || j == (*largura-1)|| j == 0 || (i == (*altura-1)) ){
                   
                    map[i][j] = '#';
                
               }else
               {
                   map[i][j] = ' ';
               }
            }  
       }
        return map;
	}

void ConstruirObstaculos(char **mapa){

    int i,j;
/* 1º OBSTACULO */
    mapa[8][4] = '#';
    mapa[9][4] = '#';
    mapa[10][4] = '#';  
    mapa[11][4] = '#';
    mapa[12][4] = '#';

    mapa[18][4] = '#';
    mapa[19][4] = '#';  
    mapa[20][4] = '#';
    mapa[21][4] = '#';
    mapa[22][4] = '#'; 
 
    mapa[18][13] = '#';
    mapa[19][13] = '#';  
    mapa[20][13] = '#';
    mapa[21][13] = '#';
    mapa[22][13] = '#'; 
    mapa[23][13] = '#'; 

    mapa[8][4] = '#';
    mapa[8][5] = '#';
    mapa[8][6] = '#';  
    mapa[8][7] = '#';
    mapa[8][8] = '#';
    mapa[8][9] = '#'; 
    mapa[8][10] = '#'; 
    mapa[8][11] = '#'; 

    mapa[8][13] = '#';
    mapa[9][13] = '#';
    mapa[10][13] = '#';  
    mapa[11][13] = '#';
    mapa[12][13] = '#';
    mapa[13][13] = '#';

    mapa[23][10] = '#';
    mapa[23][11] = '#'; 

    mapa[23][4] = '#';
    mapa[23][5] = '#';
    mapa[23][6] = '#';

    mapa[8][12] = '#';
    mapa[23][12] = '#';

    /*---------------------*/

    /* 2º OBSTACULO */
    mapa[22][17]= '#';
    mapa[23][17]= '#';
    mapa[24][17]= '#';
   

    mapa[22][18]= '#';
    mapa[22][19]= '#';
    mapa[22][20]= '#';
    mapa[22][21]= '#';
    mapa[22][22]= '#';
    mapa[22][23]= '#';

    mapa[16][23]= '#';
    mapa[17][23]= '#';
    mapa[18][23]= '#';
    mapa[19][23]= '#';
    mapa[20][23]= '#';
    mapa[21][23]= '#';

    mapa[16][27] = '#';
    mapa[17][27] = '#';
    mapa[18][27] = '#';  
    mapa[19][27] = '#';
    mapa[20][27] = '#';
    mapa[21][27] = '#'; 
    mapa[22][27] = '#'; 
    mapa[23][27] = '#'; 
    mapa[24][27] = '#';
    mapa[25][27] = '#';
    mapa[26][27] = '#'; 
    mapa[27][27] = '#'; 
    mapa[28][27] = '#'; 

    /*---------------------*/

    /* 3º OBSTACULO */
    mapa[5][28] = '#';
    mapa[5][29] = '#';
    mapa[5][30] = '#';  
    mapa[5][31] = '#';
    mapa[5][32] = '#';
    mapa[5][33] = '#'; 
    mapa[5][34] = '#'; 
    mapa[5][35] = '#'; 

    mapa[9][28] = '#';
    mapa[9][29] = '#';
    mapa[9][30] = '#';  
    mapa[9][31] = '#';
    mapa[9][32] = '#';
    mapa[9][33] = '#'; 
    mapa[9][34] = '#'; 
    mapa[9][35] = '#'; 

    mapa[13][32] = '#';
    mapa[13][33] = '#';
    mapa[13][34] = '#';  
    mapa[13][35] = '#';
    mapa[13][36] = '#';
    mapa[13][37] = '#'; 
    mapa[13][38] = '#'; 
    mapa[13][39] = '#'; 

    mapa[17][32] = '#';
    mapa[17][33] = '#';
    mapa[17][34] = '#';  
    mapa[17][35] = '#';
    mapa[17][36] = '#';
    mapa[17][37] = '#'; 
    mapa[17][38] = '#'; 
    mapa[17][39] = '#'; 
  /*---------------------*/

    /* 4º OBSTACULO */
    mapa[6][43] = '#';
    mapa[7][43] = '#';  
    mapa[8][43] = '#';
    mapa[9][43] = '#';
    mapa[10][43] = '#'; 
    mapa[11][43] = '#'; 
    /*mapa[12][43] = '#';*/

    mapa[6][44] = '#';
    mapa[6][45] = '#';
    mapa[6][46] = '#';

    mapa[6][47] = '#';
    mapa[7][47] = '#';  
    mapa[8][47] = '#';
    mapa[9][47] = '#';
    mapa[10][47] = '#'; 
    mapa[11][47] = '#'; 
    /*mapa[12][47] = '#';*/

    mapa[16][43] = '#';
    mapa[17][43] = '#';  
    mapa[18][43] = '#';
    mapa[19][43] = '#';
    mapa[20][43] = '#'; 
    mapa[21][43] = '#'; 
    mapa[22][43] = '#';

    mapa[22][44] = '#';
    mapa[22][45] = '#';
    mapa[22][46] = '#';

    mapa[16][47] = '#';
    mapa[17][47] = '#';  
    mapa[18][47] = '#';
    mapa[19][47] = '#';
    mapa[20][47] = '#'; 
    mapa[21][47] = '#'; 
    mapa[22][47] = '#';

    /*---------------------*/

    /* 5º OBSTACULO */
    mapa[10][52] = '#';
    mapa[11][52] = '#';  
    mapa[12][52] = '#';
    /*mapa[13][52] = '#';*/

    mapa[17][52] = '#'; 
    mapa[18][52] = '#'; 
    mapa[19][52] = '#';
    mapa[20][52] = '#';

    mapa[10][57] = '#';
    mapa[11][57] = '#';  
    mapa[12][57] = '#';
    mapa[13][57] = '#';
    mapa[14][57] = '#';
    mapa[15][57] = '#';
    mapa[16][57] = '#';
    mapa[17][57] = '#'; 
    mapa[18][57] = '#'; 
    mapa[19][57] = '#';
    mapa[20][57] = '#';

    mapa[10][53] = '#';
    mapa[10][54] = '#';  
    mapa[10][55] = '#';
    mapa[10][56] = '#';

    mapa[20][53] = '#';
    mapa[20][54] = '#';  
    mapa[20][55] = '#';
    mapa[20][56] = '#';
    /*---------------------*/

    /* 6º OBSTACULO */
   
    mapa[24][65] = '#';  
    mapa[23][66] = '#';
    mapa[22][67] = '#';
    mapa[21][68] = '#';
    mapa[20][69] = '#';  

    mapa[28][67] = '#';
    mapa[28][68] = '#';  
    mapa[28][69] = '#';
    mapa[28][70] = '#';
    mapa[28][71] = '#';
    mapa[28][72] = '#';
    mapa[28][73] = '#';
    mapa[28][74] = '#';

     mapa[14][74] = '#';
     mapa[15][74] = '#';
     mapa[16][74] = '#';
     mapa[17][74] = '#';
     mapa[18][74] = '#';
     mapa[19][74] = '#';
     mapa[20][74] = '#';
     mapa[21][74] = '#';
     mapa[22][74] = '#';
     mapa[23][74] = '#';
     mapa[24][74] = '#';
     mapa[25][74] = '#';
     mapa[26][74] = '#';
     mapa[27][74] = '#';
     
     /* 7º obstaculo */
     for (i=28; i<=28; i++)
        for (j=1; j<+79; j++){
            mapa[i][j]='#';
        }
        
}

void Pastilhas (char **mapa){
    int contador,lin,col;
    contador = 0;

    /* Gerando pastilhas simples em posições aleatórias */
    while (contador < 30){
        lin = rand() %(30);
        col = rand() %(80);
        if (mapa[lin][col] == ' '){
            mapa[lin][col] = '*';
            contador++;
        }
    }

    contador = 0;

    /* Gerando pastilhas especias em posições aleatórias */
    while (contador < 10){
        lin = rand() %(30);
        col = rand() %(80);
        if ((mapa[lin][col] == ' ') && (mapa[lin+1][col] == ' ') && (mapa[lin][col+1] == ' ') && (mapa[lin+1][col+1] == ' ')){
            mapa[lin][col] = '$';
            mapa[lin+1][col] = '$';
            mapa[lin][col+1] = '$';
            mapa[lin+1][col+1] = '$';
            contador++;
        } 
    }
}

void AdicionarPacman(char **mapa, int *PosLIN_Pac,int *PosCOL_Pac ){
    int i,j;
    for (i=*PosLIN_Pac; i <= *PosLIN_Pac + 2; i++){
        for (j=*PosCOL_Pac; j <= *PosCOL_Pac+ 2; j++){
            mapa[i][j] = '>';
        }
    }
}

void MostrarMapa(char **mapa, int *altura, int *largura, int *pontos, int *vida ){
    int i, j;

    for(i = 0; i < *altura; i++){  
           
            for(j = 0; j < *largura; j++)
           {
            /* cada simbolo representa um tipo de personagem, e cada personagem deve ter um par de cor diferente */
               if (mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == '^' || mapa[i][j] == 'v' ){ 
                    addch(mapa[i][j] | COLOR_PAIR(1));
               }else if(mapa[i][j] == '*'){
                    addch(mapa[i][j] | COLOR_PAIR(2));
               }else if (mapa[i][j] == '#' ){
                    addch(mapa[i][j] | COLOR_PAIR(3));
               }else if (mapa[i][j] == '$'){
                   addch(mapa[i][j] | COLOR_PAIR(4));
               }else if (mapa[i][j] == '@'){
                   addch(mapa[i][j] | COLOR_PAIR(5));
               }else if (mapa[i][j] == '&'){
                   addch(mapa[i][j] | COLOR_PAIR(7));
               }else if (mapa[i][j] == '%'){
                   addch(mapa[i][j] | COLOR_PAIR(8));
               }else if (mapa[i][j] == '?'){
                   addch(mapa[i][j] | COLOR_PAIR(9));
               }else{
                   addch(mapa[i][j] | COLOR_PAIR(6));
               }

            }
             printw("\n");
        }
    printw("PONTOS: %d\n",*pontos);
    printw("VIDA: %d\n",*vida);
}

void MoverPacman(char **mapa, int *pacman_Direcao, int *pacman_PosLIN, int *PosCOL_Pac, int *pontos, int *vida, int *Blinky_Status, int *Pinky_Status, int *Inky_Status, int *Clyde_Status){
    int i,j;
    int aux = 0;
    switch(*pacman_Direcao){       
        case 1:  /* Movimento para a direita */
 
            /* limpando restos em arestas */
            for (i=*pacman_PosLIN-1; i <= *pacman_PosLIN-1; i++ )
                for (j=*PosCOL_Pac-1; j <= *PosCOL_Pac + 4; j++){
                    if (mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == '^' || mapa[i][j] == 'v' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*pacman_PosLIN-1; i <= *pacman_PosLIN+4; i++ )
                for (j=*PosCOL_Pac-1; j <= *PosCOL_Pac -1; j++){
                    if (mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == '^' || mapa[i][j] == 'v' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*pacman_PosLIN-1; i <= *pacman_PosLIN+4; i++ )
                for (j=*PosCOL_Pac+3; j <= *PosCOL_Pac +3; j++){
                    if (mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == '^' || mapa[i][j] == 'v' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*pacman_PosLIN+3; i <= *pacman_PosLIN+3; i++ )
                for (j=*PosCOL_Pac-1; j <= *PosCOL_Pac +3; j++){
                    if (mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == '^' || mapa[i][j] == 'v' ){
                        mapa[i][j]=' ';
                    }
                }
            aux = 0;
            
             /* verificar encostou em um fantasma */
            if(mapa[*pacman_PosLIN][*PosCOL_Pac+3] == '@' || mapa[*pacman_PosLIN][*PosCOL_Pac+3] == '&' || mapa[*pacman_PosLIN][*PosCOL_Pac+3] == '%' || mapa[*pacman_PosLIN][*PosCOL_Pac+3] == '?' || mapa[*pacman_PosLIN+1][*PosCOL_Pac+3] == '@' || mapa[*pacman_PosLIN+1][*PosCOL_Pac+3] == '&' || mapa[*pacman_PosLIN+1][*PosCOL_Pac+3] == '%' || mapa[*pacman_PosLIN+1][*PosCOL_Pac+3] == '?' || mapa[*pacman_PosLIN+2][*PosCOL_Pac+3] == '@'|| mapa[*pacman_PosLIN+2][*PosCOL_Pac+3] == '&' || mapa[*pacman_PosLIN+2][*PosCOL_Pac+3] == '%' || mapa[*pacman_PosLIN+2][*PosCOL_Pac+3] == '?')
                *vida = 0;

             /* verificar se possui parede */
            if(mapa[*pacman_PosLIN][*PosCOL_Pac+3] == '#' || mapa[*pacman_PosLIN+1][*PosCOL_Pac+3] == '#' || mapa[*pacman_PosLIN+2][*PosCOL_Pac+3] == '#')
                break;
            /* verificar se possui ponto simples */
            if(mapa[*pacman_PosLIN][*PosCOL_Pac+3] == '*' || mapa[*pacman_PosLIN+1][*PosCOL_Pac+3] == '*' || mapa[*pacman_PosLIN+2][*PosCOL_Pac+3] == '*'){
                
                for (i = *pacman_PosLIN; i <= *pacman_PosLIN+2; i++)
                for (j = *PosCOL_Pac+3; j <= *PosCOL_Pac + 3; j++ ){
                    if(mapa[i][j] == '*' ){
                        *pontos = *pontos + 1;
                        mapa[i][j]=' ';
                    }     
                }
            }
            /* verificar se possui pontos especiais */
             if(mapa[*pacman_PosLIN][*PosCOL_Pac+3] == '$' || mapa[*pacman_PosLIN+1][*PosCOL_Pac+3] == '$' || mapa[*pacman_PosLIN+2][*PosCOL_Pac+3] == '$'){
                for (i = *pacman_PosLIN; i <= *pacman_PosLIN+2; i++)
                for (j = *PosCOL_Pac+3; j <= *PosCOL_Pac + 3; j++ ){
                    if (mapa[i][j] =='$'){
                        *pontos= *pontos +2;
                        *Blinky_Status = FUGIR; /* FUGIR = 1; */
                        *Pinky_Status = FUGIR; /* FUGIR = 1; */
                        *Inky_Status = FUGIR; /* FUGIR = 1; */
                        *Clyde_Status = FUGIR; /* FUGIR = 1; */
                        mapa[i][j] = ' ';
                        mapa[i][j+1] = ' ';
                        if (mapa[i-1][j] == '$'){
                            mapa[i-1][j] = ' ';
                            mapa[i-1][j+1] = ' ';
                        }
                        else if (mapa[i+1][j] == '$'){
                            mapa[i+1][j] = ' ';
                            mapa[i+1][j+1] = ' ';

                        }
                    }
                }
            }
            /* movimento */
            if (mapa[*pacman_PosLIN][*PosCOL_Pac+3] == ' ' && mapa[*pacman_PosLIN+1][*PosCOL_Pac+3] == ' ' && mapa[*pacman_PosLIN+2][*PosCOL_Pac+3] == ' '){
                /* remover os mais atras */
                for (i = *pacman_PosLIN; i <= *pacman_PosLIN+2; i++)
                for (j = *PosCOL_Pac; j <= *PosCOL_Pac; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar a direita */
                for (i = *pacman_PosLIN; i <= *pacman_PosLIN+2; i++)
                for (j = *PosCOL_Pac+1; j <= *PosCOL_Pac + 3; j++ ){
                    mapa[i][j]='>';
                    aux = 1;
                }
            }
            

            if (aux == 1){
                *PosCOL_Pac= *PosCOL_Pac +1;
                aux = 0;
            }
            break;



        case 2:  /* Movimento para baixo */
            /* limpando restos em arestas */
            for (i=*pacman_PosLIN-1; i <= *pacman_PosLIN-1; i++ )
                for (j=*PosCOL_Pac-1; j <= *PosCOL_Pac + 4; j++){
                    if (mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == '^' || mapa[i][j] == 'v' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*pacman_PosLIN-1; i <= *pacman_PosLIN+4; i++ )
                for (j=*PosCOL_Pac-1; j <= *PosCOL_Pac -1; j++){
                    if (mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == '^' || mapa[i][j] == 'v' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*pacman_PosLIN-1; i <= *pacman_PosLIN+4; i++ )
                for (j=*PosCOL_Pac+3; j <= *PosCOL_Pac +3; j++){
                    if (mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == '^' || mapa[i][j] == 'v' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*pacman_PosLIN+3; i <= *pacman_PosLIN+3; i++ )
                for (j=*PosCOL_Pac-1; j <= *PosCOL_Pac +3; j++){
                    if (mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == '^' || mapa[i][j] == 'v' ){
                        mapa[i][j]=' ';
                    }
                }

            aux = 0;

              /* verificar se encostou em um fantasma */
            if(mapa[*pacman_PosLIN+3][*PosCOL_Pac] == '@' || mapa[*pacman_PosLIN+3][*PosCOL_Pac] == '&' || mapa[*pacman_PosLIN+3][*PosCOL_Pac] == '%' || mapa[*pacman_PosLIN+3][*PosCOL_Pac] == '?' || mapa[*pacman_PosLIN+3][*PosCOL_Pac+1] == '@' || mapa[*pacman_PosLIN+3][*PosCOL_Pac+1] == '&' || mapa[*pacman_PosLIN+3][*PosCOL_Pac+1] == '%' || mapa[*pacman_PosLIN+3][*PosCOL_Pac+1] == '?' ||  mapa[*pacman_PosLIN+3][*PosCOL_Pac+2] == '@' ||  mapa[*pacman_PosLIN+3][*PosCOL_Pac+2] == '&' ||  mapa[*pacman_PosLIN+3][*PosCOL_Pac+2] == '%' ||  mapa[*pacman_PosLIN+3][*PosCOL_Pac+2] == '?'){
                     *vida = 0;
            }
             /* verificar se possui parede */
            if(mapa[*pacman_PosLIN+3][*PosCOL_Pac] == '#' || mapa[*pacman_PosLIN+3][*PosCOL_Pac+1] == '#' || mapa[*pacman_PosLIN+3][*PosCOL_Pac+2] == '#')
                break;
            /* verificar se possui ponto simples */
            if(mapa[*pacman_PosLIN+3][*PosCOL_Pac] == '*' || mapa[*pacman_PosLIN+3][*PosCOL_Pac+1] == '*' || mapa[*pacman_PosLIN+3][*PosCOL_Pac+2] == '*'){
                for (i = *pacman_PosLIN+3; i <= *pacman_PosLIN+3; i++)
                for (j = *PosCOL_Pac; j <= *PosCOL_Pac + 2; j++ ){
                    if(mapa[i][j] == '*' ){
                        *pontos = *pontos + 1;
                        mapa[i][j]=' ';
                    }                    
                }
            }
            /* verificar se possui pontos especiais */
             if(mapa[*pacman_PosLIN+3][*PosCOL_Pac] == '$' || mapa[*pacman_PosLIN+3][*PosCOL_Pac+1] == '$' || mapa[*pacman_PosLIN+3][*PosCOL_Pac+2] == '$'){
                 
                 for (i = *pacman_PosLIN+3; i <= *pacman_PosLIN+3; i++)
                 for (j = *PosCOL_Pac; j <= *PosCOL_Pac + 2; j++ ){
                    if (mapa[i][j] =='$'){
                        *pontos= *pontos +2;
                        *Blinky_Status = FUGIR; /* FUGIR = 1; */
                        *Pinky_Status = FUGIR; /* FUGIR = 1; */
                        *Inky_Status = FUGIR; /* FUGIR = 1; */
                        *Clyde_Status = FUGIR; /* FUGIR = 1; */
                        mapa[i][j] = ' ';
                        mapa[i+1][j] = ' ';
                        if (mapa[i][j-1] == '$'){
                            mapa[i][j-1] = ' ';
                            mapa[i+1][j-1] = ' ';
                        }
                        else if (mapa[i][j+1] == '$'){
                            mapa[i][j+1] = ' ';
                            mapa[i+1][j+1] = ' ';

                        }
                    }
                }
            }
             /* movimento */
            if (mapa[*pacman_PosLIN+3][*PosCOL_Pac] == ' ' && mapa[*pacman_PosLIN+3][*PosCOL_Pac+1] == ' ' && mapa[*pacman_PosLIN+3][*PosCOL_Pac+2] == ' '){
                /* remover os mais acima */
                for (i = *pacman_PosLIN; i <= *pacman_PosLIN; i++)
                for (j = *PosCOL_Pac; j <= *PosCOL_Pac + 2; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar nos abaixo */
                for (i = *pacman_PosLIN+1; i <= *pacman_PosLIN+3; i++)
                for (j = *PosCOL_Pac; j <= *PosCOL_Pac + 2; j++ ){
                    mapa[i][j]='v';
                    aux = 1;
                }
            }
            
            if (aux == 1){
                *pacman_PosLIN= *pacman_PosLIN +1;
                aux = 0;
            }
            break;



        case 3: /* Movimento para ESQUERDA */

            /* limpando restos em arestas */
            for (i=*pacman_PosLIN-1; i <= *pacman_PosLIN-1; i++ )
                for (j=*PosCOL_Pac-1; j <= *PosCOL_Pac + 3; j++){
                    if (mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == '^' || mapa[i][j] == 'v' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*pacman_PosLIN-1; i <= *pacman_PosLIN+3; i++ )
                for (j=*PosCOL_Pac-1; j <= *PosCOL_Pac -1; j++){
                    if (mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == '^' || mapa[i][j] == 'v' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*pacman_PosLIN-1; i <= *pacman_PosLIN+3; i++ )
                for (j=*PosCOL_Pac+3; j <= *PosCOL_Pac +3; j++){
                    if (mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == '^' || mapa[i][j] == 'v' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*pacman_PosLIN+3; i <= *pacman_PosLIN+3; i++ )
                for (j=*PosCOL_Pac-1; j <= *PosCOL_Pac +3; j++){
                    if (mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == '^' || mapa[i][j] == 'v' ){
                        mapa[i][j]=' ';
                    }
                }
            aux = 0;
             

             /* verificar se encostou em um fantasma */
            if(mapa[*pacman_PosLIN][*PosCOL_Pac-1] == '@' || mapa[*pacman_PosLIN][*PosCOL_Pac-1] == '&' || mapa[*pacman_PosLIN][*PosCOL_Pac-1] == '%'|| mapa[*pacman_PosLIN][*PosCOL_Pac-1] == '?'|| mapa[*pacman_PosLIN+1][*PosCOL_Pac-1] == '@' || mapa[*pacman_PosLIN+1][*PosCOL_Pac-1] == '&' || mapa[*pacman_PosLIN+1][*PosCOL_Pac-1] == '%' || mapa[*pacman_PosLIN+1][*PosCOL_Pac-1] == '?' || mapa[*pacman_PosLIN+2][*PosCOL_Pac-1] == '@'|| mapa[*pacman_PosLIN+2][*PosCOL_Pac-1] == '&' || mapa[*pacman_PosLIN+2][*PosCOL_Pac-1] == '%' || mapa[*pacman_PosLIN+2][*PosCOL_Pac-1] == '?')
                *vida = 0;

             /* verificar se possui parede */
            if(mapa[*pacman_PosLIN][*PosCOL_Pac-1] == '#' || mapa[*pacman_PosLIN+1][*PosCOL_Pac-1] == '#' || mapa[*pacman_PosLIN+2][*PosCOL_Pac-1] == '#')
                break;
            /* verificar se possui ponto simples */
            if(mapa[*pacman_PosLIN][*PosCOL_Pac-1] == '*' || mapa[*pacman_PosLIN+1][*PosCOL_Pac-1] == '*' || mapa[*pacman_PosLIN+2][*PosCOL_Pac-1] == '*'){
                
                for (i = *pacman_PosLIN; i <= *pacman_PosLIN+2; i++)
                for (j = *PosCOL_Pac-1; j <= *PosCOL_Pac -1; j++ ){
                    if(mapa[i][j] == '*' ){
                        *pontos = *pontos + 1;
                        mapa[i][j]=' ';
                    }     
                }
            }
            /* verificar se possui pontos especiais */
             if(mapa[*pacman_PosLIN][*PosCOL_Pac-1] == '$' || mapa[*pacman_PosLIN+1][*PosCOL_Pac-1] == '$' || mapa[*pacman_PosLIN+2][*PosCOL_Pac-1] == '$'){
                for (i = *pacman_PosLIN; i <= *pacman_PosLIN+2; i++)
                for (j = *PosCOL_Pac-1; j <= *PosCOL_Pac -1; j++ ){
                    if (mapa[i][j] =='$'){
                        *pontos= *pontos +2;
                        *Blinky_Status = FUGIR; /* FUGIR = 1; */
                        *Pinky_Status = FUGIR; /* FUGIR = 1; */
                        *Inky_Status = FUGIR; /* FUGIR = 1; */
                        *Clyde_Status = FUGIR; /* FUGIR = 1; */
                        mapa[i][j] = ' ';
                        mapa[i][j-1] = ' ';
                        if (mapa[i-1][j] == '$'){
                            mapa[i-1][j] = ' ';
                            mapa[i-1][j-1] = ' ';
                        }
                        else if (mapa[i+1][j] == '$'){
                            mapa[i+1][j] = ' ';
                            mapa[i+1][j-1] = ' ';

                        }
                    }
                }
            }
            /* movimento */
            if (mapa[*pacman_PosLIN][*PosCOL_Pac-1] == ' ' && mapa[*pacman_PosLIN+1][*PosCOL_Pac-1] == ' ' && mapa[*pacman_PosLIN+2][*PosCOL_Pac-1] == ' '){
                /* remover os mais atras */
                for (i = *pacman_PosLIN; i <= *pacman_PosLIN+2; i++)
                for (j = *PosCOL_Pac+2; j <= *PosCOL_Pac+2; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar a direita */
                for (i = *pacman_PosLIN; i <= *pacman_PosLIN+2; i++)
                for (j = *PosCOL_Pac-1; j <= *PosCOL_Pac + 1; j++ ){
                    mapa[i][j]='<';
                    aux = 1;
                }
            }
            

            if (aux == 1){
                *PosCOL_Pac= *PosCOL_Pac -1;
                aux = 0;
            }
            break;
    

    case 4: /* Movimento para cima */

        /* limpando restos em arestas */
            for (i=*pacman_PosLIN-1; i <= *pacman_PosLIN-1; i++ )
                for (j=*PosCOL_Pac-1; j <= *PosCOL_Pac + 4; j++){
                    if (mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == '^' || mapa[i][j] == 'v' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*pacman_PosLIN-1; i <= *pacman_PosLIN+4; i++ )
                for (j=*PosCOL_Pac-1; j <= *PosCOL_Pac -1; j++){
                    if (mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == '^' || mapa[i][j] == 'v' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*pacman_PosLIN-1; i <= *pacman_PosLIN+4; i++ )
                for (j=*PosCOL_Pac+3; j <= *PosCOL_Pac +3; j++){
                    if (mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == '^' || mapa[i][j] == 'v' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*pacman_PosLIN+3; i <= *pacman_PosLIN+3; i++ )
                for (j=*PosCOL_Pac-1; j <= *PosCOL_Pac +3; j++){
                    if (mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == '^' || mapa[i][j] == 'v' ){
                        mapa[i][j]=' ';
                    }
                }
            aux = 0;
    
            /* verificar se encostou num fantasma */
            if(mapa[*pacman_PosLIN-1][*PosCOL_Pac] == '@' || mapa[*pacman_PosLIN-1][*PosCOL_Pac] == '&' || mapa[*pacman_PosLIN-1][*PosCOL_Pac] == '%' ||mapa[*pacman_PosLIN-1][*PosCOL_Pac] == '?' || mapa[*pacman_PosLIN-1][*PosCOL_Pac+1] == '@' || mapa[*pacman_PosLIN-1][*PosCOL_Pac+1] == '&' || mapa[*pacman_PosLIN-1][*PosCOL_Pac+1] == '%' || mapa[*pacman_PosLIN-1][*PosCOL_Pac+1] == '?' || mapa[*pacman_PosLIN-1][*PosCOL_Pac+2] == '@'|| mapa[*pacman_PosLIN-1][*PosCOL_Pac+2] == '&' || mapa[*pacman_PosLIN-1][*PosCOL_Pac+2] == '%' || mapa[*pacman_PosLIN-1][*PosCOL_Pac+2] == '?')
                *vida = 0;

             /* verificar se possui parede */
            if(mapa[*pacman_PosLIN-1][*PosCOL_Pac] == '#' || mapa[*pacman_PosLIN-1][*PosCOL_Pac+1] == '#' || mapa[*pacman_PosLIN-1][*PosCOL_Pac+2] == '#')
                break;
            /* verificar se possui ponto simples */
            if(mapa[*pacman_PosLIN-1][*PosCOL_Pac] == '*' || mapa[*pacman_PosLIN-1][*PosCOL_Pac+1] == '*' || mapa[*pacman_PosLIN-1][*PosCOL_Pac+2] == '*'){
                
                for (i = *pacman_PosLIN-1; i <= *pacman_PosLIN-1; i++)
                for (j = *PosCOL_Pac; j <= *PosCOL_Pac + 2; j++ ){
                    if(mapa[i][j] == '*' ){
                        *pontos = *pontos + 1;
                        mapa[i][j]=' ';
                    }                    
                }
            }
            /* verificar se possui pontos especiais */
             if(mapa[*pacman_PosLIN-1][*PosCOL_Pac] == '$' || mapa[*pacman_PosLIN-1][*PosCOL_Pac+1] == '$' || mapa[*pacman_PosLIN-1][*PosCOL_Pac+2] == '$'){
                 
                 for (i = *pacman_PosLIN-1; i <= *pacman_PosLIN-1; i++)
                 for (j = *PosCOL_Pac; j <= *PosCOL_Pac + 2; j++ ){
                    if (mapa[i][j] =='$'){
                        *pontos= *pontos +2;
                        *Blinky_Status = FUGIR; /* FUGIR = 1; */
                        *Pinky_Status = FUGIR; /* FUGIR = 1; */
                        *Inky_Status = FUGIR; /* FUGIR = 1; */
                        *Clyde_Status = FUGIR; /* FUGIR = 1; */
                        mapa[i][j] = ' ';
                        mapa[i-1][j] = ' ';
                        if (mapa[i][j-1] == '$'){
                            mapa[i][j-1] = ' ';
                            mapa[i-1][j-1] = ' ';
                        }
                        else if (mapa[i][j+1] == '$'){
                            mapa[i][j+1] = ' ';
                            mapa[i-1][j+1] = ' ';

                        }
                    }
                }
            }
             /* movimento */
            if (mapa[*pacman_PosLIN-1][*PosCOL_Pac] == ' ' && mapa[*pacman_PosLIN-1][*PosCOL_Pac+1] == ' ' && mapa[*pacman_PosLIN-1][*PosCOL_Pac+2] == ' '){
                /* remover os mais abaixo */
                for (i = *pacman_PosLIN+2; i <= *pacman_PosLIN+2; i++)
                for (j = *PosCOL_Pac; j <= *PosCOL_Pac + 2; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar nos acima */
                for (i = *pacman_PosLIN -1; i <= *pacman_PosLIN+1; i++)
                for (j = *PosCOL_Pac; j <= *PosCOL_Pac + 2; j++ ){
                    mapa[i][j]='^';
                    aux = 1;
                }
            }
           
            

            if (aux == 1){
                *pacman_PosLIN= *pacman_PosLIN - 1;
                aux = 0;
            }
            break;
        
    }

}

void MudarDirecaoPacman(int *pacman_Direcao, int key){
    if(key == KEY_RIGHT)
        *pacman_Direcao = 1; /* DIREITA */
    if(key == KEY_DOWN)
        *pacman_Direcao = 2; /* BAIXO */
    if(key == KEY_LEFT)
        *pacman_Direcao = 3; /* ESQUERDA */
    if(key == KEY_UP)
        *pacman_Direcao = 4; /* CIMA */
}

void MoverBlinky(char **mapa, int *PosL_Blinky, int *PosC_Blinky,int *pacman_PosLIN, int *pacman_PosCOL){
    int aux;
    int i,j;
    if (( *PosL_Blinky > *pacman_PosLIN) || (*pacman_PosLIN < *PosL_Blinky )){
        /* CIMA */
        /* limpando restos em arestas */
            for (i=*PosL_Blinky-1; i <= *PosL_Blinky-1; i++ )
                for (j=*PosC_Blinky-1; j <= *PosC_Blinky + 4; j++){
                    if (mapa[i][j] == '@' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Blinky-1; i <= *PosL_Blinky+4; i++ )
                for (j=*PosC_Blinky-1; j <= *PosC_Blinky -1; j++){
                    if (mapa[i][j] == '@' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Blinky-1; i <= *PosL_Blinky+4; i++ )
                for (j=*PosC_Blinky+3; j <= *PosC_Blinky +3; j++){
                    if (mapa[i][j] == '@' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Blinky+3; i <= *PosL_Blinky+3; i++ )
                for (j=*PosC_Blinky-1; j <= *PosC_Blinky +3; j++){
                    if (mapa[i][j] == '@'  ){
                        mapa[i][j]=' ';
                    }
                }
            aux = 0;

             /* movimento */
            if (mapa[*PosL_Blinky-1][*PosC_Blinky] == ' ' && mapa[*PosL_Blinky-1][*PosC_Blinky+1] == ' ' && mapa[*PosL_Blinky-1][*PosC_Blinky+2] == ' '){
                /* remover os mais abaixo */
                for (i = *PosL_Blinky+2; i <= *PosL_Blinky+2; i++)
                for (j = *PosC_Blinky; j <= *PosC_Blinky + 2; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar nos acima */
                for (i = *PosL_Blinky -1; i <= *PosL_Blinky+1; i++)
                for (j = *PosC_Blinky; j <= *PosC_Blinky + 2; j++ ){
                    mapa[i][j]='@';
                    aux = 1;
                }
            }
           
            if (aux == 1){
                *PosL_Blinky= *PosL_Blinky - 1;
                aux = 0;
            }

    }  else if ((*PosC_Blinky <= *pacman_PosCOL) || (*pacman_PosCOL >= *PosC_Blinky)){
        /* DIREITA */
         /* limpando restos em arestas */
            for (i=*PosL_Blinky-1; i <= *PosL_Blinky-1; i++ )
                for (j=*PosC_Blinky-1; j <= *PosC_Blinky + 4; j++){
                    if (mapa[i][j] == '@' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Blinky-1; i <= *PosL_Blinky+4; i++ )
                for (j=*PosC_Blinky-1; j <= *PosC_Blinky -1; j++){
                    if (mapa[i][j] == '@' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Blinky-1; i <= *PosL_Blinky+4; i++ )
                for (j=*PosC_Blinky+3; j <= *PosC_Blinky +3; j++){
                    if (mapa[i][j] == '@' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Blinky+3; i <= *PosL_Blinky+3; i++ )
                for (j=*PosC_Blinky-1; j <= *PosC_Blinky +3; j++){
                    if (mapa[i][j] == '@'){
                        mapa[i][j]=' ';
                    }
                }
            aux = 0;
             
            /* movimento */
            if (mapa[*PosL_Blinky][*PosC_Blinky+3] == ' ' && mapa[*PosL_Blinky+1][*PosC_Blinky+3] == ' ' && mapa[*PosL_Blinky+2][*PosC_Blinky+3] == ' '){
                /* remover os mais atras */
                for (i = *PosL_Blinky; i <= *PosL_Blinky+2; i++)
                for (j = *PosC_Blinky; j <= *PosC_Blinky; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar a direita */
                for (i = *PosL_Blinky; i <= *PosL_Blinky+2; i++)
                for (j = *PosC_Blinky+1; j <= *PosC_Blinky + 3; j++ ){
                    mapa[i][j]='@';
                    aux = 1;
                }
            }
            
            if (aux == 1){
                *PosC_Blinky= *PosC_Blinky +1;
                aux = 0;
            }
 

    }  else if ( (*PosL_Blinky < *pacman_PosLIN) || ( *pacman_PosLIN > *PosL_Blinky ) ){
        /* BAIXO */
         /* limpando restos em arestas */
            for (i=*PosL_Blinky-1; i <= *PosL_Blinky-1; i++ )
                for (j=*PosC_Blinky-1; j <= *PosC_Blinky + 4; j++){
                    if (mapa[i][j] == '@'){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Blinky-1; i <= *PosL_Blinky+4; i++ )
                for (j=*PosC_Blinky-1; j <= *PosC_Blinky -1; j++){
                    if (mapa[i][j] == '@'){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Blinky-1; i <= *PosL_Blinky+4; i++ )
                for (j=*PosC_Blinky+3; j <= *PosC_Blinky +3; j++){
                    if (mapa[i][j] == '@'){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Blinky+3; i <= *PosL_Blinky+3; i++ )
                for (j=*PosC_Blinky-1; j <= *PosC_Blinky +3; j++){
                    if (mapa[i][j] == '@' ){
                        mapa[i][j]=' ';
                    }
                }

            aux = 0;
            
             /* movimento */
            if (mapa[*PosL_Blinky+3][*PosC_Blinky] == ' ' && mapa[*PosL_Blinky+3][*PosC_Blinky+1] == ' ' && mapa[*PosL_Blinky+3][*PosC_Blinky+2] == ' '){
                /* remover os mais acima */
                for (i = *PosL_Blinky; i <= *PosL_Blinky; i++)
                for (j = *PosC_Blinky; j <= *PosC_Blinky + 2; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar nos abaixo */
                for (i = *PosL_Blinky+1; i <= *PosL_Blinky+3; i++)
                for (j = *PosC_Blinky; j <= *PosC_Blinky + 2; j++ ){
                    mapa[i][j]='@';
                    aux = 1;
                }
            }
            
            if (aux == 1){
                *PosL_Blinky= *PosL_Blinky +1;
                aux = 0;
            }
        
    
    } else {
        /* ESQUERDA */
        /* limpando restos em arestas */
            for (i=*PosL_Blinky-1; i <= *PosL_Blinky-1; i++ )
                for (j=*PosC_Blinky-1; j <= *PosC_Blinky + 3; j++){
                    if (mapa[i][j] == '@' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Blinky-1; i <= *PosL_Blinky+3; i++ )
                for (j=*PosC_Blinky-1; j <= *PosC_Blinky -1; j++){
                    if (mapa[i][j] == '@' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Blinky-1; i <= *PosL_Blinky+3; i++ )
                for (j=*PosC_Blinky+3; j <= *PosC_Blinky +3; j++){
                    if (mapa[i][j] == '@' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Blinky+3; i <= *PosL_Blinky+3; i++ )
                for (j=*PosC_Blinky-1; j <= *PosC_Blinky +3; j++){
                    if (mapa[i][j] == '@' ){
                        mapa[i][j]=' ';
                    }
                }
            aux = 0;
            
            /* movimento */
            if (mapa[*PosL_Blinky][*PosC_Blinky-1] == ' ' && mapa[*PosL_Blinky+1][*PosC_Blinky-1] == ' ' && mapa[*PosL_Blinky+2][*PosC_Blinky-1] == ' '){
                /* remover os mais atras */
                for (i = *PosL_Blinky; i <= *PosL_Blinky+2; i++)
                for (j = *PosC_Blinky+2; j <= *PosC_Blinky+2; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar a direita */
                for (i = *PosL_Blinky; i <= *PosL_Blinky+2; i++)
                for (j = *PosC_Blinky-1; j <= *PosC_Blinky + 1; j++ ){
                    mapa[i][j]='@';
                    aux = 1;
                }
            }
            
            if (aux == 1){
                *PosC_Blinky= *PosC_Blinky -1;
                aux = 0;
            }
    }
    
    

}

void MoverPinky(char **mapa, int *PosL_Pinky, int *PosC_Pinky,int pacman_PosLIN, int pacman_PosCOL, int pacman_Direcao){
    /*  mira seu movimento 5 pontos na frente da posição atual do Pac-Man */
    if (pacman_Direcao == DIREITA ){
        pacman_PosCOL =  pacman_PosCOL + 5;
    } else if (pacman_Direcao == BAIXO){
        pacman_PosLIN = pacman_PosLIN + 5;
    } else if (pacman_Direcao == ESQUERDA){
         pacman_PosCOL =  pacman_PosCOL - 5;
    } else if (pacman_Direcao == CIMA){
        pacman_PosLIN = pacman_PosLIN - 5;
    }
    int aux;
    int i,j;
    if (( *PosL_Pinky > pacman_PosLIN) || (pacman_PosLIN < *PosL_Pinky )){
        /* CIMA */
        /* limpando restos em arestas */
            for (i=*PosL_Pinky-1; i <= *PosL_Pinky-1; i++ )
                for (j=*PosC_Pinky-1; j <= *PosC_Pinky + 4; j++){
                    if (mapa[i][j] == '&' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Pinky-1; i <= *PosL_Pinky+4; i++ )
                for (j=*PosC_Pinky-1; j <= *PosC_Pinky -1; j++){
                    if (mapa[i][j] == '&' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Pinky-1; i <= *PosL_Pinky+4; i++ )
                for (j=*PosC_Pinky+3; j <= *PosC_Pinky +3; j++){
                    if (mapa[i][j] == '&' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Pinky+3; i <= *PosL_Pinky+3; i++ )
                for (j=*PosC_Pinky-1; j <= *PosC_Pinky +3; j++){
                    if (mapa[i][j] == '&' ){
                        mapa[i][j]=' ';
                    }
                }
            aux = 0;

             /* movimento */
            if (mapa[*PosL_Pinky-1][*PosC_Pinky] == ' ' && mapa[*PosL_Pinky-1][*PosC_Pinky+1] == ' ' && mapa[*PosL_Pinky-1][*PosC_Pinky+2] == ' '){
                /* remover os mais abaixo */
                for (i = *PosL_Pinky+2; i <= *PosL_Pinky+2; i++)
                for (j = *PosC_Pinky; j <= *PosC_Pinky + 2; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar nos acima */
                for (i = *PosL_Pinky -1; i <= *PosL_Pinky+1; i++)
                for (j = *PosC_Pinky; j <= *PosC_Pinky + 2; j++ ){
                    mapa[i][j]='&';
                    aux = 1;
                }
            }
           
            if (aux == 1){
                *PosL_Pinky= *PosL_Pinky - 1;
                aux = 0;
            }

    }  else if ((*PosC_Pinky <= pacman_PosCOL) || (pacman_PosCOL >= *PosC_Pinky)){
        /* DIREITA */
         /* limpando restos em arestas */
            for (i=*PosL_Pinky-1; i <= *PosL_Pinky-1; i++ )
                for (j=*PosC_Pinky-1; j <= *PosC_Pinky + 4; j++){
                    if (mapa[i][j] == '&' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Pinky-1; i <= *PosL_Pinky+4; i++ )
                for (j=*PosC_Pinky-1; j <= *PosC_Pinky -1; j++){
                    if (mapa[i][j] == '&' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Pinky-1; i <= *PosL_Pinky+4; i++ )
                for (j=*PosC_Pinky+3; j <= *PosC_Pinky +3; j++){
                    if (mapa[i][j] == '&' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Pinky+3; i <= *PosL_Pinky+3; i++ )
                for (j=*PosC_Pinky-1; j <= *PosC_Pinky +3; j++){
                    if (mapa[i][j] == '&' ){
                        mapa[i][j]=' ';
                    }
                }
            aux = 0;
             
            /* movimento */
            if (mapa[*PosL_Pinky][*PosC_Pinky+3] == ' ' && mapa[*PosL_Pinky+1][*PosC_Pinky+3] == ' ' && mapa[*PosL_Pinky+2][*PosC_Pinky+3] == ' '){
                /* remover os mais atras */
                for (i = *PosL_Pinky; i <= *PosL_Pinky+2; i++)
                for (j = *PosC_Pinky; j <= *PosC_Pinky; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar a direita */
                for (i = *PosL_Pinky; i <= *PosL_Pinky+2; i++)
                for (j = *PosC_Pinky+1; j <= *PosC_Pinky + 3; j++ ){
                    mapa[i][j]='&';
                    aux = 1;
                }
            }
            
            if (aux == 1){
                *PosC_Pinky= *PosC_Pinky +1;
                aux = 0;
            }
 

    }  else if ( (*PosL_Pinky < pacman_PosLIN) || ( pacman_PosLIN > *PosL_Pinky ) ){
        /* BAIXO */
         /* limpando restos em arestas */
            for (i=*PosL_Pinky-1; i <= *PosL_Pinky-1; i++ )
                for (j=*PosC_Pinky-1; j <= *PosC_Pinky + 4; j++){
                    if (mapa[i][j] == '&' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Pinky-1; i <= *PosL_Pinky+4; i++ )
                for (j=*PosC_Pinky-1; j <= *PosC_Pinky -1; j++){
                    if (mapa[i][j] == '&' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Pinky-1; i <= *PosL_Pinky+4; i++ )
                for (j=*PosC_Pinky+3; j <= *PosC_Pinky +3; j++){
                    if (mapa[i][j] == '&' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Pinky+3; i <= *PosL_Pinky+3; i++ )
                for (j=*PosC_Pinky-1; j <= *PosC_Pinky +3; j++){
                    if (mapa[i][j] == '&' ){
                        mapa[i][j]=' ';
                    }
                }

            aux = 0;
            
             /* movimento */
            if (mapa[*PosL_Pinky+3][*PosC_Pinky] == ' ' && mapa[*PosL_Pinky+3][*PosC_Pinky+1] == ' ' && mapa[*PosL_Pinky+3][*PosC_Pinky+2] == ' '){
                /* remover os mais acima */
                for (i = *PosL_Pinky; i <= *PosL_Pinky; i++)
                for (j = *PosC_Pinky; j <= *PosC_Pinky + 2; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar nos abaixo */
                for (i = *PosL_Pinky+1; i <= *PosL_Pinky+3; i++)
                for (j = *PosC_Pinky; j <= *PosC_Pinky + 2; j++ ){
                    mapa[i][j]= '&' ;
                    aux = 1;
                }
            }
            
            if (aux == 1){
                *PosL_Pinky= *PosL_Pinky +1;
                aux = 0;
            }
        
    
    } else {
        /* ESQUERDA */
        /* limpando restos em arestas */
            for (i=*PosL_Pinky-1; i <= *PosL_Pinky-1; i++ )
                for (j=*PosC_Pinky-1; j <= *PosC_Pinky + 3; j++){
                    if (mapa[i][j] == '&' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Pinky-1; i <= *PosL_Pinky+3; i++ )
                for (j=*PosC_Pinky-1; j <= *PosC_Pinky -1; j++){
                    if (mapa[i][j] == '&'){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Pinky-1; i <= *PosL_Pinky+3; i++ )
                for (j=*PosC_Pinky+3; j <= *PosC_Pinky +3; j++){
                    if (mapa[i][j] == '&'){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Pinky+3; i <= *PosL_Pinky+3; i++ )
                for (j=*PosC_Pinky-1; j <= *PosC_Pinky +3; j++){
                    if (mapa[i][j] == '&'){
                        mapa[i][j]=' ';
                    }
                }
            aux = 0;
            
            /* movimento */
            if (mapa[*PosL_Pinky][*PosC_Pinky-1] == ' ' && mapa[*PosL_Pinky+1][*PosC_Pinky-1] == ' ' && mapa[*PosL_Pinky+2][*PosC_Pinky-1] == ' '){
                /* remover os mais atras */
                for (i = *PosL_Pinky; i <= *PosL_Pinky+2; i++)
                for (j = *PosC_Pinky+2; j <= *PosC_Pinky+2; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar a direita */
                for (i = *PosL_Pinky; i <= *PosL_Pinky+2; i++)
                for (j = *PosC_Pinky-1; j <= *PosC_Pinky + 1; j++ ){
                    mapa[i][j]= '&' ;
                    aux = 1;
                }
            }
            
            if (aux == 1){
                *PosC_Pinky= *PosC_Pinky -1;
                aux = 0;
            }
    }
    

}

void MoverInky(char **mapa, int PosL_Blinky, int PosC_Blinky,int pacman_PosLIN, int pacman_PosCOL, int *PosL_Inky,  int *PosC_Inky){
    int LINmedia, COLmedia;
    LINmedia = (PosL_Blinky + pacman_PosLIN) / 2 ;
    COLmedia = (PosC_Blinky + pacman_PosCOL ) / 2 ;

    int aux;
    int i,j;
    if (( *PosL_Inky > LINmedia) || (LINmedia < *PosL_Inky )){
        /* CIMA */
        /* limpando restos em arestas */
            for (i=*PosL_Inky-1; i <= *PosL_Inky-1; i++ )
                for (j=*PosC_Inky-1; j <= *PosC_Inky + 4; j++){
                    if (mapa[i][j] == '%' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Inky-1; i <= *PosL_Inky+4; i++ )
                for (j=*PosC_Inky-1; j <= *PosC_Inky -1; j++){
                    if (mapa[i][j] == '%' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Inky-1; i <= *PosL_Inky+4; i++ )
                for (j=*PosC_Inky+3; j <= *PosC_Inky +3; j++){
                    if (mapa[i][j] == '%' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Inky+3; i <= *PosL_Inky+3; i++ )
                for (j=*PosC_Inky-1; j <= *PosC_Inky +3; j++){
                    if (mapa[i][j] == '%' ){
                        mapa[i][j]=' ';
                    }
                }
            aux = 0;

             /* movimento */
            if (mapa[*PosL_Inky-1][*PosC_Inky] == ' ' && mapa[*PosL_Inky-1][*PosC_Inky+1] == ' ' && mapa[*PosL_Inky-1][*PosC_Inky+2] == ' '){
                /* remover os mais abaixo */
                for (i = *PosL_Inky+2; i <= *PosL_Inky+2; i++)
                for (j = *PosC_Inky; j <= *PosC_Inky + 2; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar nos acima */
                for (i = *PosL_Inky -1; i <= *PosL_Inky+1; i++)
                for (j = *PosC_Inky; j <= *PosC_Inky + 2; j++ ){
                    mapa[i][j]= '%' ;
                    aux = 1;
                }
            }
           
            if (aux == 1){
                *PosL_Inky= *PosL_Inky - 1;
                aux = 0;
            }

    }  else if ((*PosC_Inky <= COLmedia) || (COLmedia >= *PosC_Inky)){
        /* DIREITA */
         /* limpando restos em arestas */
            for (i=*PosL_Inky-1; i <= *PosL_Inky-1; i++ )
                for (j=*PosC_Inky-1; j <= *PosC_Inky + 4; j++){
                    if (mapa[i][j] == '%' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Inky-1; i <= *PosL_Inky+4; i++ )
                for (j=*PosC_Inky-1; j <= *PosC_Inky -1; j++){
                    if (mapa[i][j] == '%' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Inky-1; i <= *PosL_Inky+4; i++ )
                for (j=*PosC_Inky+3; j <= *PosC_Inky +3; j++){
                    if (mapa[i][j] == '%' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Inky+3; i <= *PosL_Inky+3; i++ )
                for (j=*PosC_Inky-1; j <= *PosC_Inky +3; j++){
                    if (mapa[i][j] == '&' ){
                        mapa[i][j]=' ';
                    }
                }
            aux = 0;
             
            /* movimento */
            if (mapa[*PosL_Inky][*PosC_Inky+3] == ' ' && mapa[*PosL_Inky+1][*PosC_Inky+3] == ' ' && mapa[*PosL_Inky+2][*PosC_Inky+3] == ' '){
                /* remover os mais atras */
                for (i = *PosL_Inky; i <= *PosL_Inky+2; i++)
                for (j = *PosC_Inky; j <= *PosC_Inky; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar a direita */
                for (i = *PosL_Inky; i <= *PosL_Inky+2; i++)
                for (j = *PosC_Inky+1; j <= *PosC_Inky + 3; j++ ){
                    mapa[i][j]= '%' ;
                    aux = 1;
                }
            }
            
            if (aux == 1){
                *PosC_Inky= *PosC_Inky +1;
                aux = 0;
            }
 

    }  else if ( (*PosL_Inky < LINmedia) || ( LINmedia > *PosL_Inky ) ){
        /* BAIXO */
         /* limpando restos em arestas */
            for (i=*PosL_Inky-1; i <= *PosL_Inky-1; i++ )
                for (j=*PosC_Inky-1; j <= *PosC_Inky + 4; j++){
                    if (mapa[i][j] == '%' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Inky-1; i <= *PosL_Inky+4; i++ )
                for (j=*PosC_Inky-1; j <= *PosC_Inky -1; j++){
                    if (mapa[i][j] == '%' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Inky-1; i <= *PosL_Inky+4; i++ )
                for (j=*PosC_Inky+3; j <= *PosC_Inky +3; j++){
                    if (mapa[i][j] == '%' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Inky+3; i <= *PosL_Inky+3; i++ )
                for (j=*PosC_Inky-1; j <= *PosC_Inky +3; j++){
                    if (mapa[i][j] == '%' ){
                        mapa[i][j]=' ';
                    }
                }

            aux = 0;
            
             /* movimento */
            if (mapa[*PosL_Inky+3][*PosC_Inky] == ' ' && mapa[*PosL_Inky+3][*PosC_Inky+1] == ' ' && mapa[*PosL_Inky+3][*PosC_Inky+2] == ' '){
                /* remover os mais acima */
                for (i = *PosL_Inky; i <= *PosL_Inky; i++)
                for (j = *PosC_Inky; j <= *PosC_Inky + 2; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar nos abaixo */
                for (i = *PosL_Inky+1; i <= *PosL_Inky+3; i++)
                for (j = *PosC_Inky; j <= *PosC_Inky + 2; j++ ){
                    mapa[i][j]= '%' ;
                    aux = 1;
                }
            }
            
            if (aux == 1){
                *PosL_Inky= *PosL_Inky +1;
                aux = 0;
            }
        
    
    } else {
        /* ESQUERDA */
        /* limpando restos em arestas */
            for (i=*PosL_Inky-1; i <= *PosL_Inky-1; i++ )
                for (j=*PosC_Inky-1; j <= *PosC_Inky + 3; j++){
                    if (mapa[i][j] == '%' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Inky-1; i <= *PosL_Inky+3; i++ )
                for (j=*PosC_Inky-1; j <= *PosC_Inky -1; j++){
                    if (mapa[i][j] == '%' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Inky-1; i <= *PosL_Inky+3; i++ )
                for (j=*PosC_Inky+3; j <= *PosC_Inky +3; j++){
                    if (mapa[i][j] == '%' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Inky+3; i <= *PosL_Inky+3; i++ )
                for (j=*PosC_Inky-1; j <= *PosC_Inky +3; j++){
                    if (mapa[i][j] == '%' ){
                        mapa[i][j]=' ';
                    }
                }
            aux = 0;
            
            /* movimento */
            if (mapa[*PosL_Inky][*PosC_Inky-1] == ' ' && mapa[*PosL_Inky+1][*PosC_Inky-1] == ' ' && mapa[*PosL_Inky+2][*PosC_Inky-1] == ' '){
                /* remover os mais atras */
                for (i = *PosL_Inky; i <= *PosL_Inky+2; i++)
                for (j = *PosC_Inky+2; j <= *PosC_Inky+2; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar a direita */
                for (i = *PosL_Inky; i <= *PosL_Inky+2; i++)
                for (j = *PosC_Inky-1; j <= *PosC_Inky + 1; j++ ){
                    mapa[i][j]= '%' ;
                    aux = 1;
                }
            }
            
            if (aux == 1){
                *PosC_Inky= *PosC_Inky -1;
                aux = 0;
            }
    }
}   

void MoverClyde(char **mapa, int *PosL_Clyde, int *PosC_Clyde,int *pacman_PosLIN, int *pacman_PosCOL){
    int randon;
    int aux, i, j;
    if(  (*PosL_Clyde - *pacman_PosLIN < 15) && (*PosL_Clyde - *pacman_PosLIN > -15) && (*PosC_Clyde - *pacman_PosCOL < 15) && (*PosC_Clyde - *pacman_PosCOL > -15) ){
        
        if (( *PosL_Clyde > *pacman_PosLIN) || (*pacman_PosLIN < *PosL_Clyde )){
        /* CIMA */
        /* limpando restos em arestas */
            for (i=*PosL_Clyde-1; i <= *PosL_Clyde-1; i++ )
                for (j=*PosC_Clyde-1; j <= *PosC_Clyde + 4; j++){
                    if (mapa[i][j] == '?' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Clyde-1; i <= *PosL_Clyde+4; i++ )
                for (j=*PosC_Clyde-1; j <= *PosC_Clyde -1; j++){
                    if (mapa[i][j] == '?' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Clyde-1; i <= *PosL_Clyde+4; i++ )
                for (j=*PosC_Clyde+3; j <= *PosC_Clyde +3; j++){
                    if (mapa[i][j] == '?'  ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Clyde+3; i <= *PosL_Clyde+3; i++ )
                for (j=*PosC_Clyde-1; j <= *PosC_Clyde +3; j++){
                    if (mapa[i][j] == '?' ){
                        mapa[i][j]=' ';
                    }
                }
            aux = 0;

             /* movimento */
            if (mapa[*PosL_Clyde-1][*PosC_Clyde] == ' ' && mapa[*PosL_Clyde-1][*PosC_Clyde+1] == ' ' && mapa[*PosL_Clyde-1][*PosC_Clyde+2] == ' '){
                /* remover os mais abaixo */
                for (i = *PosL_Clyde+2; i <= *PosL_Clyde+2; i++)
                for (j = *PosC_Clyde; j <= *PosC_Clyde + 2; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar nos acima */
                for (i = *PosL_Clyde -1; i <= *PosL_Clyde+1; i++)
                for (j = *PosC_Clyde; j <= *PosC_Clyde + 2; j++ ){
                    mapa[i][j]= '?' ;
                    aux = 1;
                }
            }
           
            if (aux == 1){
                *PosL_Clyde= *PosL_Clyde - 1;
                aux = 0;
            }

        }  else if ((*PosC_Clyde <= *pacman_PosCOL) || (*pacman_PosCOL >= *PosC_Clyde)){
        /* DIREITA */
         /* limpando restos em arestas */
            for (i=*PosL_Clyde-1; i <= *PosL_Clyde-1; i++ )
                for (j=*PosC_Clyde-1; j <= *PosC_Clyde + 4; j++){
                    if (mapa[i][j] == '?' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Clyde-1; i <= *PosL_Clyde+4; i++ )
                for (j=*PosC_Clyde-1; j <= *PosC_Clyde -1; j++){
                    if (mapa[i][j] == '?' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Clyde-1; i <= *PosL_Clyde+4; i++ )
                for (j=*PosC_Clyde+3; j <= *PosC_Clyde +3; j++){
                    if (mapa[i][j] == '?' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Clyde+3; i <= *PosL_Clyde+3; i++ )
                for (j=*PosC_Clyde-1; j <= *PosC_Clyde +3; j++){
                    if (mapa[i][j] == '?' ){
                        mapa[i][j]=' ';
                    }
                }
            aux = 0;
             
            /* movimento */
            if (mapa[*PosL_Clyde][*PosC_Clyde+3] == ' ' && mapa[*PosL_Clyde+1][*PosC_Clyde+3] == ' ' && mapa[*PosL_Clyde+2][*PosC_Clyde+3] == ' '){
                /* remover os mais atras */
                for (i = *PosL_Clyde; i <= *PosL_Clyde+2; i++)
                for (j = *PosC_Clyde; j <= *PosC_Clyde; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar a direita */
                for (i = *PosL_Clyde; i <= *PosL_Clyde+2; i++)
                for (j = *PosC_Clyde+1; j <= *PosC_Clyde + 3; j++ ){
                    mapa[i][j]= '?' ;
                    aux = 1;
                }
            }
            
            if (aux == 1){
                *PosC_Clyde= *PosC_Clyde +1;
                aux = 0;
            }
 

        }  else if ( (*PosL_Clyde < *pacman_PosLIN) || ( *pacman_PosLIN > *PosL_Clyde ) ){
        /* BAIXO */
         /* limpando restos em arestas */
            for (i=*PosL_Clyde-1; i <= *PosL_Clyde-1; i++ )
                for (j=*PosC_Clyde-1; j <= *PosC_Clyde + 4; j++){
                    if (mapa[i][j] == '?' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Clyde-1; i <= *PosL_Clyde+4; i++ )
                for (j=*PosC_Clyde-1; j <= *PosC_Clyde -1; j++){
                    if (mapa[i][j] == '?' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Clyde-1; i <= *PosL_Clyde+4; i++ )
                for (j=*PosC_Clyde+3; j <= *PosC_Clyde +3; j++){
                    if (mapa[i][j] == '?' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Clyde+3; i <= *PosL_Clyde+3; i++ )
                for (j=*PosC_Clyde-1; j <= *PosC_Clyde +3; j++){
                    if (mapa[i][j] == '?' ){
                        mapa[i][j]=' ';
                    }
                }

            aux = 0;
            
             /* movimento */
            if (mapa[*PosL_Clyde+3][*PosC_Clyde] == ' ' && mapa[*PosL_Clyde+3][*PosC_Clyde+1] == ' ' && mapa[*PosL_Clyde+3][*PosC_Clyde+2] == ' '){
                /* remover os mais acima */
                for (i = *PosL_Clyde; i <= *PosL_Clyde; i++)
                for (j = *PosC_Clyde; j <= *PosC_Clyde + 2; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar nos abaixo */
                for (i = *PosL_Clyde+1; i <= *PosL_Clyde+3; i++)
                for (j = *PosC_Clyde; j <= *PosC_Clyde + 2; j++ ){
                    mapa[i][j]= '?' ;
                    aux = 1;
                }
            }
            
            if (aux == 1){
                *PosL_Clyde= *PosL_Clyde +1;
                aux = 0;
            }
        
    
        } else {
        /* ESQUERDA */
        /* limpando restos em arestas */
            for (i=*PosL_Clyde-1; i <= *PosL_Clyde-1; i++ )
                for (j=*PosC_Clyde-1; j <= *PosC_Clyde + 3; j++){
                    if (mapa[i][j] == '?' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Clyde-1; i <= *PosL_Clyde+3; i++ )
                for (j=*PosC_Clyde-1; j <= *PosC_Clyde -1; j++){
                    if (mapa[i][j] == '?' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Clyde-1; i <= *PosL_Clyde+3; i++ )
                for (j=*PosC_Clyde+3; j <= *PosC_Clyde +3; j++){
                    if (mapa[i][j] == '?' ){
                        mapa[i][j]=' ';
                    }
                }
            for (i=*PosL_Clyde+3; i <= *PosL_Clyde+3; i++ )
                for (j=*PosC_Clyde-1; j <= *PosC_Clyde +3; j++){
                    if (mapa[i][j] == '?' ){
                        mapa[i][j]=' ';
                    }
                }
            aux = 0;
            
            /* movimento */
            if (mapa[*PosL_Clyde][*PosC_Clyde-1] == ' ' && mapa[*PosL_Clyde+1][*PosC_Clyde-1] == ' ' && mapa[*PosL_Clyde+2][*PosC_Clyde-1] == ' '){
                /* remover os mais atras */
                for (i = *PosL_Clyde; i <= *PosL_Clyde+2; i++)
                for (j = *PosC_Clyde+2; j <= *PosC_Clyde+2; j++ ){
                    mapa[i][j]=' ';
                }
                /*adicionar a direita */
                for (i = *PosL_Clyde; i <= *PosL_Clyde+2; i++)
                for (j = *PosC_Clyde-1; j <= *PosC_Clyde + 1; j++ ){
                    mapa[i][j]= '?' ;
                    aux = 1;
                }
            }
            
            if (aux == 1){
                *PosC_Clyde= *PosC_Clyde -1;
                aux = 0;
            }
        }
    
    } else {
        
        randon = rand () % 4;
        /*
         DIREITA = 1
         BAIXO  = 2
         ESQUERDA = 3
         CIMA = 4
         */
        switch(randon){
            case DIREITA:
                /* limpando restos em arestas */
                for (i=*PosL_Clyde-1; i <= *PosL_Clyde-1; i++ )
                    for (j=*PosC_Clyde-1; j <= *PosC_Clyde + 4; j++){
                        if (mapa[i][j] == '?' ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Clyde-1; i <= *PosL_Clyde+4; i++ )
                    for (j=*PosC_Clyde-1; j <= *PosC_Clyde -1; j++){
                        if (mapa[i][j] == '?' ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Clyde-1; i <= *PosL_Clyde+4; i++ )
                    for (j=*PosC_Clyde+3; j <= *PosC_Clyde +3; j++){
                        if (mapa[i][j] == '?' ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Clyde+3; i <= *PosL_Clyde+3; i++ )
                    for (j=*PosC_Clyde-1; j <= *PosC_Clyde +3; j++){
                        if (mapa[i][j] == '?' ){
                            mapa[i][j]=' ';
                        }
                    }
                aux = 0;
                
                /* movimento */
                if (mapa[*PosL_Clyde][*PosC_Clyde+3] == ' ' && mapa[*PosL_Clyde+1][*PosC_Clyde+3] == ' ' && mapa[*PosL_Clyde+2][*PosC_Clyde+3] == ' '){
                    /* remover os mais atras */
                    for (i = *PosL_Clyde; i <= *PosL_Clyde+2; i++)
                    for (j = *PosC_Clyde; j <= *PosC_Clyde; j++ ){
                        mapa[i][j]=' ';
                    }
                    /*adicionar a direita */
                    for (i = *PosL_Clyde; i <= *PosL_Clyde+2; i++)
                    for (j = *PosC_Clyde+1; j <= *PosC_Clyde + 3; j++ ){
                        mapa[i][j]= '?' ;
                        aux = 1;
                    }
                }
                
                if (aux == 1){
                    *PosC_Clyde= *PosC_Clyde +1;
                    aux = 0;
                }
                break;

            
            case ESQUERDA: 
                /* limpando restos em arestas */
                for (i=*PosL_Clyde-1; i <= *PosL_Clyde-1; i++ )
                    for (j=*PosC_Clyde-1; j <= *PosC_Clyde + 3; j++){
                        if (mapa[i][j] == '?' ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Clyde-1; i <= *PosL_Clyde+3; i++ )
                    for (j=*PosC_Clyde-1; j <= *PosC_Clyde -1; j++){
                        if (mapa[i][j] == '?' ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Clyde-1; i <= *PosL_Clyde+3; i++ )
                    for (j=*PosC_Clyde+3; j <= *PosC_Clyde +3; j++){
                        if (mapa[i][j] == '?' ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Clyde+3; i <= *PosL_Clyde+3; i++ )
                    for (j=*PosC_Clyde-1; j <= *PosC_Clyde +3; j++){
                        if (mapa[i][j] == '?' ){
                            mapa[i][j]=' ';
                        }
                    }
                aux = 0;
                
                /* movimento */
                if (mapa[*PosL_Clyde][*PosC_Clyde-1] == ' ' && mapa[*PosL_Clyde+1][*PosC_Clyde-1] == ' ' && mapa[*PosL_Clyde+2][*PosC_Clyde-1] == ' '){
                    /* remover os mais atras */
                    for (i = *PosL_Clyde; i <= *PosL_Clyde+2; i++)
                    for (j = *PosC_Clyde+2; j <= *PosC_Clyde+2; j++ ){
                        mapa[i][j]=' ';
                    }
                    /*adicionar a direita */
                    for (i = *PosL_Clyde; i <= *PosL_Clyde+2; i++)
                    for (j = *PosC_Clyde-1; j <= *PosC_Clyde + 1; j++ ){
                        mapa[i][j]= '?' ;
                        aux = 1;
                    }
                }
                
                if (aux == 1){
                    *PosC_Clyde= *PosC_Clyde -1;
                    aux = 0;
                }
                break;

            
            case BAIXO:
                /* limpando restos em arestas */
                for (i=*PosL_Clyde-1; i <= *PosL_Clyde-1; i++ )
                    for (j=*PosC_Clyde-1; j <= *PosC_Clyde + 4; j++){
                        if (mapa[i][j] == '?' ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Clyde-1; i <= *PosL_Clyde+4; i++ )
                    for (j=*PosC_Clyde-1; j <= *PosC_Clyde -1; j++){
                        if (mapa[i][j] == '?' ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Clyde-1; i <= *PosL_Clyde+4; i++ )
                    for (j=*PosC_Clyde+3; j <= *PosC_Clyde +3; j++){
                        if (mapa[i][j] == '?' ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Clyde+3; i <= *PosL_Clyde+3; i++ )
                    for (j=*PosC_Clyde-1; j <= *PosC_Clyde +3; j++){
                        if (mapa[i][j] == '?' ){
                            mapa[i][j]=' ';
                        }
                    }

                aux = 0;
                
                /* movimento */
                if (mapa[*PosL_Clyde+3][*PosC_Clyde] == ' ' && mapa[*PosL_Clyde+3][*PosC_Clyde+1] == ' ' && mapa[*PosL_Clyde+3][*PosC_Clyde+2] == ' '){
                    /* remover os mais acima */
                    for (i = *PosL_Clyde; i <= *PosL_Clyde; i++)
                    for (j = *PosC_Clyde; j <= *PosC_Clyde + 2; j++ ){
                        mapa[i][j]=' ';
                    }
                    /*adicionar nos abaixo */
                    for (i = *PosL_Clyde+1; i <= *PosL_Clyde+3; i++)
                    for (j = *PosC_Clyde; j <= *PosC_Clyde + 2; j++ ){
                        mapa[i][j]= '?' ;
                        aux = 1;
                    }
                }
                
                if (aux == 1){
                    *PosL_Clyde= *PosL_Clyde +1;
                    aux = 0;
                }
                break;


            case CIMA:
                /* limpando restos em arestas */
                for (i=*PosL_Clyde-1; i <= *PosL_Clyde-1; i++ )
                    for (j=*PosC_Clyde-1; j <= *PosC_Clyde + 4; j++){
                        if (mapa[i][j] == '?' ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Clyde-1; i <= *PosL_Clyde+4; i++ )
                    for (j=*PosC_Clyde-1; j <= *PosC_Clyde -1; j++){
                        if (mapa[i][j] == '?' ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Clyde-1; i <= *PosL_Clyde+4; i++ )
                    for (j=*PosC_Clyde+3; j <= *PosC_Clyde +3; j++){
                        if (mapa[i][j] == '?'  ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Clyde+3; i <= *PosL_Clyde+3; i++ )
                    for (j=*PosC_Clyde-1; j <= *PosC_Clyde +3; j++){
                        if (mapa[i][j] == '?' ){
                            mapa[i][j]=' ';
                        }
                    }
                aux = 0;

                /* movimento */
                if (mapa[*PosL_Clyde-1][*PosC_Clyde] == ' ' && mapa[*PosL_Clyde-1][*PosC_Clyde+1] == ' ' && mapa[*PosL_Clyde-1][*PosC_Clyde+2] == ' '){
                    /* remover os mais abaixo */
                    for (i = *PosL_Clyde+2; i <= *PosL_Clyde+2; i++)
                    for (j = *PosC_Clyde; j <= *PosC_Clyde + 2; j++ ){
                        mapa[i][j]=' ';
                    }
                    /*adicionar nos acima */
                    for (i = *PosL_Clyde -1; i <= *PosL_Clyde+1; i++)
                    for (j = *PosC_Clyde; j <= *PosC_Clyde + 2; j++ ){
                        mapa[i][j]= '?' ;
                        aux = 1;
                    }
                }
    
                if (aux == 1){
                    *PosL_Clyde= *PosL_Clyde - 1;
                    aux = 0;
                }
                break;
            
        } /* else */   

    }
}

void Fugir(char **mapa, int *PosL_Fantasma, int *PosC_Fantasma, int *Fantasma_Status, char padrao){
    int randon, i, j, aux;
    randon = rand () % 4;
    /*
    DIREITA = 1
    BAIXO  = 2
    ESQUERDA = 3
    CIMA = 4
    */

   switch(randon){
            case DIREITA:
                /* limpando restos em arestas */
                for (i=*PosL_Fantasma-1; i <= *PosL_Fantasma-1; i++ )
                    for (j=*PosC_Fantasma-1; j <= *PosC_Fantasma + 4; j++){
                        if (mapa[i][j] == padrao ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Fantasma-1; i <= *PosL_Fantasma+4; i++ )
                    for (j=*PosC_Fantasma-1; j <= *PosC_Fantasma -1; j++){
                        if (mapa[i][j] == padrao ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Fantasma-1; i <= *PosL_Fantasma+4; i++ )
                    for (j=*PosC_Fantasma+3; j <= *PosC_Fantasma +3; j++){
                        if (mapa[i][j] == padrao ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Fantasma+3; i <= *PosL_Fantasma+3; i++ )
                    for (j=*PosC_Fantasma-1; j <= *PosC_Fantasma +3; j++){
                        if (mapa[i][j] == padrao ){
                            mapa[i][j]=' ';
                        }
                    }
                aux = 0;
                
                /* movimento */
                if (mapa[*PosL_Fantasma][*PosC_Fantasma+3] == ' ' && mapa[*PosL_Fantasma+1][*PosC_Fantasma+3] == ' ' && mapa[*PosL_Fantasma+2][*PosC_Fantasma+3] == ' '){
                    /* remover os mais atras */
                    for (i = *PosL_Fantasma; i <= *PosL_Fantasma+2; i++)
                    for (j = *PosC_Fantasma; j <= *PosC_Fantasma; j++ ){
                        mapa[i][j]=' ';
                    }
                    /*adicionar a direita */
                    for (i = *PosL_Fantasma; i <= *PosL_Fantasma+2; i++)
                    for (j = *PosC_Fantasma+1; j <= *PosC_Fantasma + 3; j++ ){
                        mapa[i][j]= padrao ;
                        aux = 1;
                    }
                }
                
                if (aux == 1){
                    *PosC_Fantasma= *PosC_Fantasma +1;
                    aux = 0;
                }
                *Fantasma_Status = PERSEGUIR;
                break;

            
            case ESQUERDA: 
                /* limpando restos em arestas */
                for (i=*PosL_Fantasma-1; i <= *PosL_Fantasma-1; i++ )
                    for (j=*PosC_Fantasma-1; j <= *PosC_Fantasma + 3; j++){
                        if (mapa[i][j] == padrao ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Fantasma-1; i <= *PosL_Fantasma+3; i++ )
                    for (j=*PosC_Fantasma-1; j <= *PosC_Fantasma -1; j++){
                        if (mapa[i][j] == padrao ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Fantasma-1; i <= *PosL_Fantasma+3; i++ )
                    for (j=*PosC_Fantasma+3; j <= *PosC_Fantasma +3; j++){
                        if (mapa[i][j] == padrao ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Fantasma+3; i <= *PosL_Fantasma+3; i++ )
                    for (j=*PosC_Fantasma-1; j <= *PosC_Fantasma +3; j++){
                        if (mapa[i][j] == padrao ){
                            mapa[i][j]=' ';
                        }
                    }
                aux = 0;
                
                /* movimento */
                if (mapa[*PosL_Fantasma][*PosC_Fantasma-1] == ' ' && mapa[*PosL_Fantasma+1][*PosC_Fantasma-1] == ' ' && mapa[*PosL_Fantasma+2][*PosC_Fantasma-1] == ' '){
                    /* remover os mais atras */
                    for (i = *PosL_Fantasma; i <= *PosL_Fantasma+2; i++)
                    for (j = *PosC_Fantasma+2; j <= *PosC_Fantasma+2; j++ ){
                        mapa[i][j]=' ';
                    }
                    /*adicionar a direita */
                    for (i = *PosL_Fantasma; i <= *PosL_Fantasma+2; i++)
                    for (j = *PosC_Fantasma-1; j <= *PosC_Fantasma + 1; j++ ){
                        mapa[i][j]= padrao ;
                        aux = 1;
                    }
                }
                
                if (aux == 1){
                    *PosC_Fantasma= *PosC_Fantasma -1;
                    aux = 0;
                }
                *Fantasma_Status = PERSEGUIR;
                break;

            
            case BAIXO:
                /* limpando restos em arestas */
                for (i=*PosL_Fantasma-1; i <= *PosL_Fantasma-1; i++ )
                    for (j=*PosC_Fantasma-1; j <= *PosC_Fantasma + 4; j++){
                        if (mapa[i][j] == padrao ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Fantasma-1; i <= *PosL_Fantasma+4; i++ )
                    for (j=*PosC_Fantasma-1; j <= *PosC_Fantasma -1; j++){
                        if (mapa[i][j] == padrao ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Fantasma-1; i <= *PosL_Fantasma+4; i++ )
                    for (j=*PosC_Fantasma+3; j <= *PosC_Fantasma +3; j++){
                        if (mapa[i][j] == padrao ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Fantasma+3; i <= *PosL_Fantasma+3; i++ )
                    for (j=*PosC_Fantasma-1; j <= *PosC_Fantasma +3; j++){
                        if (mapa[i][j] == padrao ){
                            mapa[i][j]=' ';
                        }
                    }

                aux = 0;
                
                /* movimento */
                if (mapa[*PosL_Fantasma+3][*PosC_Fantasma] == ' ' && mapa[*PosL_Fantasma+3][*PosC_Fantasma+1] == ' ' && mapa[*PosL_Fantasma+3][*PosC_Fantasma+2] == ' '){
                    /* remover os mais acima */
                    for (i = *PosL_Fantasma; i <= *PosL_Fantasma; i++)
                    for (j = *PosC_Fantasma; j <= *PosC_Fantasma + 2; j++ ){
                        mapa[i][j]=' ';
                    }
                    /*adicionar nos abaixo */
                    for (i = *PosL_Fantasma+1; i <= *PosL_Fantasma+3; i++)
                    for (j = *PosC_Fantasma; j <= *PosC_Fantasma + 2; j++ ){
                        mapa[i][j]= padrao ;
                        aux = 1;
                    }
                }
                
                if (aux == 1){
                    *PosL_Fantasma= *PosL_Fantasma +1;
                    aux = 0;
                }
                *Fantasma_Status = PERSEGUIR;
                break;


            case CIMA:
                /* limpando restos em arestas */
                for (i=*PosL_Fantasma-1; i <= *PosL_Fantasma-1; i++ )
                    for (j=*PosC_Fantasma-1; j <= *PosC_Fantasma + 4; j++){
                        if (mapa[i][j] == padrao ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Fantasma-1; i <= *PosL_Fantasma+4; i++ )
                    for (j=*PosC_Fantasma-1; j <= *PosC_Fantasma -1; j++){
                        if (mapa[i][j] == padrao ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Fantasma-1; i <= *PosL_Fantasma+4; i++ )
                    for (j=*PosC_Fantasma+3; j <= *PosC_Fantasma +3; j++){
                        if (mapa[i][j] == padrao  ){
                            mapa[i][j]=' ';
                        }
                    }
                for (i=*PosL_Fantasma+3; i <= *PosL_Fantasma+3; i++ )
                    for (j=*PosC_Fantasma-1; j <= *PosC_Fantasma +3; j++){
                        if (mapa[i][j] == padrao ){
                            mapa[i][j]=' ';
                        }
                    }
                aux = 0;

                /* movimento */
                if (mapa[*PosL_Fantasma-1][*PosC_Fantasma] == ' ' && mapa[*PosL_Fantasma-1][*PosC_Fantasma+1] == ' ' && mapa[*PosL_Fantasma-1][*PosC_Fantasma+2] == ' '){
                    /* remover os mais abaixo */
                    for (i = *PosL_Fantasma+2; i <= *PosL_Fantasma+2; i++)
                    for (j = *PosC_Fantasma; j <= *PosC_Fantasma + 2; j++ ){
                        mapa[i][j]=' ';
                    }
                    /*adicionar nos acima */
                    for (i = *PosL_Fantasma -1; i <= *PosL_Fantasma+1; i++)
                    for (j = *PosC_Fantasma; j <= *PosC_Fantasma + 2; j++ ){
                        mapa[i][j]= padrao ;
                        aux = 1;
                    }
                }
    
                if (aux == 1){
                    *PosL_Fantasma= *PosL_Fantasma - 1;
                    aux = 0;
                }
                *Fantasma_Status = PERSEGUIR;
                break;
            
        }            
}